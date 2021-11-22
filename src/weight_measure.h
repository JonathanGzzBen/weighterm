#ifndef SRC_WEIGHT_MEASURE_H_
#define SRC_WEIGHT_MEASURE_H_
class WeightMeasure {
 private:
  int id_;
  double weight_;

 public:
  WeightMeasure() = default;
  WeightMeasure(int id, double weight);
  int GetId() const;
  double GetWeight() const;
  void SetWeight(double weight);
};
#endif  //  SRC_WEIGHT_MEASURE_H_
