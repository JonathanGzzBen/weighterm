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
  if (data->RegisterWeight(weight) != DataResult::OK) {
    spdlog::error("Could not register weight");
    return false;
  }
  return true;
}

bool ListWeights(const WeightermData *const weighterm_data) {
  for (const auto &weight : weighterm_data->ListWeights()) {
    spdlog::info("{}", weight);
  }
  return true;
}

bool DeleteWeightMeasurement(WeightermData *weighterm_data, int id) {
  spdlog::info("Deleting weight measure with ID: " + std::to_string(id));
  if (weighterm_data->DeleteWeight(id) != DataResult::OK) {
    spdlog::error("Could not delete weight measurement");
    return false;
  }
  return true;
}

bool ModifyWeightMeasurement(WeightermData *weighterm_data, int id,
                             double weight) {
  spdlog::info("Updating weight measure with ID: " + std::to_string(id));
  switch (weighterm_data->ModifyWeight(id, weight)) {
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
    RegisterWeight(data.get(), std::to_string(weight));
  } else if (list_command) {
    ListWeights(data.get());
  } else if (delete_command) {
    DeleteWeightMeasurement(data.get(), id);
  } else if (modify_command) {
    ModifyWeightMeasurement(data.get(), id, weight);
  } else {
    spdlog::info("Run with --help or -h to see available subcommands.");
  }
  return 0;
}
