#ifndef WEIGHTERM_SRC_WEIGHT_MEASURE_H_
#define WEIGHTERM_SRC_WEIGHT_MEASURE_H_
#include <chrono>
#include <ostream>

#include "spdlog/fmt/ostr.h"
#include "src/datetime.h"

class WeightMeasure {
 public:
  WeightMeasure(int id, double weight, Datetime datetime);
  [[nodiscard]] int GetId() const;
  [[nodiscard]] double GetWeight() const;
  [[nodiscard]] Datetime GetDatetime() const;

  template <typename OStream>
  friend OStream &operator<<(OStream &os, const WeightMeasure &weight_measure);

 private:
  int id_;
  double weight_;
  Datetime datetime_;
};
#endif  //  WEIGHTERM_SRC_WEIGHT_MEASURE_H_
