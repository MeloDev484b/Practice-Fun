#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>
using namespace std;

class Resources
{
public:
	int getGold();
	void setGold(int newGold);
private:
	int gold = 500;
};



#endif //RESOURCES_H