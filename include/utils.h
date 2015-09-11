#ifndef UTILS_H
#define UTILS_H

#include <memory>

template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Ts>(args)...));
}

#endif /* UTILS_H */
