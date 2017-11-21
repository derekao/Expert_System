#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<Token *> *> *CVector, std::vector<Fact *> link) 
			: CVectorToken(CVector), FactTab(link)
{
	for (size_t i = 0; i < CVectorToken->size(); i++)
	{
		if ((*(*CVectorToken)[i])[0]->bGetIsOperator())
		{
			Operator* tmp = reinterpret_cast<Operator *>((*(*CVectorToken)[i])[0]);
			if (tmp->iGetID() == TOKEN_QUERY || tmp->iGetID() == TOKEN_FACT)
				continue ;
		}
		splitLineToken((*CVectorToken)[i]);
	}
}

void	Parser::splitLineToken(std::vector<Token *> *tokenLine)
{
	std::vector<Token *> *input1 = new std::vector<Token *>;
	std::vector<Token *> *input2 = new std::vector<Token *>;
	Operator *middleToken = NULL;
	bool lineMiddle = false;

	for (size_t i = 0; i < tokenLine->size(); i++)
	{
		if ((*tokenLine)[i]->bGetIsOperator())
		{
			Operator* tmp = dynamic_cast<Operator *>((*tokenLine)[i]);
			if (tmp->iGetID() == TOKEN_IMPLY || tmp->iGetID() == TOKEN_EQUAL)
				lineMiddle = true;
		}
		if (lineMiddle && !middleToken)
			middleToken = dynamic_cast<Operator *>tokenLine->at(i);
		else if(!lineMiddle)
			input1->push_back((*tokenLine)[i]);
		else
			input2->push_back((*tokenLine)[i]);
	}
	if (!input1->size() || !input2->size())
	{
		std::cerr << "Error : Wrong rule" << std::endl;
		exit(0);
	}
	input1 = ShuntingYardAlgo(input1);	
	input2 = ShuntingYardAlgo(input2);
	buildGraph(input1, input2, middleToken);

}

std::vector<Token *>	*Parser::ShuntingYardAlgo(std::vector<Token *> *Input)
{
	std::vector<Token *> *Output = new std::vector<Token *>;
	std::vector<Token *> Stack;
	Token *tmp;
	int iNbNeg = 0;
	bool bNeg = false;

	for (size_t i = 0; i < Input->size(); i++)
	{
		if (!Input->at(i)->bGetIsOperator())
			Output->push_back(Input->at(i));
		else if (Input->at(i)->bGetIsOperator() 
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() >= TOKEN_AND
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() <= TOKEN_XOR) 
		{
			Stack.push_back(Input->at(i));
		}
		else if (Input->at(i)->bGetIsOperator() 
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() == TOKEN_OPEN)
		{
			Stack.push_back(Input->at(i));
		}
		else if (Input->at(i)->bGetIsOperator() 
			&& (dynamic_cast<Operator *>(Input->at(i)))->iGetID() == TOKEN_CLOSE)
		{
			iNbNeg = 0;
			while (Stack.size() 
				&& (dynamic_cast<Operator *>(Stack.back()))->iGetID() != TOKEN_OPEN)
			{
				Output->push_back(Stack.back());
				Stack.pop_back();
				iNbNeg ++;
			}
			if (!Stack.size())
			{
				std::cerr << "There are mismatched closed parentheses" << std::endl;
				exit(0);
			}
			else
			{
				bNeg = true;
				tmp = Stack.back();
				Stack.pop_back();
				delete tmp;
			}
			tmp = Input->at(i);
			delete tmp;
			for	(size_t j = 0; j < iNbNeg; j++)
			{
				(dynamic_cast<Operator *>(Output->at(Output->size() - j)))->SetNeg(bNeg);
			}
		}
	}
	while (Stack.size())
	{
		if ((dynamic_cast<Operator *>(Stack.back()))->iGetID() == TOKEN_OPEN)
		{
			std::cerr << "There are mismatched opened parentheses" << std::endl;
			exit(0);
		}	
		Output->push_back(Stack.back());
		Stack.pop_back();
	}
	delete Input;
	return(Output);

}

void Parser::buildGraph(std::vector<Token *> *input1, std::vector<Token *> *input2, Operator *middleToken)
{
	Fact * wayIn;
	Fact * wayOut;
ok
	if (middleToken->iGetID() == TOKEN_EQUAL)
	{
		wayIn = buildNode(input1, WAY_EQUAL);
		wayOut = buildNode(input2, WAY_EQUAL);
	}
	else
	{
		wayIn = buildNode(input1, WAY_EQUAL);
		wayOut = buildNode(input2, WAY_EQUAL);
	}
}

Fact * Parser::buildNode(std::vector<Token *> *input, WTF)
{
	Fact *fact1;
	Fact *fact2;
	Fact *next;
	Operator *op;
	Instr *instr;
	TokenMixed *concatToken;

	size_t i = 0;
	if (input->size() == 1)
	{ // TODO
		return input->back();
	}
	while (!input->at(i++)->bGetIsOperator())
		;
	if (i < 2)
	{
		std::err << "Operator without any Fact isn't very smart :')" << std::endl;
		exit(0);
	}
	op = dynamic_cast<Operator *>(input->at(i));
	fact1 = getFact(input->at(i - 2));
	fact2 = getFact(input->at(i - 1));
	next = new Fact("");
	concatToken = new TokenMixed(op->bGetNeg() ,next);
	input->erase(i - 2, i);
	input->insert(i, concatToken);
	instr = new Instr(fact1, fact2, next, op->iGetID(), );

}

Fact * Parser::getFact(Token * token)
{
	if (!token->bGetIsMixed())
	{
		std::string szTmp = dynamic_cast<TokenFact *>(token)->szGetName();
		for (size_t i = 0; i < FactTab.size(); i++)
		{
			if (szTmp == FactTab[i]->szGetName())
				return FactTab[i];
		}
		return new Fact(szTmp);
	}
	else
	{
		return new Fact("");
	}

}

void Parser::PrintMemory(std::vector<Token *> toto)
{
	for (size_t i = 0; i < toto.size(); i++)
	{
		if (toto[i]->bGetIsOperator())
		{
			std::cout << "Operator is = " << (dynamic_cast<Operator *>(toto[i]))->iGetID() << std::endl;
		}
		else
		{
			std::cout << "FactName is = " << (dynamic_cast<TokenFact *>(toto[i]))->szGetName() << 
				" And is neg? =" << (dynamic_cast<TokenFact *>(toto[i]))->bGetNeg() << std::endl;
		}
	}
	std::cout << "||||||||||||||||||||" << std::endl;
}