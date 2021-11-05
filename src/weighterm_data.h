#ifndef _WEIGHTERM_DATA_H
#define _WEIGHTERM_DATA_H
#include <vector>
#include "weight_measure.h"
enum class DataResult { CouldNotOpenDatabase, CouldNotRunQuery, Ok };
class WeightermData {
 public:
  WeightermData() = default;
  virtual ~WeightermData() = default;
  virtual DataResult RegisterWeight(double weight) = 0;
  virtual const std::vector<WeightMeasure> ListWeights() const = 0;
};

#endif
