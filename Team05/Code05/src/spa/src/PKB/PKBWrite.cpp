#include "PKBWrite.h"

#include "common/Exceptions.h"

namespace pkb {

void PKBWrite::AddModifies(stub::ModifiesStub) {
  throw new NotImplementedException();
}

void PKBWrite::AddParent(stub::ParentStub) {
  throw new NotImplementedException();
}

}  // namespace pkb
