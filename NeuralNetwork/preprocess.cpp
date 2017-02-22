
#include "preprocess.h"
#include "CNeuralNetwork.h"
#include "miscdef.h"
#include "CFile.h"
#include "CConfig.h"
#include "IniSettings.h"

bool	dateColumn[] = { 1,0,0,0,0,0 };
std::map<std::string, std::string> monthIndex;
std::string header = "FCP,Date,Open,High,Low,Close,Volume,\
TCP-PCP,PCP,PHP,PLP,POP,\
5D SMA PCP,6D SMA PCP,10D SMA PCP,20D SMA PCP,50D SMA PCP,200D SMA PCP,\
5D EMA PCP,6D EMA PCP,10D EMA PCP,20D EMA PCP,50D EMA PCP,200D EMA PCP,\
5D TMA PCP,6D TMA PCP,10D TMA PCP,20D TMA PCP,50D TMA PCP,200D TMA PCP,\
ADL,MACD,\
5D ACC PCP,6D ACC PCP,10D ACC PCP,20D ACC PCP,50D ACC PCP,200D ACC PCP,\
5D MOM PCP, 6D MOM PCP, 10D MOM PCP, 20D MOM PCP, 50D MOM PCP, 200D MOM PCP,\
Chaikin Volatility,Fast Stochastic%K,Fast Stochastic%D,Slow Stochastic%K,Slow Stochastic%D,\
William's %R,Relative Strength Index,Bollinger Middle Band,Bollinger Higher Band,Bollinger Lower Band,\
5D HH,6D HH,10D HH,20D HH,50D HH,200D HH,5D LL,6D LL,10D LL,20D LL,50D LL,200D LL";

double prevAvgGain = 0.0;
double prevAvgLoss = 0.0;

std::map<int, double>	maxValMap;
std::map<int, double>	minValMap;
size_t recordCount = 0;


// read the data file

void readFile(std::vector<std::string>& lineBuffer)
{
	// Read
	
	try
	{
		CFile cfile(CConfig::getInstance()->getValue(InputFile), OpenType::CF_READ);
		cfile.skipRows(1);
		cfile.readFile(lineBuffer);
		cfile.close();
	}
	catch (std::exception&)
	{
		return;
	}
}

void preprocess(void)
{

	remove(CConfig::getInstance()->getValue(IndicatorsFile).c_str());
	fillMonthIndex();

	std::vector<std::string> lineBuffer;
	readFile(lineBuffer);

	// create indicators
	std::vector<std::vector<double> > indicators;
	processIndicators(lineBuffer, indicators);
	lineBuffer.clear();

	recordCount = indicators.size();

	//stream out indicators
	try
	{
		CFile cfile(CConfig::getInstance()->getValue(IndicatorsFile), OpenType::CF_WRITE);
		cfile.writeFile(header);
		std::string str = "\n";
		cfile.writeFile(str);
		for (size_t i = atoi(CConfig::getInstance()->getValue(PreviousDays).c_str()); i < (indicators.size() - 1); i++)
		{
			std::vector<double>& row = indicators[i];
			// first column will be result
			// don't write last result, there is no result for today (we do not know tomorrow's value)
			if (indicators[i][atoi(CConfig::getInstance()->getValue(CLOSE_INDEX).c_str())] 
				<= indicators[i + 1][atoi(CConfig::getInstance()->getValue(CLOSE_INDEX).c_str())])
			{
				// going up
				str = "1,";
				cfile.writeFile(str);
			}
			else
			{
				// going down
				str = "0,";
				cfile.writeFile(str);
			}
			cfile.writeFile(row);
		}

		// write
		cfile.close();
	}
	catch (std::exception&)
	{
		return;
	}

	indicators.clear();
}


