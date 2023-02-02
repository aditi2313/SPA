#pragma once

#include <vector>
#include <unordered_set>

#include "Filter.h"
#include "PKB/data/ModifiesData.h"
#include "common/Exceptions.h"

namespace filter {

typedef pkb::Table<pkb::ModifiesData> ModifiesTable;
typedef std::unique_ptr<ModifiesTable> ModifiesTablePtr;
typedef Filter<pkb::ModifiesData> ModifiesFilter;

class ModifiesFilterByLine : public Filter<pkb::ModifiesData> {
 public:
  ModifiesFilterByLine(int line) : line_(line) {}
  
  inline ModifiesTablePtr FilterTable(
      ModifiesTablePtr table) override {
    ModifiesTablePtr result = std::make_unique<ModifiesTable>();
    auto row = table->get_row(line_);
    result->add_row(line_, row);
    return result;
  }

 private:
  int line_;
};

class ModifiesFilterByVariable : public Filter<pkb::ModifiesData> {
 public:
  ModifiesFilterByVariable(std::unordered_set<std::string>& variables) : variables_(variables) {
    
  }  

  ModifiesTablePtr FilterTable(ModifiesTablePtr) override;

 private:
  std::unordered_set<std::string> variables_;
};

}  // namespace filter
