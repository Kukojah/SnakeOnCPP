#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>
#ifndef VK_R
#define VK_R 0x52
#endif
#include "field.cpp"
#include "food.cpp"
#include "snake.cpp"

class TheGame
{
    private:
        const int FPS = 10;
        const int FIELD_WIDTH = 20;
        const int FIELD_HEIGHT = 15;
        Field GameField;
        Food Meat;
        Snake Player;
        bool GameRun = true;
        bool GameOver = false;
        char SnakeDrctn = 'o';
        int Score = 0;

        char ReadKeys(char CurrKey)
        {
            if (GetAsyncKeyState(VK_UP) != 0 && CurrKey != 'd')
            {
                return 'u';
            };
           if (GetAsyncKeyState(VK_RIGHT) != 0 && CurrKey != 'l')
            {
               return 'r';
            };
            if (GetAsyncKeyState(VK_DOWN) != 0 && CurrKey != 'u')
            {
                return 'd';
            };
            if (GetAsyncKeyState(VK_LEFT) != 0 && CurrKey != 'r')
            {
                return 'l';
            };
            if ((GetAsyncKeyState(VK_R) & 0x8000) != 0)
            {
                GameOver = true;
            };
            if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
            {
                GameRun = false;
            };
            return CurrKey;
        }

    int StartGame()
    {
        system("cls");
        GameField.SetField(FIELD_WIDTH, FIELD_HEIGHT);
        Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
        Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
        return 0;
    }

    int CheckCollision(std::deque<std::vector<int>> SnakePos, std::vector<int> FoodPos, int OldScore)
    {
        int NewScore = OldScore;
        if (SnakePos[0][0] > FIELD_WIDTH - 1 || SnakePos[0][0] < 0)
        {
            GameOver = true;
        };
        if (SnakePos[0][1] > FIELD_HEIGHT - 1 || SnakePos[0][1] < 0)
        {
            GameOver = true;
        };
        if (SnakePos[0][0] == FoodPos[0] && SnakePos[0][1] == FoodPos[1])
        {
            Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
            NewScore++;
        };
        return NewScore;
    }

public:
    int RunGame()
    {
        StartGame();
        while (GameRun)
        {
            SnakeDrctn = ReadKeys(SnakeDrctn);
            Player.SetMove(SnakeDrctn);
            Player.UpdatePos(FIELD_WIDTH, FIELD_HEIGHT);
            Score = CheckCollision(Player.ReadPos(), Meat.ReadPos(), Score);

            if (GameOver)
            {
                SnakeDrctn = 'o';
                Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
                Score = 0;
                Meat.SetPos(Player.ReadPos(), FIELD_WIDTH, FIELD_HEIGHT);
                GameOver = false;
            }

            GameField.UpdateLayout(Meat.ReadPos(), Player.ReadPos());
            GameField.PrintField(Score);
            Sleep(1000 / FPS);
        }
        return 0;
    }
};
