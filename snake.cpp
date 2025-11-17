#include <iostream>
#include <vector>
#include <deque>
#include <windows.h>

class Snake
{
    private:
        std::deque<std::vector<int>> Pos;
        int Length;
        std::vector<int> Movement;
    public:
        std::deque<std::vector<int>> SetPos(int W, int H)
        {
            Pos = {{W / 2, H / 2}, {(W / 2) - 1, H / 2}};
            Length = Pos.size();
            Movement = {0, 0};
            return Pos;
        }

        std::deque<std::vector<int>> ReadPos()
        {
            return Pos;
        }

        std::vector<int> ReadMovement()
        {
            return Movement;
        }

        std::vector<int> SetMove(char LastInput)
        {
            if (LastInput == 'u')
            {
                Movement = {0, -1};
            };
            if (LastInput == 'r')
            {
                Movement = {1, 0};
            };
            if (LastInput == 'd')
            {
                Movement = {0, 1};
            };
            if (LastInput == 'l')
            {
                Movement = {-1, 0};
            };
            return Movement;
        }

        std::deque<std::vector<int>> UpdatePos(int W, int H)
        {
            std::deque<std::vector<int>> NewPos = Pos;
            if (NewPos[0][0] + Movement[0] > W - 1 || NewPos[0][0] + Movement[0] < 0)
            {
                Pos = SetPos(W, H);
            }
            if (NewPos[0][1] + Movement[1] > H - 1 || NewPos[0][1] + Movement[1] < 0)
            {
                Pos = SetPos(W, H);
            }
            for (int i = Length - 1; i >= 1; i--)
            {
                Pos[i][0] = Pos[i - 1][0];
                Pos[i][1] = Pos[i - 1][1];
            }
            Pos[0][0] += Movement[0];
            Pos[0][1] += Movement[1];

            return NewPos;
        }
};
