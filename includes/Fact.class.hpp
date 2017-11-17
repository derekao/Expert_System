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
#include "Link.class.hpp"

class Fact : public Link
{

private:
	std::string const szName;
	Fact();

public:
	Fact(std::string & name);
	~Fact() {} ;

	std::string getName() { return szName; };
};