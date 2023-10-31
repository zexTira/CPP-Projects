#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Management.h"

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Menu
{
private:
	string name;
	unsigned int count;
	double cost;
	double price;

public:
	static std::vector<Menu> itemList;

	Menu() = default;
	Menu(string name, unsigned int count, double cost, double price) :
		name(name), count(count), cost(cost), price(price) {}

	void AddItem(Management& dailyCost);
	void DeleteItem();
	void ReduceQuantity(unsigned int quantity);
	bool CompareQuantityBigger(unsigned int quantity);
	double CalculateCost();
	void ShowMenuList();

	friend double GetCurrentPrice(vector<Menu>::iterator itemIt);
	friend std::vector<Menu>::iterator SearchForItem(string itemName);
	friend void WriteMenuToFile();
};

Menu CreateItem();
double GetCurrentPrice(vector<Menu>::iterator itemIt);
std::vector<Menu>::iterator SearchForItem(string itemName);
void WriteMenuToFile();
void ReadMenuFromFile();
