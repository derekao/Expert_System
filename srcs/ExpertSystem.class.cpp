#include "ExpertSystem.class.hpp"

ExpertSystem::ExpertSystem(std::vector<Fact *> * vtabFact, std::vector<std::string> * vtabQuery) : tabFact(vtabFact), tabQuery(vtabQuery), bVerbose(true)
{
    bool bInTabFact = false;

    for (size_t i = 0; i < tabQuery->size(); i++)
    {
        bInTabFact = false;
        for (size_t j = 0; j < tabFact->size(); j++)
        {
            if (tabFact->at(j)->szGetName() == tabQuery->at(i))
            {
                bInTabFact = true;
				backWardChaining(tabFact->at(j));
				if (tabFact->at(j)->iGetState() == STATE_FALSE)
					std::cout << tabQuery->at(i) << " = False " << tabFact->at(j)->bGetIsSet() << std::endl;
				else if (tabFact->at(j)->iGetState() == STATE_TRUE)
					std::cout << tabQuery->at(i) << " = True " << tabFact->at(j)->bGetIsSet() << std::endl;
				else if (tabFact->at(j)->iGetState() == STATE_UNKNOWN)
					std::cout << tabQuery->at(i) << " = Unknown" << std::endl;
				else
				{
					std::cerr << "WTF IS GOING ON ON LINE 23 ON EXPERT SYSTEM" << std::endl;
					exit (0);
				}
                break ;
            }
        }
        if (!bInTabFact)
        {
            std::cout << tabQuery->at(i) << " = False" << std::endl;
        }
    }
}

void ExpertSystem::backWardChaining(Fact * queryFact)
{
	Instr *instr;
	for (size_t i = 0; i < queryFact->tabLink.size(); i++)
	{
		instr = queryFact->tabLink[i];
		if (instr->iGetNbIteration() >= NB_ITERATION_INSTR)
			continue ;
		else
			instr->IncreaseInteration();
		if ((instr->iGetWay() == WAY_DOWN || instr->iGetWay() == WAY_EQUAL) && queryFact == instr->getNext())
		{
			switch (instr->iGetOperator())
			{
				case TOKEN_AND :
				{
					wayDownAND(instr);
					break;
				}
				case TOKEN_OR :
				{
					wayDownOR(instr);
					break;
				}
				case TOKEN_XOR :
				{
					wayDownXOR(instr);
					break;
				}
				case TOKEN_IMPLY :
				{
					wayDownIMPLY(instr);
					break;
				}
				case TOKEN_EQUAL :
				{
					wayDownEQUAL(instr);
					break;
				}
			}
		}
		else if ((instr->iGetWay() == WAY_UP || instr->iGetWay() == WAY_EQUAL) && queryFact != instr->getNext())
		{
			switch (instr->iGetOperator())
			{
				case TOKEN_AND :
				{
					wayUpAND(instr, queryFact);
					break;
				}
				case TOKEN_OR :
				{
					wayUpOR(instr, queryFact);
					break;
				}
				case TOKEN_XOR :
				{
					wayUpXOR(instr, queryFact);
					break;
				}
				case TOKEN_IMPLY :
				{
					wayUpIMPLY(instr);
					break;
				}
				case TOKEN_EQUAL :
				{
					wayDownEQUAL(instr);
					break;
				}
			}
		}
	}
}

int ExpertSystem::getStateValue(int iState, bool bNeg)
{
	if (iState == STATE_UNKNOWN)
		return STATE_UNKNOWN;
	else if (iState == STATE_TRUE)
	{
		if (bNeg)
			return STATE_FALSE;
		else
			return STATE_TRUE;
	}
	else
	{
		if (!bNeg)
			return STATE_FALSE;
		else
			return STATE_TRUE;
	}
}

void ExpertSystem::SetState(int iState, bool bNeg, Fact * fact)
{
	if (iState == STATE_TRUE)
	{ 
		if (bNeg)
			fact->SetState(STATE_FALSE);
		else
			fact->SetState(STATE_TRUE);
	}
	else
	{
		if (bNeg)
			fact->SetState(STATE_TRUE);
		else
			fact->SetState(STATE_FALSE);
	}
}

