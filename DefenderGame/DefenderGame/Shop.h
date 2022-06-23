#ifndef SHOP_H
#define SHOP_H

#include <iostream>

class Shop
{
	public:
		int priceIncrease(int itemToIncrease);
		int getWeaponsUpgradePrice() const;
		int getArmourUpgradePrice() const;
		int getReinforcementsUpgradePrice() const;
		int getArchersUpgradePrice() const;
	private:
		//items for sale
		int weaponsUpgrade = 300;
		int armourUpgrade = 300;
		int reinforcements = 200; //recruit 20 foot soldiers
		int archers = 400; //increase ranged strength by 4
};


#endif //SHOP_H

//future implementation