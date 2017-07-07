/*
 * Recovery.h
 *
 *  Created on: 7.07.2017 ã.
 *      Author: IVY
 */

#ifndef RECOVERY_H_
#define RECOVERY_H_

#include "pugixml.hpp"
#include "Statistics.h"

#include <iostream>
#include <sstream>
#include <map>

using std::endl;
using std::cout;
using std::cerr;
using std::map;
using std::stringstream;

class Recovery
{
public:
	Recovery();
	virtual ~Recovery();

	// returns map with all the data from the file
	map< int, Statistics > ReadFromXML();

	// puts data in the same file and deletes the previous data
	void WriteXML(map<int, Statistics>);

	// prints the data
	void Print(map<int, Statistics>);
};

#endif /* RECOVERY_H_ */
