#pragma once
#include "Management.h"
#include "Room.h"
#include "Guest.h"
#include "Menu.h"

class Controller {
private:
	Management currentManager;
	Room currentRoom;
	Guest currentGuest;
	Menu currentMenu;

public:
	Controller() = default;

	void InitObjects();

	friend void Interface(Controller& ctrler);
};

void InitFromFile();
void Interface(Controller& ctrler);
void Exec();
