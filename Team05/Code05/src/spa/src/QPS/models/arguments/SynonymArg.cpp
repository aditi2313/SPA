#include "SynonymArg.h"

#include "QPS/evaluator/TableJoiner.h"

namespace qps {
void SynonymArg::UpdateTableWithAttrValue(
    const pkb::PKBReadPtr &pkb,
    Table &query_table) {
  if (attr_name_.empty()) return;  // Not an attr ref
  bool is_secondary_attr_value = is_secondary_attr_ref();

  // Update query_table with rows mapping from
  // Index to AttrValue
  // e.g. calls (line) to calls (procName)
  EntitySet indexes;
  InitializeEntities(
      query_table, pkb, indexes, false);
  Table::TwoSynonymRows rows;

  for (auto &index : indexes) {
    if (is_secondary_attr_value) {
      rows.emplace_back(index, get_secondary_attr_value(pkb, index));
    } else {
      rows.emplace_back(index, index);
    }
  }

  std::vector<SynonymName> columns;
  SynonymName col1 = get_syn_name();
  SynonymName col2 = get_full_name();
  columns.emplace_back(col1);
  columns.emplace_back(col2);
  Table new_table(columns);

  new_table.add_values(col1, col2, rows);

  query_table = TableJoiner::Join(query_table, new_table);
}
}  // namespace qps