void processIndicators(const std::vector<std::string>& lineBuffer, std::vector<std::vector<double> >& slicedData)
{
	size_t len = lineBuffer.size();

	assert(lineBuffer.size() > (size_t)(atoi(CConfig::getInstance()->getValue(PreviousDays).c_str())));

	// skip first row and previous days.
	for (size_t i = 0; i < len; i++)
	{
		std::vector<double> temp;
		std::string str = lineBuffer[i];
		size_t ti = 0;
		std::string t_str;
		bool first_column = true;
		size_t col = 0;
		for (size_t j = 0; j < str.length(); j++)
		{
			char c = str[j];
			if (c == ',')
			{
				double val = dateColumn[col++] ? toNumericDate(t_str) : atof(t_str.c_str());
				temp.push_back(val);
				t_str.clear();
				continue;
			}
			else
			{
				t_str += c;
			}

		}

		double val = dateColumn[col++] ? toNumericDate(t_str) : atof(t_str.c_str());
		temp.push_back(val);

		if (i >= (size_t)atoi(CConfig::getInstance()->getValue(PreviousDays).c_str()))
		{
			// process rest of the indicators
			processIndicatorsForRow(slicedData, temp, i);
		}

		slicedData.push_back(temp);
		temp.clear();
	}

	// get the max for each column
	maxValMap.insert(std::pair<int, double>(0, 1));
	size_t two_hd_ll = (size_t)atoi(CConfig::getInstance()->getValue(TWO_HD_LOWEST_LOW_INDEX).c_str());
	for (size_t i = 0; i <= two_hd_ll; i++)
	{
		std::vector<double> temp;
		double hh = max(slicedData, i, atoi(CConfig::getInstance()->getValue(PreviousDays).c_str()), slicedData.size() - 1);
		maxValMap.insert(std::pair<int, double>(i+1, hh));
	}

	minValMap.insert(std::pair<int, double>(0, 0));
	for (size_t i = 0; i <= two_hd_ll; i++)
	{
		std::vector<double> temp;
		double ll = min(slicedData, i, atoi(CConfig::getInstance()->getValue(PreviousDays).c_str()), slicedData.size() - 1);
		minValMap.insert(std::pair<int, double>(i + 1, ll));
	}

}

double toNumericDate(std::string& str)
{
	size_t hiphen1 = str.find('-');
	size_t hiphen2 = str.find_last_of('-');

	std::string day = (hiphen1 == 1) ? "0" + str.substr(0, hiphen1) : str.substr(0, hiphen1);
	std::string month = str.substr((hiphen1 + 1), hiphen2 - hiphen1 - 1);
	month = monthIndex[month];
	std::string year = "20" + str.substr(hiphen2 + 1);
	std::string strDate = year + month + day;
	double date = atoi(strDate.c_str());;
	
	//std::string month = monthIndex(str.substr())
	return date;
}

void fillMonthIndex()
{
	monthIndex.insert(std::pair<std::string, std::string>("Jan", "01"));
	monthIndex.insert(std::pair<std::string, std::string>("Feb", "02"));
	monthIndex.insert(std::pair<std::string, std::string>("Mar", "03"));
	monthIndex.insert(std::pair<std::string, std::string>("Apr", "04"));
	monthIndex.insert(std::pair<std::string, std::string>("May", "05"));
	monthIndex.insert(std::pair<std::string, std::string>("jun", "06"));
	monthIndex.insert(std::pair<std::string, std::string>("Jul", "07"));
	monthIndex.insert(std::pair<std::string, std::string>("Aug", "08"));
	monthIndex.insert(std::pair<std::string, std::string>("Sep", "09"));
	monthIndex.insert(std::pair<std::string, std::string>("Oct", "10"));
	monthIndex.insert(std::pair<std::string, std::string>("Nov", "11"));
	monthIndex.insert(std::pair<std::string, std::string>("Dec", "12"));
}

