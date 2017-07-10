/*
 * Pawn.h
 *
 *  Created on: 10.07.2017 ã.
 *      Author: IVY
 */

#ifndef PAWN_H_
#define PAWN_H_


#include <iostream>
using std::endl;
using std::cout;
using std::cerr;
using std::string;

class Pawn
{
private:
	unsigned int m_uiPosition;
	string m_strColor;
public:
	Pawn();
	virtual ~Pawn();
};

#endif /* PAWN_H_ */
