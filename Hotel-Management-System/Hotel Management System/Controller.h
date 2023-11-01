#pragma once
#include "Management.h"
#include "Room.h"
#include "Guest.h"
#include "Menu.h"

//	 This class defines basic functions of the whole system.
class Controller {
private:
	Management currentManager;		// These are current objects of our customized objects
	Room currentRoom;
	Guest currentGuest;
	Menu currentMenu;

public:
	Controller() = default;

	void InitObjects();	// Initialize four objects in this class.

	friend void Interface(Controller& ctrler);
};

void InitFromFile();	// Read data from file and initialize those static lists.
void Interface(Controller& ctrler);	// User interface
void Exec();	// Execution process
