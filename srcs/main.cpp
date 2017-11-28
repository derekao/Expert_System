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
		Parser(&CVectorToken, &TabFact, &TabQuery);
		ExpertSystem(&TabFact, &TabQuery);
	
	}
	return 0;
}