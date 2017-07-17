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

deque< Player* > Recovery::ReadFromXML()
{
	pugi::xml_document doc;

	// checking if the file is loaded
	if (!doc.load_file("Recovery.xml"))
	{
		cerr << "The XML file would not load." << endl;
	}


	// the vector which will be returned
	deque<Player*> result;

	pugi::xml_node players = doc.first_child();

	for (pugi::xml_node player = players.first_child(); player;
			player = player.next_sibling())
	{

		// making helper object
		Player * person = new Player(NONE);
		// filling the Player object
		person->setEColor(static_cast<Colors>(player.child("Color").text().as_int()));
		person->setISteps(player.child("Steps").text().as_int());
		person->setITaken(player.child("Taken").text().as_int());
		person->setIHadTaken(player.child("HadTaken").text().as_int());
		person->setIDiceRoll(player.child("LastDiceRoll").text().as_int());
		result.push_back(person);

	}

	return result;
}

void Recovery::WriteXML(deque< Player*> players)
{
	pugi::xml_document doc;
	// making the biggest node
	pugi::xml_node game = doc.append_child("Game");

	for (unsigned int i = 0 ; i < players.size(); i++)
	{
		// making the player node
		pugi::xml_node player = game.append_child("Player");

		// the rest of the values are integer type and we can't use them
		// in the set_value method - so we are changing them to be string
		// value with stringstream variable
		stringstream str;

		str << players[i]->getEColor();
		// making the subnodes of player
		pugi::xml_node color = player.append_child("Color");
		color.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		pugi::xml_node steps = player.append_child("Steps");
		str << players[i]->getISteps();
		steps.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		// setting the input to empty before using the variable again
		str.str("");

		pugi::xml_node taken = player.append_child("Taken");
		str << players[i]->getITaken();
		taken.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		pugi::xml_node hadTaken = player.append_child("HadTaken");
		str << players[i]->getIHadTaken();
		hadTaken.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		pugi::xml_node diceRoll = player.append_child("LastDiceRoll");
		str << players[i]->getIDiceRoll();
		diceRoll.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

	}

	doc.save_file("Recovery.xml");
}

void Recovery::Print(deque< Player*> players)
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		players[i]->Print();
	}
}
