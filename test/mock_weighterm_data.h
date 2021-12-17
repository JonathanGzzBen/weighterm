#ifndef WEIGHTERM_TEST_MOCK_WEIGHTERM_DATA_H_
#define WEIGHTERM_TEST_MOCK_WEIGHTERM_DATA_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>

#include "gmock/gmock-function-mocker.h"
#include "src/weight_measure.h"
#include "src/weighterm_data.h"

class MockWeightermData : public WeightermData {
 public:
  MOCK_METHOD(DataResultCode, RegisterWeight, (double weight), (override));
  MOCK_METHOD(std::vector<WeightMeasure>, ListWeights, (), (const, override));
  MOCK_METHOD(DataResultCode, DeleteWeight, (int id), (override));
  MOCK_METHOD(DataResultCode, ModifyWeight, (int id, double weight),
              (override));
};

#endif  // WEIGHTERM_TEST_MOCK_WEIGHTERM_DATA_H_
