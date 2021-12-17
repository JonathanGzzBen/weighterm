#ifndef WEIGHTERM_SRC_WEIGHTERM_DATA_SQLITE_H_
#define WEIGHTERM_SRC_WEIGHTERM_DATA_SQLITE_H_
#include <sqlite3.h>

#include <iostream>
#include <vector>

#include "src/weighterm_data.h"

class WeightermDataSqlite : public WeightermData {
 private:
  DataResultCode InitializeDatabase();
  sqlite3* db_ = nullptr;

 public:
  WeightermDataSqlite();
  ~WeightermDataSqlite() override;
  DataResult<WeightMeasure> FindWeight(int id) override;
  DataResultCode RegisterWeight(double weight, Datetime datetime) override;
  [[nodiscard]] DataResult<std::vector<WeightMeasure>> ListWeights()
      const override;
  DataResultCode DeleteWeight(int id) override;
  DataResultCode ModifyWeight(int id, double weight,
                              Datetime datetime) override;
};
#endif  // WEIGHTERM_SRC_WEIGHTERM_DATA_SQLITE_H_
