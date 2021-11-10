#ifndef SRC_DATA_EXCEPTION_H_
#define SRC_DATA_EXCEPTION_H_
#include <exception>
#include <string>
class DataException : public std::exception {
 private:
  std::string m_message;

 public:
  explicit DataException(std::string message) noexcept : m_message{message} {};
  ~DataException() = default;
  virtual const char* what() const noexcept { return m_message.c_str(); };
};
#endif  // SRC_DATA_EXCEPTION_H_
