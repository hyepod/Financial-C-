#pragma once
#include "Option.h"


#include <string>
#include <iostream>
#include <cmath>


class ClosedForm
{
public:
	ClosedForm();
	~ClosedForm();
	void ComputePrice(Option * option, int n);
	void printPrice();

private:
	double payoff;
	type typeOption;
	std::string typeOption2;

	double factorial(int n);
};

