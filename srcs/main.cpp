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
	if (ac == 2)
	{
		std::vector< std::vector<Token *> *> CVectorToken;
		std::vector<Fact *> TabFact;
		std::vector<std::string> TabQuery;

		Lexer(std::string(av[1]), &CVectorToken);
		Parser tmp = Parser(&CVectorToken, &TabFact, &TabQuery);
		/*std::cout << TabQuery.size() << " Query" << std::endl;
		for (size_t i = 0; i < TabQuery.size(); i++){
			std::cout << TabQuery[i] << std::endl;
		}
		std::cout << TabFact.size() << " Fact" << std::endl;
		for (size_t i = 0; i < TabFact.size(); i++){
			std::cout << "Maillion N° "<< TabFact.at(i)->szGetName() << " et " << TabFact.at(i)->iGetSate() << " et " << TabFact.at(i)->bGetIsSet() << std::endl;
		}*/

	//	tmp.PrintGraph();
		ExpertSystem(&TabFact, &TabQuery);
	}
	return 0;
}