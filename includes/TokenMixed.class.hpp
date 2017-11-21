// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   TokenMixed.class.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/20 16:49:44 by semartin          #+#    #+#             //
//   Updated: 2017/11/20 16:49:44 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#pragma once

#include <iostream>
#include "Token.class.hpp"
#include "Fact.class.hpp"

class TokenMixed : public Token
{

private:
	bool 	bNeg;
	Fact 	*_fact;

	TokenMixed();

public:
	TokenMixed(bool Neg, Fact *fact);
	virtual ~TokenMixed(void) {};

	/*Accessors*/
	bool	bGetNeg() const { return bNeg; } ;
	bool	getFact() const { return _fact; } ;

};