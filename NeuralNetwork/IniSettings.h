#pragma once

#ifndef __INI_SETTINGS_H__
#define __INI_SETTINGS_H__

#include <string>

static std::string OutputLayerNodeCount = "OutputLayerNodeCount";
static std::string HiddenLayerNodeCount = "HiddenLayerNodeCount";
static std::string LearningRate = "LearningRate";
static std::string PreviousDays = "PreviousDays";
static std::string InputFile = "InputFile";
static std::string IndicatorsFile = "IndicatorsFile";
static std::string TrainingFile = "TrainingFile";
static std::string TestFile = "TestFile";
static std::string TrainingSize = "TrainingSize";
static std::string LogFile = "LogFile";
static std::string LoggingLevel = "LoggingLevel";
static std::string RunCombinations = "RunCombinations";


// indicators
static std::string DATE_INDEX = "DATE_INDEX";
static std::string OPEN_INDEX = "OPEN_INDEX";
static std::string HIGH_INDEX = "HIGH_INDEX";
static std::string LOW_INDEX = "LOW_INDEX";
static std::string CLOSE_INDEX = "CLOSE_INDEX";
static std::string VOL_INDEX = "VOL_INDEX";

static std::string TCP_MINUS_PCP_INDEX = "TCP_MINUS_PCP_INDEX";
static std::string PCP_INDEX = "PCP_INDEX";
static std::string PHP_INDEX = "PHP_INDEX";
static std::string PLP_INDEX = "PLP_INDEX";
static std::string POP_INDEX = "POP_INDEX";

static std::string FIVE_DAY_SMA_CLOSING_INDEX = "FIVE_DAY_SMA_CLOSING_INDEX";
static std::string SIX_DAY_SMA_CLOSING_INDEX = "SIX_DAY_SMA_CLOSING_INDEX";
static std::string TEN_DAY_SMA_CLOSING_INDEX = "TEN_DAY_SMA_CLOSING_INDEX";
static std::string TWENTY_DAY_SMA_CLOSING_INDEX = "TWENTY_DAY_SMA_CLOSING_INDEX";
static std::string FIFTY_DAY_SMA_CLOSING_INDEX = "FIFTY_DAY_SMA_CLOSING_INDEX";
static std::string TWO_H_DAY_SMA_CLOSING_INDEX = "TWO_H_DAY_SMA_CLOSING_INDEX";

static std::string FIVE_DAY_EMA_CLOSING_INDEX = "FIVE_DAY_EMA_CLOSING_INDEX";
static std::string SIX_DAY_EMA_CLOSING_INDEX = "SIX_DAY_EMA_CLOSING_INDEX";
static std::string TEN_DAY_EMA_CLOSING_INDEX = "TEN_DAY_EMA_CLOSING_INDEX";
static std::string TWENTY_DAY_EMA_CLOSING_INDEX = "TWENTY_DAY_EMA_CLOSING_INDEX";
static std::string FIFTY_DAY_EMA_CLOSING_INDEX = "FIFTY_DAY_EMA_CLOSING_INDEX";
static std::string TWO_H_DAY_EMA_CLOSING_INDEX = "TWO_H_DAY_EMA_CLOSING_INDEX";

static std::string FIVE_DAY_TMA_CLOSING_INDEX = "FIVE_DAY_TMA_CLOSING_INDEX";
static std::string SIX_DAY_TMA_CLOSING_INDEX = "SIX_DAY_TMA_CLOSING_INDEX";
static std::string TEN_DAY_TMA_CLOSING_INDEX = "TEN_DAY_TMA_CLOSING_INDEX";
static std::string TWENTY_DAY_TMA_CLOSING_INDEX = "TWENTY_DAY_TMA_CLOSING_INDEX";
static std::string FIFTY_DAY_TMA_CLOSING_INDEX = "FIFTY_DAY_TMA_CLOSING_INDEX";
static std::string TWO_H_DAY_TMA_CLOSING_INDEX = "TWO_H_DAY_TMA_CLOSING_INDEX";

static std::string ADL_CLOSING_INDEX = "ADL_CLOSING_INDEX";
static std::string MACD_CLOSING_INDEX = "MACD_CLOSING_INDEX";

static std::string FIVE_DAY_ACC_CLOSING_INDEX = "FIVE_DAY_ACC_CLOSING_INDEX";
static std::string SIX_DAY_ACC_CLOSING_INDEX = "SIX_DAY_ACC_CLOSING_INDEX";
static std::string TEN_DAY_ACC_CLOSING_INDEX = "TEN_DAY_ACC_CLOSING_INDEX";
static std::string TWENTY_DAY_ACC_CLOSING_INDEX = "TWENTY_DAY_ACC_CLOSING_INDEX";
static std::string FIFTY_DAY_ACC_CLOSING_INDEX = "FIFTY_DAY_ACC_CLOSING_INDEX";
static std::string FTWO_H_DAY_ACC_CLOSING_INDEX = "FTWO_H_DAY_ACC_CLOSING_INDEX";

