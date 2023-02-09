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

}  // namespace util
