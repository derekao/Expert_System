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