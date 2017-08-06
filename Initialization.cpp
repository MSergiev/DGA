/*
 * Initialization.cpp
 *
 *  Created on: 4.08.2017 ã.
 *      Author: IVY
 */

#include "Initialization.h"

Initialization::Initialization()
		: width()
{
	InitializeData();

}

Initialization::~Initialization()
{

}

int Initialization::getHeight() const
{
	return height;
}

int Initialization::getBoardHeight() const
{
	return BOARD_HEIGHT;
}

void Initialization::setBoardHeight(int boardHeight)
{
	BOARD_HEIGHT = boardHeight;
}

int Initialization::getBoardLength() const
{
	return BOARD_LENGTH;
}

void Initialization::setBoardLength(int boardLength)
{
	BOARD_LENGTH = boardLength;
}

int Initialization::getBoardWidth() const
{
	return BOARD_WIDTH;
}

void Initialization::setBoardWidth(int boardWidth)
{
	BOARD_WIDTH = boardWidth;
}

int Initialization::getButtonHeight() const
{
	return BUTTON_HEIGHT;
}

void Initialization::setButtonHeight(int buttonHeight)
{
	BUTTON_HEIGHT = buttonHeight;
}

int Initialization::getButtonWidth() const
{
	return BUTTON_WIDTH;
}

void Initialization::setButtonWidth(int buttonWidth)
{
	BUTTON_WIDTH = buttonWidth;
}

int Initialization::getFieldHeight() const
{
	return FIELD_HEIGHT;
}

void Initialization::setFieldHeight(int fieldHeight)
{
	FIELD_HEIGHT = fieldHeight;
}

int Initialization::getFontSize() const
{
	return FONT_SIZE;
}

void Initialization::setFontSize(int fontSize)
{
	FONT_SIZE = fontSize;
}

int Initialization::getFw() const
{
	return fw;
}

void Initialization::setFw(int fw)
{
	this->fw = fw;
}

int Initialization::getRulesHeight() const
{
	return RULES_HEIGHT;
}

void Initialization::setRulesHeight(int rulesHeight)
{
	RULES_HEIGHT = rulesHeight;
}

int Initialization::getRulesWidth() const
{
	return RULES_WIDTH;
}

void Initialization::setRulesWidth(int rulesWidth)
{
	RULES_WIDTH = rulesWidth;
}

int Initialization::getSquareSize() const
{
	return SQUARE_SIZE;
}

void Initialization::setSquareSize(int squareSize)
{
	SQUARE_SIZE = squareSize;
}

void Initialization::setHeight(int height)
{
	this->height = height;
}

int Initialization::getWidth() const
{
	return width;
}

void Initialization::setWidth(int width)
{
	this->width = width;

}

void Initialization::InitializeData()
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("Constants.xml");

	// checking if the file is loaded
	if (!res)
	{
		// show what is the problem
		cerr << "ERROR with the xml file: " << res.description()
				<< endl;
		return;
	}

	pugi::xml_node constants = doc.first_child();
	pugi::xml_node sizes = constants.first_child();

	for (pugi::xml_node size = sizes.first_child(); size;
			size = size.next_sibling())
	{
		width = setWidth(size.child("WIDTH").text().as_int());
		height = setHeight(size.child("HEIGHT").text().as_int());
		fw = setFieldHeight(
				size.child("FIELD_WIDTH").text().as_int());
		BOARD_LENGTH = setBoardLength(
				size.child("BOARD_LENGTH").text().as_int());
		BOARD_WIDTH = setBoardWidth(
				size.child("BOARD_WIDTH").text().as_int());
		BOARD_HEIGHT = setBoardHeight(
				size.child("BOARD_HEIGHT").text().as_int());
		SQUARE_SIZE = setSquareSize(
				size.child("SQUARE_SIZE").text().as_int());
		BUTTON_WIDTH = setSquareSize(
				size.child("BUTTON_WIDTH").text().as_int());
		BUTTON_HEIGHT = setSquareSize(
				size.child("BUTTON_HEIGHT").text().as_int());
		FONT_SIZE = setSquareSize(
				size.child("FONT_SIZE").text().as_int());
		RULES_WIDTH = setSquareSize(
				size.child("RULES_WIDTH").text().as_int());
		RULES_HEIGHT = setSquareSize(
				size.child("RULES_HEIGHT").text().as_int());
	}

}

template<typename T>
int InitIntData(int variable, const char* name)
{

	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file("Constants.xml");

	// checking if the file is loaded
	if (!res)
	{
		// show what is the problem
		cerr << "ERROR with the xml file: " << res.description()
				<< endl;
		return;
	}

	pugi::xml_node constants = doc.first_child();
	pugi::xml_node sizes = constants.first_child();

	string intString = "int";
	string str = "string";

	for (pugi::xml_node constants = constants.first_child();
			constants; constants = constants.next_sibling())
	{
		for (pugi::xml_node size = sizes.first_child(); size; size =
				size.next_sibling())
		{
			if (intString.compare(typeid(variable).name()))
			{
				return size.child(name).text().as_int();
			} else
			{
				if (str.compare(typeid(variable).name()))
				{
					return size.child(name).text().as_string();
				}
			}
		}
	}
}
