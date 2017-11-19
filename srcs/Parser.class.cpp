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
	
	size_t j = 0;

	// PrintMemory();
	for (size_t i = 0; i < tokenLine->size(); i++)
	{
		if ((*tokenLine)[i]->bGetIsOperator())
		{
			Operator* tmp = reinterpret_cast<Operator *>((*tokenLine)[i]);
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
			// PrintMemory();
			input1.push_back((*tokenLine)[i]);
			std::cout << "YOLO " << input1[i]->bGetIsOperator() << std::endl;
		}
		else
		{
			// PrintMemory();
			input2.push_back((*tokenLine)[i]);
			std::cout << input2[j++]->bGetIsOperator() << std::endl;
		}
		
	}
}

// void Parser::PrintMemory()
// {
// 	for (size_t i = 0; i < CVectorToken->size(); i++)
// 	{
// 		for (size_t j = 0; j < (*(*CVectorToken)[i]).size(); j++)
// 		{
// 			std::cout << (*(*CVectorToken)[i])[j] << std::endl;
// 		}
// 		std::cout << "--------------" << std::endl;
// 	}
// 	std::cout << "||||||||||||||||||||" << std::endl;
// }