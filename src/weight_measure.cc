#include "src/weight_measure.h"

WeightMeasure::WeightMeasure(int id, double weight, Datetime datetime)
    : id_(id), weight_(weight), datetime_(datetime) {}

int WeightMeasure::GetId() const { return id_; }

double WeightMeasure::GetWeight() const { return weight_; }

Datetime WeightMeasure::GetDatetime() const { return datetime_; }

template <typename OStream>
OStream& operator<<(OStream& os, const WeightMeasure& weight_measure) {
  return os << "[WeightMeasure ID=" << weight_measure.GetId()
            << " Kg=" << weight_measure.GetWeight()
            << " Datetime=" << weight_measure.GetDatetime().ToString() << "]";
}
