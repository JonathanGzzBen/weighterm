#ifndef WEIGHTERM_SRC_WEIGHTERM_CLI_H_
#define WEIGHTERM_SRC_WEIGHTERM_CLI_H_
#include <string>

#include "src/weighterm_data.h"

bool RegisterWeight(WeightermData* data, const std::string& weight_string);
bool ListWeights(const WeightermData* weighterm_data);
bool DeleteWeightMeasurement(WeightermData* weighterm_data, int id);
bool ModifyWeightMeasurement(WeightermData* weighterm_data, int id,
                             double weight);
int HandleCli(int argc, char** argv);
#endif  // WEIGHTERM_SRC_WEIGHTERM_CLI_H_
