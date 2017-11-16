// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Lexer.class.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 12:40:00 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 12:40:06 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Lexer.class.hpp"

/* CORE */

Lexer::Lexer(std::string szFileName, std::vector< std::vector<Token> > & CVector) : 
			bError(false), CVectorToken(CVector)
{
	CFileStream = new std::ifstream(szFileName);

	if (CFileStream->fail())
	{
		std::cerr << "Wrong File !" << std::endl;
		exit(0);
	}

	{ // Read the file line per line
		std::string szLine;
		int i = 0;

		while (std::getline(*CFileStream, szLine))
		{
			CheckLineFormat(szLine, i);
			i++;
		}
		if (bError)
		{
			for (size_t i = 0; i < VectorError.size() ; i++)
			{
				std::cerr << VectorError[i] << std::endl;
			}
		}
		else
		{
			std::cout << CVectorToken.size() << std::endl; 
		}
	}

	return ;
}

Lexer::~Lexer()
{
	delete CFileStream;
}

void Lexer::CheckLineFormat(std::string & szLine, int iLine)
{
	int i = 0;

	while (isspace(szLine[i]))
		i++;

	switch (szLine[i])
	{
		case '#' :
		{
			break;
		}

		default :
		{
			LexLine(szLine.substr(i), iLine);
		}
	}
}

void Lexer::LexLine(std::string szLine, int iLine)
{
	std::vector<Token> tmpVector;

	for (size_t i = 0; i < szLine.length(); i++)
	{
		while (isspace(szLine[i]))
			i++;
		if (szLine[i] == '#')
			break ;
		else if (szLine[i] == '+')
			tmpVector.push_back(Operator(TOKEN_AND));
		else if (szLine[i] == '|')
			tmpVector.push_back(Operator(TOKEN_OR));
		else if (szLine[i] == '^')
			tmpVector.push_back(Operator(TOKEN_XOR));
		else if (szLine[i] == '!')
			tmpVector.push_back(Operator(TOKEN_NEG));
		else if (szLine[i] == '(')
			tmpVector.push_back(Operator(TOKEN_OPEN));
		else if (szLine[i] == ')')
			tmpVector.push_back(Operator(TOKEN_CLOSE));
		else if (szLine[i] == '=' && szLine[i + 1] == '>')
		{
			tmpVector.push_back(Operator(TOKEN_IMPLY));
			i++;
		}
		else if (szLine[i] == '<' && szLine[i + 1] == '=' && szLine[i + 2] == '>')
		{
			tmpVector.push_back(Operator(TOKEN_EQUAL));
			i += 2;
		}
		else if (szLine[i] == '?')
			tmpVector.push_back(Operator(TOKEN_QUERY));
		else if (szLine[i] == '=')
			tmpVector.push_back(Operator(TOKEN_FACT));
		else if (isupper(szLine[i]))
		{
			int j = i + 1;
			while (islower(szLine[j]))
				j++;
			tmpVector.push_back(TokenFact(szLine.substr(i, j - i)));
			i += j - i - 1;
		}
		else
		{
			bError = true;
			VectorError.push_back("Unknown char : " + szLine.substr(i, 1)
					+ " at line : " + std::to_string(iLine));
			return ;
		}
	}
	CVectorToken.push_back(tmpVector);
}
