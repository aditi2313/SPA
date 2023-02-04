#include <catch.hpp>

#include <Validator.h>
#include <Exceptions.h>
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
    query_string = "variable v; Select v such that Modifies(6, v)";
    
    
 }