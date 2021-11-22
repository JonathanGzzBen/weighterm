#include "src/weight_measure.h"

WeightMeasure::WeightMeasure(int id, double weight)
    : id_(id), weight_(weight) {}

int WeightMeasure::GetId() const { return id_; }

double WeightMeasure::GetWeight() const { return weight_; }

void WeightMeasure::SetWeight(double weight) { weight_ = weight; }
