#include "ExpertSystem.class.hpp"

ExpertSystem::ExpertSystem(std::vector<Fact *> * vtabFact, std::vector<std::string> * vtabQuery) : tabFact(vtabFact), tabQuery(vtabQuery)
{
    bool bInTabFact = false;

    for (size_t i = 0; i < tabQuery->size(), i++)
    {
        bInTabFact = false;
        for (size_t j = 0; j < tabFact->size(); j++)
        {
            if (tabFact->at(j)->szGetName() == tabQuery->at(i))
            {
                bInTabFact = true;
				tabFact->at(j)->SetState(backWardChaining(tabFact->at(j)));
				if (tabFact->at(j)->iGetState() == STATE_FALSE)
					std::cout << tabQuery->at(i) << " = True" << std::endl;
				else if (tabFact->at(j)->iGetState() == STATE_TRUE)
					std::cout << tabQuery->at(i) << " = False" << std::endl;
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

int ExpertSystem::backWardChaining(Fact * queryFact)
{
	if (queryFact->bGetIsSet()) 
		return  queryFact->iGetSate();

	Instr *instr;
	for (size_t i = 0; i < queryFact->tabLink.size(); i++)
	{
		instr = queryFact->tabLink[i];
		if ((instr->iWay == WAY_DOWN || instr->iWay == WAY_EQUAL) && queryFact == instr->next)
		{
			// TODO BREAK
			switch (instr->iOperator)
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
		else if ((instr->iWay == WAY_UP || instr->iWay == WAY_EQUAL) && queryFact != instr->next)
		{

		}

	}

}

void wayDownAND(Instr * instr)
{
	Fact * fstFact = instr->getFirstLink();
	Fact * sndFact = instr->getSecLink();
	backWardChaining(fstFact);
	backWardChaining(sndFact);

	if (fstFact->iGetSate() == STATE_TRUE && sndFact->iGetSate() == STATE_TRUE)
	{
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		instr->getNext()->SetState(STATE_TRUE);
	}
	else if (FirstLink == STATE_FALSE || SecLink == STATE_FALSE)
	{
		if (fstFact->bGetIsSet() && sndFact->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		instr->getNext()->SetState(STATE_FALSE);
	}
	else
	{
		instr->getNext()->SetState(STATE_UNKNOWN)
	}
}

void wayDownOR(Instr * instr)
{
	backWardChaining(instr->getFirstLink());
	backWardChaining(instr->getSecLink());

	if (FirstLink == STATE_TRUE || SecLink == STATE_TRUE)
	{
		if ((instr->getFirstLink()->bGetIsSet() && FirstLink->SetState()
			 || instr->getSecLink()->bGetIsSet())
		 {
			instr->getNext()->SetIsSet(true);
		 }
		instr->getNext()->SetState(STATE_TRUE);
	}
	else if (FirstLink == STATE_FALSE && SecLink == STATE_FALSE)
	{
		if (instr->getFirstLink()->bGetIsSet() && instr->getSecLink()->bGetIsSet())
			instr->getNext()->SetIsSet(true);
		instr->getNext()->SetState(STATE_FALSE);
	}
	else
	{
		instr->getNext()->SetState(STATE_UNKNOWN)
	}
}

int wayDownXOR(Instr * instr)
{
	int FirstLink = backWardChaining(instr->getFirstLink());
	int SecLink = backWardChaining(instr->getSecLink());


	if (FirstLink == STATE_UNKNOWN || SecLink == STATE_UNKNOWN)
		return STATE_UNKNOWN;
	if (XOR<int>(FirstLink, SecLink) == STATE_TRUE)
		return STATE_TRUE;
	else if (FirstLink == STATE_FALSE && SecLink == STATE_FALSE)
		return STATE_FALSE;
	else
		return STATE_UNKNOWN;
}