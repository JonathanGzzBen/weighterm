#include "src/weighterm_cli.h"

#include <iomanip>
#include <iostream>

#include "spdlog/spdlog.h"

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
