#include "Parser.class.hpp"

Parser::Parser(std::vector< std::vector<Token *> *> *CVector, std::vector<std::string> * link) 
			: CVectorToken(CVector), Link(link)
{
	for (size_t i = 0; i < CVectorToken->size(); i++)
	{
		if ((*(*CVectorToken)[i])[0]->bGetIsOperator())
		{
			Operator* tmp = reinterpret_cast<Operator *>((*(*CVectorToken)[i])[0]);
			if (tmp->iGetID() == TOKEN_QUERY || tmp->iGetID() == TOKEN_FACT)
				continue ;
		}
		buildGraph((*CVectorToken)[i]);
	}
}

void	Parser::buildGraph(std::vector<Token *> *tokenLine)
{
	// std::cout << tokenLine[0]->bGetIsOperator() << std::endl;
	std::vector<Token *> input1;
	std::vector<Token *> input2;
	bool lineMiddle = false;
	bool bIsMidle = false;

//	PrintMemory();
	for (size_t i = 0;i < tokenLine->size(); i++)
	{
		if ((*tokenLine)[i]->bGetIsOperator())
		{
			std::cout << "1---------------------------------------------------" << std::endl;
			PrintMemory();
			std::cout << "2---------------------------------------------------" << std::endl;
			Operator* tmp = reinterpret_cast<Operator *>((*tokenLine)[i]);
			std::cout << "3---------------------------------------------------" << std::endl;
			PrintMemory();
			std::cout << "4---------------------------------------------------" << std::endl;
			std::cout << "ARE YOU REAL "<< tmp->bGetIsOperator() << std::endl;
			if (tmp->iGetID() == TOKEN_IMPLY || tmp->iGetID() == TOKEN_EQUAL)
			{
				lineMiddle = true;
				bIsMidle = true;
			}
		}
		if (bIsMidle)
			bIsMidle = false;
		else if (!lineMiddle)
		{
			input1.push_back((*tokenLine)[i]);
			std::cout << "YOLO " <<input1[i]->bGetIsOperator() << std::endl;
		}
		else
		{
			PrintMemory();
			std::cout << "5---------------------------------------------------" << std::endl;
			std::cout << "YOLO1 " <<input2[i]->bGetIsOperator() << std::endl;
			input2.push_back((*tokenLine)[i]);
		}
		
	}
}

void Parser::PrintMemory()
{
	for (size_t i = 0; i < CVectorToken->size(); i++)
	{
		for (size_t j = 0; j < (*(*CVectorToken)[i]).size(); j++)
		{
			std::cout << (*(*CVectorToken)[i])[j] << std::endl;
		}
		std::cout << "--------------" << std::endl;
	}
	std::cout << "||||||||||||||||||||" << std::endl;
}