#pragma once
#include <iostream>
#include <Vector>
#include "Date.h"
#include "Room.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

//	 This class defines some related operation on daily revenue computing.
class Management {
private:
	double managementFeePerRoom;		// Defines daily management fee pri room.
	double dayCost;	// Defines daily cost.
	double dayIncome;	// Defines daily income.
	double dayProfit;	// Defines daily profit.

public:
	Date currentDate;	// Defines date of today.
	static std::vector<Management> dailyManagementList;	// Vector storing revenue every day.

	Management() = default;
	Management(Date currDate, double managementFee) :
		currentDate(currDate), managementFeePerRoom(managementFee), dayCost(0), dayIncome(0), dayProfit(0) {};
	Management(Date currDate, double managementFee, double dayCost, double dayIncome, double dayProfit) :
		currentDate(currDate), managementFeePerRoom(managementFee), dayCost(dayCost), dayIncome(dayIncome), dayProfit(dayProfit) {};

	void RecordRevenue(unsigned int sign);	// According to the value of sign, write today's revenue object into list or not, param: sign
	void AddDayCostRoom();	// Add daily cost from room maintenance
	void AddDayCostMenu(double cost);	//	Add daily cost from adding menu item
	void AddDayIncome(double income);	//Add daily income 
	void CalculateDayprofit();	
	void ShowRevenueToday();
	void ShowPreviousRevenue();

	friend void WriteRevenueToFile();
};

Management& CreateDailyRevenue(unsigned int& sign);	/* Create revenue object for today,
																						param: sign which indicates created a new object or continue using today's revenue object.
																						returns a reference of Manager object.*/
void WriteRevenueToFile();
void ReadRevenueFromFile();
