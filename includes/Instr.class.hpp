#pragma once

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