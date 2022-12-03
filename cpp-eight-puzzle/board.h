#ifndef BOARD_TYPE_H
#define BOARD_TYPE_H

#include <iostream>
#include <sstream>

class boardType
{
public:
    boardType(std::string);
    boardType(int inputBoard[3][3], int r0, int c0, int rNew, int cNew);
    bool isSolution();
    void printBoard() const;

    int board[3][3];
    boardType *link;
    int key;

private:
    int calculateHashKey();
};

boardType::boardType(std::string argv)
{

    // fill initial board from argv
    // assumes valid array of integers
    int iPos = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->board[i][j] = argv[iPos++] - '0';
        }
    }
    key = calculateHashKey();
}
// Constructor to create a boardType from a parent, and alter it from the parent by one move
boardType::boardType(int inputBoard[3][3], int r0, int c0, int rNew, int cNew)
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->board[i][j] = inputBoard[i][j];
        }
    }
    this->board[r0][c0] = this->board[rNew][cNew];
    this->board[rNew][cNew] = 0;
    key = calculateHashKey();
}
// Returns true if the board is equal to the goal board, false if it is not
bool boardType::isSolution()
{
    int answerNum = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (answerNum == 9)
            {
                return true;
            }
            else if (this->board[i][j] != answerNum)
            {
                return false;
            }
            answerNum++;
        }
    }
    return false;
}

void boardType::printBoard() const
{
    std::cout << std::endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//  Return hash code that satisfies rotational symmetry
//  considers the four corners of the board, selects the lowest digit
//  uses the remaining eight positions in a fixed order to 'build' an
//  integer of digits then converts to a returned string
int boardType::calculateHashKey()
{
    int dr;
    int dc;
    int d;
    bool rFirst;

    std::hash<std::string> str_hash;

    d = this->board[0][0]; // assume board[0][0] is lowest digit
    dr = +1;
    dc = +1;
    rFirst = true;

    if (this->board[0][2] < d)
    {
        d = this->board[0][2];
        dr = +1;
        dc = -1;
        rFirst = false;
    }
    if (this->board[2][2] < d)
    {
        d = this->board[2][2];
        dr = -1;
        dc = -1;
        rFirst = true;
    }
    if (this->board[2][0] < d)
    {
        d = this->board[2][0];
        dr = -1;
        dc = +1;
        rFirst = false;
    }

    std::ostringstream s;

    if (rFirst)
    {
        for (int r = -dr + 1; dr * r <= dr + 1; r += dr)
        {
            for (int c = -dc + 1; dc * c <= dc + 1; c += dc)
            {
                s << this->board[r][c];
            }
        }
    }
    else
    {
        for (int c = -dc + 1; dc * c <= dc + 1; c += dc)
        {
            for (int r = -dr + 1; dr * r <= dr + 1; r += dr)
            {
                s << this->board[r][c];
            }
        }
    }
    return (str_hash(s.str()));
}
#endif