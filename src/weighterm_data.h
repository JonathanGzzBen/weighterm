#ifndef WEIGHTERM_SRC_WEIGHTERM_DATA_H_
#define WEIGHTERM_SRC_WEIGHTERM_DATA_H_
#include <vector>

#include "src/weight_measure.h"

enum class DataResult {
  COULD_NOT_OPEN_DATABASE,
  COULD_NOT_RUN_QUERY,
  NOT_FOUND,
  OK
};

class WeightermData {
 public:
  WeightermData() = default;
  virtual ~WeightermData() = default;
  virtual DataResult RegisterWeight(double weight) = 0;
  [[nodiscard]] virtual std::vector<WeightMeasure> ListWeights() const = 0;
  virtual DataResult DeleteWeight(int id) = 0;
  virtual DataResult ModifyWeight(int id, double weight) = 0;
};

#endif  // WEIGHTERM_SRC_WEIGHTERM_DATA_H_
