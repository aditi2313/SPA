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
/// Obtains the row with the line given.
/// </summary>
class ModifiesFilterByLine : public IndexableFilter<pkb::ModifiesData> {
 public:
  explicit ModifiesFilterByLine(int line) : line_(line) {}

  inline ModifiesTablePtr FilterTable(ModifiesTablePtr table) override {
    ModifiesTablePtr result = std::make_unique<pkb::ModifiesTable>();
    auto row = table->get_row(line_);
    result->add_row(row.get_line(), row);
    return result;
  }

 private:
  int line_;
};

/// <summary>
/// A filter for an indexable table by variable.
/// Looks through the indexable table and removes the variable.
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