void ExpertSystem::PrintVerbose(std::string instr, std::string fact1, std::string fact2, std::string next, bool bNeg1, bool bNeg2, bool bNegNext, std::string str, int iState)
{
	std::string szValueNext;
	std::string szName1;
	std::string szName2;
	std::string szName3;

	if (iState == STATE_TRUE)
		szValueNext = "True";
	else if (iState == STATE_FALSE)
		szValueNext = "False";
	else
		szValueNext = "Unknown";

	if (!fact1.compare(""))
		szName1 = "Token Mixed";
	else
		szName1 = fact1;

	if (!fact2.compare(""))
		szName2 = "Token Mixed";
	else
		szName2 = fact2;

	if (!next.compare(""))
		szName3 = "Token Mixed";
	else
		szName3 = next;
	

	std::cout << "Instruction \033[33m" << instr << "\033[m on \033[32m" << (bNeg1 ? "!" : "") << szName1
			<< "\033[m and \033[32m" << (bNeg2 ? "!" : "") << szName2 << "\033[m " << str << ", the result is : \033[32m" 
			<< (bNegNext ? "!" : "") << szName3 << "\033[m = \033[31m" << szValueNext << "\033[m" << std::endl;
}

void ExpertSystem::wayDownAND(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * sndFact = instr->getSecLink();
	backWardChaining(fstFact);
	backWardChaining(sndFact);

	int valueFirst = getStateValue(fstFact->iGetState(), instr->bGetNegOne());
	int valueSecond = getStateValue(sndFact->iGetState(), instr->bGetNegTwo());

	if (valueFirst == STATE_TRUE && valueSecond == STATE_TRUE)
	{
		SetState(STATE_TRUE, instr->bGetNegNext(), instr->getNext());
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		if (bVerbose)
		{
			PrintVerbose("AND", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with both fact true", instr->getNext()->iGetState());
		}
	}
	else if (valueFirst == STATE_FALSE || valueSecond == STATE_FALSE)
	{
		SetState(STATE_TRUE, !instr->bGetNegNext(), instr->getNext());
		if ((fstFact->bGetIsSet() && valueFirst == STATE_FALSE)
		|| (sndFact->bGetIsSet() && valueSecond == STATE_FALSE))
			instr->getNext()->SetIsSet(true);
		if (bVerbose)
		{
			PrintVerbose("AND", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with at least one of the fact false", instr->getNext()->iGetState());
		}
	}
	else
	{
		instr->getNext()->SetState(STATE_UNKNOWN);
		if (bVerbose)
		{
			PrintVerbose("AND", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with at least one of the fact unknown and none are false", instr->getNext()->iGetState());
		}
	}
}

void ExpertSystem::wayDownOR(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * sndFact = instr->getSecLink();
	backWardChaining(fstFact);
	backWardChaining(sndFact);

	int valueFirst = getStateValue(fstFact->iGetState(), instr->bGetNegOne());
	int valueSecond = getStateValue(sndFact->iGetState(), instr->bGetNegTwo());

	if (valueFirst == STATE_TRUE || valueSecond == STATE_TRUE)
	{
		SetState(STATE_TRUE, instr->bGetNegNext(), instr->getNext());
		if ((fstFact->bGetIsSet() && valueFirst == STATE_TRUE)
		|| (sndFact->bGetIsSet() && valueSecond == STATE_TRUE))
			instr->getNext()->SetIsSet(true);

		if (bVerbose)
		{
			PrintVerbose("OR", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with at least one fact true", instr->getNext()->iGetState());
		}
	}
	else if (valueFirst == STATE_FALSE && valueSecond == STATE_FALSE)
	{
		SetState(STATE_TRUE, !instr->bGetNegNext(), instr->getNext());
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		
		if (bVerbose)
		{
			PrintVerbose("OR", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with both fact false", instr->getNext()->iGetState());
		}
	}
	else
	{
		instr->getNext()->SetState(STATE_UNKNOWN);

		if (bVerbose)
		{
			PrintVerbose("OR", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with at least one of the fact unknown and none are true", instr->getNext()->iGetState());
		}
	}
}

void ExpertSystem::wayDownXOR(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * sndFact = instr->getSecLink();
	backWardChaining(fstFact);
	backWardChaining(sndFact);

	int valueFirst = getStateValue(fstFact->iGetState(), instr->bGetNegOne());
	int valueSecond = getStateValue(sndFact->iGetState(), instr->bGetNegTwo());

	if (valueFirst == STATE_UNKNOWN || valueSecond == STATE_UNKNOWN)
	{
		instr->getNext()->SetState(STATE_UNKNOWN);

		if (bVerbose)
		{
			PrintVerbose("XOR", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with at least one fact is unknown", instr->getNext()->iGetState());
		}
	}
	else if (XOR<int>(valueFirst, valueSecond) == STATE_TRUE)
	{
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		SetState(STATE_TRUE, instr->bGetNegNext(), instr->getNext());

		if (bVerbose)
		{
			PrintVerbose("XOR", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with only one of the fact true", instr->getNext()->iGetState());
		}
	}
	else
	{
		SetState(STATE_TRUE, !instr->bGetNegNext(), instr->getNext());
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);

		if (bVerbose)
		{
			PrintVerbose("XOR", fstFact->szGetName(), sndFact->szGetName(), instr->getNext()->szGetName(),
				instr->bGetNegOne(), instr->bGetNegTwo(), instr->bGetNegNext(), "with both fact identical", instr->getNext()->iGetState());
		}
	}
}

void ExpertSystem::wayDownIMPLY(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * nextFact = instr->getNext();
	backWardChaining(fstFact);
	int valueFirst = getStateValue(fstFact->iGetState(), instr->bGetNegOne());
	int valueNext = getStateValue(nextFact->iGetState(), instr->bGetNegNext());

	if (valueFirst == STATE_TRUE)
	{
		if (fstFact->bGetIsSet())
		{
			if (nextFact->bGetIsSet() && valueFirst != valueNext)
			{
				std::cerr <<  "Incoherence in the rules N1" << std::endl;
				exit(0);
			}
			SetState(STATE_TRUE, instr->bGetNegNext(), nextFact);
			nextFact->SetIsSet(true);
		}
		else if (!nextFact->bGetIsSet())
			SetState(STATE_TRUE, instr->bGetNegNext(), nextFact);
	}
	else if (valueNext == STATE_FALSE && nextFact->bGetIsSet()) // Contrapose
	{
		if (fstFact->bGetIsSet() && valueFirst != valueNext)
		{
			std::cerr <<  "Incoherence in the rules N2" << std::endl;
			exit(0);
		}
		SetState(STATE_FALSE, instr->bGetNegOne(), fstFact);
		fstFact->SetIsSet(true);
	}
	else if (valueFirst == STATE_UNKNOWN && !nextFact->bGetIsSet())
	{
		nextFact->SetState(STATE_UNKNOWN);
	}
	else if (valueNext == STATE_UNKNOWN && !fstFact->bGetIsSet())
	{
		fstFact->SetState(STATE_UNKNOWN);
	}
	else if (valueNext == STATE_FALSE) // Contrapose
	{
		SetState(STATE_FALSE, instr->bGetNegOne(), fstFact);
	}
}

void ExpertSystem::wayDownEQUAL(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * nextFact = instr->getNext();
	backWardChaining(fstFact);
	int valueFirst = getStateValue(fstFact->iGetState(), instr->bGetNegOne());
	int valueNext = getStateValue(nextFact->iGetState(), instr->bGetNegNext());
	
	if (fstFact->bGetIsSet() && nextFact->bGetIsSet() && valueFirst != valueNext)
	{
		std::cerr <<  "Incoherence in the rules N3" << std::endl;
		exit(0);
	}
	else if (fstFact->bGetIsSet() && !nextFact->bGetIsSet())
	{
		if (instr->bGetNegNext())
		{
			nextFact->SetState(getStateValue(valueFirst, true));
		}
		else
			nextFact->SetState(valueFirst);

		nextFact->SetIsSet(true);
	}
	else if (nextFact->bGetIsSet() && !fstFact->bGetIsSet())
	{
		if (instr->bGetNegOne())
			fstFact->SetState(getStateValue(valueNext, true));
		else
			fstFact->SetState(valueNext);

		fstFact->SetIsSet(true);
	}
	else if (!fstFact->bGetIsSet() && !nextFact->bGetIsSet())
	{
		if (instr->bGetNegNext())
			nextFact->SetState(getStateValue(valueFirst, true));
		else
			nextFact->SetState(valueFirst);
	}
	else
	{
		// YOU ARE USLESS BRO
	}
}

void ExpertSystem::wayUpAND(Instr * instr, Fact * queryFact)
{
	Fact * fstFact;
	Fact * sndFact;
	Fact * nextFact = instr->getNext();

	bool bNegFst;
	bool bNegSnd;

	if (queryFact == instr->getFirstLink())
	{
		fstFact = queryFact;
		sndFact = instr->getSecLink();
		bNegFst = instr->bGetNegOne();
		bNegSnd = instr->bGetNegTwo();
	}
	else
	{
		fstFact = queryFact;
		sndFact = instr->getFirstLink();
		bNegFst = instr->bGetNegTwo();
		bNegSnd = instr->bGetNegOne();
	}

	backWardChaining(sndFact);
	backWardChaining(nextFact);

	int valueNext = getStateValue(nextFact->iGetState(), instr->bGetNegNext());
	int valueSecond = getStateValue(sndFact->iGetState(), bNegSnd);

	if (nextFact->bGetIsSet())
	{
		if (valueNext == STATE_TRUE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				std::cerr <<  "Incoherence in the rules N4" << std::endl;
				exit(0);
			}
			else if (!sndFact->bGetIsSet())
			{
				SetState(STATE_TRUE, bNegSnd, sndFact);
				sndFact->SetIsSet(true);

				SetState(STATE_TRUE, bNegFst, fstFact);
				fstFact->SetIsSet(true);
			}
		}
		else if (valueNext == STATE_FALSE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_TRUE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
				fstFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet() && valueSecond == STATE_TRUE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
			}
		}
	}
	else
	{
		if (valueNext == STATE_TRUE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				SetState(STATE_FALSE, instr->bGetNegNext(), nextFact);
				nextFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet())
			{
				SetState(STATE_TRUE, bNegSnd, sndFact);
				SetState(STATE_TRUE, bNegFst, fstFact);
			}
		}
		else if (valueNext == STATE_FALSE)
		{
			if (valueSecond == STATE_TRUE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
			}	
		}
	}

}

void ExpertSystem::wayUpOR(Instr * instr, Fact * queryFact)
{
	Fact * fstFact;
	Fact * sndFact;
	Fact * nextFact = instr->getNext();

	bool bNegFst;
	bool bNegSnd;

	if (queryFact == instr->getFirstLink())
	{
		fstFact = queryFact;
		sndFact = instr->getSecLink();
		bNegFst = instr->bGetNegOne();
		bNegSnd = instr->bGetNegTwo();
	}
	else
	{
		fstFact = queryFact;
		sndFact = instr->getFirstLink();
		bNegFst = instr->bGetNegTwo();
		bNegSnd = instr->bGetNegOne();
	}

	backWardChaining(sndFact);
	backWardChaining(nextFact);

	int valueNext = getStateValue(nextFact->iGetState(), instr->bGetNegNext());
	int valueSecond = getStateValue(sndFact->iGetState(), bNegSnd);

	if (nextFact->bGetIsSet())
	{
		if (valueNext == STATE_FALSE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_TRUE)
			{
				std::cerr <<  "Incoherence in the rules N5" << std::endl;
				exit(0);
			}
			else if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
				fstFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet())
			{
				SetState(STATE_FALSE, bNegSnd, sndFact);
				sndFact->SetIsSet(true);

				SetState(STATE_FALSE, bNegFst, fstFact);
				fstFact->SetIsSet(true);
			}
		}
		else if (valueNext == STATE_TRUE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				SetState(STATE_TRUE, bNegFst, fstFact);
				fstFact->SetIsSet(true);
			}
			else
			{
				fstFact->SetState(STATE_UNKNOWN);
			}
		}
	}
	else
	{
		if (valueNext == STATE_FALSE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_TRUE)
			{
				SetState(STATE_TRUE, instr->bGetNegNext(), nextFact);
				nextFact->SetIsSet(true);
			}
			else if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
			}
			else if (!sndFact->bGetIsSet())
			{
				SetState(STATE_FALSE, bNegSnd, sndFact);
				SetState(STATE_FALSE, bNegFst, fstFact);
			}
		}
		else if (valueNext == STATE_TRUE)
		{
			if (valueSecond == STATE_FALSE)
			{
				SetState(STATE_TRUE, bNegFst, fstFact);
			}
			else
			{
				fstFact->SetState(STATE_UNKNOWN);
			}
		}
	}
}

