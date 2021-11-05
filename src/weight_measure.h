#ifndef _WEIGHT_MEASURE_H_
#define _WEIGHT_MEASURE_H_
class WeightMeasure {
 private:
  int m_id;
  double m_weight;

 public:
  WeightMeasure() = default;
  WeightMeasure(int id, double weight);
  int get_id();
  double get_weight();
  void set_weight(double weight);
};
#endif
