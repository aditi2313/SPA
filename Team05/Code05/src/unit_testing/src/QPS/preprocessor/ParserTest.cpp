#include <exception>
#include <catch.hpp>

#include "QPS/preprocessor/SelectClParser.h"
#include "QPS/models/PQL.h"

using namespace qps; // NOLINT

// Helper method for testing
QueryPtr BuildQuery(
    std::vector<std::pair<SynonymName, EntityName>> synonyms,
    std::vector<std::string> selected_synonyms
) {
  QueryPtr query = std::make_unique<Query>();
  for (auto [syn, entity] : synonyms) {
    query->declare_synonym(syn, entity);
  }
  for (auto selected_syn : selected_synonyms) {
    query->add_selected_synonym(selected_syn);
  }

  return query;
}

TEST_CASE("Test SelectClParser methods") {
  SelectClParser parser;
  SECTION("Test PreprocessQueryString") {
    std::string query_string = "variable p; select p such that "
                               "Modifies(6, v) pattern a(_, \" x + y \")";
    std::vector<std::string> expected_tokens{
        "variable", "p", ";", "select", "p", "such", "that",
        "Modifies", "(", "6", ",", "v", ")",
        "pattern", "a", "(", "_", ",", "x+y", ")"
    };
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);

    // With random whitespaces and newlines
    query_string = "variable     p;\n   select    p   such  \n   "
                   "that Modifies(6, v) \n pattern a(_, \"x+y\")";
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);
  }

  SECTION("Test state transitions") {
    REQUIRE(parser.NextState(0, "Select") == 1);
    REQUIRE(parser.NextState(1, "such") == 2);
    REQUIRE(parser.NextState(2, "pattern") == 3);
    REQUIRE(parser.NextState(1, "pattern") == 3);
  };
}

TEST_CASE("Test ParseQuery") {
  SelectClParser parser;

  SECTION("Query with no clauses should parse correctly") {
    std::string query_string = "procedure p; Select p";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"p", PQL::kProcedureEntityName}},
        {"p"});

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one such-that clauses should parse correctly") {
    std::string query_string = "variable v; Select v such that Modifies(6, v)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}},
        {"v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("6"),
            expected_query->CreateArgument("v")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with one pattern clauses should parse correctly") {
    std::string query_string = "assign a; Select a pattern a(v, \"x + y\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"a", PQL::kAssignEntityName}},
        {"a"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("x+y")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses should parse correctly") {
    std::string query_string = "variable v; procedure p; "
                               "Select v such that Modifies(6, v) "
                               "such that Modifies(3, v) "
                               "pattern a(_, \"x + y\") "
                               "pattern a(\"variable\", \"x\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}, {"p", PQL::kProcedureEntityName}},
        {"v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("6"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("3"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("x+y")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("variable")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("x")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses and many random whitespaces "
      "should parse correctly") {
    std::string query_string = "variable    v;    procedure    p; "
                               "Select v such  that  Modifies(  6, v) "
                               "  such      that    Modifies(3, v) "
                               "pattern a(_, \"x + y\") pattern a(_,  \"x\")";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName}, {"p", PQL::kProcedureEntityName}},
        {"v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("6"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("3"),
            expected_query->CreateArgument("v")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("x+y")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("x")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION("Query with wrong order of states should "
          "throw PqlSyntaxErrorException") {
    // Pattern should not be before such-that
    std::string query_string = "variable v; procedure p; "
                               "Select v, p pattern a(_, \"x + y\") "
                               "such that Modifies(6, v)";

    REQUIRE_THROWS_AS(
        parser.ParseQuery(query_string),
        PqlSyntaxErrorException);
  }
}
