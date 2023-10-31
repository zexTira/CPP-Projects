#include "Management.h"
#include "Guest.h"

std::vector<Management> Management::dailyManagementList;

void Management::RecordRevenue(unsigned int sign)
{
	if (sign)
	{
		Management::dailyManagementList.push_back(*this);
		WriteRevenueToFile();
	}
}

void Management::AddDayCostRoom()
{
	this->dayCost += this->managementFeePerRoom * Guest::guestList.size();
	WriteRevenueToFile();
}

void Management::AddDayCostMenu(double cost)
{
	this->dayCost += cost;
	WriteRevenueToFile();
}

void Management::AddDayIncome(double income)
{
	this->dayIncome += income;
	WriteRevenueToFile();
}

void Management::CalculateDayprofit()
{
	dayProfit = dayIncome - dayCost;
	WriteRevenueToFile();
}

void Management::ShowRevenueToday()
{
	cout << "Date: " << this->currentDate.DateToString() << endl;
	cout << "Cost today: " << this->dayCost;
	cout << "Income today: " << this->dayIncome;
	cout << "Profit today:" << this->dayProfit;
}

void Management::ShowPreviousRevenue()
{
	cout << "Date: " << "\t\t" << "Cost: " << "\t\t" << "Income: " << "\t\t" << "Profit:" << endl;
	for (auto it = Management::dailyManagementList.begin(); it != Management::dailyManagementList.end(); ++it)
	{
		cout << it->currentDate.DateToString() << "\t\t" << it->dayCost << "\t\t" << it->dayIncome << "\t\t" << it->dayProfit << endl;
	}
}

Management& CreateDailyRevenue(unsigned int& sign)
{
	if (Management::dailyManagementList.empty())
	{
		Date currentDate = ReadCurrentTime();
		double managementFee;
		cout << "Please enter the management fee per room today:";
		cin >> managementFee;

		Management managerEntity = Management(currentDate, managementFee);
		sign = 1;
		return managerEntity;
	}
	else
	{
		auto it = Management::dailyManagementList.end() - 1;
		if (it->currentDate != ReadCurrentTime())
		{
			Date currentDate = ReadCurrentTime();
			double managementFee;
			cout << "Please enter the management fee per room today:";
			cin >> managementFee;

			Management managerEntity = Management(currentDate, managementFee);
			sign = 1;
			return managerEntity;
		}
		else
		{
			sign = 0;
			return *it;
		}
	}
}

void WriteRevenueToFile()
{
	std::ofstream ofs;
	ofs.open("./Data/DailyIncome.txt", std::ios::out);
	if (!ofs)
	{
		cout << "Cannot write data to file!" << endl;
		return;
	}

	std::size_t size = Management::dailyManagementList.size();
	for (int i = 0; i < size; ++i)
	{
		ofs << Management::dailyManagementList[i].currentDate.DateToString() << '\t' << Management::dailyManagementList[i].managementFeePerRoom << '\t'
			<< Management::dailyManagementList[i].dayCost << '\t' << Management::dailyManagementList[i].dayIncome << '\t'
			<< Management::dailyManagementList[i].dayProfit << endl;
	}
	ofs.close();
}

void ReadRevenueFromFile()
{
	string currentDate;
	double managementFeePerRoom;
	double dayCost;
	double dayIncome;
	double dayProfit;

	std::ifstream ifs;
	ifs.open("./Data/DailyIncome.txt", std::ios::in);
	if (!ifs)
	{
		cout << "Cannot read data from file!" << endl;
		return;
	}
	while (ifs >> currentDate >> managementFeePerRoom >> dayCost >> dayIncome >> dayProfit)
	{
		Management managerEntity = Management(FormatStringToDate(currentDate), managementFeePerRoom, dayCost, dayIncome, dayProfit);
		Management::dailyManagementList.push_back(managerEntity);
	}
	ifs.close();
}
