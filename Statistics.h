/*
 * Statistics.h
 *
 *  Created on: 7.07.2017 ã.
 *      Author: IVY
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_
#include <iostream>
using std::endl;
using std::cout;
using std::cerr;
using std::string;

class Statistics
{
private:
	int m_iPlayerPosition;
	string m_strColor;
	int m_iSteps;
	int m_iTaken;
	int m_iHadTaken;

public:
	Statistics();
	virtual ~Statistics();

	//setters & getters
	const string& getColor() const;
	void setColor(const string& color);

	int getIHadTaken() const;
	void setIHadTaken(int iHadTaken);

	int getIPlayerPosition() const;
	void setIPlayerPosition(int iPlayerPosition);

	int getISteps() const;
	void setISteps(int iSteps);

	int getITaken() const;
	void setITaken(int iTaken);

	// methods
	void print();
};

#endif /* STATISTICS_H_ */