void processIndicatorsForRow(std::vector<std::vector<double> >& slicedData, std::vector<double>& temp, size_t index)
{
	temp.push_back(tcpMinuspcp(slicedData, temp, index));
	temp.push_back(pcp(slicedData, index));
	temp.push_back(php(slicedData, index));
	temp.push_back(plp(slicedData, index));
	temp.push_back(pop(slicedData, index));


	// simple moving averages
	temp.push_back(simpleMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 5));
	temp.push_back(simpleMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 6));
	temp.push_back(simpleMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 10));
	temp.push_back(simpleMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));
	temp.push_back(simpleMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 50));
	temp.push_back(simpleMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 200));

	// exponential moving averages
	temp.push_back(exponentialMovingAverage(slicedData, temp, index, 
		atoi(CConfig::getInstance()->getValue(FIVE_DAY_EMA_CLOSING_INDEX).c_str()),	CConfig::getInstance()->getCloseIndex(), 5));
	temp.push_back(exponentialMovingAverage(slicedData, temp, index, 
		atoi(CConfig::getInstance()->getValue(SIX_DAY_EMA_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 6));
	temp.push_back(exponentialMovingAverage(slicedData, temp, index, 
		atoi(CConfig::getInstance()->getValue(TEN_DAY_EMA_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 10));
	temp.push_back(exponentialMovingAverage(slicedData, temp, index, 
		atoi(CConfig::getInstance()->getValue(TWENTY_DAY_EMA_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 20));
	temp.push_back(exponentialMovingAverage(slicedData, temp, index, 
		atoi(CConfig::getInstance()->getValue(FIFTY_DAY_EMA_CLOSING_INDEX).c_str()),CConfig::getInstance()->getCloseIndex(), 50));
	temp.push_back(exponentialMovingAverage(slicedData, temp, index, 
		atoi(CConfig::getInstance()->getValue(TWO_H_DAY_EMA_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 200));

	// Triangular Moving Average
	temp.push_back(triangularMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 5));
	temp.push_back(triangularMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 6));
	temp.push_back(triangularMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 10));
	temp.push_back(triangularMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));
	temp.push_back(triangularMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 50));
	temp.push_back(triangularMovingAverage(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 200));

	// ADL
	temp.push_back(accumulationDistributionLine(slicedData, temp, index));

	//MACD
	temp.push_back(movingAverageConvergenceDivergence(slicedData, temp, index));

	// 9 period EMA on MACD ?? need to calculate.

	// accelerated close price
	temp.push_back(accelerationOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 5));
	temp.push_back(accelerationOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 6));
	temp.push_back(accelerationOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 10));
	temp.push_back(accelerationOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));
	temp.push_back(accelerationOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 50));
	temp.push_back(accelerationOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 200));

	// momentum close price
	temp.push_back(momentumOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 5));
	temp.push_back(momentumOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 6));
	temp.push_back(momentumOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 10));
	temp.push_back(momentumOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));
	temp.push_back(momentumOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 50));
	temp.push_back(momentumOscillator(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 200));

	// chaikinvolatility
	temp.push_back(chaikinvolatility(slicedData, temp, index));

	// Fast stochastic %K
	temp.push_back(fastStochasticPercentK(slicedData, temp, index, 14));

	// Fast stochastic %D
	temp.push_back(fastStochasticPercentD(slicedData, temp, index, 14));

	// Slow stochastic %K
	temp.push_back(slowStochasticPercentK(temp));

	// Slow stochastic %D
	temp.push_back(slowStochasticPercentD(slicedData, temp, index, 14));

	// Williams %R
	temp.push_back(williamsRPercent(slicedData, temp, index, 14));
	
	// RSI
	temp.push_back(relativeStrengthIndex(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 14));
	
	// Bollinger Middle Band
	temp.push_back(bollingerMiddleBand(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));

	// Bollinger Higher Band
	temp.push_back(bollingerHigherBand(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));

	// Bollinger Lower Band
	temp.push_back(bollingerLowerBand(slicedData, temp, index, CConfig::getInstance()->getCloseIndex(), 20));

	// highest high
	temp.push_back(highestHigh(slicedData, temp, index, CConfig::getInstance()->getHighIndex(), 5));
	temp.push_back(highestHigh(slicedData, temp, index, CConfig::getInstance()->getHighIndex(), 6));
	temp.push_back(highestHigh(slicedData, temp, index, CConfig::getInstance()->getHighIndex(), 10));
	temp.push_back(highestHigh(slicedData, temp, index, CConfig::getInstance()->getHighIndex(), 20));
	temp.push_back(highestHigh(slicedData, temp, index, CConfig::getInstance()->getHighIndex(), 50));
	temp.push_back(highestHigh(slicedData, temp, index, CConfig::getInstance()->getHighIndex(), 200));

	// lowest low
	temp.push_back(lowestLow(slicedData, temp, index, CConfig::getInstance()->getLowIndex(), 5));
	temp.push_back(lowestLow(slicedData, temp, index, CConfig::getInstance()->getLowIndex(), 6));
	temp.push_back(lowestLow(slicedData, temp, index, CConfig::getInstance()->getLowIndex(), 10));
	temp.push_back(lowestLow(slicedData, temp, index, CConfig::getInstance()->getLowIndex(), 20));
	temp.push_back(lowestLow(slicedData, temp, index, CConfig::getInstance()->getLowIndex(), 50));
	temp.push_back(lowestLow(slicedData, temp, index, CConfig::getInstance()->getLowIndex(), 200));
}

