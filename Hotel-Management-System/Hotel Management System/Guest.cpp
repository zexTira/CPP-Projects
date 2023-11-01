#include "Guest.h"

std::vector<Guest> Guest::guestList;

void Guest::Register()	// Let a guest register, record his/her info and set the room assigned occupied.
{
	Guest::guestList.push_back(*this);

	auto it = SearchRoomInfo(this->roomNum);
	Room thisroom = *it;
	thisroom.AlterRoomOccupied();
	WriteGuestInFile();
}

void Guest::Leave()
{
	for (auto it = Guest::guestList.begin(); it != Guest::guestList.end(); ++it)
	{
		if (it->name == this->name)
		{
			Guest::guestList.erase(it);

			auto it = SearchRoomInfo(this->roomNum);
			Room thisroom = *it;
			thisroom.AlterRoomOccupied();
			WriteGuestInFile();
			break;
		}
	}
}

void Guest::Purchase(Management& dailyIncome)
{
	string itemname;
	unsigned int quantity;

	cout << "Please enter the name of the item you want to buy:";
	cin >> itemname;
	auto it = SearchForItem(itemname);
	if (it == Menu::itemList.end())
	{
		cout << "Cannot find this item!" << endl;
		return;
	}

	cout << "Please enter the quantity of this item you want to buy:";
	cin >> quantity;
	if (it->CompareQuantityBigger(quantity))		
	{
		it->ReduceQuantity(quantity);		// Reduce the item number in inventory and calculate income.
		dailyIncome.AddDayIncome(quantity * GetCurrentPrice(it));
		cout << "Item ordered successfully!" << endl;
	}
	else    // If the guest wants more than currently in inventory, deny by returning.
	{
		cout << "The quantity you require is bigger than that of the item in inventory, please try again later!" << endl;
		return;
	}
}

double Guest::CauculatePriceRoom()		// Calculate according to price sheet.
{
	return Room::priceSheet[this->roomType] * this->leftDayIn;
}

void Guest::ShowGuestList()
{
	cout << "Name:" << "\t\t" << "ID number:" << "\t\t" << "Phone number:" << "\t\t"
		<< "Start Date:" << "\t\t" << "Days In:" << "Room Type" << "\t\t" << "Room Number:" << endl;
	for (auto it = Guest::guestList.begin(); it != Guest::guestList.end(); ++it)
	{
		cout << it->name << "\t\t" << it->idNum << "\t\t" << it->phoneNum << "\t\t"
			<< it->startDate.DateToString() << "\t\t" << it->leftDayIn << it->roomType << "\t\t" << it->roomNum << endl;
	}
}

Guest CreateGuest()	// Create a guest and assign an empty room for him/her. If there are no empty rooms, return a invalid object.
{
	string name;
	string idNum;
	string phoneNum;
	Date startDate;
	unsigned int leftDayIn;
	unsigned int roomType;
	int roomNum;

	cout << "please enter the name of guest:";
	cin >> name;
	cout << "please enter the id number of guest:";
	cin >> idNum;
	cout << "please enter the phone number of guest:";
	cin >> phoneNum;
	startDate = ReadCurrentTime();
	cout << "please enter the days the guest wants to live in:";
	cin >> leftDayIn;
	cout << "please enter the room type of the guest wants to live in (1:single, 2:double, 3....) :";
	cin >> roomType;
	roomNum = AssignEmptyRoom(roomType);
	if (roomNum < 0)
	{
		cout << "Room Assigning Failed! This type of room has already been full!" << endl;
		return Guest();
	}
	Guest guestEntity = Guest(name, idNum, phoneNum, startDate, leftDayIn, roomType, roomNum);
	return guestEntity;
}

void JudgeLeave(Management& dailyIncome)
{
	Date currentDate = ReadCurrentTime();
	for (auto it = Guest::guestList.begin(); it != Guest::guestList.end(); ++it)
	{
		int daysDiffrence = currentDate - it->startDate;	// using date difference to judge leave (the difference equal to day in means leave)
		if (daysDiffrence == it->leftDayIn)
		{
			dailyIncome.AddDayIncome(it->CauculatePriceRoom());
			it->Leave();
			break;
		}
	}
}

void WriteGuestInFile()
{
	std::ofstream ofs;
	ofs.open("./Data/GuestList.txt", std::ios::out);
	if (!ofs)
	{
		cout << "Cannot write data to file!" << endl;
		return;
	}

	std::size_t size = Guest::guestList.size();
	for (int i = 0; i < size; ++i)
	{
		ofs << Guest::guestList[i].name << '\t' << Guest::guestList[i].idNum << '\t' << Guest::guestList[i].phoneNum << '\t'
			<< Guest::guestList[i].startDate.DateToString() << '\t' << Guest::guestList[i].leftDayIn << '\t' << Guest::guestList[i].roomType << '\t'
			<< Guest::guestList[i].roomNum << endl;
	}
	ofs.close();
}

void ReadGuestFromFile()
{
	string name;
	string idNum;
	string phoneNum;
	string startDate;
	unsigned int leftDayIn;
	unsigned int roomType;
	int roomNum;

	std::ifstream ifs;
	ifs.open("./Data/GuestList.txt", std::ios::in);
	if (!ifs)
	{
		cout << "Cannot read data from file!" << endl;
		return;
	}
	while (ifs >> name >> idNum >> phoneNum >> startDate >> leftDayIn >> roomType >> roomNum)
	{
		Guest guestEntity = Guest(name, idNum, phoneNum, FormatStringToDate(startDate), leftDayIn, roomType, roomNum);		// Initialize a Guest object from the data in file and add it to the list.
		Guest::guestList.push_back(guestEntity);
	}
	ifs.close();
}
