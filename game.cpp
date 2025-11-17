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
        char SnakeDrctn = 'o';
        int Score = 0;

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
                Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
            };
            if (SnakePos[0][1] > FIELD_HEIGHT - 1 || SnakePos[0][1] < 0)
            {
                Player.SetPos(FIELD_WIDTH, FIELD_HEIGHT);
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
                GameField.PrintField(Score);
                Sleep(1000 / FPS);
            }
            return 0;
        }
};
