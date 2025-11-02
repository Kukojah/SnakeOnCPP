#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>

const int FPS = 60;
const int FIELD_WIDTH = 20;
const int FIELD_HEIGHT = 15;

enum class Direction {
    up,
    right,
    down,
    left
};

int UpdateCheck;
std::vector<std::vector<int>> Field(FIELD_WIDTH, std::vector<int> (FIELD_HEIGHT, 0));
std::vector<int> Fruit(2, 0);
std::deque<std::vector<int>> Snake(2, std::vector<int> (2, 0));
bool GameRun = true;
Direction SnakeDirctn = right;

std::vector<int> SetFruitPos();

std::deque<std::vector<int>> SetSnakePos();

int PrintField(std::vector<std::vector<int>> Field);

Direction ReadKeys()
{
    int[] KeysPressed = GetAsyncKeyState(VK_UP);
};

std::vector<std::vector<int>> UpdateField(std::vector<int> Fruit, std::deque<std::vector<int>> Snake);

int main()
{
    system("cls");
    Snake = SetSnakePos();
    Fruit = SetFruitPos();
    while (GameRun)
    {
        Field = UpdateField(Fruit, Snake);
        UpdateCheck = PrintField(Field);
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
        {
            GameRun = false;
        }
        Sleep(1000 / FPS);
        system("cls");
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

std::vector<std::vector<int>> UpdateField(std::vector<int> Fruit, std::deque<std::vector<int>> Snake)
{
    std::vector<std::vector<int>> NewField(FIELD_WIDTH, std::vector<int> (FIELD_HEIGHT, 0));

    NewField[Fruit[0]][Fruit[1]] = 1;
    NewField[Snake[0][0]][Snake[0][1]] = 2;
    NewField[Snake[1][0]][Snake[1][1]] = 2;

    return NewField;
}
