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

//	std::cout << "0-----------------------------------------" << std::endl;
	for (size_t i = 0; i < tokenLine->size(); i++)
	{
		if ((*tokenLine)[i]->bGetIsOperator())
		{
			Operator* tmp = dynamic_cast<Operator *>((*tokenLine)[i]);
			if (tmp->iGetID() == TOKEN_IMPLY || tmp->iGetID() == TOKEN_EQUAL)
				lineMiddle = true;
		}
		if (lineMiddle && !middleToken)
			middleToken = dynamic_cast<Operator *>(tokenLine->at(i));
		else if(!lineMiddle)
			input1->push_back((*tokenLine)[i]);
		else
			input2->push_back((*tokenLine)[i]);
	}
//	std::cout << "01-----------------------------------------" << std::endl;
	if (!input1->size() || !input2->size())
	{
		std::cerr << "Error : Wrong rule" << std::endl;
		exit(0);
	}
	std::cout << "A-----------------------------------------" << std::endl;
	input1 = ShuntingYardAlgo(input1);	
	std::cout << "B-----------------------------------------" << std::endl;
	input2 = ShuntingYardAlgo(input2);
	std::cout << "C-----------------------------------------" << std::endl;
	buildGraph(input1, input2, middleToken);

}

std::vector<Token *>	*Parser::ShuntingYardAlgo(std::vector<Token *> *Input)
{
	std::vector<Token *> *Output = new std::vector<Token *>;
	std::vector<Token *> Stack;
	Token *tmp;
	size_t iNbNeg = 0;
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
				(dynamic_cast<Operator *>(Output->at(Output->size() - j - 1)))->SetNeg(bNeg);
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
	Instr *instr;

	std::cout << "2-----------------------------------------" << std::endl;
	if (middleToken->iGetID() == TOKEN_EQUAL)
	{
		std::cout << "2.1-----------------------------------------" << std::endl;
		wayIn = buildNode(input1, WAY_EQUAL);
		wayOut = buildNode(input2, WAY_EQUAL);
		instr = new Instr(wayIn, NULL, wayOut, TOKEN_EQUAL, WAY_EQUAL);
	}
	else
	{
		std::cout << "2.21-----------------------------------------" << std::endl;
		wayIn = buildNode(input1, WAY_DOWN);
		std::cout << "2.22-----------------------------------------" << std::endl;
		wayOut = buildNode(input2, WAY_UP);
		std::cout << "2.23-----------------------------------------" << std::endl;
		instr = new Instr(wayIn, NULL, wayOut, TOKEN_IMPLY, WAY_DOWN);
		std::cout << "2.24-----------------------------------------" << std::endl;
	}
	std::cout << "3-----------------------------------------" << std::endl;
	wayIn->tabLink.push_back(instr);
	std::cout << "4-----------------------------------------" << std::endl;
	wayOut->tabLink.push_back(instr);
	std::cout << "5-----------------------------------------" << std::endl;
//	CheckRuleRight(); TODO
}

Fact * Parser::buildNode(std::vector<Token *> *input, int iWay)
{
	Fact *fact1;
	Fact *fact2;
	Fact *next;

	Token *token1;
	Token *token2;
	Operator *op;
	
	Instr *instr;
	TokenMixed *concatToken;

	size_t i = 0;
	std::cout << "Node1-----------------------------------------" << std::endl;
	if (input->size() == 1)
	{
		return getFact(input->back());
	}
	while (!input->at(i)->bGetIsOperator())
		i++;
	std::cout << "Node2----------------------------------------- et = " << i << "et" << input->size() << std::endl;
	if (i < 2)
	{
		std::cerr << "Operator without any Fact isn't very smart :')" << std::endl;
		exit(0);
	}
	std::cout << "Node3----------------------------------------- = " << i << " et " << input->size() << std::endl;
	op = dynamic_cast<Operator *>(input->at(i));
	fact1 = getFact(input->at(i - 2));
	fact2 = getFact(input->at(i - 1));
	next = new Fact();
	concatToken = new TokenMixed(op->bGetNeg(), next);
	std::cout << "Node4.1-----------------------------------------" << std::endl;
	token1 = input->at(i - 2);
	token2 = input->at(i - 1);
	input->erase(input->begin() + i - 2, input->begin() + i);
	std::cout << "Node4.2-----------------------------------------" << std::endl;
	i -= 2;
	input->insert(input->begin() + i, concatToken);
	std::cout << "Node4.3-----------------------------------------" << std::endl;
	instr = new Instr(fact1, fact2, next, op->iGetID(), iWay);
	std::cout << "Node4.4-----------------------------------------" << std::endl;
	instr->SetNeg(token1->bGetNeg(),token2->bGetNeg(),op->bGetNeg());
	std::cout << "Node5-----------------------------------------" << std::endl;
	fact1->tabLink.push_back(instr);
	fact2->tabLink.push_back(instr);
	next->tabLink.push_back(instr);
	std::cout << "Node6----------------------------------------- et = " << input->size() << std::endl;
	return buildNode(input, iWay);
}

Fact * Parser::getFact(Token *token)
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
		return dynamic_cast<TokenMixed *>(token)->getFact();
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