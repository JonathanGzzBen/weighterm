#include "src/weight_measure.h"

WeightMeasure::WeightMeasure(int id, double weight)
    : m_id(id), m_weight(weight) {}

double WeightMeasure::get_weight() { return m_weight; }

void WeightMeasure::set_weight(double weight) { m_weight = weight; }
