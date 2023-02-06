#include <common/Exceptions.h>
#include <QPS/preprocessor/Validator.h>
#include <QPS/preprocessor/Parser.h>

#include <utility>
#include <catch.hpp>

using qps::Argument;
using qps::ModifiesClause;
using qps::Validator;
using qps::Query;
using qps::Clause;
using qps::Parser;

std::unique_ptr<Query> BuildQuery(
    std::vector<std::pair<std::string, models::EntityStub>> synonyms,
    std::vector<std::string> selected_synonyms);  // Forward declaration

TEST_CASE("Test IsWildcard") {
  Validator validator;
  SECTION("Happy path") {
    // No wildcard
    std::unique_ptr<Query> query = BuildQuery(
        {{"v", models::EntityStub()}}, {"v"});
    query->add_clause(
        std::make_unique<qps::ModifiesClause>(Argument("6"), Argument("v")));

    std::vector<std::unique_ptr<Clause>> &clauses = query->get_clauses();
    REQUIRE(Validator::IsWildcard(clauses));
  }
}

TEST_CASE("Test invalidWildcard") {
  SECTION("Wildcard is in the wrong area") {
    std::unique_ptr<Query> query = BuildQuery(
        {{"v", models::EntityStub()}}, {"v"});
    query->add_clause(
        std::make_unique<qps::ModifiesClause>(Argument("_"), Argument("v")));

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
        {{"v", models::EntityStub()}}, {"v"});
    query->add_clause(
        std::make_unique<ModifiesClause>(Argument("6"), Argument("v")));

    std::vector<std::unique_ptr<Clause>> &clauses = query->get_clauses();
    std::vector<std::string> synonym = query->get_selected_synonyms();

    REQUIRE(Validator::SynonymCheck(clauses, synonym));
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

