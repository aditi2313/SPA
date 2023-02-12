#pragma once
namespace util {

// Todo(Gab) replace all dynamic cast checks with this.

/// <summary>
/// Utility function for checking the instance of a
/// object.
/// </summary>
/// <typeparam name="Base">The base class of the object.</typeparam>
/// <typeparam name="Derived">The possibly derived class of the
/// object.</typeparam> <param name="other">The object to check</param>
/// <returns></returns>
template <class Derived, class Base>
bool InstanceOf(const Base& object) {
  return dynamic_cast<const Derived*>(&object) != nullptr;
}


/// <summary>
/// Utility function for comparing between two vectors of
/// unique pointers
/// </summary>
/// <returns>True if the two vectors are the same size and
/// the object each pointer is pointing to compares equal</returns>
template<class UniquePointer>
bool CompareVectorOfPointers(const std::vector<UniquePointer> &LHS,
                                const std::vector<UniquePointer> &RHS) {
  if(LHS.size() != RHS.size()) return false;
  for(int N = LHS.size(), i = 0; i < N; ++i) {
    if(*(LHS.at(i)) != *(RHS.at(i))) return false;
  }
  return true;
}
}  // namespace util
