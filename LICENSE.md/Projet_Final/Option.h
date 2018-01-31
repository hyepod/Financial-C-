#pragma once

#include <vector>

enum type { PUT, CALL };

class  Option
{
public:
	Option();
	Option(type t, double r, double sigma, double k, double T, double s, double b);
	~Option();

	virtual double ComputePayoff(const std::vector<double> & prix) = 0;

	type t;
	double r;
	double sigma;
	double k;
	double T;
	double S;
	double b;
};

