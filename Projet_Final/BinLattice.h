#pragma once
#include "Option.h"
#include "noeud.h"


#include <vector>
#include <iostream>
#include <typeinfo>
#include <string>


using namespace std;

template <class T>
class BinLattice
{
public:
	BinLattice() {}
	~BinLattice() {}
	T ComputePrice(Option * option, int length)
	{
		typeOption2 = (string)(typeid(*option).name());
		//T h = option->T / length;
		//T up = exp((option->r+  option->sigma*option->sigma/2)*h  + option->sigma*sqrt(h)) ;
		//T down = exp((option->r + option->sigma*option->sigma / 2)*h - option->sigma*sqrt(h));
		//T R = exp(option->r*h);
		T up = exp(option->sigma*sqrt(option->T / length));
		T down = 1 / up;
		double R = exp(option->r / length);
		T q = (R - down) / (up - down);
		vector<T> a(length);
		vector<T> b(length);
		vector<vector<T>> payoffs2(length, a);
		vector<vector<T>> lattice2(length, b);

		lattice2[0][0] = option->S;
		for (size_t j = 0; j < length - 1; j++)
		{
			for (size_t i = 0; i < length - 1; i++)
			{
				if (i <= j)
				{
					lattice2[i][j + 1] = lattice2[i][j] * up;
					lattice2[i + 1][j + 1] = lattice2[i][j] * down;
				}
			}
		}
		for (size_t i = 0; i < length; i++)
		{
			payoffs2[i][length - 1] = option->ComputePayoff(lattice2[i]);
		}

		if (typeid(*option).name() == typeid(AmericanOption).name())
		{
			for (size_t j = length - 1; j > 0; j--)
			{
				for (size_t i = length - 1; i > 0; i--)
				{
					if (i <= j)
					{
						T a = (payoffs2[i][j] * (1 - q) + payoffs2[i - 1][j] * q) / R;
						T b = lattice2[i][j];
						if (option->t == CALL)
							payoffs2[i - 1][j - 1] = a > (b - option->k) ? a : (b - option->k);
						else
							payoffs2[i - 1][j - 1] = a > (option->k - b) ? a : (option->k - b);
					}
				}
			}
		}
		else
		{
			for (size_t j = length - 1; j > 0; j--)
			{
				for (size_t i = length - 1; i > 0; i--)
				{
					if (i <= j)
						payoffs2[i - 1][j - 1] = (payoffs2[i][j] * (1 - q) + payoffs2[i - 1][j] * q) / R;
				}
			}
		}
		payoff = payoffs2[0][0];
		return payoff;
	}
	void Print()
	{
		std::cout << std::endl << std::endl << std::endl << "*****************    BIN LATTICE    *****************" << std::endl << std::endl;
		std::cout << "Type de l'Option :  " << typeOption2 << std::endl <<std::endl;
		if (typeOption == CALL)
			std::cout << std::endl << "Prix du Call : " << payoff << std::endl;
		else
			std::cout << "Prix du Put : " << payoff << std::endl;
	}

	void SetN(int lenght) {}
	void SetNode() {}
	void GetNode() {}

private:
	T payoff;
	type typeOption;
	string typeOption2;
	vector<vector<T>> lattice;
	vector<vector<T>> payoffs;
};

