#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#include "field.cpp"
#include "food.cpp"
#ifndef VK_R
#define VK_R 0x52
#endif

const int FPS = 10;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;

int UpdateCheck;
Field GameField;
Food Meat;
std::deque<std::vector<int>> Snake(2, std::vector<int> (2, 0));
bool GameRun = true;
char SnakeDrctn = 'o';
std::vector<int> SnakeMoves = {0, 0};
int Score = 0;
bool IsInSnake = false;

std::deque<std::vector<int>> SetSnakePos();

char ReadKeys(char CurrKey);

std::vector<int> SetSnakeMove(char SnakeDrctn);

std::deque<std::vector<int>> UpdateSnakePos(std::deque<std::vector<int>> Snake, std::vector<int> SnakeMoves);

int main()
{
    system("cls");
    GameField.SetField(FIELD_WIDTH, FIELD_HEIGHT);
    Snake = SetSnakePos();
    Meat.SetFoodPos(Snake, FIELD_WIDTH, FIELD_HEIGHT);
    while (GameRun)
    {
        SnakeDrctn = ReadKeys(SnakeDrctn);
        SnakeMoves = SetSnakeMove(SnakeDrctn);
        Snake = UpdateSnakePos(Snake, SnakeMoves);
        if (Meat.CheckCollision(Snake))
        {
            Meat.SetFoodPos(Snake, FIELD_WIDTH, FIELD_HEIGHT);
            Score++;
        }
        if ((GetAsyncKeyState(VK_R) & 0x8000) != 0)
        {
            SnakeDrctn = 'o';
            SnakeMoves = {0, 0};
            Score = 0;
            Snake = SetSnakePos();
            Meat.SetFoodPos(Snake, FIELD_WIDTH, FIELD_HEIGHT);
        }
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
        {
            GameRun = false;
        }
        GameField.UpdateLayout(Meat.ReadPos(), Snake);
        UpdateCheck = GameField.PrintField(Score);
        Sleep(1000 / FPS);
    }
    return UpdateCheck;
}

std::deque<std::vector<int>> SetSnakePos()
{
    return {{FIELD_WIDTH / 2, FIELD_HEIGHT / 2}, {(FIELD_WIDTH / 2) - 1, FIELD_HEIGHT / 2}};
}

std::deque<std::vector<int>> UpdateSnakePos(std::deque<std::vector<int>> Snake, std::vector<int> SnakeMoves)
{
    std::deque<std::vector<int>> NewSnake = Snake;
    if (NewSnake[0][0] + SnakeMoves[0] > FIELD_WIDTH - 1 || NewSnake[0][0] + SnakeMoves[0] < 0)
    {
        NewSnake = SetSnakePos();
    }
    if (NewSnake[0][1] + SnakeMoves[1] > FIELD_HEIGHT - 1 || NewSnake[0][1] + SnakeMoves[1] < 0)
    {
        NewSnake = SetSnakePos();
    }
    NewSnake[1][0] = Snake[0][0];
    NewSnake[1][1] = Snake[0][1];
    NewSnake[0][0] += SnakeMoves[0];
    NewSnake[0][1] += SnakeMoves[1];

    return NewSnake;
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

std::vector<int> SetSnakeMove(char SnakeDrctn)
{
    std::vector<int> SnakeMove = {0, 0};
    if (SnakeDrctn == 'u')
    {
        SnakeMove = {0, -1};
    };
    if (SnakeDrctn == 'r')
    {
        SnakeMove = {1, 0};
    };
    if (SnakeDrctn == 'd')
    {
        SnakeMove = {0, 1};
    };
    if (SnakeDrctn == 'l')
    {
        SnakeMove = {-1, 0};
    };
    return SnakeMove;
}
