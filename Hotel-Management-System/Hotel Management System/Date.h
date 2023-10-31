#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

//	This class defines how to describe a date and some related function.
class Date {
public:
	int day;
	int month;
	int year;

	Date() {}
	Date(int month, int day, int year) :
		month(month), day(day), year(year) {}

	string DateToString();	// Converts a Date object to the date string format MM-DD-YYYY and returns it.
};

bool operator==(Date d1, Date d2);		// Judge if two dates are identical.
bool operator!=(Date d1, Date d2);
int operator-(Date d1, Date d2);

Date ReadCurrentTime();	// Gets current system date.
Date FormatStringToDate(string formatDate);	// Convert format string to Date object
void ShowCurrentDate();		// Outputs the format date string.
