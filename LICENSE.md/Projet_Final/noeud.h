#pragma once
class noeud
{
public:
	noeud();
	noeud(noeud* parent, double value);
	~noeud();

	noeud* childUp;
	noeud* childDown;
	noeud* parent;
	double value;
	double priceCall;
	double pricePut;
};

