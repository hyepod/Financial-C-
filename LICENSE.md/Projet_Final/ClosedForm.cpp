#include "stdafx.h"
#include "ClosedForm.h"

ClosedForm::ClosedForm()
{
}

ClosedForm::~ClosedForm()
{
}

void ClosedForm::ComputePrice(Option * option, int n)
{
	this->typeOption = option->t;
	this->typeOption2 = typeid(*option).name();
	double res = 0;
	double up = exp(option->sigma*sqrt(option->T / n));
	double down = 1 / up;
	double R = exp(option->r / n);
	double q = (R - down) / (up - down);
	double h = 0;
	std::vector<double> tab = std::vector<double>(1);
	for (int i = 0; i <= n; i++)
	{
		tab[0] = option->S*pow((up), i)*pow((down), n - i);
		h = (option->ComputePayoff(tab));
		res += pow(q, i)*pow((1 - q), (n - i))*h*factorial(n) / (factorial(i)*factorial(n - i));
	}
	res /= R;
	payoff = res;
}

double ClosedForm::factorial(int n)
{
	double res = 1;
	for (int i = 1; i <= n; i++)
	{
		res *= i;
	}
	return res;
}

void ClosedForm::printPrice()
{
	std::cout << std::endl << std::endl << std::endl << "*****************    CLOSED FORM    *****************" << std::endl << std::endl;
	std::cout << "Type de l'Option :  " << typeOption2 << std::endl << std::endl;
	if (typeOption == CALL)
		std::cout << "Prix du Call : " << payoff << std::endl;
	else
		std::cout << "Prix du Put : " << payoff << std::endl;
}