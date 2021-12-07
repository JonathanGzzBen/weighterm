#include "datetime.h"

#include <chrono>
#include <iomanip>

Datetime::Datetime(time_t datetime_t) : datetime_t_(datetime_t) {}

Datetime::Datetime(std::string date_string) {
  std::stringstream date_stream{date_string};
  struct std::tm datetime_tm {};
  date_stream >> std::get_time(&datetime_tm, "%Y-%m-%d %H:%M:%S");
  datetime_t_ = mktime(&datetime_tm);
}

std::string Datetime::toString() {
  std::stringstream datetime_string_stream{};
  datetime_string_stream << std::put_time(std::localtime(&datetime_t_),
                                          "%Y-%m-%d %H:%M:%S");
  return datetime_string_stream.str();
}
