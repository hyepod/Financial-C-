#include "stdafx.h"
#include "noeud.h"


noeud::noeud()
{
}

noeud::noeud(noeud* parent, double value)
{
	this->parent = parent;
	this->value = value;
}

noeud::~noeud()
{
}
