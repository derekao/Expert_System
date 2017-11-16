// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fact.class.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/11/16 15:29:27 by semartin          #+#    #+#             //
//   Updated: 2017/11/16 15:29:27 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //
 
#pragma once

#include <iostream>

#define FACT_TRUE 0
#define FACT_FALSE 1
#define FACT_UNKOWN 2

class Fact
{

private:
	std::string const szName;
	int iState;
	bool bIsSet;

	Fact();

public:
	Fact(std::string & name);
	~Fact() {} ;

	void setState(int state) { iSate = state; } ;
	void setbSet(bool isSet)  {bIsSet = isSet; } ;

	int iGetState() { return iState; } ;
	bool bGetIsSet() { return bIsSet; } ;

};