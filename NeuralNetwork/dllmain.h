#pragma once
#include <vector>

extern "C" __declspec(dllexport) int __cdecl ProcessNeuralNetwork();
void setCombinations(bool RunCombinations);
extern "C" __declspec(dllexport) int __cdecl Init(char* configFile);
extern "C" __declspec(dllexport) size_t __cdecl getProgress();
extern "C" __declspec(dllexport) size_t __cdecl getDataSize();