#include "Menu.h"

std::vector<Menu> Menu::itemList;

void Menu::AddItem(Management& dailyCost)
{
	Menu::itemList.push_back(*this);
	dailyCost.AddDayCostMenu(this->CalculateCost());

	WriteMenuToFile();
	cout << "Item has been successfully added to the menu!"<<endl;
}

void Menu::DeleteItem()
{
	auto it = SearchForItem(this->name);
	if (it != Menu::itemList.end())
	{
		Menu::itemList.erase(it);
		WriteMenuToFile();
		cout << "Item has been successfully deleted!" << endl;
	}
	else
	{
		cout << "Item not found! Please check if the name of item exists!" << endl;
	}	
}

void Menu::ReduceQuantity(unsigned int quantity)
{
	this->count -= quantity;
	WriteMenuToFile();
}

bool Menu::CompareQuantityBigger(unsigned int quantity)
{
	if (quantity >= this->count)
	{
		return true;
	}
	else
	{
		return false;
	}
}

double Menu::CalculateCost()
{
	double cost = 0.0;
	cost += this->cost * this->count;
	return cost;
}

void Menu::ShowMenuList()
{
	cout << "Name:" << "\t\t" << "Quantities:" << "\t\t" << "Cost:" << "\t\t" << "Price:" << endl;
	for (auto it = Menu::itemList.begin(); it != Menu::itemList.end(); ++it)
	{
		cout << it->name << "\t\t" << it->count << "\t\t" << it->cost << "\t\t" << it->price << endl;
	}
}

Menu CreateItem()
{
	string name;
	unsigned int count;
	double cost;
	double price;

	cout << "Please enter the name of the item:" << endl;
	cin >> name;
	cout << "Please enter the quantity of this item:" << endl;
	cin >> count;;
	cout << "Please enter the cost of this item:" << endl;
	cin >> cost;
	cout << "Please enter the price of the item:" << endl;
	cin >> price;

	return Menu(name, count, cost, price);
}

double GetCurrentPrice(vector<Menu>::iterator itemIt)
{
	return itemIt->price;
}

std::vector<Menu>::iterator SearchForItem(string itemName)
{
	for (auto it = Menu::itemList.begin(); it != Menu::itemList.end(); ++it)
	{
		if (it->name == itemName)
		{
			return it;
		}
	}
	return Menu::itemList.end();
}

void WriteMenuToFile()
{
	std::ofstream ofs;
	ofs.open("./Data/MenuList.txt", std::ios::out);
	if (!ofs)
	{
		cout << "Cannot write data to file!" << endl;
		return;
	}

	std::size_t size = Menu::itemList.size();
	for (int i = 0; i < size; ++i)
	{
		ofs << Menu::itemList[i].name << "\t\t" << Menu::itemList[i].count << '\t' << 
			Menu::itemList[i].cost << '\t' << Menu::itemList[i].price << endl;
	}
	ofs.close();
}

void ReadMenuFromFile()
{
	string name;
	unsigned int count;
	double cost;
	double price;

	std::ifstream ifs;
	ifs.open("./Data/MenuList.txt", std::ios::in);
	if (!ifs)
	{
		cout << "Cannot read data from file!" << endl;
		return;
	}
	while (ifs >> name >> count >> cost >> price)
	{
		Menu menuEntity = Menu(name, count, cost, price);		// Initialize a Menu object from the data in file and add it to the list.
		Menu::itemList.push_back(menuEntity);
	}
	ifs.close();
}
