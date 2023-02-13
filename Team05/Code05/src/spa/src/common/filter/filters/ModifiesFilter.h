#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "IndexableFilter.h"
#include "PKB/data/ModifiesData.h"
#include "PKB/tables/IndexableTable.h"
#include "common/Exceptions.h"

namespace filter {

typedef std::unique_ptr<pkb::ModifiesTable> ModifiesTablePtr;
typedef IndexableFilter<pkb::ModifiesData> ModifiesFilter;

/// <summary>
/// A filter for a ModifiesTable by line.
/// Looks through the indexable table and returns all
/// rows that have the line as its LHS.
/// </summary>
class ModifiesFilterByLine : public IndexableFilter<pkb::ModifiesData> {
 public:
  explicit ModifiesFilterByLine(int line) : line_(line) {}

  inline ModifiesTablePtr FilterTable(ModifiesTablePtr table) override {
    ModifiesTablePtr result = std::make_unique<pkb::ModifiesTable>();
    auto indexes = table->get_indexes();
    if (indexes.find(line_) == indexes.end()) {
      return result;
    }
    auto row = table->get_row(line_);
    result->add_row(row.get_line(), row);
    return result;
  }

 private:
  int line_;
};

/// <summary>
/// A filter for an Indexable table by variable.
/// Looks through the indexable table and returns all rows
/// that have the variable in the RHS.
/// </summary>
class ModifiesFilterByVariable : public IndexableFilter<pkb::ModifiesData> {
 public:
  explicit ModifiesFilterByVariable(std::unordered_set<std::string> variables)
      : variables_(variables) {}

  ModifiesTablePtr FilterTable(ModifiesTablePtr) override;

 private:
  std::unordered_set<std::string> variables_;
};

}  // namespace filter
