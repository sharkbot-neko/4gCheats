#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <vector>
#include <iostream>

class Item {
public:
    uint8_t GetNowSelect();
    bool IsSelected();
    void AddItem(uint32_t base_address, uint16_t item_id, int count);
};

#endif