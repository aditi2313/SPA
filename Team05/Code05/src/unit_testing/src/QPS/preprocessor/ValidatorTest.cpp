#include <catch.hpp>

#include <QPS/preprocessor/Validator.h>
#include <Common/Exceptions.h>
using namespace qps;



Query BuildQuery(
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
    //No wildcard
std::string query_string = "variable v; Select v such that Modifies(6, v)";

    std::vector<std::unique_ptr<Clause>> clauses =
        ModifiesClause(Argument("6"), Argument("v"));

    REQUIRE(Validator::isWildcard(clauses) == true);
    
    
 }