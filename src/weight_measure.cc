#include "src/weight_measure.h"

WeightMeasure::WeightMeasure() : WeightMeasure(0, 0, Datetime{}) {}

WeightMeasure::WeightMeasure(int id, double weight, Datetime datetime)
    : id_(id), weight_(weight), datetime_(datetime) {}

int WeightMeasure::GetId() const { return id_; }

double WeightMeasure::GetWeight() const { return weight_; }

Datetime WeightMeasure::GetDatetime() const { return datetime_; }
