// test executions
// solvePuzzle 182043765
// solvePuzzle 812043765
// solvePuzzle 123540876
#include <iostream>
#include <queue>
#include "board.h"
#include "solveBoard.h"
bool solvable(int board[3][3])
{
    int counter = 0;
    int current = 0;
    int temp = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) // First nested for loop to iterate through the board
        {
            temp = j; // Used to reset the tricky nature of a 2d array
            current = board[i][j];
            for (int m = i; m < 3; m++) // Second nested for loop to iterate through the rest of the board after current
            {
                for (int k = temp; k < 3; k++)
                {
                    if (board[m][k] != 0 && current > board[m][k])
                    {
                        counter++;
                    }
                }
                temp = 0;
            }
        }
    }

    if (counter % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: solvePuzzle initalBoard " << std::endl;
        return -1;
    }
    boardType *initialBoard = nullptr;
    initialBoard = new boardType(argv[1]);
    initialBoard->link = nullptr;

    std::cout << "initial: " << std::endl;
    initialBoard->printBoard();

    if (solvable(initialBoard->board))
    {
        solveBoard initialB;
        std::queue<boardType *> firstQ;
        firstQ.push(initialBoard);
        initialB.breadthDepth(firstQ);
        initialB.printSolution();
    }
    else
    {
        std::cout << "This board is not solvable";
    }

    return 0;
}
