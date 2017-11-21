// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Operator.class.cpp                                 :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/04 17:16:38 by semartin          #+#    #+#             //
//   Updated: 2017/04/04 17:16:39 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Token.class.hpp"
#include "Operator.class.hpp"

/* CORE */
Operator::Operator(int iID) : Token(true), _iID(iID), _bNeg(false)
{
	return ;
}

Operator::Operator(int iID, bool bNeg) : Token(true), _iID(iID), _bNeg(bNeg)
{
	return ;
}

/* Accessors */
int Operator::iGetID(void) const
{
	return (_iID);
}

int Operator::bGetNeg(void) const
{
	return (_bNeg);
}


