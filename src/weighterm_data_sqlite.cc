#include "src/weighterm_data_sqlite.h"

#include <sqlite3.h>

#include <chrono>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

#include "spdlog/spdlog.h"
#include "src/data_exception.h"

DataResult WeightermDataSqlite::InitializeDatabase() {
  auto result_code = sqlite3_open("weighterm.db", &db_);
  if (result_code != SQLITE_OK) {
    std::stringstream error_message;
    error_message << "Error opening DB: " << sqlite3_errmsg(db_);
    spdlog::error(error_message.str());
    return DataResult::COULD_NOT_OPEN_DATABASE;
  } else {
    spdlog::info("Opened database successfully");

    char* error_message = nullptr;

    sqlite3_exec(db_, R"(
CREATE TABLE weight(
    ID INTEGER PRIMARY KEY AUTOINCREMENT,
    Kg REAL NOT NULL,
    Datetime TEXT
);
    )",
                 nullptr, nullptr, &error_message);

    if (error_message != nullptr) {
      std::string str_error_message{error_message};
      if (str_error_message != "table weight already exists") {
        spdlog::error(error_message);
        sqlite3_free(error_message);
        return DataResult::COULD_NOT_OPEN_DATABASE;
      }
    }

    return DataResult::OK;
  }
}

WeightermDataSqlite::WeightermDataSqlite() : WeightermData() {
  auto result = InitializeDatabase();
  if (result != DataResult::OK) {
    throw DataException{"Could not initialize database"};
  }
}

WeightermDataSqlite::~WeightermDataSqlite() {
  sqlite3_close(db_);
  spdlog::info("Database connection closed");
}

DataResult WeightermDataSqlite::RegisterWeight(double weight) {
  char* error_message = nullptr;
  auto time_t_now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  Datetime datetime{time_t_now};
  std::stringstream insert_statement_sql{};
  insert_statement_sql << "INSERT INTO weight(Kg, Datetime) VALUES (" << weight
                       << ",\"" << datetime.ToString() << "\");";
  spdlog::info(insert_statement_sql.str());
  if (auto rc{sqlite3_exec(db_, insert_statement_sql.str().c_str(), nullptr,
                           nullptr, &error_message)};
      rc != SQLITE_OK) {
    std::string str_error_message{error_message};
    sqlite3_free(error_message);
    return DataResult::COULD_NOT_OPEN_DATABASE;
  }
  return DataResult::OK;
}

std::vector<WeightMeasure> WeightermDataSqlite::ListWeights() const {
  std::vector<WeightMeasure> results{};
  char* error_message = nullptr;
  if (auto rc = sqlite3_exec(
          db_, R"(
      SELECT ID, Kg, Datetime FROM weight;
);
    )",
          [](void* weight_measures_vector_ptr, int argc, char** argv,
             char** az_col_name) {
            std::map<std::string, std::string> values{};
            for (int i{0}; i < argc; i++) {
              values[az_col_name[i]] = argv[i];
            }
            auto results_ptr = static_cast<std::vector<WeightMeasure>*>(
                weight_measures_vector_ptr);
            results_ptr->emplace_back(std::stoi(values.at("ID")),
                                      std::stof(values.at("Kg")),
                                      Datetime{values.at("Datetime")});
            return 0;
          },
          &results, &error_message);
      rc != SQLITE_OK) {
    sqlite3_free(error_message);
  }
  return results;
}
DataResult WeightermDataSqlite::DeleteWeight(int id) {
  char* error_message = nullptr;
  std::stringstream count_statement_sql{};
  count_statement_sql << "SELECT COUNT(*) FROM weight WHERE ID=" << id << ";";
  int rows_found{0};
  auto rc = sqlite3_exec(
      db_, count_statement_sql.str().c_str(),
      [](void* rows_found, int argc, char** argv, char**) {
        if (argc == 1 && argv) {
          *static_cast<int*>(rows_found) = std::stoi(argv[0]);
        }
        return 0;
      },
      &rows_found, &error_message);

  if (rc != SQLITE_OK || rows_found <= 0) {
    sqlite3_free(error_message);
    return DataResult::NOT_FOUND;
  }

  std::stringstream insert_statement_sql{};
  insert_statement_sql << "DELETE FROM weight WHERE ID=" << id << ";";
  spdlog::info(insert_statement_sql.str());
  rc = sqlite3_exec(
      db_, insert_statement_sql.str().c_str(),
      [](void* const, int, char**, char**) { return 0; }, nullptr,
      &error_message);
  if (rc != SQLITE_OK) {
    sqlite3_free(error_message);
    return DataResult::COULD_NOT_RUN_QUERY;
  }
  return DataResult::OK;
}

DataResult WeightermDataSqlite::ModifyWeight(int id, double weight,
                                             Datetime datetime) {
  char* error_message = nullptr;
  std::string count_statement_sql{
      "SELECT COUNT(*) FROM weight WHERE ID=" + std::to_string(id) + ";"};
  int rows_found{0};
  auto rc = sqlite3_exec(
      db_, count_statement_sql.c_str(),
      [](void* rows_found, int argc, char** argv, char**) {
        if (argc == 1 && argv) {
          *static_cast<int*>(rows_found) = std::stoi(argv[0]);
        }
        return 0;
      },
      &rows_found, &error_message);

  if (rc != SQLITE_OK || rows_found <= 0) {
    sqlite3_free(error_message);
    return DataResult::NOT_FOUND;
  }

  std::string update_statement_sql{
      "UPDATE weight SET Kg=" + std::to_string(weight) + ", Datetime=(\"" +
      datetime.ToString() + "\") WHERE ID=" + std::to_string(id) + ";"};
  spdlog::info(update_statement_sql);
  rc = sqlite3_exec(db_, update_statement_sql.c_str(), nullptr, nullptr,
                    &error_message);
  if (rc != SQLITE_OK) {
    sqlite3_free(error_message);
    return DataResult::COULD_NOT_RUN_QUERY;
  }
  return DataResult::OK;
}
