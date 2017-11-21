// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TokenMixed.class.cpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/20 16:49:31 by semartin          #+#    #+#             //
//   Updated: 2017/11/20 16:49:32 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Token.class.hpp"
#include "TokenMixed.class.hpp"

TokenFact::TokenFact(bool Neg, Fact *fact) : Token(false),  bNeg(Neg), _fact(fact)
{
	return ;
}