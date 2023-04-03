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
  // TODO(LOD)
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
        // Not an assign statement, skip
        if (!relation_table_->assign_.count(curr)) return true;
        if (relation_table_->uses_table_.exists(curr)) {
          auto& data = relation_table_->uses_table_.get_row(curr);
          // check that this assign stmt uses the variable
          if (data.get_variables().count(modified_var)) {
            result.insert(curr);
          }
        }
        // if this stmt modifies the variable then don't do anything
        auto curr_modified_var = relation_table_->assign_table_.get_row(curr).get_variable();
        return curr_modified_var != modified_var;
      });

  // Write to cache
  cache_->WriteAffects(s, result);
  return result;
}

Line PKBRead::ReverseAffects(Line stmt) {
  Line answer;
  auto& next_table = relation_table_->next_d_table_;

  if (!relation_table_->assign_.count(stmt)
      || !next_table.exists2(stmt)) {
    // Not an assign statement or
    // Next*(_, s) is false
    return {};
  }
  // TODO(LOD)
  // Used variables
  auto& used_vars = relation_table_->uses_table_.get_row(stmt).get_variables();

  util::GraphSearch<Line, LineSet>::BFS(
      [&](Line& v) {
        if (!next_table.exists2(v))
          return LineSet{};
        return next_table.get_row_index2(v);
      },
      next_table.get_row_index2(stmt),
      [&](const Line& curr) {
        // TODO(LOD)
        // Not an assign statement, skip
        if(!relation_table_->assign_.count(curr)) return true;
        auto modified_var = relation_table_->assign_table_.get_row(curr).get_variable();
        if (used_vars.count(modified_var)) {
          answer = curr;  // Found reverse Affects
          return false;  // No need to continue, there can only be one answer
        }
        return true;
      });

  return answer;
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
  LineSet result;

  auto& next_table = relation_table_->next_d_table_;
  if (!next_table.exists2(stmt)) {
    return {};
  }

  util::GraphSearch<Line, LineSet>::BFS(
      [&](Line& curr) {
        if (!next_table.exists2(curr))
          return LineSet{};
        return next_table.get_row_index2(curr);
      },
      next_table.get_row_index2(stmt),
      [&](const Line& curr) {
        result.insert(curr);
        return true;
      });

  return result;
}
}  // namespace pkb
