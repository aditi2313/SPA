#include <catch.hpp>
#include <exception>

#include "QPS/preprocessor/Parser.h"

using namespace qps; // NOLINT

// Helper method for testing
Query BuildQuery(
    std::vector<std::pair<std::string, models::EntityStub>> synonyms,
    std::vector<std::string> selected_synonyms
) {
  Query query;
  for (auto [syn, entity] : synonyms) {
    query.set_synonym(syn, entity);
  }
  for (auto selected_syn : selected_synonyms) {
    query.add_selected_synonym(selected_syn);
  }

  return query;
}

TEST_CASE("Test Parser methods") {
  Parser parser;
  SECTION("Test PreprocessQueryString") {
    std::string query_string = "variable p; select p such that "
                               "Modifies(6, v) pattern a(_, \" x + y \")";
    std::vector<std::string> expected_tokens{
        "variable", "p", ";", "select", "p", "such", "that", "Modifies", "(", "6", ",", "v", ")",
        "pattern", "a", "(", "_", ",", "x+y", ")"
    };
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);

    // With random whitespaces and newlines
    query_string = "variable     p;\n   select    p   such  \n   "
                   "that Modifies(6, v) \n pattern a(_, \"x+y\")";
    REQUIRE(parser.PreprocessQueryString(query_string) == expected_tokens);
  }

  SECTION("Test state transitions") {
    REQUIRE(parser.ShouldGoToNextState(0, "Select") == true);
    REQUIRE(parser.ShouldGoToNextState(1, "such") == true);
    REQUIRE(parser.ShouldGoToNextState(2, "pattern") == true);
  };

  SECTION("Validation methods") {
    REQUIRE(Parser::is_ident("a") == true);
    REQUIRE(Parser::is_ident("abc") == true);
    REQUIRE(Parser::is_ident("abc0123") == true);
    REQUIRE(Parser::is_ident("1") == false);
    REQUIRE(Parser::is_ident("a&") == false);
  };
}

// TODO(JL): Replace EntityStub
TEST_CASE("Test ParseQuery") {
  Parser parser;
  SECTION("Happy path") {
    // No clauses
    std::string query_string = "procedure p; Select p";
    Query actual_query = parser.ParseQuery(query_string);
    Query expected_query = BuildQuery(
        {{"p", models::EntityStub()}},
        {"p"}
    );

    REQUIRE(actual_query == expected_query);

    // One such-that clause
    query_string = "variable v; Select v such that Modifies(6, v)";
    actual_query = parser.ParseQuery(query_string);
    expected_query = BuildQuery(
        {{"v", models::EntityStub()}},
        {"v"}
    );
    expected_query.add_clause(
        std::make_unique<ModifiesClause>(Argument("6"), Argument("v"))
    );

    REQUIRE(actual_query == expected_query);

    // Multiple declarations, multiple synonyms and
    // multiple clauses (both such-that and pattern)
    query_string = "variable v; procedure p; "
                   "Select v, p such that Modifies(6, v) such that Modifies(3, v) "
                   "pattern a(_, \"x + y\") pattern a(_, \"x\")";
    actual_query = parser.ParseQuery(query_string);

    expected_query = BuildQuery(
        {{"v", models::EntityStub()}, {"p", models::EntityStub()}},
        {"v", "p"}
    );
    expected_query.add_clause(
        std::make_unique<ModifiesClause>(Argument("6"), Argument("v")));
    expected_query.add_clause(
        std::make_unique<ModifiesClause>(Argument("3"), Argument("v")));
    expected_query.add_clause(
        std::make_unique<PatternClause>(Argument("_"), Argument("x+y")));
    expected_query.add_clause(
        std::make_unique<PatternClause>(Argument("_"), Argument("x")));

    REQUIRE(actual_query == expected_query);
 
    // Random whitespaces
    query_string = "variable    v;    procedure    p; "
                   "Select v,   p    such    that    Modifies(  6, v) such that Modifies(3, v) "
                   "pattern    a(_, \"x + y\")    pattern     a(_,  \"x\")";
    actual_query = parser.ParseQuery(query_string);
    REQUIRE(actual_query == expected_query);
  }

  SECTION("Error cases") {
    // Wrong order of states
    // Pattern should not be before such-that
    std::string query_string = "variable v; procedure p; "
                               "Select v, p pattern a(_, \"x + y\") such that Modifies(6, v)";

    REQUIRE_THROWS_AS(
        parser.ParseQuery(query_string),
        PqlSyntaxErrorException
    );
  }

}
