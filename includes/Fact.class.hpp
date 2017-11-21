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
#include "Instr.class.hpp"

class Fact
{

private:
	std::vector<Instr> tabLink;

	std::string const szName;
	bool	bAbstract;
	Fact();

public:
	Fact(std::string & name, bool abstract);
	Fact(std::string & name);
	~Fact() {} ;

	std::string getName() { return szName; };
	bool 	getAbstract() { return bAbstract; };
};