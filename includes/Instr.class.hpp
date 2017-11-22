#pragma once

#define WAY_EQUAL 0
#define WAY_DOWN 1
#define WAY_UP 2


class Fact;

class Instr
{
private:
	Fact *firstLink;
	Fact *SecLink;
	Fact *next;
	int iOperator;
	int iWay;
	bool bNegOne;
	bool bNegTwo;
	bool bNegNext;

	Instr(void);

public:
	Instr(Fact *fL, Fact *sL, Fact *next, int Op, int way);

	void SetNeg(bool first, bool snd, bool next);

	//Accessor
	Fact * getFirstLink() { return firstLink; };
	Fact * getSecLink() { return SecLink; };
	Fact * getNext() { return next; };

	int iGetOperator() { return iOperator; } ;
	int iGetWay() { return iWay; } ;

	bool bGetNegOne() { return bNegOne; } ;
	bool bGetNegTwo() { return bNegTwo; } ;
	bool bGetNegNext() { return bNegNext; } ;


	~Instr(void) {};

};