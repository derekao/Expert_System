#include "Instr.class.hpp"

Instr::Instr(Fact *fL, Fact *sL, Fact *nxt, int Op, int way) :
			firstLink(fL), SecLink(sL), next(nxt), iOperator(Op), iWay(way)
{

}

void Instr::SetNeg(bool first, bool snd, bool next)
{
	bNegOne = first;
	bNegTwo = snd;
	bNegNext = next;
}