void ExpertSystem::wayUpXOR(Instr * instr, Fact * queryFact)
{
	Fact * fstFact;
	Fact * sndFact;
	Fact * nextFact = instr->getNext();

	bool bNegFst;
	bool bNegSnd;

	if (queryFact == instr->getFirstLink())
	{
		fstFact = queryFact;
		sndFact = instr->getSecLink();
		bNegFst = instr->bGetNegOne();
		bNegSnd = instr->bGetNegTwo();
	}
	else
	{
		fstFact = queryFact;
		sndFact = instr->getFirstLink();
		bNegFst = instr->bGetNegTwo();
		bNegSnd = instr->bGetNegOne();
	}

	backWardChaining(sndFact);
	backWardChaining(nextFact);

	int valueNext = getStateValue(nextFact->iGetState(), instr->bGetNegNext());
	int valueSecond = getStateValue(sndFact->iGetState(), bNegSnd);

	if (nextFact->bGetIsSet())
	{
		if (valueNext == STATE_TRUE)
		{
			if (valueSecond == STATE_TRUE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
				if (sndFact->bGetIsSet())
					fstFact->SetIsSet(true);	
			}
			else if (valueSecond == STATE_FALSE)
			{
				SetState(STATE_TRUE, bNegFst, fstFact);
				if (sndFact->bGetIsSet())
					fstFact->SetIsSet(true);
			}
			else if (valueSecond == STATE_UNKNOWN)
			{
				fstFact->SetState(STATE_UNKNOWN);
			}
		}
		else if (valueNext == STATE_FALSE)
		{
			if (valueSecond == STATE_TRUE)
			{
				SetState(STATE_TRUE, bNegFst, fstFact);
				if (sndFact->bGetIsSet())
					fstFact->SetIsSet(true);	
			}
			else if (valueSecond == STATE_FALSE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
				if (sndFact->bGetIsSet())
					fstFact->SetIsSet(true);
			}
			else if (valueSecond == STATE_UNKNOWN)
			{
				fstFact->SetState(STATE_UNKNOWN);
			}
		}
	}
	else
	{
		if (valueNext == STATE_TRUE)
		{
			if (valueSecond == STATE_TRUE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
			}
			else if (valueSecond == STATE_FALSE)
			{
				SetState(STATE_TRUE, bNegFst, fstFact);
			}
			else if (valueSecond == STATE_UNKNOWN)
			{
				fstFact->SetState(STATE_UNKNOWN);
			}
		}
		else if (valueNext == STATE_FALSE)
		{
			if (valueSecond == STATE_TRUE)
			{
				SetState(STATE_TRUE, bNegFst, fstFact);
			}
			else if (valueSecond == STATE_FALSE)
			{
				SetState(STATE_FALSE, bNegFst, fstFact);
			}
			else if (valueSecond == STATE_UNKNOWN)
			{
				fstFact->SetState(STATE_UNKNOWN);
			}
		}
		else if (valueNext == STATE_UNKNOWN)
		{
			fstFact->SetState(STATE_UNKNOWN);
		}
	}
}

