
#include "algo.h"


double max(std::vector<std::vector<double> >& data, size_t col_index, size_t range_min, size_t range_max)
{
	double m = -99999999.0;
	for (size_t i = range_min; i <= range_max; i++)
	{
		std::vector<double>& d = data[i];
		if (d[col_index] > m)
		{
			m = d[col_index];
		}
	}
	return m;
}

double min(std::vector<std::vector<double> >& data, size_t col_index, size_t range_min, size_t range_max)
{
	double m = 99999999;
	for (size_t i = range_min; i <= range_max; i++)
	{
		std::vector<double>& d = data[i];
		if (d[col_index] < m)
		{
			m = d[col_index];
		}
	}
	return m;
}