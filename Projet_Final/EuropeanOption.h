#pragma once
#include "Option.h"

#include <cmath>
#include <vector>


class EuropeanOption : public Option
{
public:
	EuropeanOption();
	EuropeanOption(type t, double r, double sigma, double k, double T, double s, double b) : Option(t, r, sigma, k, T, s, b) {}
	~EuropeanOption();

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

