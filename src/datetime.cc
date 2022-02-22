#include "datetime.h"

#include <chrono>
#include <sstream>
#include <iomanip>

Datetime::Datetime() {
  auto datetime_time_point{std::chrono::system_clock::now()};
  datetime_t_ = std::chrono::system_clock::to_time_t(datetime_time_point);
}

Datetime::Datetime(time_t datetime_t) : datetime_t_(datetime_t) {}

Datetime::Datetime(const std::string& date_string) {
  if (date_string.empty()) {
    auto datetime_time_point{std::chrono::system_clock::now()};
    datetime_t_ = std::chrono::system_clock::to_time_t(datetime_time_point);
    return;
  }
  std::stringstream date_stream{date_string};
  struct std::tm datetime_tm {};
  date_stream >> std::get_time(&datetime_tm, "%Y-%m-%d %H:%M:%S");
  datetime_t_ = mktime(&datetime_tm);
  if (date_stream.fail()) {
    throw std::invalid_argument{"Invalid datetime string"};
  }
}

std::string Datetime::ToString() const {
  std::stringstream datetime_string_stream{};
  datetime_string_stream << std::put_time(std::localtime(&datetime_t_),
                                          "%Y-%m-%d %H:%M:%S");
  return datetime_string_stream.str();
}
