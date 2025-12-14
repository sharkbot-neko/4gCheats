// MiniMenu
#include "cheats.hpp"
#include "Address.hpp"

#include <algorithm>

bool menuOpen = false;
int cursor = 0;
int scrollOffset = 0;

enum ValueType {
    NONE,
    BOOL,
    FLOAT,
    SPEEDFLOAT,
    NUMBER
};

struct MenuItem {
    std::string name;
    bool isFolder;
    std::vector<MenuItem> subItems;

    float *floatValue;
    bool *boolValue;
    int *numberValue;
    std::vector<std::string> *listValue;

    ValueType valueType;
};

// ===== 設定値 =====
bool in_quest, change_coord;
float player_coord_x, player_coord_y, player_coord_z;

bool change_width;
float player_width_x, player_width_y, player_width_z;

bool change_money;
int player_money;

bool max_story;

std::vector<MenuItem> rootMenu = {
    {"Players", true, {
        {"Change Money", false, {}, nullptr, &change_money, nullptr, nullptr, BOOL},
        {"PlayerMoney", false, {}, nullptr, nullptr, &player_money, nullptr, NUMBER},

        {"================", false, {}, nullptr, nullptr, nullptr, nullptr, NONE},

        {"In Quest", false, {}, nullptr, &in_quest, nullptr, nullptr, BOOL},
        {"Change Coord", false, {}, nullptr, &change_coord, nullptr, nullptr, BOOL},
        {"PlayerCoord (X)",  false, {}, &player_coord_x, nullptr, nullptr, nullptr, SPEEDFLOAT},
        {"PlayerCoord (Y)", false, {}, &player_coord_y, nullptr, nullptr, nullptr, SPEEDFLOAT},
        {"PlayerCoord (Z)", false, {}, &player_coord_z, nullptr, nullptr, nullptr, SPEEDFLOAT},

        {"================", false, {}, nullptr, nullptr, nullptr, nullptr, NONE},

        {"Change Width", false, {}, nullptr, &change_width, nullptr, nullptr, BOOL},
        {"PlayerWidth (X)",  false, {}, &player_width_x, nullptr, nullptr, nullptr, FLOAT},
        {"PlayerWidth (Y)", false, {}, &player_width_y, nullptr, nullptr, nullptr, FLOAT},
        {"PlayerWidth (Z)", false, {}, &player_width_z, nullptr, nullptr, nullptr, FLOAT},

        {"================", false, {}, nullptr, nullptr, nullptr, nullptr, NONE},

        {"Complete stories", false, {}, nullptr, &max_story, nullptr, nullptr, BOOL},
    }},
    {"Exit", false, {}, nullptr, nullptr, nullptr, nullptr,  NONE}
};

std::vector<MenuItem>* currentMenu = &rootMenu;
std::vector<std::vector<MenuItem>*> menuStack;

namespace CTRPluginFramework
{
    const int x = 10;
    const int y = 20;
    const int width = 200;
    const int itemHeight = 18;
    const int visibleItems = 10;

    // 数値を安全に短くする
    std::string FloatToShort(float v)
    {
        char buf[16];
        snprintf(buf, sizeof(buf), "%.2f", v);
        return std::string(buf);
    }

    void DrawRightValue(const Screen &screen, const MenuItem &item, int x, int y)
    {
        std::string txt;

        switch (item.valueType)
        {
            case BOOL:
                txt = *item.boolValue ? "[ON]" : "[OFF]";
                break;

            case FLOAT:
            case SPEEDFLOAT:
                txt = "[" + FloatToShort(*item.floatValue) + "]";
                break;

            case NUMBER:
            {
                char buf[16];
                snprintf(buf, sizeof(buf), "%d", *item.numberValue);
                txt = std::string("[") + buf + "]";
            }
            break;

            default:
                return;
        }

        screen.DrawSysfont(txt, x + width - 20, y, Color::White);
    }

    bool DrawMiniMenu(const Screen &screen)
    {
        if (!screen.IsTop) return true;

        int menuSize = currentMenu->size();
        int drawCount = std::min(menuSize, visibleItems);

        screen.DrawRect(x, y, x + width,
                        y + drawCount * itemHeight + 10,
                        Color(0, 0, 0, 160));

        if (cursor < scrollOffset)
            scrollOffset = cursor;
        if (cursor >= scrollOffset + visibleItems)
            scrollOffset = cursor - visibleItems + 1;

        for (int i = scrollOffset; i < scrollOffset + drawCount; i++)
        {
            int index = i;
            int itemY = y + 5 + (i - scrollOffset) * itemHeight;

            if (cursor == index)
            {
                screen.DrawRect(
                    x + 2,
                    itemY,
                    x + width - 2,
                    itemHeight,
                    Color(70, 70, 200, 150)
                );
            }
            MenuItem &item = (*currentMenu)[index];

            std::string text = item.name;
            if (item.isFolder)
                text += " >";

            screen.DrawSysfont(text, x + 5, itemY, Color::White);

            DrawRightValue(screen, item, x, itemY);
        }

        return true;
    }

