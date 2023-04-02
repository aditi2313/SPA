#include "PKBRead.h"

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_set>

#include "common/exceptions/QPSExceptions.h"
#include "common/filter/filters/Export.h"
#include "tables/reader/DoubleIndexReader.h"

namespace pkb {
ModifiesDataReader& PKBRead::Modifies(filter::ModifiesTableFilter& filter) {
  return filter.FilterTable(relation_table_->modifies_table_);
}

AssignDataReader& PKBRead::Assigns(filter::AssignTableFilter& filter) {
  return filter.FilterTable(relation_table_->assign_table_);
}

UsesDataReader& PKBRead::Uses(filter::UsesTableFilter& filter) {
  return filter.FilterTable(relation_table_->uses_table_);
}

ConditionDataReader& PKBRead::Condition(filter::ConditionTableFilter& filter) {
  return filter.FilterTable(relation_table_->condition_table_);
}

LineSet PKBRead::Affects(Line s) {
  // Return cached result immediately if it has been
  // calculated before
  if (cache_->ExistsAffects(s)) {
    return cache_->GetAffects(s);
  }

  LineSet result;

  if (!relation_table_->assign_.count(s)) {
    cache_->WriteAffects(s, {});
    return {};
  }
  LineSet empt{};
  auto& table = relation_table_->next_d_table_;
  auto& modified = relation_table_->assign_table_.get_row(s);
  auto& modified_var = modified.get_variable();
  auto& n_im_l = table.exists(s) ? table.get_row(s).get_next_im_list() : empt;

  util::GraphSearch<Line, LineSet>::BFS(
      [&](Line& v) {
        if (!table.exists(v))
          return LineSet{};
        auto& next = table.get_row(v);
        return next.get_next_im_list();
      },
      n_im_l,
      [&](const Line& curr) {
        if (relation_table_->uses_table_.exists(curr)) {
          auto& data = relation_table_->uses_table_.get_row(curr);
          // check that this assign stmt uses the variable
          if (data.get_variables().count(modified_var) &&
              relation_table_->assign_.count(curr)) {
            result.insert(curr);
          }
        }
        // if this stmt modifies the variable then don't do anything
        if (relation_table_->modifies_table_.exists(curr) &&
            !IsContainerStmt(curr)) {
          auto& data = relation_table_->modifies_table_.get_row(curr);
          if (data.get_variables().count(modified_var)) {
            return false;
          }
        }
        return true;
      });
  // Write to cache
  cache_->WriteAffects(s, result);
  return result;
}

LineSet PKBRead::AffectsT(Line s) {
  // Return cached result immediately if it has been
  // calculated before
  if (cache_->ExistsAffectsT(s)) {
    return cache_->GetAffectsT(s);
  }

  LineSet affected_lines = Affects(s);
  LineSet affectedT_lines(affected_lines);

  std::queue<Line> q;
  LineSet visited;

  // Initialize BFS queue
  for (auto& line : affected_lines) {
    q.push(line);
    visited.insert(line);
  }

  while (!q.empty()) {
    Line curr = q.front();
    q.pop();
    affectedT_lines.insert(curr);  // Update result
    auto neighbors = Affects(curr);

    for (auto& neighbor : neighbors) {
      // Note: moving the visited check here helps to prevent
      // pushing many duplicate lines into the queue
      if (visited.count(neighbor)) continue;
      q.push(neighbor);
      visited.insert(neighbor);
    }
  }

  // Write back to cache
  cache_->WriteAffectsT(s, affectedT_lines);
  return affectedT_lines;
}

LineSet PKBRead::NextT(Line v) {
  LineSet visited;
  std::queue<Line> frontier;
  LineSet result;

  auto& next_table = relation_table_->next_d_table_;
  if (!next_table.exists(v)) {
    return {};
  }
  auto& data = next_table.get_row(v);

  util::GraphSearch<Line, LineSet>::BFS(
      [&](Line& curr) {
        if (!next_table.exists(curr))
          return LineSet{};
        auto& child_data = next_table.get_row(curr);
        return child_data.get_next_im_list();
      },
      data.get_next_im_list(),
      [&](const Line& curr) {
        result.insert(curr);
        return true;
      });

  return result;
}

LineSet PKBRead::ReverseNextT(Line stmt) {
  LineSet visited;
  LineSet result;

  auto& next_table = relation_table_->next_d_table_;
  if (!next_table.exists2(stmt)) {
    return {};
  }

  util::GraphSearch<Line, LineSet>::BFS(
      [&](Line& curr) {
        if (!next_table.exists2(curr))
          return LineSet{};
        return next_table.get_reverse_values(curr);
      },
      next_table.get_reverse_values(stmt),
      [&](const Line& curr) {
        result.insert(curr);
        return true;
      });

  return result;
}
}  // namespace pkb
