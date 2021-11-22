#ifndef SRC_DATA_EXCEPTION_H_
#define SRC_DATA_EXCEPTION_H_
#include <exception>
#include <string>
struct DataException : public std::runtime_error {
  explicit DataException(const char* msg) noexcept : std::runtime_error(msg) {}
};
#endif  // SRC_DATA_EXCEPTION_H_
