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

// Helper method for testing
void TestNoThrows(std::string query_string) {
  SelectClParser parser;
  REQUIRE_NOTHROW(parser.ParseQuery(query_string));
}

TEST_CASE("Test SelectClParser methods") {
  SelectClParser parser;
  SECTION("Test PreprocessQueryString") {
    std::string query_string = "variable p; select p such that "
                               "Modifies(6, v) pattern a(_, _\" x + y \"_)";
    std::vector<std::string> expected_tokens{
        "variable", "p", ";", "select", "p", "such", "that",
        "Modifies", "(", "6", ",", "v", ")",
        "pattern", "a", "(", "_", ",", "_\"x+y\"_", ")"
    };
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);

    // With random whitespaces and newlines
    query_string = "variable     p;\n   select    p   such  \n   "
                   "that Modifies(6, v) \n pattern a(_, _\"x+y\"_)";
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);
  }
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

  SECTION("Query with one clause and selected tuple should parse correctly") {
    std::string query_string = "variable v; stmt s; "
                               "Select <s, v> such that Modifies(s, v)";
    QueryPtr actual_query = parser.ParseQuery(query_string);
    QueryPtr expected_query = BuildQuery(
        {{"v", PQL::kVariableEntityName},
         {"s", PQL::kStmtEntityName}},
        {"s", "v"});
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("s"),
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
            expected_query->CreateArgument("\"x+y\"")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses should parse correctly") {
    std::string query_string = "variable v; procedure p; "
                               "Select v such that Modifies(6, v) "
                               "such that Modifies(3, v) "
                               "pattern a(_, \"x + y\") "
                               "pattern a(\"variable\", _\"x\"_)";
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
            expected_query->CreateArgument("\"x+y\"")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"variable\"")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_\"x\"_")));

    REQUIRE(*actual_query == *expected_query);
  }

  SECTION(
      "Query with multiple declarations, multiple synonyms "
      "and multiple such-that and pattern clauses and "
      "many random whitespaces and tabs"
      "should parse correctly") {
    std::string query_string = "variable  \t  v;    procedure    p; "
                               "Select v such  that \t  Modifies(  6, v) "
                               "  such  \t    that    Modifies(3, v) "
                               "pattern a(_, \"x + y   \t  \") "
                               "   \t pattern a(_,  \"   x  \t\")";
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
            expected_query->CreateArgument("\"x+y\"")));
    expected_query->add_clause(
        std::make_unique<ModifiesClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("_")));
    expected_query->add_clause(
        std::make_unique<PatternClause>(
            expected_query->CreateArgument("a"),
            expected_query->CreateArgument("\"x\"")));

    REQUIRE(*actual_query == *expected_query);
  }

    // In these following testcases, it is too verbose to create the
    // full expected clause for much longer queries, so will just be testing NoThrows.
    // The previous testcases cover whether the expected query has the
    // correct clauses
  SECTION("Query with pattern before such-that should parse correctly") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v)";

    TestNoThrows(query_string);
  }

  SECTION("Query with many interleaving clauses of different types"
          "should parse correctly") {
    std::string query_string = "variable v;"
                               "Select v pattern a(_, \"x + y\") "
                               "such that Modifies(6, v) "
                               "pattern a(v, _\"x\"_) "
                               "such that Uses(6, v) "
                               "such that Parent(6, 7)";

    TestNoThrows(query_string);
  }
}
