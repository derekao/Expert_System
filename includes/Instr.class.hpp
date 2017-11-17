#pragma once

class Link;

class Instr
{
private:
	Link *firstLink;
	Link *SecLink;
	Link *previous;
	int iOperator;
	int iWay;
	bool bNegOne;
	bool bNegTwo;
	bool bNegPrev;

	Instr(void);

public:
	Instr();
	~Instr(void) {};

};