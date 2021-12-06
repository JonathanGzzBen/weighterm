#include "src/weighterm_cli.h"

#include <CLI/CLI.hpp>
#include <iomanip>
#include <iostream>

#include "data_exception.h"
#include "spdlog/spdlog.h"
#include "weighterm_data_sqlite.h"

bool RegisterWeight(WeightermData *data, const std::string &weight_string) {
  double weight;
  try {
    weight = std::stod(weight_string);
  } catch (const std::invalid_argument &) {
    spdlog::error("Weight must be a numeric value");
    return false;
  } catch (const std::out_of_range &) {
    spdlog::error("Weight out of range");
    return false;
  }
  auto result{data->RegisterWeight(weight)};
  if (result != DataResult::OK) {
    spdlog::error("Could not register weight");
    return false;
  }
  return true;
}

bool ListWeights(const WeightermData *const weighterm_data) {
  auto weight_measures{weighterm_data->ListWeights()};
  for (const auto &weight : weight_measures) {
    auto datetime = weight.GetDatetime();
    std::stringstream time_stream{};
    time_stream << std::put_time(std::localtime(&datetime), "%F %T");
    std::cout << "ID: " << std::setw(4) << std::left << weight.GetId()
              << "Weight: " << std::setw(5) << weight.GetWeight()
              << "Datetime: " << time_stream.str() << std::endl;
  }
  return true;
}

bool DeleteWeightMeasurement(WeightermData *weighterm_data, int id) {
  spdlog::info("Deleting weight measure with ID: " + std::to_string(id));
  auto const kResult{weighterm_data->DeleteWeight(id)};
  if (kResult != DataResult::OK) {
    spdlog::error("Could not delete weight measurement");
    return false;
  }
  return true;
}

bool ModifyWeightMeasurement(WeightermData *weighterm_data, int id,
                             double weight) {
  spdlog::info("Updating weight measure with ID: " + std::to_string(id));
  auto const kResult{weighterm_data->ModifyWeight(id, weight)};
  switch (kResult) {
    case DataResult::OK:
      spdlog::info("Weight measurement updated");
      return true;
    case DataResult::NOT_FOUND:
      spdlog::error("There is no weight measurement with that ID");
      break;
    default:
      spdlog::error("Could not update weight measurement");
  }
  return false;
}

int HandleCli(int argc, char **argv) {
  CLI::App cli_global{"weighterm 0.2"};
  auto &register_command = *cli_global.add_subcommand(
      "register", "Register a new weight measurement");
  double weight;
  register_command.add_option("weight", weight, "Weight to register")
      ->required()
      ->check(CLI::PositiveNumber);
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

  CLI11_PARSE(cli_global, argc, argv)
  std::unique_ptr<WeightermData> data;
  try {
    data = std::make_unique<WeightermDataSqlite>();
  } catch (const DataException &e) {
    spdlog::error(e.what());
  }
  if (register_command) {
    const auto kWeightStr{std::to_string(weight)};
    RegisterWeight(data.get(), kWeightStr);
  } else if (list_command) {
    ListWeights(data.get());
  } else if (delete_command) {
    DeleteWeightMeasurement(data.get(), id);
  } else if (modify_command) {
    ModifyWeightMeasurement(data.get(), id, weight);
  } else {
    std::cout << "Run with --help or -h to see available subcommands."
              << std::endl;
  }
  return 0;
}
