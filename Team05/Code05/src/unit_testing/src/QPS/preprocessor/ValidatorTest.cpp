#include <Common/Exceptions.h>
#include <QPS/preprocessor/Validator.h>
#include <QPS/preprocessor/Parser.h>
#include <QPS/preprocessor/Parser.cpp>

#include <exception>
#include <catch.hpp>
using namespace qps;

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
      std::make_unique<ModifiesClause>(Argument("6"), Argument("v")));

  std::vector<std::unique_ptr<Clause>>& clauses = expected_query.get_clauses();
  REQUIRE(Validator::isWildcard(std::move(clauses)));
}

TEST_CASE("Test invalidWildcard") {
    SECTION("wildcare is in the wrong area");
    std::string query_string2 = "variable v; Select v such that Modifies(_, v)";
    auto clause1 = ModifiesClause(Argument("_"), Argument("v"));

    Query expected_query2 = BuildQuery1({{"v", models::EntityStub()}}, {"v"});
    expected_query2.add_clause(
        std::make_unique<ModifiesClause>(Argument("_"), Argument("v")));

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
  std::cout << "painful";
  expected_query2.add_clause(
      std::make_unique<ModifiesClause>(Argument("6"), Argument("a")));

  std::vector<std::unique_ptr<Clause>>& clauses2 =
      expected_query2.get_clauses();
  std::vector<std::string> synonym2 = expected_query2.get_selected_synonyms();

  REQUIRE(!Validator::SynonymCheck(std::move(clauses2), synonym2));
}

TEST_CASE("semantic error") {
  Parser parser;
    SECTION("invalid wildcard");
    std::string query_string2 = "variable v; select v such that modifies(_, a)";
    Query query = parser.ParseQuery(query_string2);
    REQUIRE_THROWS_AS(Validator::validator(std::move(query)), PqlSemanticErrorException);
}

