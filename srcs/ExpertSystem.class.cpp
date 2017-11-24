#include "ExpertSystem.class.hpp"

ExpertSystem::ExpertSystem(std::vector<Fact *> * vtabFact, std::vector<std::string> * vtabQuery) : tabFact(vtabFact), tabQuery(vtabQuery)
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
					std::cout << tabQuery->at(i) << " = False" << std::endl;
				else if (tabFact->at(j)->iGetState() == STATE_TRUE)
					std::cout << tabQuery->at(i) << " = True" << std::endl;
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
	// if (queryFact->bGetIsSet()) 
	// 	return ;

	Instr *instr;
	for (size_t i = 0; i < queryFact->tabLink.size(); i++)
	{
		instr = queryFact->tabLink[i];
		// if (queryFact->bGetIsSet()) 
		// 	break ;
		if (instr->iGetNbIteration() >= NB_ITERATION_INSTR)
			continue ;
		else
			instr->IncreaseInteration();
		if ((instr->iGetWay() == WAY_DOWN || instr->iGetWay() == WAY_EQUAL) && queryFact == instr->getNext())
		{
			// TODO BREAK
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
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		if (instr->bGetNegNext())
			instr->getNext()->SetState(STATE_FALSE);
		else
			instr->getNext()->SetState(STATE_TRUE);
	}
	else if (valueFirst == STATE_FALSE || valueSecond == STATE_FALSE)
	{
		if ((fstFact->bGetIsSet() && valueFirst == STATE_FALSE)
			|| (sndFact->bGetIsSet() && valueSecond == STATE_FALSE))
			instr->getNext()->SetIsSet(true);
		if (!instr->bGetNegNext())
			instr->getNext()->SetState(STATE_FALSE);
		else
			instr->getNext()->SetState(STATE_TRUE);
	}
	else
	{
		instr->getNext()->SetState(STATE_UNKNOWN);
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
		if ((fstFact->bGetIsSet() && valueFirst == STATE_TRUE)
			|| (sndFact->bGetIsSet() && valueSecond == STATE_TRUE))
			instr->getNext()->SetIsSet(true);
		if (instr->bGetNegNext())
			instr->getNext()->SetState(STATE_FALSE);
		else
			instr->getNext()->SetState(STATE_TRUE);
	}
	else if (valueFirst == STATE_FALSE && valueSecond == STATE_FALSE)
	{
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		if (!instr->bGetNegNext())
			instr->getNext()->SetState(STATE_FALSE);
		else
			instr->getNext()->SetState(STATE_TRUE);
	}
	else
	{
		instr->getNext()->SetState(STATE_UNKNOWN);
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
		instr->getNext()->SetState(STATE_UNKNOWN);
	else if (XOR<int>(valueFirst, valueSecond) == STATE_TRUE)
	{
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		if (instr->bGetNegNext())
			instr->getNext()->SetState(STATE_FALSE);
		else
			instr->getNext()->SetState(STATE_TRUE);
	}
	else
	{
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		if (!instr->bGetNegNext())
			instr->getNext()->SetState(STATE_FALSE);
		else
			instr->getNext()->SetState(STATE_TRUE);
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
				std::cerr <<  "Incoherence in the rules" << std::endl;
				exit(0);
			}
			nextFact->SetIsSet(true);
			if (instr->bGetNegNext())
				nextFact->SetState(STATE_FALSE);
			else
				nextFact->SetState(STATE_TRUE);
		}
		else if (!nextFact->bGetIsSet())
		{
			if (instr->bGetNegNext())
				nextFact->SetState(STATE_FALSE);
			else
				nextFact->SetState(STATE_TRUE);
		}
	}
	else if (valueNext == STATE_FALSE) // Contrapose
	{
		if (nextFact->bGetIsSet())
		{
			if (fstFact->bGetIsSet() && valueFirst != valueNext)
			{
				std::cerr <<  "Incoherence in the rules" << std::endl;
				exit(0);
			}
			fstFact->SetIsSet(true);
			if (instr->bGetNegOne())
				fstFact->SetState(STATE_TRUE);
			else
				fstFact->SetState(STATE_FALSE);
		}
		else if (!fstFact->bGetIsSet())
		{
			if (instr->bGetNegOne())
				fstFact->SetState(STATE_TRUE);
			else
				fstFact->SetState(STATE_FALSE);
		}
	}
	else if (valueFirst == STATE_UNKNOWN && !nextFact->bGetIsSet())
	{
		nextFact->SetState(STATE_UNKNOWN);
	}
	else if (valueNext == STATE_UNKNOWN && !fstFact->bGetIsSet())
	{
		fstFact->SetState(STATE_UNKNOWN);
	}
	else
	{
		// TODO do nothing
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
		std::cerr <<  "Incoherence in the rules" << std::endl;
		exit(0);
	}
	else if (fstFact->bGetIsSet() && !nextFact->bGetIsSet())
	{
		if (instr->bGetNegNext())
			nextFact->SetState(getStateValue(valueFirst, false));
		else
			nextFact->SetState(valueFirst);

		nextFact->SetIsSet(true);
	}
	else if (nextFact->bGetIsSet() && !fstFact->bGetIsSet())
	{
		if (instr->bGetNegOne())
			fstFact->SetState(getStateValue(valueNext, false));
		else
			fstFact->SetState(valueNext);

		fstFact->SetIsSet(true);
	}
	else if (!fstFact->bGetIsSet() && !nextFact->bGetIsSet())
	{
		if (instr->bGetNegNext())
			nextFact->SetState(getStateValue(valueFirst, false));
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
				std::cerr <<  "Incoherence in the rules" << std::endl;
				exit(0);
			}
			else if (!sndFact->bGetIsSet())
			{
				if (bNegSnd)
					sndFact->SetState(STATE_FALSE);
				else
					sndFact->SetState(STATE_TRUE);
				sndFact->SetIsSet(true);

				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
				fstFact->SetIsSet(true);
			}
		}
		else if (valueNext == STATE_FALSE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_TRUE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
				fstFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet() && valueSecond == STATE_TRUE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
			}
		}
	}
	else
	{
		if (valueNext == STATE_TRUE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (instr->bGetNegNext())
					nextFact->SetState(STATE_TRUE);
				else
					nextFact->SetState(STATE_FALSE);
				nextFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet())
			{
				if (bNegSnd)
					sndFact->SetState(STATE_FALSE);
				else
					sndFact->SetState(STATE_TRUE);

				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
			}
		}
		else if (valueNext == STATE_FALSE)
		{
			if (valueSecond == STATE_TRUE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
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
				std::cerr <<  "Incoherence in the rules" << std::endl;
				exit(0);
			}
			else if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
				fstFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet())
			{
				if (bNegSnd)
					sndFact->SetState(STATE_TRUE);
				else
					sndFact->SetState(STATE_FALSE);
				sndFact->SetIsSet(true);

				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
				fstFact->SetIsSet(true);
			}
		}
		else if (valueNext == STATE_TRUE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
				fstFact->SetIsSet(true);
			}
			else if (!sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
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
				if (instr->bGetNegNext())
					nextFact->SetState(STATE_FALSE);
				else
					nextFact->SetState(STATE_TRUE);
				nextFact->SetIsSet(true);
			}
			else if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
			}
			else if (!sndFact->bGetIsSet())
			{
				if (bNegSnd)
					sndFact->SetState(STATE_TRUE);
				else
					sndFact->SetState(STATE_FALSE);

				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
			}
		}
		else if (valueNext == STATE_TRUE)
		{
			if (sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
			}
			else if (!sndFact->bGetIsSet() && valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
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
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
				if (sndFact->bGetIsSet())
					fstFact->SetIsSet(true);	
			}
			else if (valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
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
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
				if (sndFact->bGetIsSet())
					fstFact->SetIsSet(true);	
			}
			else if (valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
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
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
			}
			else if (valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
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
				if (bNegFst)
					fstFact->SetState(STATE_FALSE);
				else
					fstFact->SetState(STATE_TRUE);
			}
			else if (valueSecond == STATE_FALSE)
			{
				if (bNegFst)
					fstFact->SetState(STATE_TRUE);
				else
					fstFact->SetState(STATE_FALSE);
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
				std::cerr <<  "Incoherence in the rules" << std::endl;
				exit(0);
			}
			nextFact->SetIsSet(true);
			if (instr->bGetNegNext())
				nextFact->SetState(STATE_FALSE);
			else
				nextFact->SetState(STATE_TRUE);
		}
		else if (!nextFact->bGetIsSet())
		{
			if (instr->bGetNegNext())
				nextFact->SetState(STATE_FALSE);
			else
				nextFact->SetState(STATE_TRUE);
		}
	}
	else if (valueNext == STATE_FALSE) // Contrapose
	{
		if (nextFact->bGetIsSet())
		{
			if (fstFact->bGetIsSet() && valueFirst != valueNext)
			{
				std::cerr <<  "Incoherence in the rules" << std::endl;
				exit(0);
			}
			fstFact->SetIsSet(true);
			if (instr->bGetNegOne())
				fstFact->SetState(STATE_TRUE);
			else
				fstFact->SetState(STATE_FALSE);
		}
		else if (!fstFact->bGetIsSet())
		{
			if (instr->bGetNegOne())
				fstFact->SetState(STATE_TRUE);
			else
				fstFact->SetState(STATE_FALSE);
		}
	}
	else if (valueFirst == STATE_UNKNOWN && !nextFact->bGetIsSet())
	{
		nextFact->SetState(STATE_UNKNOWN);
	}
	else if (valueNext == STATE_UNKNOWN && !fstFact->bGetIsSet())
	{
		fstFact->SetState(STATE_UNKNOWN);
	}
	else
	{
		// TODO do nothing
	}
}