double tcpMinuspcp(std::vector<std::vector<double> >& slicedData, std::vector<double>& temp, size_t index)
{
	return temp[CConfig::getInstance()->getCloseIndex()] - slicedData[index - 1][CConfig::getInstance()->getCloseIndex()];
}

double pcp(std::vector<std::vector<double> >& slicedData, size_t index)
{
	return slicedData[index - 1][CConfig::getInstance()->getCloseIndex()];
}

double php(std::vector<std::vector<double> >& slicedData, size_t index)
{
	return slicedData[index - 1][CConfig::getInstance()->getHighIndex()];
}

double plp(std::vector<std::vector<double> >& slicedData, size_t index)
{
	return slicedData[index - 1][CConfig::getInstance()->getLowIndex()];
}

double pop(std::vector<std::vector<double> >& slicedData, size_t index)
{
	return slicedData[index - 1][CConfig::getInstance()->getLowIndex()];
}

double simpleMovingAverage(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	double sma = 0.0;

	// last (prev_day_count - 1) + current_day (from temp)
	// 5D SMA = average(previous 4 days closing prices + current day closing price)
	for (size_t i = (curr_index - time_period + 1); i < curr_index; i++)
	{
		sma += slicedData[i][col_index];
	}
	sma += temp[col_index];
	sma /= time_period;

	return sma;
}

double exponentialMovingAverage(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	size_t col_index_not_exist,
	int time_period)
{
	double ema = 0.0;

	// first EMA will be equal to SMA
	// if SMA are not found for previous day, its the first time
	if (slicedData[curr_index - 1].size() < col_index)
	{
		ema = simpleMovingAverage(slicedData, temp, curr_index, col_index_not_exist, time_period);		// EMA = SMA
	}
	else
	{
		// weight * (close_price - previous_EMA) + previous_EMA
		double weight = (2.0 / (time_period + 1.0));
		ema = (weight *(temp[CConfig::getInstance()->getCloseIndex()] - slicedData[curr_index - 1][col_index])) + slicedData[curr_index - 1][col_index];
	}

	return ema;
}

// Average of SMA
double triangularMovingAverage(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	double tma = 0.0;

	// Average(SMA[i]), where I goes from 1 to time_period
	for (int i = 1; i <= time_period; i++)
	{
		tma += simpleMovingAverage(slicedData, temp, curr_index, col_index, i);
	}
	tma /= time_period;

	return tma;
}

/*
1. Money Flow Multiplier (MFM) = [(Close  -  Low) - (High - Close)] /(High - Low)
2. Money Flow Volume (MFV) = Money Flow Multiplier x Volume
3. ADL = Previous ADL + Current Period's Money Flow Volume
*/
double accumulationDistributionLine(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index)
{
	double adl = 0.0;

	// step-1
	double MFM = ((temp[CConfig::getInstance()->getCloseIndex()] 
		- temp[CConfig::getInstance()->getLowIndex()]) - (temp[CConfig::getInstance()->getHighIndex()]
		- temp[CConfig::getInstance()->getCloseIndex()])) / (temp[CConfig::getInstance()->getHighIndex()] 
		- temp[CConfig::getInstance()->getLowIndex()]);
	double MFV = MFM * temp[atoi(CConfig::getInstance()->getValue(VOL_INDEX).c_str())];

	// first ADL will be equal to MFV
	// if ADL are not found for previous day, its the first time
	if (slicedData[curr_index - 1].size() < (size_t)atoi(CConfig::getInstance()->getValue(ADL_CLOSING_INDEX).c_str()))
	{
		adl = MFV;		// ADL = MFV
	}
	else
	{
		// MFV + previous ADL
		adl = MFV + slicedData[curr_index - 1][atoi(CConfig::getInstance()->getValue(ADL_CLOSING_INDEX).c_str())];
	}

	return adl;
}


