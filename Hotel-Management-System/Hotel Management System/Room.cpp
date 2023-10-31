#include "Room.h"

std::vector<Room> Room::roomList;
std::unordered_map<unsigned int, double> Room::priceSheet;

void Room::AddRoomInfo()		
{
	Room::roomList.push_back(*this);
	WriteRoomsInfoToFile();
}

void Room::DeleteRoomInfo()	
{
	auto it = SearchRoomInfo(this->number);
	if (it == Room::roomList.end())		// Search with the room number of this object and check if it can be found.
	{
		cout << "Cannot find the room with this number." << endl;
		return;
	}
	else
	{
		Room::roomList.erase(it);		// Erase and rewrite.
		WriteRoomsInfoToFile();
	}
}

void Room::AlterRoomOccupied()		
{
	auto it = SearchRoomInfo(this->number);
	if (it == Room::roomList.end())
	{
		cout << "Cannot find the room with this number." << endl;
		return;
	}
	else
	{
		if (this->isOccupied)
		{
			this->isOccupied = false;
		}
		else
		{
			this->isOccupied = true;
		}
		*it = Room(this->roomType, this->number, this->price, this->isOccupied);	// Write new data to the list.
		WriteRoomsInfoToFile();
	}
}

void Room::ShowRoomList()
{
	cout << "Room Type:" << "\t\t" << "Number:" << "\t\t" << "Price:" << "\t\t" << "Is Occupied" << endl;
	for (auto it = Room::roomList.begin(); it != Room::roomList.end(); ++it)
	{
		cout << it->roomType << "\t\t" << it->number << "\t\t" << it->price << "\t\t" << std::boolalpha << it->isOccupied << std::noboolalpha << endl;
	}
}

Room CreateRoom()		// Customized room type and number, isOccupied will be set to default and price will be defined from the type-price map 
{
	unsigned int roomType;
	int number;
	double price;
	bool isOccupied;

	cout << "Please enter the room type of the guest wants to live in (1:single, 2:double, 3:deluxe) :";
	cin >> roomType;
	cout << "Please enter the number of room:";
	cin >> number;
	price = Room::priceSheet[roomType];
	isOccupied = false;
	Room roomEntity = Room(roomType, number, price, isOccupied);
	return roomEntity;
}

std::vector<Room>::iterator SearchRoomInfo(int num)	
{
	auto it = Room::roomList.begin();	
	for (; it != Room::roomList.end(); ++it)
	{
		if (it->number == num)		// Search by room number
		{
			break;
		}
	}
	return it;
}

bool CheckIfFull(unsigned int roomTypeNum)
{
	for (auto it = Room::roomList.begin(); it != Room::roomList.end(); ++it)
	{
		if (it->roomType == roomTypeNum)
		{
			if (!it->isOccupied)	// Once one room is empty, return false.
			{
				return false;
			}
		}
	}
	return true;		// If all rooms are occupied return true.
}

int AssignEmptyRoom(unsigned int roomType)
{
	if (CheckIfFull(roomType))
	{
		cout << "No room of such type left!" << endl;		// If this type of rooms are full, return -1 as an error code.
		return -1;
	}
	else
	{
		for (auto it = Room::roomList.begin(); it != Room::roomList.end(); ++it)
		{
			if (it->roomType == roomType)
			{
				if (!it->isOccupied)
				{
					cout << "Room "<<it->number<<" assigned automatically!" << endl;
					return it->number;			//	return the room number
				}
			}
		}
		cout << "Can not find rooms with this type!" << endl;		//If the type can not be found, return -2 as an error code.
		return -2;
	}
}

void CreatePriceSheet()
{
	unsigned int roomType;
	cout << "Please enter the number of room types:" << endl;
	cin >> roomType;
	double price;
	for (unsigned int i = 1; i <= roomType; ++i)
	{
		cout << "Please enter the price for room of type " << i << " : " << endl;
		cin >> price;
		Room::priceSheet[i] = price;
	}
}

void AlterPriceSheet()
{
	cout << "Pease enter the roomtype whose price you'd like to change: " << endl;
	unsigned int choice;
	cin >> choice;
	if (choice > Room::priceSheet.size())
	{
		cout << "Cannot find this room type, please try again!" << endl;
		return;
	}

	cout << "Pease enter the new price: " << endl;
	double newPrice;
	cin >> newPrice;
	Room::priceSheet[choice] = newPrice;
	cout << "The price of this room type successfully changed";
}

void ShowPriceSheet()
{
	cout << "Room Type:" << "\t\t" << "Price:" << endl;
	for (auto it = Room::priceSheet.begin(); it != Room::priceSheet.end(); ++it)
	{
		cout << it->first << "\t\t" << it->second << endl;
	}
}

void WritePriceInfoToFile()
{
	std::ofstream ofs;
	ofs.open("./Data/PriceSheet.txt", std::ios::out);
	if (!ofs)
	{
		cout << "Cannot write data to file!" << endl;
		return;
	}

	std::size_t size = Room::priceSheet.size();
	for (int i = 1; i <= size; ++i)
	{
		ofs << i << '\t' << Room::priceSheet[i] << endl;
	}
	ofs.close();
}

void ReadPriceInfoFromFile()
{
	unsigned int roomType;
	double price;

	std::ifstream ifs;
	ifs.open("./Data/PriceSheet.txt", std::ios::in);
	if (!ifs)
	{
		cout << "Cannot read data from file!" << endl;
		return;
	}
	while (ifs >> roomType >> price)
	{
		Room::priceSheet[roomType] = price;
	}
	ifs.close();
}

void WriteRoomsInfoToFile()
{
	std::ofstream ofs;
	ofs.open("./Data/RoomList.txt", std::ios::out);
	if (!ofs)
	{
		cout << "Cannot write data to file!" << endl;
		return;
	}

	std::size_t size = GetRoomQuantity();
	for (int i = 0; i < size; ++i)
	{
		ofs << Room::roomList[i].roomType << '\t' << Room::roomList[i].number << '\t' << Room::roomList[i].price << '\t' << Room::roomList[i].isOccupied << endl;
	}
	ofs.close();
}

void ReadRoomsInfoFromFile()
{
	unsigned int roomType;
	int number;
	double price;
	bool isOccupied;

	std::ifstream ifs;
	ifs.open("./Data/RoomList.txt", std::ios::in);
	if (!ifs)
	{
		cout << "Cannot read data from file!" << endl;
		return;
	}
	while (ifs >> roomType >> number >> price >> isOccupied)
	{
		Room roomEntity = Room(roomType, number, price, isOccupied);		// Initialize a Room object from the data in file and add it to the list.
		Room::roomList.push_back(roomEntity);
	}
	ifs.close();
}
