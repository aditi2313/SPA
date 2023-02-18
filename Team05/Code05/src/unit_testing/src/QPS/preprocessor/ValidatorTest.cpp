#include <common/Exceptions.h>
#include <QPS/preprocessor/Validator.h>
#include <QPS/preprocessor/SelectClParser.h>
#include <QPS/models/PQL.h>

#include <utility>
#include <catch.hpp>

using namespace qps;  // NOLINT

std::unique_ptr<Query> BuildQuery(
    std::vector<std::pair<SynonymName, EntityName>> synonyms,
    std::vector<std::string> selected_synonyms);  // Forward declaration

TEST_CASE("Test IsWildcard") {
  Validator validator;
  SECTION("Happy path") {
    // No wildcard
    std::unique_ptr<Query> query = BuildQuery(
        {{"v", PQL::kVariableEntityName}}, {"v"});
    query->add_clause(
        std::make_unique<qps::ModifiesClause>(
            query->CreateArgument("6"),
            query->CreateArgument("v")));

    std::vector<std::unique_ptr<Clause>> &clauses = query->get_clauses();
    REQUIRE(Validator::IsWildcard(clauses));
  }
}

TEST_CASE("Test invalidWildcard") {
  SECTION("Wildcard is in the wrong area") {
    std::unique_ptr<Query> query = BuildQuery(
        {{"v", PQL::kVariableEntityName}}, {"v"});
    query->add_clause(
        std::make_unique<qps::ModifiesClause>(
            query->CreateArgument("_"),
            query->CreateArgument("v")));

    std::vector<std::unique_ptr<Clause>> &clauses2 =
        query->get_clauses();

    REQUIRE(!Validator::IsWildcard(clauses2));
  }
}
TEST_CASE("Test SynonymCheck") {
  Validator validator;
  SECTION("Happy path") {
    // All used synonyms are declared
    std::unique_ptr<Query> query = BuildQuery(
        {{"v", PQL::kVariableEntityName}}, {"v"});
    query->add_clause(
        std::make_unique<ModifiesClause>(
            query->CreateArgument("6"),
            query->CreateArgument("v")));

    REQUIRE(Validator::SynonymCheck(query));
  }
}
//  TEST_CASE("Invalid synonym used") {
//  SECTION("Undeclared synoym used");
//  // One undeclared synonym used
//  std::string query_string2 = "variable v; Select v such that Modifies(6, a)";
//
//  std::unique_ptr<Query> expected_query2 =
//  BuildQuery({{"v", PQL::kVariableEntityName}}, {"v"});
//  expected_query2->add_clause(
//      std::make_unique<ModifiesClause>(
//          expected_query2->CreateArgument("6"),
//          expected_query2->CreateArgument("a")));
//
//    REQUIRE(!Validator::SynonymCheck(expected_query2));
//}

// TEST_CASE("Semantically correct") {
//    SelectClParser parser;
//  SECTION("All is valid");
//    std::string query_string =
//        "variable v; select v such that modifies(v, 6)";
//    std::unique_ptr<Query> query = parser.ParseQuery(query_string);
//    bool result = Validator::validate(std::move(query));
//    REQUIRE(result);
//}

// TEST_CASE("Semantically incorrect") {
//  SelectClParser parser;
//  SECTION("Wrong semantics");
//  std::string query_string =
//      "variable v; select v such that modifies(v, 6)";
//  std::unique_ptr<Query> query = parser.ParseQuery(query_string);
//  REQUIRE_THROWS_AS(Validator::validate(std::move(query)),
//      PqlSemanticErrorException);
//}

