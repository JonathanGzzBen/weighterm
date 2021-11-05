#include "weighterm_data_sqlite.h"

#include <sqlite3.h>

#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "data_exception.h"

DataResult WeightermDataSqlite::initializeDatabase() {
  auto result_code = sqlite3_open("weighterm.db", &m_db);
  if (result_code != SQLITE_OK) {
    std::cerr << "Error opening DB " << sqlite3_errmsg(m_db) << std::endl;
    return DataResult::CouldNotOpenDatabase;
  } else {
    std::cout << "Opened database succesfully" << std::endl;

    char* errorMessage = NULL;

    sqlite3_exec(m_db, R"(
CREATE TABLE weight(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Kg REAL NOT NULL
);
    )",
                 NULL, NULL, &errorMessage);

    if (errorMessage != NULL) {
      std::string strErrorMessage{errorMessage};
      if (strErrorMessage != "table weight already exists") {
        std::cout << errorMessage << std::endl;
        sqlite3_free(errorMessage);
        return DataResult::CouldNotOpenDatabase;
      }
    }

    return DataResult::Ok;
  }
}

WeightermDataSqlite::WeightermDataSqlite() : WeightermData() {
  auto result = initializeDatabase();
  if (result != DataResult::Ok) {
    throw DataException{"Could not initialize database"};
  }
}

WeightermDataSqlite::~WeightermDataSqlite() {
  sqlite3_close(m_db);
  std::cout << "Database connection closed" << std::endl;
}

DataResult WeightermDataSqlite::RegisterWeight(double weight) {
  char* errorMessage = NULL;
  std::stringstream insert_statement_sql{};
  std::cout << insert_statement_sql.str() << std::endl;
  int rc = sqlite3_exec(m_db, insert_statement_sql.str().c_str(), NULL, NULL,
                        &errorMessage);
  if (rc != SQLITE_OK) {
    std::string strErrorMessage{errorMessage};
    return DataResult::CouldNotOpenDatabase;
    sqlite3_free(errorMessage);
  }
  return DataResult::Ok;
}

const std::vector<WeightMeasure> WeightermDataSqlite::ListWeights() const {
  std::vector<WeightMeasure> results{};
  char* errorMessage = NULL;
  int rc = sqlite3_exec(
      m_db, R"(
      SELECT ID, kg FROM weight;
);
    )",
      [](void* weightMeasuresVectorPtr, int argc, char** argv,
         char** azColName) {
        std::map<std::string, std::string> values{};
        for (int i{0}; i < argc; i++) {
          values[azColName[i]] = argv[i];
        }
        auto resultsPtr =
            static_cast<std::vector<WeightMeasure>*>(weightMeasuresVectorPtr);
        resultsPtr->emplace_back(std::stoi(values.at("ID")),
                                 std::stof(values.at("Kg")));
        return 0;
      },
      &results, &errorMessage);
  if (rc != SQLITE_OK) {
    sqlite3_free(errorMessage);
  }
  return results;
}
