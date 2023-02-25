#include "Table.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace qps {
void Table::PrintDebug() {
  size_t col_width = 0;
  int num_cols = columns_.size();
  for (auto syn : columns_) {
    col_width = std::max(col_width, syn.size() + 2);
  }
  for (auto &row : rows_) {
    for (auto &entity : row) {
      col_width = std::max(col_width, entity.to_str().size());
    }
  }

  size_t table_width = num_cols * (col_width + 2);
  std::string horizontal_line =
      "\n" + std::string(table_width, '-') + "\n";

  std::cout << "|";
  for (auto syn : columns_) {
    std::cout << "*" << syn << "*";
    std::cout << std::string(
        col_width - syn.size() - 2, ' ');
    std::cout << "|";
  }

  std::cout << horizontal_line;

  for (auto &row : rows_) {
    std::cout << "|";
    for (auto &entity : row) {
      std::cout << entity.to_str();
      std::cout << std::string(
          col_width - entity.to_str().size(), ' ');
      std::cout << "|";
    }
    std::cout << horizontal_line;
  }
}

}  // namespace qps
