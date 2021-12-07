#ifndef WEIGHTERM_SRC_DATETIME_H_
#define WEIGHTERM_SRC_DATETIME_H_

#include <chrono>
#include <string>

class Datetime {
 public:
  explicit Datetime(time_t datetime_t);
  explicit Datetime(const std::string& date_string);
  [[nodiscard]] std::string ToString() const;

 private:
  std::time_t datetime_t_;
};

#endif  // WEIGHTERM_SRC_DATETIME_H_
