#include "stdafx.h"
#include "MonteCarlo.h"


MonteCarlo::MonteCarlo()
{
}

MonteCarlo::~MonteCarlo()
{
}

double MonteCarlo::ComputePrice(Option * option, double step, double generationNumber)
{
	this->typeOption = option->t;
	this->typeOption2 = typeid(*option).name();
	vector<double> tab = vector<double>(step);
	vector<double> totalPrice = vector<double>(generationNumber);
	double average = 0;

	for (int i = 0; i < generationNumber; i++)
	{
		GenerateRandomPath(option, step, tab);
		totalPrice[i] = option->ComputePayoff(tab);
		average = totalPrice[i] + average;
	}
	payoff = average / generationNumber;
	return payoff;
}

void MonteCarlo::GenerateRandomPath(Option * option, double step, vector<double> &tab)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	normal_distribution<double> distribution(0.0, 1.0);
	double number = distribution(generator);
	tab[0] = (option->S);

	for (int i = 1; i < step; i++)
	{
		number = distribution(generator);
		tab[i] = tab[i - 1] * exp((option->r - pow(option->sigma, 2) / 2)*(1 / step) + option->sigma*sqrt(1 / step)*number);
	}
}

void MonteCarlo::printPrice()
{
	cout << endl << endl << endl << "*****************    MONTE CARLO    *****************" << endl << std::endl;
	std::cout << "Type de l'Option :  " << typeOption2 << std::endl << std::endl;
	if (typeOption == CALL)
		cout << "Prix du Call : " << payoff << endl;
	else
		cout << "Prix du Put : " << payoff << endl << endl;
}