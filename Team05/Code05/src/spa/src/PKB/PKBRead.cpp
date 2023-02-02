#include "PKBRead.h"

#include "common/Exceptions.h"

namespace pkb {
models::ModifiesResult PKBRead::Modifies(filter::ModifiesFilter) {
  throw new NotImplementedException();
}

}  // namespace pkb
