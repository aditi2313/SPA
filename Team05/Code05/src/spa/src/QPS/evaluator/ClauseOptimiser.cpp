#include "ClauseOptimiser.h"

namespace qps {
std::vector<int> ClauseOptimiser::GroupClauses(std::vector<ClausePtr> &clauses) {

}

ClauseOptimiser::AdjList &ClauseOptimiser::PreprocessClauses(std::vector<ClausePtr> &clauses) {
  int num_clauses = clauses.size();
  for (int i = 0; i < num_clauses; ++i) {
    for (int j = 0; j < i; ++j) {

    };
  }
}
}  // namespace qps
