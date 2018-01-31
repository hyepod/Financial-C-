#include "stdafx.h"
#include "BlackScholes.h"

BlackScholes::BlackScholes()
{
}


BlackScholes::~BlackScholes()
{
}

double BlackScholes::ComputeD1(Option * option, double t)
{
	return (log(option->S / option->k) + (option->r + 0.5*option->sigma*option->sigma)*(option->T - t)) / option->sigma*sqrt(option->T - t);
}

double BlackScholes::ComputeD2(Option * option, double t)
{
	return ComputeD1(option, t) - option->sigma*sqrt(option->T - t);
}


double BlackScholes::ComputePrice(Option * option, double t)
{
	this->typeOption = option->t;
	this->typeOption2 = typeid(*option).name();
	if (option->t == CALL)
	{
		payoff = option->S*normalDistribution(ComputeD1(option, t)) - option->k*exp(-option->r*(option->T - t))*normalDistribution(ComputeD2(option, t));
		return payoff;
	}
	else
	{
		payoff = option->k*exp(-option->r*(option->T - t))*normalDistribution(-ComputeD2(option, t)) - option->S*normalDistribution(-ComputeD1(option, t));
		return payoff;
	}
}

double BlackScholes::normalDistribution(double x)
{
	static const double RT2PI = sqrt(4.0*acos(0.0));
	static const double SPLIT = 10. / sqrt(2);
	static const double a[] = { 220.206867912376,221.213596169931,112.079291497871,33.912866078383,6.37396220353165,0.700383064443688,3.52624965998911e-02 };
	static const double b[] = { 440.413735824752,793.826512519948,637.333633378831,296.564248779674,86.7807322029461,16.064177579207,1.75566716318264,8.83883476483184e-02 };

	const double z = fabs(x);
	double Nz = 0.0;

	// if z outside these limits then value effectively 0 or 1 for machine precision
	if (z <= 37.0)
	{
		// NDash = N'(z) * sqrt{2\pi}
		const double NDash = exp(-z * z / 2.0) / RT2PI;
		if (z<SPLIT)
		{
			const double Pz = (((((a[6] * z + a[5])*z + a[4])*z + a[3])*z + a[2])*z + a[1])*z + a[0];
			const double Qz = ((((((b[7] * z + b[6])*z + b[5])*z + b[4])*z + b[3])*z + b[2])*z + b[1])*z + b[0];
			Nz = RT2PI * NDash*Pz / Qz;
		}
		else
		{
			const double F4z = z + 1.0 / (z + 2.0 / (z + 3.0 / (z + 4.0 / (z + 13.0 / 20.0))));
			Nz = NDash / F4z;
		}
	}
	return x >= 0.0 ? 1 - Nz : Nz;
}

void BlackScholes::printPrice()
{
	std::cout << "*****************    BLACK SCHOLES    *****************" << std::endl << std::endl;
	std::cout << "Type de l'Option :  " << typeOption2 << std::endl << std::endl;
	if (typeOption == CALL)
		std::cout << "Prix du Call : " << payoff << std::endl;
	else
		std::cout << "Prix du Put : " << payoff << std::endl;
}