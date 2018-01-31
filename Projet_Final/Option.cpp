#include "stdafx.h"
#include "Option.h"


Option::Option()
{
}

Option::Option(type t, double r, double sigma, double k, double T, double s, double b)
{
	this->t = t;
	this->r = r;
	this->sigma = sigma;
	this->k = k;
	this->T = T;
	this->S = s;
	this->b = b;
}

Option::~Option()
{
}
