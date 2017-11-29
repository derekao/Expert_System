// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 14:13:36 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 14:13:36 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Lexer.class.hpp"
#include "Parser.class.hpp"
#include "ExpertSystem.class.hpp"
#include "Fact.class.hpp"

int main(int ac, char **av)
{
	if (ac >= 2)
	{
		std::vector<std::string> vecArgv;

		bool	bVerbose = false;
		bool 	bDebug = false;
		bool	bUnknown = false;
		
		for (size_t i = 0; i < static_cast<size_t>(ac) - 1; i++)
		{
			vecArgv.push_back(std::string(av[i + 1]));
			if (vecArgv.back().compare("-v") == 0)
			{
				bVerbose = true;
				vecArgv.pop_back();
			}
			else if (vecArgv.back().compare("-d") == 0)
			{
				std::cout << "DEBUG MODE : ON" << std::endl;
				bDebug = true;
				vecArgv.pop_back();
			}
			else if (vecArgv.back().compare("-u") == 0)
			{
				bUnknown = true;
				vecArgv.pop_back();
			}
		}
		for (size_t i = 0; i < vecArgv.size(); i++)
		{		
			std::vector< std::vector<Token *> *> CVectorToken;
			std::vector<Fact *> TabFact;
			std::vector<std::string> TabQuery;

			Fact::setUnknown(bUnknown);
			Lexer(vecArgv[i], &CVectorToken);
			Parser(&CVectorToken, &TabFact, &TabQuery, bDebug);
			ExpertSystem(&TabFact, &TabQuery, bVerbose, bUnknown, bDebug);
			return 0;
		}
	}
	return 0;
}