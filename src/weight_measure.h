#ifndef WEIGHTERM_SRC_WEIGHT_MEASURE_H_
#define WEIGHTERM_SRC_WEIGHT_MEASURE_H_
#include <chrono>

#include "src/datetime.h"

class WeightMeasure {
 private:
  int id_;
  double weight_;
  Datetime datetime_;

 public:
  WeightMeasure(int id, double weight, Datetime datetime);
  int GetId() const;
  double GetWeight() const;
  Datetime GetDatetime() const;
  void SetWeight(double weight);
};
#endif  //  WEIGHTERM_SRC_WEIGHT_MEASURE_H_
