#include "Table.h"

#include <algorithm>
#include <iostream>
#include <string>

namespace qps {
// Method used for debugging purposes
// Prints the Table in this given format:
// | *v* | *s* |
// | var | 10  |
// | abc | 20  |
void Table::PrintDebug() {
  size_t col_width = 0;
  int num_cols = columns_.size();
  for (auto syn : columns_) {
    col_width = std::max(col_width, syn.size() + 4);
  }
  for (auto &row : rows_) {
    for (auto &entity : row) {
      col_width = std::max(col_width, entity.to_str().size() + 2);
    }
  }

  std::cout << "|";
  for (auto syn : columns_) {
    int lead_buffer = (col_width - syn.size() - 2) / 2;
    int trail_buffer = col_width - syn.size() - 2 - lead_buffer;
    std::cout << std::string(lead_buffer, ' ');
    std::cout << "*" << syn << "*";
    std::cout << std::string(trail_buffer, ' ');
    std::cout << "|";
  }
  std::cout << "\n";

  for (auto &row : rows_) {
    std::cout << "|";
    for (auto &entity : row) {
      int lead_buffer = (col_width - entity.to_str().size()) / 2;
      int trail_buffer = col_width - entity.to_str().size() - lead_buffer;
      std::cout << std::string(lead_buffer, ' ');
      std::cout << entity.to_str();
      std::cout << std::string(trail_buffer, ' ');
      std::cout << "|";
    }
    std::cout << "\n";
  }
}

}  // namespace qps
