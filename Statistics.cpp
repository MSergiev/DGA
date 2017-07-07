/*
 * Statistics.cpp
 *
 *  Created on: 7.07.2017 ã.
 *      Author: IVY
 */

#include "Statistics.h"

Statistics::Statistics()
		: m_iHadTaken(), m_iPlayerPosition(), m_iSteps(), m_iTaken(), m_strColor()
{
	// TODO Auto-generated constructor stub

}

const string& Statistics::getColor() const
{
	return m_strColor;
}

void Statistics::setColor(const string& color)
{
	this->m_strColor = color;
}

int Statistics::getIHadTaken() const
{
	return m_iHadTaken;
}

void Statistics::setIHadTaken(int iHadTaken)
{
	m_iHadTaken = iHadTaken;
}

int Statistics::getIPlayerPosition() const
{
	return m_iPlayerPosition;
}

void Statistics::setIPlayerPosition(int iPlayerPosition)
{
	m_iPlayerPosition = iPlayerPosition;
}

int Statistics::getISteps() const
{
	return m_iSteps;
}

void Statistics::setISteps(int iSteps)
{
	m_iSteps = iSteps;
}

int Statistics::getITaken() const
{
	return m_iTaken;
}

void Statistics::setITaken(int iTaken)
{
	m_iTaken = iTaken;
}

Statistics::~Statistics()
{
	// TODO Auto-generated destructor stub
}

void Statistics::print()
{
	cout << "Color: " << getColor() << endl
			<< "Steps: " << getISteps() << endl
			<< "Taken: " << getITaken() << endl
			<< "Had taken: " << getIHadTaken() << endl
	<< endl;
}
