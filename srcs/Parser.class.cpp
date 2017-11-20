#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<Token *> *> *CVector, std::vector<Fact> link) 
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
	Token *middleToken = NULL;
	bool lineMiddle = false;

	for (size_t i = 0; i < tokenLine->size(); i++)
	{
		if ((*tokenLine)[i]->bGetIsOperator())
		{
			Operator* tmp = reinterpret_cast<Operator *>((*tokenLine)[i]);
			if (tmp->iGetID() == TOKEN_IMPLY || tmp->iGetID() == TOKEN_EQUAL)
				lineMiddle = true;
		}
		if (lineMiddle && !middleToken)
			middleToken = tokenLine->at(i);
		else else if (!lineMiddle)
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
	buildGraph(intput1, input2, middleToken);
}

std::vector<Token *>	*Parser::ShuntingYardAlgo(std::vector<Token *> *Input)
{
	std::vector<Token *> *Output = new std::vector<Token *>;
	std::vector<Token *> Stack;
	Token *tmp;

	for (size_t i = 0; i < Input->size(); i++)
	{
		if (!Input->at(i)->bGetIsOperator())
			Output->push_back(Input->at(i));
		else if (Input->at(i)->bGetIsOperator() 
			&& (reinterpret_cast<Operator *>(Input->at(i)))->iGetID() >= TOKEN_AND
			&& (reinterpret_cast<Operator *>(Input->at(i)))->iGetID() <= TOKEN_XOR) 
		{
			Stack.push_back(Input->at(i));
		}
		else if (Input->at(i)->bGetIsOperator() 
			&& (reinterpret_cast<Operator *>(Input->at(i)))->iGetID() == TOKEN_OPEN)
		{
			Stack.push_back(Input->at(i));
		}
		else if (Input->at(i)->bGetIsOperator() 
			&& (reinterpret_cast<Operator *>(Input->at(i)))->iGetID() == TOKEN_CLOSE)
		{
			while (Stack.size() 
				&& (reinterpret_cast<Operator *>(Stack.back()))->iGetID() != TOKEN_OPEN)
			{
				Output->push_back(Stack.back());
				Stack.pop_back();
			}
			if (!Stack.size())
			{
				std::cerr << "There are mismatched closed parentheses" << std::endl;
				exit(0);
			}
			else
			{
				tmp = Stack.back();
				Stack.pop_back();
				delete tmp;
			}
			tmp = Input->at(i);
			delete tmp;
		}
	}
	while (Stack.size())
	{
		if ((reinterpret_cast<Operator *>(Stack.back()))->iGetID() == TOKEN_OPEN)
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

void Parser::buildGraph(std::vector<Token *> *input1, std::vector<Token *> *input2, Token *middleToken)
{
	Link * wayIn;
	Link * wayOut;

	wayIn = buildNode(input1, WTF);
	wayOut = buildNode(input2, WTF);
}

Link * Parser::buildNode(std::vector<Token *> *input, WTF)
{
	Link *tmpLink = new Link;
	Instr *tmpInstr = new Instr;

	size_t i = 0;
	if (input->size() == 1)
		return input->back();
	while (!input->at(i++)->bGetIsOperator())
		;
	if (i < 2)
	{
		std::err < "Operator without any Fact isn't very smart :')" << std::endl;
		exit(0);
	}
	

}

void Parser::PrintMemory(std::vector<Token *> toto)
{
	for (size_t i = 0; i < toto.size(); i++)
	{
		if (toto[i]->bGetIsOperator())
		{
			std::cout << "Operator is = " << (reinterpret_cast<Operator *>(toto[i]))->iGetID() << std::endl;
		}
		else
		{
			std::cout << "FactName is = " << (reinterpret_cast<TokenFact *>(toto[i]))->szGetName() << 
				" And is neg? =" << (reinterpret_cast<TokenFact *>(toto[i]))->bGetNeg() << std::endl;
		}
	}
	std::cout << "||||||||||||||||||||" << std::endl;
}