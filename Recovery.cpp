/*
 * Recovery.cpp
 *
 *  Created on: 7.07.2017 ã.
 *      Author: IVY
 */

#include "Recovery.h"

Recovery::Recovery()
{
	// TODO Auto-generated constructor stub

}

Recovery::~Recovery()
{
	// TODO Auto-generated destructor stub
}

map<int, Statistics> Recovery::ReadFromXML()
{
	pugi::xml_document doc;
	if (!doc.load_file("Recovery.xml"))
	{
		cerr << "The XML file would not load." << endl;
	}

	// making helper variables
	int playerPos;
	Statistics stat;

	// the map which will be returned
	map<int, Statistics> result;

	pugi::xml_node players = doc.first_child();

	for (pugi::xml_node player = players.first_child(); player;
			player = player.next_sibling())
	{
		// taking the position for the map
		playerPos = player.attribute("Position").as_int();

		// filling the Statistics object
		stat.setIPlayerPosition(playerPos);
		stat.setColor(player.child("Name").text().as_string());
		stat.setISteps(player.child("Steps").text().as_int());
		stat.setITaken(player.child("Taken").text().as_int());
		stat.setIHadTaken(player.child("HadTaken").text().as_int());

		// putting the data in the map
		// key - playerPos
		// value - Statistics object
		result[playerPos] = stat;

	}

	return result;
}

void Recovery::WriteXML(map<int, Statistics> stat)
{
	pugi::xml_document doc;
	// making the biggest node
	pugi::xml_node game = doc.append_child("Game");

	for (map<int, Statistics>::iterator i = stat.begin();
			i != stat.end(); i++)
	{
		// making the player node
		pugi::xml_node player = game.append_child("Player");
		player.append_attribute("Position").set_value(i->first);

		// making the subnodes of player
		pugi::xml_node name = player.append_child("Name");
		name.append_child(pugi::node_pcdata).set_value(	i->second.getColor().c_str());

		// the rest of the values are integer type and we can't use them
		// in the set_value method - so we are changing them to be string
		// value with stringstream variable
		stringstream str;

		pugi::xml_node steps = player.append_child("Steps");
		str << i->second.getISteps();
		steps.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		// cleaning the input before using the variable again
		str.str();

		pugi::xml_node taken = player.append_child("Taken");
		str << i->second.getITaken();
		taken.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		// cleaning
		str.str();

		pugi::xml_node hadTaken = player.append_child("HadTaken");
		str << i->second.getIHadTaken();
		hadTaken.append_child(pugi::node_pcdata).set_value(str.str().c_str());
	}

	doc.save_file("Recovery.xml");
}

void Recovery::Print(map<int, Statistics> mP)
{
	for (map<int, Statistics>::iterator o = mP.begin(); o != mP.end();
			o++)
	{
		cout << o->first << " " << endl;
		// the value of the key is an object so we call its' print method
		o->second.print();
	}
}
