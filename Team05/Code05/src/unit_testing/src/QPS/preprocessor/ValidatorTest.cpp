#include <catch.hpp>

#include <QPS/preprocessor/Validator.h>
#include <Common/Exceptions.h>
#include <QPS/preprocessor/ParserTest.cpp>
using namespace qps;
void require(bool b) { REQUIRE(b);  }

TEST_CASE("Test isWildcard") { 
    Validator validator; 
  SECTION("Happy path");
    //No wildcard
    std::string query_string = "variable v; Select v such that Modifies(6, v)";

    Query expected_query = BuildQuery({{"v", models::EntityStub()}}, {"v"});
    expected_query.add_clause(std::make_unique<ModifiesClause>(Argument("6"), Argument("v")));

    std::vector<std::unique_ptr<Clause>>& clauses = expected_query.get_clauses();
    
    require(Validator::isWildcard(std::move(clauses)));

    SECTION("wildcare is in the wrong area");
    std::string query_string2= "variable v; Select v such that Modifies(_, v)";
    auto clause1 = ModifiesClause(Argument("_"), Argument("v"));

    Query expected_query2 = BuildQuery({{"v", models::EntityStub()}}, {"v"});
    expected_query2.add_clause(
        std::make_unique<ModifiesClause>(Argument("_"), Argument("v")));

    std::vector<std::unique_ptr<Clause>>& clauses2 =
        expected_query2.get_clauses();

    require(!Validator::isWildcard(std::move(clauses2)));

 }

TEST_CASE("Test SynonymCheck") { 
    Validator validator;
    SECTION("Happy path");
    //All used synonyms are declared
    std::string query_string = "variable v; Select v such that Modifies(6, v)";

    Query expected_query = BuildQuery({{"v", models::EntityStub()}}, {"v"});
    expected_query.add_clause(std::make_unique<ModifiesClause>(Argument("6"), Argument("v")));

    std::vector<std::unique_ptr<Clause>>& clauses = expected_query.get_clauses();
    std::vector<std::string> synonym = expected_query.get_selected_synonyms();

    require(Validator::SynonymCheck(std::move(clauses), synonym));

    SECTION("Undeclared synoym used");
    //One undeclared synonym used
    std::string query_string2 = "variable v; Select v such that Modifies(6, a)";

    Query expected_query2 = BuildQuery({{"v", models::EntityStub()}}, {"a"});
    expected_query.add_clause(
        std::make_unique<ModifiesClause>(Argument("6"), Argument("a")));

    std::vector<std::unique_ptr<Clause>>& clauses2 =
        expected_query2.get_clauses();
    std::vector<std::string> synonym2 = expected_query2.get_selected_synonyms();

    require(!Validator::SynonymCheck(std::move(clauses2), synonym));
}
