#include "Controller.h"

void Controller::InitObjects()
{
	unsigned int managerFlag = 0;
	this->currentManager = CreateDailyRevenue(managerFlag);
	this->currentManager.RecordRevenue(managerFlag);

	if (Room::priceSheet.empty())
	{
		CreatePriceSheet();
	}

	if (Room::roomList.empty())
	{
		cout << "Please add at least one room to continue!" << endl;
		this->currentRoom = CreateRoom();
		this->currentRoom.AddRoomInfo();
	}
	else
	{
		this->currentRoom = *Room::roomList.begin();
	}

	if (Menu::itemList.empty())
	{
		cout << "Please add at least one item to menu to continue!" << endl;
		this->currentMenu = CreateItem();
		this->currentMenu.AddItem(this->currentManager);
	}
	else
	{
		this->currentMenu = *Menu::itemList.begin();
	}

	if (Guest::guestList.empty())
	{
		cout << "Please add at least one guest to continue!" << endl;
		this->currentGuest = CreateGuest();
		this->currentGuest.Register();
	}
	else
	{
		this->currentGuest = *Guest::guestList.begin();
	}

	this->currentManager.AddDayCostRoom();
	JudgeLeave(this->currentManager);
}

void InitFromFile()
{
	ReadRoomsInfoFromFile();
	ReadPriceInfoFromFile();
	ReadMenuFromFile();
	ReadGuestFromFile();
	ReadRevenueFromFile();
}

void Interface(Controller& ctrler)
{
	int* choiceArr = new int[2];
	cout << endl << "1. Guest operations\n" << "2. Room operations\n" << "3. Menu operations\n" << "4. Manager operations\n" << "5. Quit the system" << endl;
	while (choiceArr[0] != 5)
	{
		cout << "Please choose nex step:";
		cin >> choiceArr[0];
		switch (choiceArr[0])
		{
			case 1:
			{
				cout << endl << "1. Register\n" << "2. Purchase items\n" << "3. Show Guest List\n" << "4. Return to previous step" << endl << endl;
				cout << "Please choose next step:";
				cin >> choiceArr[1];
				while (choiceArr[1] != 4)
				{
					switch (choiceArr[1])
					{
						case 1:
						{
							ctrler.currentGuest = CreateGuest();
							ctrler.currentGuest.Register();
							break;
						}
						case 2:
						{
							ctrler.currentGuest.Purchase(ctrler.currentManager);
							break;
						}
						case 3:
						{
							ctrler.currentGuest.ShowGuestList();
							break;
						}
						case 4:
						{
							cout << "Returned to previous step!\n" << endl;
							break;
						}
						default:
						{
							cout << "Invalid choice, please reinput the choice:";
							cin >> choiceArr[1];
						}
					}
				}
			}
			case 2:
			{
				cout << endl << "1. Add a room\n" << "2. Delete a room\n" << "3. Show room list\n" <<
					"4. Alter price info\n" << "5. Show price info\n" << "6. Return to previous step" << endl;
				while (choiceArr[1] != 6)
				{
					cout << "Please choose next step:";
					cin >> choiceArr[1];
					switch (choiceArr[1])
					{
						case 1:
						{
							ctrler.currentRoom = CreateRoom();
							ctrler.currentRoom.AddRoomInfo();
							break;
						}
						case 2:
						{
							ctrler.currentRoom.DeleteRoomInfo();
							break;
						}
						case 3:
						{
							ctrler.currentRoom.ShowRoomList();
							break;
						}
						case 4:
						{
							AlterPriceSheet();	
							break;
						}
						case 5:
						{
							ShowPriceSheet();
							break;
						}
						case 6:
						{
							cout << "Returned to previous step!\n" << endl;
							break;
						}
						default:
						{
							cout << "Invalid choice, please reinput the choice:";
							cin >> choiceArr[1];
						}
					}
				}
			}
			case 3:
			{
				cout << endl << "1. Add an item\n" << "2. Delete an item\n" << "3. Show menu" << "4. Return to previous step\n" << endl;
				cout << "Please choose next step:" << endl;
				cin >> choiceArr[1];
				while (choiceArr[1] != 4)
				{
					switch (choiceArr[1])
					{
						case 1:
						{
							ctrler.currentMenu = CreateItem();
							ctrler.currentMenu.AddItem(ctrler.currentManager);
							break;
						}
						case 2:
						{
							ctrler.currentMenu.DeleteItem();
							break;
						}
						case 3:
						{
							ctrler.currentMenu.ShowMenuList();
							break;
						}
						case 4:
						{
							cout << "Returned to previous step!\n" << endl;
							break;
						}
						default:
						{
							cout << "Invalid choice, please reinput the choice:";
							cin >> choiceArr[1];
						}
					}
				}
			}
			case 4:
			{
				cout << endl << "1. Show the revenue today.\n" << "2. Show all previous revenues\n" << "3. Return to previous step\n" << endl;
				cout << "Please choose next step:" << endl;
				cin >> choiceArr[1];
				while (choiceArr[1] != 3)
				{
					switch (choiceArr[1])
					{
						case 1:
						{
							ctrler.currentManager.CalculateDayprofit();
							ctrler.currentManager.ShowRevenueToday();
							break;
						}
						case 2:
						{
							ctrler.currentManager.ShowPreviousRevenue();
							break;
						}
						case 3:
						{
							cout << "Returned to previous step!\n" << endl;
							break;
						}
					default:
						{
							cout << "Invalid choice, please reinput the choice:";
							cin >> choiceArr[1];
						}
					}
				}
			}
			case 5: 
			{
				ctrler.currentManager.CalculateDayprofit();
				cout << "Today's revenue has been written to file!" << endl;
				delete[] choiceArr;
				cout << "System Quit." << endl;
				break;
			}
			default:
			{
				cout << "Invalid choice, please reinput the choice:";
				cin >> choiceArr[0];
			}
		}
	}
}

void Exec()
{
	cout << "Welcome to hotel management system!" << endl;
	InitFromFile();
	cout << "Datas have been successfully read to the system!" << endl;
	cout << "System initializing..." << endl;
	Controller ctrler = Controller();
	ctrler.InitObjects();
	
	cout << "System initialized! Feel free to manage the hotel!" << endl;
	Interface(ctrler);
	return;
}
