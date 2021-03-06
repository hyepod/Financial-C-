// Projet_Final.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "EuropeanOption.h"
#include "AsianOption.h"
#include "AmericanOption.h"
#include "BlackScholes.h"
#include "Tree.h"
#include "ClosedForm.h"
#include "MonteCarlo.h"
#include "BinLattice.h"


#include <iostream>

int main()
{
	// Différentes Options

	EuropeanOption * op1 = new EuropeanOption(CALL, 0.01, 0.2, 40, 1, 40, 0);
	AsianOption * opAsian1 = new AsianOption(PUT, 0.01, 0.2, 40, 1, 40, 0);
	AmericanOption * opAmerican = new AmericanOption(PUT, 0.01, 0.2, 40, 1, 40, 0);


	// Modèle Black & scholes

	BlackScholes pricer;
	pricer.ComputePrice(op1, 0);
	pricer.printPrice();


	//Modèle arbre binaire

	Tree t1(5, op1);
	t1.CalculatePrice();
	t1.printPrice();


	//Modèle BinLattice (arbre binaire recombinant)

	BinLattice<double> b1;
	b1.ComputePrice(op1, 100);
	b1.Print();

	b1.ComputePrice(opAmerican,100);
	b1.Print();


	//Modèle Closed-Form

	ClosedForm c1;
	c1.ComputePrice(op1,50);
	c1.printPrice();

	//Modèle MonteCarlo
	
	MonteCarlo mont1;
	mont1.ComputePrice(op1, 30, 10000);
	mont1.printPrice();

	mont1.ComputePrice(opAsian1, 30, 1000);
	mont1.printPrice();






	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}

