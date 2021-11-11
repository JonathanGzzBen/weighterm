#ifndef SRC_WEIGHTERM_DATA_SQLITE_H_
#define SRC_WEIGHTERM_DATA_SQLITE_H_
#include <sqlite3.h>

#include <iostream>
#include <vector>

#include "src/weighterm_data.h"
class WeightermDataSqlite : public WeightermData {
 private:
  DataResult initializeDatabase();
  sqlite3* m_db;

 public:
  WeightermDataSqlite();
  virtual ~WeightermDataSqlite();
  virtual DataResult RegisterWeight(double weight);
  virtual const std::vector<WeightMeasure> ListWeights() const;
};
#endif  // SRC_WEIGHTERM_DATA_SQLITE_H_