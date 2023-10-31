#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Room {
private:
	unsigned int roomType;		// Type of room(1: , 2: , 3: , 4:)
	int number;							// The number of room
	double price;						// The price of the room
	bool isOccupied;					// The status indicating if a room is occupied by a guest now.
	
public:
	static std::vector<Room> roomList;			// List storing	current rooms
	static std::unordered_map<unsigned int, double> priceSheet;		//	Hashmap storing the corresponding price for each room type.

	Room() = default;		// Default constructor
	Room(unsigned int roomType, int number, double price, bool isOccupied) :		// Customized constructor
		roomType(roomType), number(number), price(price), isOccupied(isOccupied) {};

	void AddRoomInfo();	// Add Room object to the list and rewrite room list.
	void DeleteRoomInfo();	// Delete room info from list and rewrite the list.
	void AlterRoomOccupied();	// Alter the room occupied status to another state.
	void ShowRoomList();	// Print the list of current rooms.

	friend std::vector<Room>::iterator SearchRoomInfo(int num);
	friend bool CheckIfFull(unsigned int roomTypeNum);
	friend int AssignEmptyRoom(unsigned int roomType);
	friend void WriteRoomsInfoToFile();
};

Room CreateRoom();		// Create new Room object and return the object
std::vector<Room>::iterator SearchRoomInfo(int num);	//	Search by room number in the room list, return the iterator of the room found.
bool CheckIfFull(unsigned int roomTypeNum);		//	Check if certain type of rooms are full, return a bool value.
int AssignEmptyRoom(unsigned int roomType);		//	When a guest is registered, assign an empty room with corresponding type for him/her, return the room number assigned
void CreatePriceSheet();
void AlterPriceSheet();
void ShowPriceSheet();
void WritePriceInfoToFile();		//	Write current price map info to file.
void ReadPriceInfoFromFile();	// Read current price info from file and initialize the price map.
void WriteRoomsInfoToFile();		//	Write current room list info to file.
void ReadRoomsInfoFromFile();	// Read current room info from file and initialize the room list.

inline std::size_t GetRoomQuantity()	// return how many rooms are there now
{
	return Room::roomList.size();
}