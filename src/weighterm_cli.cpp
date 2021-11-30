#include "src/weighterm_cli.h"

#include <CLI/CLI.hpp>
#include <iomanip>
#include <iostream>

#include "data_exception.h"
#include "spdlog/spdlog.h"
#include "weighterm_data_sqlite.h"

bool RegisterWeight(WeightermData* data, const std::string& weight_string) {
  double weight;
  try {
    weight = std::stod(weight_string);
  } catch (const std::invalid_argument&) {
    spdlog::error("Weight must be a numeric value");
    return false;
  } catch(const std::out_of_range&) {
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

bool ListWeights(const WeightermData* const weighterm_data) {
  auto weight_measures{weighterm_data->ListWeights()};
  for (const auto& weight : weight_measures) {
    std::cout << "ID: " << std::setw(4) << std::left << weight.GetId()
              << "Weight: " << weight.GetWeight() << std::endl;
  }
  return true;
}
int HandleCli(int argc, char **argv){
  CLI::App cli_global{"weighterm 0.1"};
  auto &register_command = *cli_global.add_subcommand(
      "register", "Register a new weight measurement");
  double weight;
  register_command.add_option("weight", weight, "Weight to register")
      ->required();
  auto const &list_command =
      *cli_global.add_subcommand("list", "List registered weight measurements");
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
  }
  if (list_command) {
    ListWeights(data.get());
  }
  return 0;
}
