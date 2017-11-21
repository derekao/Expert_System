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
#include <vector>
#include "Instr.class.hpp"

class Fact
{

private:
	std::string const szName;

public:
	Fact(std::string & name);
	Fact();
	~Fact() {} ;

	std::vector<Instr *> tabLink;

	std::string szGetName() { return szName; };
};