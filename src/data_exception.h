#ifndef WEIGHTERM_SRC_DATA_EXCEPTION_H_
#define WEIGHTERM_SRC_DATA_EXCEPTION_H_
#include <exception>
#include <string>

struct DataException : public std::runtime_error {
  explicit DataException(const char* msg) noexcept : std::runtime_error(msg) {}
};
#endif  // WEIGHTERM_SRC_DATA_EXCEPTION_H_