void ExpertSystem::wayUpIMPLY(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * nextFact = instr->getNext();
	backWardChaining(nextFact);
	int valueFirst = getStateValue(fstFact->iGetState(), instr->bGetNegOne());
	int valueNext = getStateValue(nextFact->iGetState(), instr->bGetNegNext());
	if (valueFirst == STATE_TRUE)
	{
		if (fstFact->bGetIsSet())
		{
			if (nextFact->bGetIsSet() && valueFirst != valueNext)
			{
				std::cerr <<  "Incoherence in the rules N1" << std::endl;
				exit(0);
			}
			SetState(STATE_TRUE, instr->bGetNegNext(), nextFact);
			nextFact->SetIsSet(true);
		}
		else if (!nextFact->bGetIsSet())
			SetState(STATE_TRUE, instr->bGetNegNext(), nextFact);
	}
	else if (valueNext == STATE_FALSE && nextFact->bGetIsSet()) // Contrapose
	{
		if (fstFact->bGetIsSet() && valueFirst != valueNext)
		{
			std::cerr <<  "Incoherence in the rules N2" << std::endl;
			exit(0);
		}
		SetState(STATE_FALSE, instr->bGetNegOne(), fstFact);
		fstFact->SetIsSet(true);
	}
	else if (valueFirst == STATE_UNKNOWN && !nextFact->bGetIsSet())
	{
		nextFact->SetState(STATE_UNKNOWN);
	}
	else if (valueNext == STATE_UNKNOWN && !fstFact->bGetIsSet())
	{
		fstFact->SetState(STATE_UNKNOWN);
	}
	else if (valueNext == STATE_FALSE) // Contrapose
	{
		SetState(STATE_FALSE, instr->bGetNegOne(), fstFact);
	}
}