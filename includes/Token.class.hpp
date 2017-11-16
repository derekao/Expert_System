// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Token.class.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: semartin <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/04/04 17:08:56 by semartin          #+#    #+#             //
//   Updated: 2017/04/04 17:08:59 by semartin         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TOKEN_CLASS_HPP
# define TOKEN_CLASS_HPP

# include <iostream>

class Token
{
	
private:
	bool _bIsOperator;

	Token(void);

public:
	Token(bool bIsOperator);
	~Token(void) {};

	/* Accessors */
	bool bGetIsOperator(void) const;
};

#endif
