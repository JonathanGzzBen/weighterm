#include "src/weighterm_cli.h"

#include <CLI/CLI.hpp>
#include <iomanip>

#include "data_exception.h"
#include "spdlog/spdlog.h"
#include "weighterm_data_sqlite.h"

bool RegisterWeight(WeightermData *data, const double &weight,
                    const std::string &datetime_str) {
  if (Datetime datetime{datetime_str};
      data->RegisterWeight(weight, datetime) != DataResultCode::OK) {
    spdlog::error("Could not register weight");
    return false;
  }
  return true;
}

bool ListWeights(const WeightermData *const weighterm_data) {
  auto res{weighterm_data->ListWeights()};
  if (res.code != DataResultCode::OK) {
    spdlog::error("Could not fetch weight measurements");
  }
  for (const auto &weight : res.value) {
    std::cout << weight << std::endl;
  }
  return true;
}

bool DeleteWeightMeasurement(WeightermData *weighterm_data, int id) {
  if (weighterm_data->DeleteWeight(id) != DataResultCode::OK) {
    spdlog::error("Could not delete weight measurement");
    return false;
  }
  std::cout << "Deleted weight measurement with ID: " << std::to_string(id)
            << std::endl;
  return true;
}

bool ModifyWeightMeasurement(WeightermData *weighterm_data, int id,
                             double weight, const std::string &datetime_str) {
  Datetime datetime{datetime_str};
  if (datetime_str.empty()) {
    auto weight_in_db = weighterm_data->FindWeight(id);
    if (weight_in_db.code == DataResultCode::NOT_FOUND) {
      spdlog::error("There is no weight measurement with that ID");
      return false;
    }
    datetime = weight_in_db.value.GetDatetime();
  }
  switch (weighterm_data->ModifyWeight(id, weight, datetime)) {
    case DataResultCode::OK:
      std::cout << "Modified weight measurement with ID: " << std::to_string(id)
                << std::endl;
      return true;
    case DataResultCode::NOT_FOUND:
      spdlog::error("There is no weight measurement with that ID");
      break;
    default:
      spdlog::error("Could not update weight measurement");
  }
  return false;
}

int HandleCli(int argc, char **argv) {
  CLI::App cli_global{"weighterm 0.3.0"};
  auto &register_command = *cli_global.add_subcommand(
      "register", "Register a new weight measurement");
  double weight;
  register_command.add_option("weight", weight, "Weight to register")
      ->required()
      ->check(CLI::PositiveNumber);

  auto transform_datetime_modify = CLI::Validator(
      [](std::string &input) {
        try {
          input = Datetime{input}.ToString();
          return std::string();
        } catch (const std::invalid_argument &) {
          auto datetime_time_point{std::chrono::system_clock::now()};
          if (input == "yesterday") {
            datetime_time_point -= std::chrono::days(1);
          } else if (input != "now") {
            return std::string{
                "Specify a valid datetime (\"now\", \"yesterday\", "
                "\"2021-12-31 "
                "12:00:00\")"};
          }
          input = Datetime{std::chrono::system_clock::to_time_t(
                               datetime_time_point)}
                      .ToString();
          return std::string();
        }
      },
      "DATETIME", "Datetime transformer");
  std::string datetime_str{};
  register_command
      .add_option("datetime", datetime_str, "Datetime of weight measurement")
      ->transform(transform_datetime_modify);

  auto const &list_command =
      *cli_global.add_subcommand("list", "List registered weight measurements");

  auto &delete_command = *cli_global.add_subcommand(
      "delete", "Delete specific weight measurement");
  int id;
  delete_command.add_option("ID", id, "ID of weight measurement to delete")
      ->required()
      ->check(CLI::PositiveNumber);
  auto &modify_command = *cli_global.add_subcommand(
      "modify", "Modify specific weight measurement");
  modify_command.add_option("ID", id, "ID of weight measurement to modify")
      ->required()
      ->check(CLI::PositiveNumber);
  modify_command.add_option("weight", weight, "New weight")
      ->required()
      ->check(CLI::PositiveNumber);

  modify_command
      .add_option("datetime", datetime_str, "Datetime of weight measurement")
      ->transform(transform_datetime_modify);

  CLI11_PARSE(cli_global, argc, argv) std::unique_ptr<WeightermData> data;
  try {
    data = std::make_unique<WeightermDataSqlite>();
  } catch (const DataException &e) {
    spdlog::error(e.what());
  }
  if (register_command) {
    RegisterWeight(data.get(), weight, datetime_str);
  } else if (list_command) {
    ListWeights(data.get());
  } else if (delete_command) {
    DeleteWeightMeasurement(data.get(), id);
  } else if (modify_command) {
    ModifyWeightMeasurement(data.get(), id, weight, datetime_str);
  } else {
    std::cout << "Run with --help or -h to see available subcommands."
              << std::endl;
  }
  return 0;
}
