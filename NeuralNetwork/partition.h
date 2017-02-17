#pragma once

#include "miscdef.h"
#include "CMatrix.h"

bool partition(double trainPercent);
bool writeData(std::vector<std::string> lineBuffer, std::string file, size_t lineFrom, size_t lineTo);