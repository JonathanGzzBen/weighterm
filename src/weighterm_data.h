#ifndef WEIGHTERM_SRC_WEIGHTERM_DATA_H_
#define WEIGHTERM_SRC_WEIGHTERM_DATA_H_
#include <vector>

#include "src/weight_measure.h"

enum class DataResultCode {
  COULD_NOT_OPEN_DATABASE,
  COULD_NOT_RUN_QUERY,
  NOT_FOUND,
  OK
};

template <typename T>
struct DataResult {
  DataResultCode code = DataResultCode::COULD_NOT_OPEN_DATABASE;
  T value;
};

class WeightermData {
 public:
  WeightermData() = default;
  virtual ~WeightermData() = default;
  virtual DataResult<WeightMeasure> FindWeight(int id) = 0;
  virtual DataResultCode RegisterWeight(double weight, Datetime datetime) = 0;
  [[nodiscard]] virtual DataResult<std::vector<WeightMeasure>> ListWeights()
      const = 0;
  virtual DataResultCode DeleteWeight(int id) = 0;
  virtual DataResultCode ModifyWeight(int id, double weight,
                                      Datetime datetime) = 0;
};

#endif  // WEIGHTERM_SRC_WEIGHTERM_DATA_H_
