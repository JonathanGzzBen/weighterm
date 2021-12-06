#ifndef SRC_WEIGHT_MEASURE_H_
#define SRC_WEIGHT_MEASURE_H_
#include <chrono>
class WeightMeasure {
 private:
  int id_;
  double weight_;
  std::time_t datetime_;

 public:
  WeightMeasure() = default;
  WeightMeasure(int id, double weight);
  WeightMeasure(int id, double weight, time_t datetime);
  int GetId() const;
  double GetWeight() const;
  std::time_t GetDatetime() const;
  void SetWeight(double weight);
};
#endif  //  SRC_WEIGHT_MEASURE_H_
