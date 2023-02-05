#include <Common/Exceptions.h>
#include <QPS/preprocessor/Validator.h>
#include <QPS/preprocessor/Parser.h>

#include <exception>
#include <catch.hpp>
#include <utility>
using qps::Argument;
using qps::ModifiesClause;
using qps::Validator;
using qps::Query;
using qps::Clause;
using qps::Parser;

void require1(bool b) { REQUIRE(b); }

Query BuildQuery1(
    std::vector<std::pair<std::string, models::EntityStub>> synonyms,
    std::vector<std::string> selected_synonyms) {
  Query query;
  for (auto [syn, entity] : synonyms) {
    query.set_synonym(syn, entity);
  }
  for (auto selected_syn : selected_synonyms) {
    query.add_selected_synonym(selected_syn);
  }

  return query;
}

TEST_CASE("Test isWildcard") {
  Validator validator;
  SECTION("Happy path");
  // No wildcard
  std::string query_string = "variable v; Select v such that Modifies(6, v)";

  Query expected_query = BuildQuery1({{"v", models::EntityStub()}}, {"v"});
  expected_query.add_clause(
      std::make_unique<qps::ModifiesClause>(Argument("6"), Argument("v")));

  std::vector<std::unique_ptr<Clause>>& clauses = expected_query.get_clauses();
  REQUIRE(Validator::isWildcard(std::move(clauses)));
}

TEST_CASE("Test invalidWildcard") {
    SECTION("wildcare is in the wrong area");
    std::string query_string2 = "variable v; Select v such that Modifies(_, v)";
    auto clause1 = ModifiesClause(Argument("_"), Argument("v"));

    Query expected_query2 = BuildQuery1({{"v", models::EntityStub()}}, {"v"});
    expected_query2.add_clause(
        std::make_unique<qps::ModifiesClause>(Argument("_"), Argument("v")));

    std::vector<std::unique_ptr<Clause>>& clauses2 =
        expected_query2.get_clauses();

    REQUIRE(!Validator::isWildcard(std::move(clauses2)));
  }
TEST_CASE("Test SynonymCheck") {
  Validator validator;
  SECTION("Happy path");
  // All used synonyms are declared
  std::string query_string = "variable v; Select v such that Modifies(6, v)";

  Query expected_query = BuildQuery1({{"v", models::EntityStub()}}, {"v"});
  expected_query.add_clause(
      std::make_unique<ModifiesClause>(Argument("6"), Argument("v")));

  std::vector<std::unique_ptr<Clause>>& clauses = expected_query.get_clauses();
  std::vector<std::string> synonym = expected_query.get_selected_synonyms();

  REQUIRE(Validator::SynonymCheck(std::move(clauses), synonym));
}
TEST_CASE("Invalid synonym used") {
  SECTION("Undeclared synoym used");
  // One undeclared synonym used
  std::string query_string2 = "variable v; Select v such that Modifies(6, a)";

  Query expected_query2 = BuildQuery1({{"v", models::EntityStub()}}, {"v"});
  expected_query2.add_clause(
      std::make_unique<ModifiesClause>(Argument("6"), Argument("a")));

  std::vector<std::unique_ptr<Clause>>& clauses2 =
      expected_query2.get_clauses();
  std::vector<std::string> synonym2 = expected_query2.get_selected_synonyms();

  REQUIRE(!Validator::SynonymCheck(std::move(clauses2), synonym2));
}
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