static std::string FIVE_DAY_MOM_CLOSING_INDEX = "FIVE_DAY_MOM_CLOSING_INDEX";
static std::string SIX_DAY_MOM_CLOSING_INDEX = "SIX_DAY_MOM_CLOSING_INDEX";
static std::string TEN_DAY_MOM_CLOSING_INDEX = "TEN_DAY_MOM_CLOSING_INDEX";
static std::string TWENTY_DAY_MOM_CLOSING_INDEX = "TWENTY_DAY_MOM_CLOSING_INDEX";
static std::string FIFTY_DAY_MOM_CLOSING_INDEX = "FIFTY_DAY_MOM_CLOSING_INDEX";
static std::string TWO_H_DAY_MOM_CLOSING_INDEX = "TWO_H_DAY_MOM_CLOSING_INDEX";

static std::string CHAIKIN_VOLATILITY_INDEX = "CHAIKIN_VOLATILITY_INDEX";

static std::string FAST_STOCHASTIC_PERCENTK = "FAST_STOCHASTIC_PERCENTK";
static std::string FAST_STOCHASTIC_PERCENTD = "FAST_STOCHASTIC_PERCENTD";
static std::string SLOW_STOCHASTIC_PERCENTK = "SLOW_STOCHASTIC_PERCENTK";
static std::string SLOW_STOCHASTIC_PERCENTD = "SLOW_STOCHASTIC_PERCENTD";

static std::string WILLIAMS_PERCENT_R_INDEX = "WILLIAMS_PERCENT_R_INDEX";
static std::string RELATIVE_STRENGTH_INDEX = "RELATIVE_STRENGTH_INDEX";
static std::string BOLLINGER_MIDDLE_BAND_INDEX = "BOLLINGER_MIDDLE_BAND_INDEX";
static std::string BOLLINGER_HIGHER_BAND_INDEX = "BOLLINGER_HIGHER_BAND_INDEX";
static std::string BOLLINGER_LOWER_BAND_INDEX = "BOLLINGER_LOWER_BAND_INDEX";

static std::string FIVED_HIGHEST_HIGH_INDEX = "FIVED_HIGHEST_HIGH_INDEX";
static std::string SIXD_HIGHEST_HIGH_INDEX = "SIXD_HIGHEST_HIGH_INDEX";
static std::string TEND_HIGHEST_HIGH_INDEX = "TEND_HIGHEST_HIGH_INDEX";
static std::string TWENTYD_HIGHEST_HIGH_INDEX = "TWENTYD_HIGHEST_HIGH_INDEX";
static std::string FIFTYD_HIGHEST_HIGH_INDEX = "FIFTYD_HIGHEST_HIGH_INDEX";
static std::string TWO_HD_HIGHEST_HIGH_INDEX = "TWO_HD_HIGHEST_HIGH_INDEX";

static std::string FIVED_LOWEST_LOW_INDEX = "FIVED_LOWEST_LOW_INDEX";
static std::string SIXD_LOWEST_LOW_INDEX = "SIXD_LOWEST_LOW_INDEX";
static std::string TEND_LOWEST_LOW_INDEX = "TEND_LOWEST_LOW_INDEX";
static std::string TWENTYD_LOWEST_LOW_INDEX = "TWENTYD_LOWEST_LOW_INDEX";
static std::string FIFTYD_LOWEST_LOW_INDEX = "FIFTYD_LOWEST_LOW_INDEX";
static std::string TWO_HD_LOWEST_LOW_INDEX = "TWO_HD_LOWEST_LOW_INDEX";

static std::string FIVED_MEDIAN_PRICE_INDEX = "FIVED_MEDIAN_PRICE_INDEX";
static std::string SIXD_MEDIAN_PRICE_INDEX = "SIXD_MEDIAN_PRICE_INDEX";
static std::string TEND_MEDIAN_PRICE_INDEX = "TEND_MEDIAN_PRICE_INDEX";
static std::string TWENTYD_MEDIAN_PRICE_INDEX = "TWENTYD_MEDIAN_PRICE_INDEX";
static std::string FIFTYD_MEDIAN_PRICE_INDEX = "FIFTYD_MEDIAN_PRICE_INDEX";
static std::string TWO_HD_MEDIAN_PRICE_INDEX = "TWO_HD_MEDIAN_PRICE_INDEX";

#endif


