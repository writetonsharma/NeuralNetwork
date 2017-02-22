#pragma once

#include "miscdef.h"



void preprocess(void);
void readFile(std::vector<std::string>& lineBuffer);
void processIndicators(const std::vector<std::string>& lineBuffer, std::vector<std::vector<double> >& slicedData);
double toNumericDate(std::string& str);
void fillMonthIndex();
void processIndicatorsForRow(std::vector<std::vector<double> >& slicedData, std::vector<double>& temp, size_t index);


// indicator calculators

// today's close price - previous close price
double tcpMinuspcp(std::vector<std::vector<double> >& slicedData, std::vector<double>& temp, size_t index);
// previous close price
double pcp(std::vector<std::vector<double> >& slicedData, size_t index);
// previous highest price
double php(std::vector<std::vector<double> >& slicedData, size_t index);
// previous lowest price
double plp(std::vector<std::vector<double> >& slicedData, size_t index);
// previous open price
double pop(std::vector<std::vector<double> >& slicedData, size_t index);

// simple moving average for time period
// curr_index - present day
// col_index - like closing price, lowest price etc
// time_preiod - how many previous days to calculate
double simpleMovingAverage(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// exponential moving average for time period
double exponentialMovingAverage(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	size_t col_index_not_exist,
	int time_period);

// Triangular Moving Average for time period
double triangularMovingAverage(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// ADL
double accumulationDistributionLine(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index);

// moving average convergence/divergence
double movingAverageConvergenceDivergence(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index);

// Acceleration of price index
double accelerationOscillator(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// momentum Oscillator
double momentumOscillator(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// chaikin volatility
double chaikinvolatility(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index);

// Fast stochastic %K, default is 14 days
double fastStochasticPercentK(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period = 14);

// Fast stochastic %D, default is 14 days
double fastStochasticPercentD(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period = 14);

// Slow stochastic %K, default is 14 days
double slowStochasticPercentK(std::vector<double>& temp);

// Slow stochastic %D, default is 14 days
double slowStochasticPercentD(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period);

// Williams %R
double williamsRPercent(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period = 14);

double relativeStrengthIndex(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period = 14);

void averageGainLoss(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	double& avgGain,
	double& avgLoss,
	int time_period);

// standard deviation
double stdDeviation(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// Bollinger Middle Band
double bollingerMiddleBand(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// Bollinger Higher Band
double bollingerHigherBand(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

// Bollinger Lower Band
double bollingerLowerBand(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

double highestHigh(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

double lowestLow(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period);

