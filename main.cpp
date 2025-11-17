#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#include "field.cpp"
#include "food.cpp"
#include "snake.cpp"
#ifndef VK_R
#define VK_R 0x52
#endif

const int FPS = 10;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;

int UpdateCheck;
Field GameField;
Food Meat;
Snake Player;
bool GameRun = true;
char SnakeDrctn = 'o';
int Score = 0;

char ReadKeys(char CurrKey);

int main()
{
    system("cls");
    GameField.SetField(FIELD_WIDTH, FIELD_HEIGHT);
    Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
    Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
    while (GameRun)
    {
        SnakeDrctn = ReadKeys(SnakeDrctn);
        Player.SetMove(SnakeDrctn);
        Player.UpdatePos(FIELD_WIDTH, FIELD_HEIGHT);
        if (Meat.CheckCollision(Player.ReadPos()))
        {
            Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
            Score++;
        }
        if ((GetAsyncKeyState(VK_R) & 0x8000) != 0)
        {
            SnakeDrctn = 'o';
            Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
            Score = 0;
            Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
        }
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
        {
            GameRun = false;
        }
        GameField.UpdateLayout(Meat.ReadPos(), Player.ReadPos());
        UpdateCheck = GameField.PrintField(Score);
        Sleep(1000 / FPS);
    }
    return UpdateCheck;
}

char ReadKeys(char CurrKey)
{
    int KeysPressed[] = {
    GetAsyncKeyState(VK_UP),
    GetAsyncKeyState(VK_RIGHT),
    GetAsyncKeyState(VK_DOWN),
    GetAsyncKeyState(VK_LEFT)
    };
    char NewCurrKey = CurrKey;
    if ((KeysPressed[0] & 0x8000) != 0 && CurrKey != 'd')
    {
        NewCurrKey = 'u';
    };
    if ((KeysPressed[1] & 0x8000) != 0 && CurrKey != 'l')
    {
        NewCurrKey = 'r';
    };
    if ((KeysPressed[2] & 0x8000) != 0 && CurrKey != 'u')
    {
        NewCurrKey = 'd';
    };
    if ((KeysPressed[3] & 0x8000) != 0 && CurrKey != 'r')
    {
        NewCurrKey = 'l';
    };
    return NewCurrKey;
}
