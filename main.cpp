#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#ifndef VK_R
#define VK_R 0x52
#endif

const int FPS = 10;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;

int UpdateCheck;
std::vector<std::vector<int>> Field(FIELD_WIDTH, std::vector<int> (FIELD_HEIGHT, 0));
std::vector<int> Fruit(2, 0);
std::deque<std::vector<int>> Snake(2, std::vector<int> (2, 0));
bool GameRun = true;
char SnakeDrctn = 'o';
std::vector<int> SnakeMoves = {0, 0};
int Score = 0;
bool IsInSnake = false;

std::vector<int> SetFruitPos();

std::deque<std::vector<int>> SetSnakePos();

int PrintField(std::vector<std::vector<int>> Field);

char ReadKeys(char CurrKey);

std::vector<int> SetSnakeMove(char SnakeDrctn);

std::deque<std::vector<int>> UpdateSnakePos(std::deque<std::vector<int>> Snake, std::vector<int> SnakeMoves);

std::vector<std::vector<int>> UpdateField(std::vector<int> Fruit, std::deque<std::vector<int>> Snake);

int main()
{
    system("cls");
    Snake = SetSnakePos();
    Fruit = SetFruitPos();
    while (GameRun)
    {
        SnakeDrctn = ReadKeys(SnakeDrctn);
        SnakeMoves = SetSnakeMove(SnakeDrctn);
        Snake = UpdateSnakePos(Snake, SnakeMoves);
        if (Snake[0][0] == Fruit[0] && Snake[0][1] == Fruit[1])
        {
            IsInSnake = true;
            while (IsInSnake){
                IsInSnake = false;
                Fruit = SetFruitPos();
                for (std::vector<int> Value : Snake)
                {
                    if (Value[0] == Fruit[0] && Value[1] == Fruit[1])
                    {
                        IsInSnake = true;
                    }
                }
            }
            Score++;
        }
        UpdateCheck = PrintField(Field);
        std::cout << Score;
        if ((GetAsyncKeyState(VK_R) & 0x8000) != 0)
        {
            SnakeDrctn = 'o';
            SnakeMoves = {0, 0};
            Score = 0;
            Snake = SetSnakePos();
            Fruit = SetFruitPos();
        }
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
        {
            GameRun = false;
        }
        Field = UpdateField(Fruit, Snake);
        Sleep(1000 / FPS);
    }
    return UpdateCheck;
}

std::vector<int> SetFruitPos()
{
    int X = rand() % FIELD_WIDTH;
    int Y = rand() % FIELD_HEIGHT;

    return {X, Y};
}

std::deque<std::vector<int>> SetSnakePos()
{
    return {{FIELD_WIDTH / 2, FIELD_HEIGHT / 2}, {(FIELD_WIDTH / 2) - 1, FIELD_HEIGHT / 2}};
}

int PrintField(std::vector<std::vector<int>> Field)
{
    system("cls");
    for (int i = 0; i < FIELD_HEIGHT; i++)
    {
        for (int u = 0; u < FIELD_WIDTH; u++)
        {
            std::cout << Field[u][i];
        }
    std::cout << std::endl;
    }
    return 1;
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

std::vector<std::vector<int>> UpdateField(std::vector<int> Fruit, std::deque<std::vector<int>> Snake)
{
    std::vector<std::vector<int>> NewField(FIELD_WIDTH, std::vector<int> (FIELD_HEIGHT, 0));

    NewField[Fruit[0]][Fruit[1]] = 1;
    NewField[Snake[0][0]][Snake[0][1]] = 2;
    NewField[Snake[1][0]][Snake[1][1]] = 2;

    return NewField;
}
