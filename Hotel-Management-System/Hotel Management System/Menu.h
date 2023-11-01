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

// The class defines some operations on menu, like adding / deleting / searching items, change quantities of items
class Menu
{
private:
	string name;		// These are basic info of an item.
	unsigned int count;
	double cost;
	double price;

public:
	static std::vector<Menu> itemList;	// Vector storing item objects

	Menu() = default;
	Menu(string name, unsigned int count, double cost, double price) :
		name(name), count(count), cost(cost), price(price) {}

	void AddItem(Management& dailyCost);	//	Add item to the list and receive the cost by a manament object.
	void DeleteItem();
	void ReduceQuantity(unsigned int quantity);	// Reduce the quantity of an item by the param quantity.
	bool CompareQuantityBigger(unsigned int quantity);	// Campare if the quantity of an item is greater than param quantity.
	double CalculateCost();		//	Calculate the cost and return it.
	void ShowMenuList();

	friend double GetCurrentPrice(vector<Menu>::iterator itemIt);	
	friend std::vector<Menu>::iterator SearchForItem(string itemName);
	friend void WriteMenuToFile();
};

Menu CreateItem();	// Create an item object
double GetCurrentPrice(vector<Menu>::iterator itemIt);		// Search for an item and return its current price.
std::vector<Menu>::iterator SearchForItem(string itemName);	// Search the item in the list and returns its iterator.
void WriteMenuToFile();
void ReadMenuFromFile();
