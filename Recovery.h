/*
 * Recovery.h
 *
 *  Created on: 7.07.2017 ã.
 *      Author: IVY
 */

#ifndef RECOVERY_H_
#define RECOVERY_H_
#include "pugixml.hpp"
#include "Player.h"
#include "Shared.h"

#include <iostream>
#include <sstream>
#include <deque>

using std::endl;
using std::cout;
using std::cerr;
using std::deque;
using std::stringstream;

class Recovery
{
public:
	Recovery();
	virtual ~Recovery();

	// returns map with all the data from the file
	deque< Player* > ReadFromXML();

	// puts data in the same file and deletes the previous data
	void WriteXML(deque <Player*>);

	// prints the data
	void Print(deque <Player*>);
};

#endif /* RECOVERY_H_ */
