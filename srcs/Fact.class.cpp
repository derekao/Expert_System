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

Fact::Fact(std::string & name) : szName(name), iState(STATE_FALSE), bIsSet(false)
{
	
}

Fact::Fact() : szName(""), iState(STATE_FALSE), bIsSet(false)
{
	
}

void Fact::SetState(int state) 
{
	if (!bIsSet || iState == state)
		iState = state;
	else
	{
		std::cerr <<  "Incoherence in the rules" << std::endl;
		exit(0);
	}
}