#include "Date.h"

string Date::DateToString()
{
	string formatMonth;
	string formatDay;

	if (this->month < 10)	// If month number only contains one digit, add a "0" as a prefix.
	{
		formatMonth = "0" + std::to_string(this->month);
	}
	else
	{
		formatMonth = std::to_string(this->month);
	}

	if (this->day < 10)	// Day number as well.
	{
		formatDay = "0" + std::to_string(this->day);
	}
	else
	{
		formatDay = std::to_string(this->day);
	}
	string date = formatMonth + "-" + formatDay + "-" + std::to_string(this->year);	// Date string format
	
	return date;
}

bool operator==(Date d1, Date d2)
{
	return(d1.day == d2.day && d1.month == d2.month && d1.year == d2.year);
}

bool operator!=(Date d1, Date d2)
{
	return !(d1 == d2);
}

int operator-(Date d1, Date d2)
{
	tm info1;
	info1.tm_year = d1.year-1900;
	info1.tm_mon = d1.month-1;
	info1.tm_mday = d1.day;

	tm info2;
	info2.tm_year = d2.year - 1900;
	info2.tm_mon = d2.month - 1;
	info2.tm_mday = d2.day;
	return (mktime(&info1) - mktime(&info2)) / 24 / 3600;
}

Date ReadCurrentTime()	// Gets current system date and returns a Date object.
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	int month = st.wMonth;
	int day = st.wDay;
	int year = st.wYear;
	Date currentDate = Date(month, day, year);
	return currentDate;
}

Date FormatStringToDate(string formatDate)
{
	std::vector<int> nums;
	string tempResult;
	for (int i = 0; i < formatDate.size(); ++i)
	{
		tempResult += formatDate[i];
		if (formatDate[i] == '-')
		{
			nums.push_back(std::stoi(tempResult));
			tempResult = "";
		}
	}
	nums.push_back(stoi(tempResult));

	if (nums.size() != 3)
	{
		cout << "Wrong date format!" << endl;
		return Date();
	}
	else
	{
		return Date(nums[0],nums[1],nums[2]);
	}
}

void ShowCurrentDate()	// Outputs the format date string.
{
	Date currentDate = ReadCurrentTime();
	cout << "Current date is (MM/DD/YYYY):" << currentDate.DateToString() << endl;
}
