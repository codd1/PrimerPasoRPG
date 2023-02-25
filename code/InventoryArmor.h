#pragma once

#include "Inventory.h"

class CInventoryArmor :
    public CInventory
{
protected:
    CInventoryArmor();
    ~CInventoryArmor();
private:
    friend class CInventory;
};

