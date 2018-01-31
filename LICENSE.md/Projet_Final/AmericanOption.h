#pragma once
#include "Option.h"


class AmericanOption : public Option
{
public:
	AmericanOption();
	~AmericanOption();
	AmericanOption(type t, double r, double sigma, double k, double T, double s, double b) : Option(t, r, sigma, k, T, s, b) {}

	double ComputePayoff(const std::vector<double> & prix)
	{
		if (t == CALL)
		{
			return prix[prix.size() - 1] - k > 0 ? prix[prix.size() - 1] - k : 0;
		}
		else
		{
			return k - prix[prix.size() - 1] > 0 ? k - prix[prix.size() - 1] : 0;
		}
	}
};

