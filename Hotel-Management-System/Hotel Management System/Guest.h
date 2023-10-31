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

class Guest
{
private:
	string name;
	string idNum;
	string phoneNum;
	Date startDate;
	unsigned int leftDayIn;
	unsigned int roomType;
	unsigned int roomNum;

public:
	static std::vector<Guest> guestList;
	Guest() = default;
	Guest(string name, string idNum, string phoneNum, Date startDate, unsigned int leftDayIn, unsigned int roomType, int roomNum)
		:name(name), idNum(idNum), phoneNum(phoneNum), startDate(startDate), leftDayIn(leftDayIn), roomType(roomType), roomNum(roomNum) {}

	void Register();
	void Leave();
	void Purchase(Management& dailyIncome);
	double CauculatePriceRoom();
	void ShowGuestList();

	friend void JudgeLeave(Management& dailyIncome);
	friend void WriteGuestInFile();
};

Guest CreateGuest();
void JudgeLeave(Management& dailyIncome);
void WriteGuestInFile();
void ReadGuestFromFile();
