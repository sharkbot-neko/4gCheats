// ====== MiniMenu.cpp ======
#include "cheats.hpp"
#include <algorithm>

bool menuOpen = false;
int cursor = 0;
int scrollOffset = 0;

enum ValueType {
    NONE,
    BOOL,
    FLOAT,
    SPEEDFLOAT
};

struct MenuItem {
    std::string name;
    bool isFolder;
    std::vector<MenuItem> subItems;

    float *floatValue;
    bool *boolValue;

    ValueType valueType;
};

// ===== 設定値 =====
bool in_quest;
bool change_coord;
float player_coord_x;
float player_coord_y;
float player_coord_z;

bool change_width;
float player_width_x;
float player_width_y;
float player_width_z;

std::vector<MenuItem> rootMenu = {
    {"Players", true, {
        {"In Quest", false, {}, nullptr, &in_quest, BOOL},
        {"Change Coord", false, {}, nullptr, &change_coord, BOOL},
        {"PlayerCoord (X)",  false, {}, &player_coord_x, nullptr, SPEEDFLOAT},
        {"PlayerCoord (Y)", false, {}, &player_coord_y, nullptr, SPEEDFLOAT},
        {"PlayerCoord (Z)", false, {}, &player_coord_z, nullptr, SPEEDFLOAT},

        {"================", false, {}, nullptr, nullptr, NONE},

        {"Change Width", false, {}, nullptr, &change_width, BOOL},
        {"PlayerWidth (X)",  false, {}, &player_width_x, nullptr, FLOAT},
        {"PlayerWidth (Y)", false, {}, &player_width_y, nullptr, FLOAT},
        {"PlayerWidth (Z)", false, {}, &player_width_z, nullptr, FLOAT},
    }},
    {"Exit", false, {}, nullptr, nullptr, NONE}
};

std::vector<MenuItem>* currentMenu = &rootMenu;
std::vector<std::vector<MenuItem>*> menuStack;

namespace CTRPluginFramework
{
    const int x = 10;
    const int y = 20;
    const int width = 180;
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
                txt = "[" + FloatToShort(*item.floatValue) + "]";
                break;

            case SPEEDFLOAT:
                txt = "[" + FloatToShort(*item.floatValue) + "]";
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

        if (menuSize > visibleItems)
        {
            float ratio = (float)visibleItems / menuSize;
            int barHeight = (int)(ratio * (drawCount * itemHeight));
            int barY = y + (scrollOffset * itemHeight * ratio);

            screen.DrawRect(x + width - 6, barY, x + width - 2,
                            barY + barHeight,
                            Color(200, 200, 200, 180));
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

    void ProcessCheats()
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
    }


    void ProcessFrameCallback()
    {

        Controller ctr;
        // ctr.Update();

        ProcessCheats();

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