double movingAverageConvergenceDivergence(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index)
{
	//12D EMA - 26D EMA
	return exponentialMovingAverage(slicedData, temp, curr_index, 
		atoi(CConfig::getInstance()->getValue(MACD_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 12) -
		exponentialMovingAverage(slicedData, temp, curr_index, 
			atoi(CConfig::getInstance()->getValue(MACD_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 26);
}

double accelerationOscillator(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	// (close price[current period] - Close price time_period ago)/time_period;
	return (temp[col_index] - slicedData[curr_index - time_period + 1][col_index]) / time_period;
}

double momentumOscillator(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	// ((close price[current period] - Close price time_period ago)/Close price time_period ago)*100;
	return ((temp[col_index] - slicedData[curr_index - time_period + 1][col_index]) / slicedData[curr_index - time_period + 1][col_index]) * 100;
}

/*
1. Chaikin Oscillator = (3-day EMA of ADL)  -  (10-day EMA of ADL)
// refer calculation of ADL & EMA
*/
double chaikinvolatility(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index)
{
	return exponentialMovingAverage(slicedData, temp, curr_index, 
		atoi(CConfig::getInstance()->getValue(ADL_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 3) -
		exponentialMovingAverage(slicedData, temp, curr_index, 
			atoi(CConfig::getInstance()->getValue(ADL_CLOSING_INDEX).c_str()), CConfig::getInstance()->getCloseIndex(), 10);
}


double fastStochasticPercentK(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period)
{
	// (Current Close - Lowest Low)/(Highest High - Lowest Low) * 100
	double hh = max(slicedData, CConfig::getInstance()->getHighIndex(), (curr_index - 1) - (time_period - 2), curr_index - 1);
	if (temp[CConfig::getInstance()->getHighIndex()] > hh)
	{
		hh = temp[CConfig::getInstance()->getHighIndex()];
	}
	
	double ll = min(slicedData, CConfig::getInstance()->getLowIndex(), (curr_index - 1) - (time_period - 2), curr_index - 1);
	if (temp[CConfig::getInstance()->getLowIndex()] < ll)
	{
		ll = temp[CConfig::getInstance()->getLowIndex()];
	}

	return ((temp[CConfig::getInstance()->getCloseIndex()]- ll)/(hh - ll))*100;
}

double fastStochasticPercentD(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period)
{
	// 3 - day SMA of fast %K
	double percentD = 0.0;

	// for current period
	percentD += temp[atoi(CConfig::getInstance()->getValue(FAST_STOCHASTIC_PERCENTK).c_str())];

	// %K for previous 2 day period
	for (int i = 1; i < 3; i++)
	{
		double hh = max(slicedData, CConfig::getInstance()->getHighIndex(), (curr_index - 1 - i) - (time_period - 1 - i), curr_index - 1 - i);
		double ll = min(slicedData, CConfig::getInstance()->getLowIndex(), (curr_index - 1 - i) - (time_period - 1 - i), curr_index - 1 - i);
		percentD += ((slicedData[curr_index - i][CConfig::getInstance()->getCloseIndex()] - ll) / (hh - ll)) * 100;
	}
	percentD /= 3;

	return percentD;
}

double slowStochasticPercentK(std::vector<double>& temp)
{
	// equals current Fast stochastic %D
	return temp[atoi(CConfig::getInstance()->getValue(FAST_STOCHASTIC_PERCENTD).c_str())];
}

double slowStochasticPercentD(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period)
{
	// Slow %D = 3 - period SMA of Slow %K
	// Slow %K = Fast %D
	// which means, 3-period Fast %D SMA
	double percentD = 0.0;
	for (int i = 0; i < 3; i++)
	{
		percentD += fastStochasticPercentD(slicedData, temp, curr_index - i, time_period);
	}
	percentD /= 3;

	return percentD;
}

double williamsRPercent(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	int time_period)
{
	//%R = (Highest High - Close) / (Highest High - Lowest Low) * -100
	// default is 14 days period

	double hh = max(slicedData, CConfig::getInstance()->getHighIndex(), (curr_index - 1) - (time_period - 2), curr_index - 1);
	if (temp[CConfig::getInstance()->getHighIndex()] > hh)
	{
		hh = temp[CConfig::getInstance()->getHighIndex()];
	}

	double ll = min(slicedData, CConfig::getInstance()->getLowIndex(), (curr_index - 1) - (time_period - 2), curr_index - 1);
	if (temp[CConfig::getInstance()->getLowIndex()] < ll)
	{
		ll = temp[CConfig::getInstance()->getLowIndex()];
	}

	return ((hh - temp[CConfig::getInstance()->getCloseIndex()]) / (hh - ll)) * (100 * -1);
}


double relativeStrengthIndex(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	double avgGain = 0.0;
	double avgLoss = 0.0;
	averageGainLoss(slicedData, temp, curr_index, col_index, avgGain, avgLoss, time_period);
	double RS = avgGain / avgLoss;
	return (100.00 - (100.00/(1.00 + RS)));
}

void averageGainLoss(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	double& avgGain,
	double& avgLoss,
	int time_period)
{
	avgGain = avgLoss = 0.0;

	// check for first time
	if (slicedData[curr_index - 1].size() < (size_t)atoi(CConfig::getInstance()->getValue(RELATIVE_STRENGTH_INDEX).c_str()))
	{
		for (int i = 0; i < time_period; i++)
		{
			double diff = slicedData[curr_index - 1 - i][CConfig::getInstance()->getCloseIndex()] 
				- slicedData[curr_index - 1 - (i + 1)][CConfig::getInstance()->getCloseIndex()];
			if (diff > 0)
			{
				// gain
				avgGain += diff;
			}
			else if (diff < 0)
			{
				// loss
				avgLoss += (diff * -1);		// make it positive
			}
		}
		avgGain /= time_period;
		prevAvgGain = avgGain;
		avgLoss /= time_period;
		prevAvgLoss = avgLoss;
	}
	else
	{
		double diff = slicedData[curr_index - 1][CConfig::getInstance()->getCloseIndex()] 
			- slicedData[curr_index - 2][CConfig::getInstance()->getCloseIndex()];
		double gain = 0.0;
		double loss = 0.0;
		if (diff > 0)
		{
			gain = diff;
		}
		else if(diff < 0)
		{
			loss = (diff * -1);
		}

		// gain
		avgGain += (gain + (prevAvgGain*(time_period-1)))/time_period;
		prevAvgGain = avgGain;
		// loss
		avgLoss += (loss + (prevAvgLoss*(time_period - 1))) / time_period;		// make it positive
		prevAvgLoss = avgLoss;
	}

	return;
}

double bollingerMiddleBand(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	// simple moving average for 20 day period
	return simpleMovingAverage(slicedData, temp, curr_index, col_index, time_period);
}

double bollingerHigherBand(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	// 20 - day SMA + (20 - day standard deviation of price x 2)
	return temp[atoi(CConfig::getInstance()->getValue(BOLLINGER_MIDDLE_BAND_INDEX).c_str())] 
		+ (stdDeviation(slicedData, temp, curr_index, col_index, time_period) * 2);
}

double bollingerLowerBand(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	// 20 - day SMA - (20 - day standard deviation of price x 2)
	return temp[atoi(CConfig::getInstance()->getValue(BOLLINGER_MIDDLE_BAND_INDEX).c_str())] 
		- (stdDeviation(slicedData, temp, curr_index, col_index, time_period) * 2);
}

double stdDeviation(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	double mean = simpleMovingAverage(slicedData, temp, curr_index, col_index, time_period);

	double sumSqrDiffMean = 0.0;
	for (size_t i = (curr_index - time_period + 1); i < curr_index; i++)
	{
		double diffSqr = slicedData[i][col_index] - mean;
		diffSqr *= diffSqr;
		sumSqrDiffMean += diffSqr;
	}
	double diffSqr = temp[col_index] - mean;
	diffSqr *= diffSqr;
	sumSqrDiffMean += diffSqr;

	sumSqrDiffMean /= time_period;
	return sqrt(sumSqrDiffMean);
}

double highestHigh(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	double hh = max(slicedData, col_index, (curr_index - 1) - (time_period - 2), curr_index - 1);
	if (temp.size() && temp[col_index] > hh)
	{
		hh = temp[col_index];
	}

	return hh;
}

double lowestLow(std::vector<std::vector<double> >& slicedData,
	std::vector<double>& temp,
	size_t curr_index,
	size_t col_index,
	int time_period)
{
	double ll = min(slicedData, col_index, (curr_index - 1) - (time_period - 2), curr_index - 1);
	if (temp[col_index] < ll)
	{
		ll = temp[col_index];
	}

	return ll;
}

