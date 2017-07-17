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
	
	hasRolled = 0;

	pugi::xml_document doc;

	// checking if the file is loaded
	if (!doc.load_file("Recovery.xml"))
	{
		cerr << "The XML file would not load." << endl;
	} else {

	pugi::xml_node players = doc.first_child();
	hasRolled = players.first_attribute().as_bool();

	for (pugi::xml_node player = players.first_child(); player;
			player = player.next_sibling())
		{
	
			// making helper object
			Player* person = new Player(NONE);
			// filling the Player object
			person->setEColor(static_cast<Colors>(player.child("Color").text().as_int()));
			person->setISteps(player.child("Steps").text().as_int());
			person->setITaken(player.child("Taken").text().as_int());
			person->setILost(player.child("Lost").text().as_int());
			person->setIActivePawns(player.child("Active").text().as_int());
			person->setIDiceRoll(player.child("LastDiceRoll").text().as_int());
			// read pawn positions
			int count = 0;
			pugi::xml_node pawns = player.child("Pawns");
			cout << pawns.first_child().text() << endl;
			for(pugi::xml_node pawn = pawns.first_child(); pawn;
				   	pawn = pawn.next_sibling())
			{
				cout << pawn.first_attribute().as_int() << " " << count << endl;
				person->m_vPawns[count]->setIPosition(pawn.first_attribute().as_int());
				count++;
			}
			
			result.push_front(person);
	
		}
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
		pugi::xml_node diceRoll = player.append_child("LastDiceRoll");
		str << players[i]->getIDiceRoll();
		diceRoll.append_child(pugi::node_pcdata).set_value(str.str().c_str());
		str.str("");

		// write pawn positions
		pugi::xml_node pawns = player.append_child("Pawns");
		for(unsigned j = 0; j < players[i]->m_vPawns.size(); j++)
		{
			pugi::xml_node pawn = pawns.append_child("Pawn");
			pawn.append_attribute("Pos") = players[i]->m_vPawns[j]->getIPosition();
		}

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
