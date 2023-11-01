#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"
#include "Date.h"
#include "Room.h"
#include "Menu.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

// This class defines some behaviors of guest like registering, purchasing, leaving.
class Guest
{
private:
	string name;		// These are basic info of a guest.
	string idNum;
	string phoneNum;
	Date startDate;
	unsigned int leftDayIn;
	unsigned int roomType;
	unsigned int roomNum;

public:
	static std::vector<Guest> guestList;		//	Vector storing guests
	Guest() = default;
	Guest(string name, string idNum, string phoneNum, Date startDate, unsigned int leftDayIn, unsigned int roomType, int roomNum)
		:name(name), idNum(idNum), phoneNum(phoneNum), startDate(startDate), leftDayIn(leftDayIn), roomType(roomType), roomNum(roomNum) {}

	void Register();	// Register a guest and push into list
	void Leave();		// When a guest leaves the hotel delete it from the list.
	void Purchase(Management& dailyIncome);	//	A guest purchases some items from menu and calculate income by a reference of management object
	double CauculatePriceRoom();	//	 Calculates the total cost of a guest living in a room for seeral days.
	void ShowGuestList();	

	friend void JudgeLeave(Management& dailyIncome);	
	friend void WriteGuestInFile();
};

Guest CreateGuest();	// Create a guest entity
void JudgeLeave(Management& dailyIncome);	// Every day we judge how many guests leave and calculate the income by a reference of management object
void WriteGuestInFile();
void ReadGuestFromFile();
