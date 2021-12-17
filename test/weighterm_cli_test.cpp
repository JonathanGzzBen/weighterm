#include "src/weighterm_cli.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <iostream>
#include <memory>

#include "src/weighterm_data_sqlite.h"
#include "test/mock_weighterm_data.h"

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

TEST(HandleRegister, NonNumericStringArgumentReturnFalse) {
  auto data = std::make_unique<MockWeightermData>();
  auto result{RegisterWeight(data.get(), "asdfasdf")};
  EXPECT_FALSE(result);
}

TEST(HandleRegister, NumericStringArgumentReturnFalse) {
  auto data = std::make_unique<MockWeightermData>();
  EXPECT_CALL(*data, RegisterWeight(_))
      .Times(Exactly(1))
      .WillOnce(Return(DataResultCode::OK));
  auto result{RegisterWeight(data.get(), "12.4")};
  EXPECT_TRUE(result);
}
