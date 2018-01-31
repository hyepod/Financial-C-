#pragma once
#include "Option.h"


#include <iostream>
#include <string>
#include <cmath>


class BlackScholes
{
public:
	BlackScholes();
	~BlackScholes();
	double ComputePrice(Option * option, double t);
	void printPrice();

private:
	double payoff;
	type typeOption;
	std::string typeOption2;

	double ComputeD1(Option * option, double t);
	double ComputeD2(Option * option, double t);
	double normalDistribution(double x);
};

