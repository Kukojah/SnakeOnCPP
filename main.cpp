#include <iostream>
#include <vector>
#include <deque>

const int FIELD_WIDTH = 40;
const int FIELD_HEIGHT = 30;

int UpdateCheck;
std::vector<std::vector<int>> Field(FIELD_WIDTH, std::vector<int> (FIELD_HEIGHT, 0));
std::vector<int> Fruit(2, 0);
std::deque<std::vector<int>> Snake(2, std::vector<int> (2, 0));

std::vector<int> SetFruitPos();

std::deque<std::vector<int>> SetSnakePos();

int PrintField(std::vector<std::vector<int>> Field);

std::vector<std::vector<int>> UpdateField(std::vector<int> Fruit, std::deque<std::vector<int>> Snake);

int main()
{
    Snake = SetSnakePos();
    Fruit = SetFruitPos();
    Field = UpdateField(Fruit, Snake);

    UpdateCheck = PrintField(Field);

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

    return 1;
}

std::vector<std::vector<int>> UpdateField(std::vector<int> Fruit, std::deque<std::vector<int>> Snake)
{
    std::vector<std::vector<int>> NewField(FIELD_WIDTH, std::vector<int> (FIELD_HEIGHT, 0));

    NewField[Fruit[0]][Fruit[1]] = 1;
    NewField[Snake[0][0]][Snake[0][1]] = 2;
    NewField[Snake[1][0]][Snake[1][1]] = 2

    return NewField;
}
