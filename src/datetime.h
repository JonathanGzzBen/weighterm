#ifndef WEIGHTERM_SRC_DATETIME_H_
#define WEIGHTERM_SRC_DATETIME_H_

#include <chrono>
#include <string>

class Datetime {
 private:
  std::time_t datetime_t_;

 public:
  Datetime(time_t datetime_t);
  Datetime(const std::string& date_string);
  std::string toString();
};

#endif  // WEIGHTERM_SRC_DATETIME_H_
