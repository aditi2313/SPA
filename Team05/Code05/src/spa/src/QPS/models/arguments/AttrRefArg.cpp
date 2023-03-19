#include "AttrRefArg.h"

#include "QPS/evaluator/TableJoiner.h"

namespace qps {
void AttrRefArg::UpdateTableWithAttrValue(
    pkb::PKBReadPtr &pkb,
    Table &query_table,
    bool &is_table_initialized) {
  // Update query_table with rows mapping from
  // Index to AttrValue
  // e.g. calls (line) to calls (procName)
  EntitySet indexes;
  SynonymArg::InitializeEntities(query_table, pkb, indexes);
  Table::TwoSynonymRows rows;

  for (auto &index : indexes) {
    rows.emplace_back(index, get_attr_value(pkb, index));
  }

  std::vector<SynonymName> columns;
  SynonymName col1 = get_syn_name();
  SynonymName col2 = get_full_name();
  columns.emplace_back(col1);
  columns.emplace_back(col2);
  Table new_table(columns);

  new_table.add_values(col1, col2, rows);
  if (!is_table_initialized) {
    query_table = new_table;
    is_table_initialized = true;
  } else {
    query_table = TableJoiner::Join(query_table, new_table);
  }
}

void AttrRefArg::InitializeEntities(
    Table &table, pkb::PKBReadPtr &pkb, EntitySet &results) {
  EntitySet indexes;
  SynonymArg::InitializeEntities(table, pkb, indexes);

  for (auto &index : indexes) {
    results.insert(get_attr_value(pkb, index));
  }
}
}  // namespace qps
