// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fact.class.cpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 15:29:16 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 15:29:16 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Fact.class.hpp"
bool Fact::bUnknown = false; 

Fact::Fact(std::string & name) : szName(name), iState(STATE_FALSE), bIsSet(false)
{
	
}

Fact::Fact() : szName(""), iState(STATE_FALSE), bIsSet(false)
{
	
}

void Fact::SetState(int state) 
{
	int tmp;

	if (!bIsSet || iState == state)
	{
		if (Fact::bUnknown && state == STATE_UNKNOWN)
		{
			std::cout << "The value of \"" << szGetName() << "\" is UNKNOWN, please enter 2 for true and 1 for false" << std::endl;
			std::cin >> tmp;
			if (tmp != 2 && tmp != 1)
			{
				std::cout << "FUCK YOU BITCH THIS ISN'T 0 OR 1! ARE YOU STUPID DUMBASS" << std::endl;
				exit(0);
			}
			iState = tmp - 1;
			bIsSet = true;
		}
		else
		{
			iState = state;
		}
	}
	else if (bIsSet && state == STATE_UNKNOWN)
		return;
	else
	{
		std::cerr <<  "Incoherence in the rules : Trying to set a fact that has already been set" << std::endl;
		exit(0);
	}
}
