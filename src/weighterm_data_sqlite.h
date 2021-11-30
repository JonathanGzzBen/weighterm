#ifndef SRC_WEIGHTERM_DATA_SQLITE_H_
#define SRC_WEIGHTERM_DATA_SQLITE_H_
#include <sqlite3.h>

#include <iostream>
#include <vector>

#include "src/weighterm_data.h"
class WeightermDataSqlite : public WeightermData {
 private:
  DataResult InitializeDatabase();
  sqlite3* db_ = nullptr;

 public:
  WeightermDataSqlite();
  ~WeightermDataSqlite() override;
  DataResult RegisterWeight(double weight) override;
  std::vector<WeightMeasure> ListWeights() const override;
  DataResult DeleteWeight(int id) override;
};
#endif  // SRC_WEIGHTERM_DATA_SQLITE_H_
