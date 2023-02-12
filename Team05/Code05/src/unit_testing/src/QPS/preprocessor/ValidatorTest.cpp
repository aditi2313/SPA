#include <common/Exceptions.h>
#include <QPS/preprocessor/Validator.h>
#include <QPS/preprocessor/Parser.h>
#include <QPS/models/PQL.h>

#include <utility>
#include <catch.hpp>

using namespace qps;  // NOLINT

std::unique_ptr<Query> BuildQuery(
    std::vector<std::pair<Synonym, EntityId>> synonyms,
    std::vector<std::string> selected_synonyms);  // Forward declaration

TEST_CASE("Test IsWildcard") {
  Validator validator;
  SECTION("Happy path") {
    // No wildcard
    std::unique_ptr<Query> query = BuildQuery(
        {{"v", PQL::kVariableEntityId}}, {"v"});
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
        {{"v", PQL::kVariableEntityId}}, {"v"});
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
        {{"v", PQL::kVariableEntityId}}, {"v"});
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
//  Query expected_query2 = BuildQuery({{"v", models::EntityStub()}}, {"v"});
//  expected_query2.add_clause(
//      std::make_unique<ModifiesClause>(Argument("6"), Argument("a")));
//
//  std::vector<std::unique_ptr<Clause>>& clauses2 =
//      expected_query2.get_clauses();
//  std::vector<std::string> synonym2 = expected_query2.get_selected_synonyms();
//
//  REQUIRE(!Validator::SynonymCheck(std::move(clauses2), synonym2));
//}
//
// TEST_CASE("Semantically correct") {
//    Parser parser;
//  SECTION("All is valid");
//    std::string query_string =
//        "variable v; select v such that modifies(v, 6)";
//    std::unique_ptr<Query> query = parser.ParseQuery(query_string);
//    std::unique_ptr<Query> result = Validator::validator(std::move(query));
//    REQUIRE(result == query);
//}
//
// TEST_CASE("Semantically incorrect") {
//  Parser parser;
//  SECTION("Wrong semantics");
//  std::string query_string =
//      "variable v; select v such that modifies(v, 6)";
//  std::unique_ptr<Query> query = parser.ParseQuery(query_string);
//  REQUIRE_THROWS_AS(Validator::validator(std::move(query)),
//      PqlSemanticErrorException);
//}

