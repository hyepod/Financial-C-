#pragma once
#include "noeud.h"
#include "Option.h"


#include <string>
#include <random>
#include <iostream>
#include <cmath>


class Tree
{
public:
	Tree();
	Tree(int n, Option *Op);
	~Tree();
	void printPrice();
	void CalculatePrice();
	void Cross(noeud* ptr);


private:
	void Create(noeud* first, int step);
	noeud* firstNoeud;
	int n;
	double down;
	double up;
	double firstPrice;
	double strike;
	double r;
	double sigma;
	std::string typeOption2;
};

