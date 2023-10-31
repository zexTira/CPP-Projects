#pragma once
#include <iostream>
#include <Vector>
#include "Date.h"
#include "Room.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Management {
private:
	double managementFeePerRoom;
	double dayCost;
	double dayIncome;
	double dayProfit;

public:
	Date currentDate;
	static std::vector<Management> dailyManagementList;

	Management() = default;
	Management(Date currDate, double managementFee) :
		currentDate(currDate), managementFeePerRoom(managementFee), dayCost(0), dayIncome(0), dayProfit(0) {};
	Management(Date currDate, double managementFee, double dayCost, double dayIncome, double dayProfit) :
		currentDate(currDate), managementFeePerRoom(managementFee), dayCost(dayCost), dayIncome(dayIncome), dayProfit(dayProfit) {};

	void RecordRevenue(unsigned int sign);
	void AddDayCostRoom();
	void AddDayCostMenu(double cost);
	void AddDayIncome(double income);
	void CalculateDayprofit();
	void ShowRevenueToday();
	void ShowPreviousRevenue();

	friend void WriteRevenueToFile();
};

Management& CreateDailyRevenue(unsigned int& sign);
void WriteRevenueToFile();
void ReadRevenueFromFile();
