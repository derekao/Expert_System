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

	~Instr(void) {};

};