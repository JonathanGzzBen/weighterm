#include "src/weight_measure.h"

WeightMeasure::WeightMeasure(int id, double weight)
    : id_(id), weight_(weight) {}

WeightMeasure::WeightMeasure(int id, double weight, std::time_t datetime)
    : id_(id), weight_(weight), datetime_(datetime) {}

int WeightMeasure::GetId() const { return id_; }

double WeightMeasure::GetWeight() const { return weight_; }

std::time_t WeightMeasure::GetDatetime() const { return datetime_; };

void WeightMeasure::SetWeight(double weight) { weight_ = weight; }
