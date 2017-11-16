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
Operator::Operator(int iID) : Token(true), _iID(iID)
{
	return ;
}

/* Accessors */
int Operator::iGetID(void) const
{
	return (_iID);
}

int Operator::iGetPrecedence(void) //TODO
{
/*	if (_iID == TOKEN_ADD || _iID == TOKEN_MINUS)
	{
		return 1;
	}
	else if (_iID == TOKEN_PRODUCT || _iID == TOKEN_DIVISION)
	{
		return 2;
	}
	else if (_iID == TOKEN_OPEN || _iID == TOKEN_CLOSE)
	{
		return 3;
	}
	else
	{
		return -1;
	}*/
	return (0);
}

