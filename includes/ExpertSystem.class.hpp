#pragma once

#include "Instr.class.hpp"
#include "Fact.class.hpp"
#include "Operator.class.hpp"
#include <vector>

#define NB_ITERATION_INSTR 2

class ExpertSystem
{

private:

	std::vector<Fact *> * tabFact;
	std::vector<std::string> * tabQuery;

	ExpertSystem();

	int getStateValue(int iState, bool bNeg);

	void wayDownAND(Instr * instr);
	void wayDownOR(Instr * instr);
	void wayDownXOR(Instr * instr);
	void wayDownIMPLY(Instr * instr);
	void wayDownEQUAL(Instr * instr);

	void wayUpAND(Instr * instr, Fact * queryFact);
	void wayUpOR(Instr * instr, Fact * queryFact);
	void wayUpXOR(Instr * instr, Fact * queryFact);
	void wayUpIMPLY(Instr * instr);
	void backWardChaining(Fact *);

public:
	ExpertSystem(std::vector<Fact *> *, std::vector<std::string> *);
	~ExpertSystem() {} ;

};