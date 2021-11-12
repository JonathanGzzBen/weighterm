#ifndef SRC_WEIGHT_MEASURE_H_
#define SRC_WEIGHT_MEASURE_H_
class WeightMeasure {
 private:
  int m_id;
  double m_weight;

 public:
  WeightMeasure() = default;
  WeightMeasure(int id, double weight);
  int get_id() const;
  double get_weight() const;
  void set_weight(double weight);
};
#endif  //  SRC_WEIGHT_MEASURE_H_
