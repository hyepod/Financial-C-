#include "stdafx.h"
#include "Tree.h"


Tree::Tree()
{

}

Tree::Tree(int n, Option *Op)
{
	this->typeOption2 = typeid(*Op).name();
	this->n = n;
	this->strike = Op->k;
	this->r = Op->r;
	this->sigma = Op->sigma;
	this->up = exp(sigma*sqrt(Op->T / n));
	this->down = 1 / up;
	this->firstPrice = Op->S;
	firstNoeud = new noeud(NULL, firstPrice);
	Create(firstNoeud, 0);
}

void Tree::Create(noeud* first, int step)
{
	if (step < n)
	{
		noeud* noeudD = new noeud(first, first->value*(down));
		noeud* noeudU = new noeud(first, first->value*(up));
		first->childUp = noeudU;
		first->childDown = noeudD;
		Create(noeudU, step + 1);
		Create(noeudD, step + 1);
	}
}

void Tree::printPrice()
{
	std::cout << std::endl << std::endl << std::endl << "*****************    BINOMIAL TREE    *****************" << std::endl << std::endl;
	std::cout << "Type de l'Option :  " << typeOption2 << std::endl << std::endl;
	std::cout << "Prix du Call : " << firstNoeud->priceCall << std::endl;
	std::cout << "Prix du Put : " << firstNoeud->pricePut << std::endl;
}

void Tree::CalculatePrice()
{
	Cross(firstNoeud);
}

void Tree::Cross(noeud* ptr)
{
	if (ptr->childDown == NULL && ptr->childUp == NULL)
	{
		ptr->priceCall = ptr->value - strike > 0 ? ptr->value - strike : 0;
		ptr->pricePut = strike - ptr->value > 0 ? strike - ptr->value : 0;
	}
	else
	{
		Cross(ptr->childDown);
		Cross(ptr->childUp);
		double R = exp(r / n);
		double q = (R - down) / (up - down);
		ptr->priceCall = (q*ptr->childUp->priceCall + (1 - q)*ptr->childDown->priceCall) / (R);
		ptr->pricePut = (q*ptr->childUp->pricePut + (1 - q)*ptr->childDown->pricePut) / (R);
	}
}

Tree::~Tree()
{
}
