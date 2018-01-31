#pragma once
#include "Option.h"


class AsianOption : public Option
{
public:
	AsianOption();
	~AsianOption();
	AsianOption(type t, double r, double sigma, double k, double T, double s, double b) : Option(t, r, sigma, k, T, s, b) {}

	double ComputePayoff(const std::vector<double> & prix)
	{
		double average = 0;
		for (size_t i = 0; i < prix.size(); i++)
		{
			average += prix[i];
		}
		if (t = CALL)
		{
			return average / prix.size() - k > 0 ? average / prix.size() - k : 0;
		}
		else
		{
			return k - average / prix.size() > 0 ? k - average / prix.size() : 0;
		}
	}
};

