#ifndef TEST_MOCK_WEIGHTERM_DATA_H_
#define TEST_MOCK_WEIGHTERM_DATA_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "gmock/gmock-function-mocker.h"
#include "src/weight_measure.h"
#include "src/weighterm_data.h"

class MockWeightermData : public WeightermData {
 public:
  MOCK_METHOD(DataResult, RegisterWeight, (double weight), (override));
  MOCK_METHOD(const std::vector<WeightMeasure>, ListWeights, (),
              (const, override));
};

#endif  // TEST_MOCK_WEIGHTERM_DATA_H_
