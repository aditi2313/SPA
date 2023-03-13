#include <catch.hpp>
#include <unordered_set>

#include "../../spa/src/SP/SourceProcessor.h"
#include "PKB/PKBRead.h"
#include "PKB/PKBRelationTable.h"
#include "PKB/PKBWrite.h"
#include "SP/visitors/ModifiesVisitor.h"
#include "common/filter/filters/PredicateFilter.h"

pkb::ModifiesTable InitializeModifies(std::string program) {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  auto root = sp::SourceProcessor::ParseProgram(program);
  sp::SourceProcessor::ExtractRelationships(root, table);
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ModifiesPredicateFilter>(
      [](pkb::ModifiesData data) { return true; });
  auto results_ptr = reader.Modifies(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}

pkb::ModifiesTable InitializeEmptyModifies() {
  std::unique_ptr<pkb::PKBRelationTable> table =
      std::make_unique<pkb::PKBRelationTable>();
  pkb::PKBRead reader(std::move(table));
  auto ftr = std::make_unique<filter::ModifiesPredicateFilter>(
      [](pkb::ModifiesData data) { return true; });
  auto results_ptr = reader.Modifies(std::move(ftr));
  auto results = *(results_ptr->get_result());

  return results;
}
