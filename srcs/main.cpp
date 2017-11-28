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

int main(int ac, char **av)
{
	if (ac >= 2)
	{
		std::vector<std::string> vecArgv;

		bool	bVerbose = false;
		
		for (size_t i = 0; i < static_cast<size_t>(ac) - 1; i++)
		{
			vecArgv.push_back(std::string(av[i + 1]));
			if (vecArgv[i].compare("-v") == 0)
			{
				bVerbose = true;
				vecArgv.pop_back();
			}

		}
	
		for (size_t i = 0; i < vecArgv.size(); i++)
		{		
			std::vector< std::vector<Token *> *> CVectorToken;
			std::vector<Fact *> TabFact;
			std::vector<std::string> TabQuery;

			Lexer(vecArgv[i], &CVectorToken);
			Parser(&CVectorToken, &TabFact, &TabQuery);
			ExpertSystem(&TabFact, &TabQuery, bVerbose);
			std::cout << "\033[35m----------------------------------------------------------------------------------------------\033[m" << std::endl;
		}
	
	}
	return 0;
}