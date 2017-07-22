/*
 * Recovery.cpp
 *
 *  Created on: 7.07.2017 ã.
 *      Author: IVY
 */

#include "Recovery.h"

bool Recovery::hasRolled;

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
	// the vector which will be returned
	deque<Player*> result;
	
	// sets the flag to false
	hasRolled = 0;

	pugi::xml_document doc;

	// checking if the file is loaded
	if (!doc.load_file("Recovery.xml"))
	{
		// return empty deque
		return result;
	}

	// make a variable with contains the data in which player you are in
	pugi::xml_node players = doc.first_child();
	// take the correct data for the flag
	hasRolled = players.first_attribute().as_bool();

	// for each node of the players
	for (pugi::xml_node player = players.first_child(); player;
			player = player.next_sibling())
		{
	
			// making helper object
			Player* person = new Player(NONE);
			// fill the Player object with the data from the xml
			// static_cast<Colors> - so we can give the right type of the color
			person->setEColor(static_cast<Colors>(player.child("Color").text().as_int()));
			person->setISteps(player.child("Steps").text().as_int());
			person->setITaken(player.child("Taken").text().as_int());
			person->setILost(player.child("Lost").text().as_int());
			person->setIActivePawns(player.child("Active").text().as_int());
			person->setIFinishPosition(player.child("Finished").text().as_int());
			person->setIDiceRoll(player.child("LastDiceRoll").text().as_int());

			// read pawn positions
			int count = 0;
			// the node of the pawns
			pugi::xml_node pawns = player.child("Pawns");
			// for each pawn
			for(pugi::xml_node pawn = pawns.first_child(); pawn;
				   	pawn = pawn.next_sibling())
			{
				// put the data in the vector in the correct order
				person->m_vPawns[count]->setIXPosition(pawn.attribute("PosX").as_int());
				person->m_vPawns[count]->setIYPosition(pawn.attribute("PosY").as_int());
				// increment the helper variable
				count++;
			}
			// fill the deque which will be returned
			result.push_back(person);
	
		}
	return result;
}

void Recovery::WriteXML(deque< Player*> players, bool rolled)
{
	hasRolled = rolled;
	pugi::xml_document doc;
	doc.save_file("Recovery.xml");
	// making the biggest node
	pugi::xml_node game = doc.append_child("Game");
	game.append_attribute("Rolled") = rolled;

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
		// making it as a type text and setting it to the node
		// node_pcdata - Plain character data, i.e. 'text'
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

		pugi::xml_node lost = player.append_child("Lost");
		str << players[i]->getILost();
		lost.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		pugi::xml_node active = player.append_child("Active");
		str << players[i]->getIActivePawns();
		active.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		pugi::xml_node finished = player.append_child("Finished");
		str << players[i]->getIFinishPosition();
		finished.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		pugi::xml_node diceRoll = player.append_child("LastDiceRoll");
		str << players[i]->getIDiceRoll();
		diceRoll.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		// write pawn positions
		pugi::xml_node pawns = player.append_child("Pawns");
		// for each pawn
		for(unsigned j = 0; j < players[i]->m_vPawns.size(); j++)
		{
			// make a node pawn
			pugi::xml_node pawn = pawns.append_child("Pawn");
			// add attribute and give it value of the position of the pawn
			pawn.append_attribute("PosX") = players[i]->m_vPawns[j]->getIXPosition();
			pawn.append_attribute("PosY") = players[i]->m_vPawns[j]->getIYPosition();
		}

	}

	doc.save_file("Recovery.xml");
}

void Recovery::Print(deque< Player*> players)
{
	// for each player
	for (unsigned int i = 0; i < players.size(); i++)
	{
		// print the data
		players[i]->Print();
	}
}
