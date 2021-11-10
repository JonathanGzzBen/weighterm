#ifndef SRC_WEIGHTERM_DATA_H_
#define SRC_WEIGHTERM_DATA_H_
#include <vector>

#include "src/weight_measure.h"
enum class DataResult { CouldNotOpenDatabase, CouldNotRunQuery, Ok };
class WeightermData {
 public:
  WeightermData() = default;
  virtual ~WeightermData() = default;
  virtual DataResult RegisterWeight(double weight) = 0;
  virtual const std::vector<WeightMeasure> ListWeights() const = 0;
};

#endif  // SRC_WEIGHTERM_DATA_H_
