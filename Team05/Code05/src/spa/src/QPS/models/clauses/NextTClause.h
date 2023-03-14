#pragma once

#include <memory>
#include <queue>
#include <utility>

#include "Clause.h"

namespace qps {

class NextTClause : public Clause {
 public:
  NextTClause(ArgumentPtr arg1, ArgumentPtr arg2)
      : Clause(std::move(arg1), std::move(arg2)) {
    rel_name_ = PQL::kNextTRelName;
  }

  inline void Index(const Entity& index, const pkb::PKBReadPtr& pkb,
                    EntitySet& results) override {
    Clause::Index<pkb::NextData>(
        index,
        [&](Entity::Value key) {
          auto filter = std::make_unique<NextIndexFilter>(key);
          return std::move(pkb->Next(std::move(filter))->get_result());
        },
        [&](EntitySet& result, pkb::NextData data) {
          std::unordered_set<int> visited;
          std::queue<int> frontier;
          for (auto& l : data.get_next_im_list()) {
            frontier.push(l);
            result.insert(Entity(l));
          }
          while (!frontier.empty()) {
            int c = frontier.front();
            frontier.pop();
            if (visited.count(c)) continue;
            visited.insert(c);
            auto d = pkb->Next(NextIndexFilter::of(c));
            auto res = d->get_result();
            if (!res->exists(c)) continue;
            for (auto& l : res->get_row(c).get_next_im_list()) {
              frontier.push(l);
              result.insert(Entity(l));
            }
          }
        },
        results);
  }
};

}  // namespace qps