    bool OverlayCallback(const Screen &scr)
    {
        if (menuOpen)
            DrawMiniMenu(scr);
            return true;
        return false;
    }

    void ProcessPlayer()
    {
        Quest quest;
        Home home;

        if (change_coord)
        {
            Player *p = (in_quest ? quest.GetPlayerStructs() : home.GetPlayerStructs());
            if (p && p->playerbodywork)
            {
                p->playerbodywork->vec_x = player_coord_x;
                p->playerbodywork->vec_y = player_coord_y;
                p->playerbodywork->vec_z = player_coord_z;
            }
        } else {
            Player *p = (in_quest ? quest.GetPlayerStructs() : home.GetPlayerStructs());
            if (p && p->playerbodywork)
            {
                player_coord_x = p->playerbodywork->vec_x;
                player_coord_y = p->playerbodywork->vec_y;
                player_coord_z = p->playerbodywork->vec_z;
            }
        }

        if (change_width)
        {
            Player *p = (in_quest ? quest.GetPlayerStructs() : home.GetPlayerStructs());
            if (p)
            {
                p->playerWidthX = player_width_x;
                p->playerWidthY = player_width_y;
                p->playerWidthZ = player_width_z;
            }
        } else {
            Player *p = (in_quest ? quest.GetPlayerStructs() : home.GetPlayerStructs());
            if (p)
            {
                player_width_x = p->playerWidthX;
                player_width_y = p->playerWidthY;
                player_width_z = p->playerWidthZ;
            }
        }

        // お金
        {
            if (change_money) {
                Process::Write32(MoneyAddress, player_money);
            } else {
                u32 cur_money;
                Process::Read32(MoneyAddress, cur_money);

                player_money = cur_money;
            }
        }

        // ストーリー全クリア
        {
            if (max_story) {
                Process::Write32(0x0062B8B4, 0xE3A00001);
                Process::Write32(0x00C00344, 0xE3A00001);
                Process::Write32(0x00C01300, 0xE3A00001);
                Process::Write32(0x00C0167C, 0xE3A00001);
                Process::Write32(0x00C02AC4, 0xE3A00001);
                Process::Write32(0x00C072B8, 0xE3A00001);
            }
        }
    }

    void ProcessFrameCallback()
    {

        Controller ctr;
        // ctr.Update();

        ProcessPlayer();

        if (ctr.IsKeysPressed(Key::Start))
            menuOpen = !menuOpen;

        if (!menuOpen)
            return;

        int menuSize = currentMenu->size();
        MenuItem &item = (*currentMenu)[cursor];

        if (ctr.IsKeysPressed(Key::DPadUp))
            cursor = (cursor - 1 + menuSize) % menuSize;
        if (ctr.IsKeysPressed(Key::DPadDown))
            cursor = (cursor + 1) % menuSize;

        if (ctr.IsKeyDown(Key::A))
        {
            if (item.valueType == BOOL)
            {
                if (ctr.IsKeysPressed(Key::DPadLeft) ||
                    ctr.IsKeysPressed(Key::DPadRight))
                {
                    *item.boolValue = !*item.boolValue;
                }
            }
            else if (item.valueType == FLOAT)
            {
                if (ctr.IsKeysPressed(Key::DPadLeft))
                    *item.floatValue -= 0.1f;

                if (ctr.IsKeysPressed(Key::DPadRight))
                    *item.floatValue += 0.1f;
            }
            else if (item.valueType == SPEEDFLOAT)
            {
                if (ctr.IsKeyDown(Key::DPadLeft))
                    *item.floatValue -= 1.0f;

                if (ctr.IsKeyDown(Key::DPadRight))
                    *item.floatValue += 1.0f;
            }
            else if (item.valueType == NUMBER)
            {
                if (ctr.IsKeyDown(Key::DPadLeft))
                    (*item.numberValue) -= 1;

                if (ctr.IsKeyDown(Key::DPadRight))
                    (*item.numberValue) += 1;
            }
        }

        if (ctr.IsKeysPressed(Key::A))
        {
            if (item.isFolder)
            {
                menuStack.push_back(currentMenu);
                currentMenu = &item.subItems;
                cursor = 0;
                scrollOffset = 0;
            }
            else if (item.name == "Exit")
                menuOpen = false;
        }

        if (ctr.IsKeysPressed(Key::B))
        {
            if (!menuStack.empty())
            {
                currentMenu = menuStack.back();
                menuStack.pop_back();
                cursor = 0;
                scrollOffset = 0;
            }
            else
                menuOpen = false;
        }
    }
}