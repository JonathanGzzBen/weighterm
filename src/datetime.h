#ifndef WEIGHTERM_DATETIME_H
#define WEIGHTERM_DATETIME_H

#include <chrono>
#include <string>
class Datetime {
 private:
  std::time_t datetime_t_;

 public:
  Datetime(time_t datetime_t);
  Datetime(std::string date_string);
  std::string toString();
};

#endif  // WEIGHTERM_DATETIME_H
