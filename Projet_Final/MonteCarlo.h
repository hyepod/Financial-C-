#pragma once
#include "Option.h"


#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class MonteCarlo
{
public:
	MonteCarlo();
	~MonteCarlo();
	double ComputePrice(Option *option, double step, double generationNumber);
	void printPrice();

private:
	double payoff;
	type typeOption;
	std::string typeOption2;

	void GenerateRandomPath(Option *option, double step, vector<double> & tab);
};

