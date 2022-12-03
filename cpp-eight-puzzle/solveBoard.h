#ifndef SOLVE_BOARD_H
#define SOLVE_BOARD_H

#include <iostream>
#include "board.h"
#include "queue"

class solveBoard
{
public:
    void breadthDepth(std::queue<boardType *> &queue);
    void printSolution() const;

private:
    void newMoves(boardType *parent, std::queue<boardType *> &childrenQ);
    void addMove(int r0, int c0, int rNew, int cNew, boardType *parent, std::queue<boardType *> &childrenQ);
    bool isKeyNew(int key);
    std::vector<boardType *> solutionList;
    std::vector<int> listOfKeys;
};
// Uses recursion to solve the initial sliding eight puzzle, does not check if the initial board is solvable
void solveBoard::breadthDepth(std::queue<boardType *> &queue)
{
    int queueSize = queue.size();
    std::queue<boardType *> newQueue;
    for (int i = 0; i < queueSize; i++)
    {
        // If the solution is found, the line from the initial board to the solution board is saved
        if (queue.front()->isSolution())
        {
            boardType *current;
            current = queue.front();
            while (current != nullptr)
            {
                solutionList.push_back(current);
                current = current->link;
            }

            return;
        }
        if (isKeyNew(queue.front()->key))
        {
            listOfKeys.push_back(queue.front()->key);
            newMoves(queue.front(), newQueue);
        }
        queue.pop();
    }
    breadthDepth(newQueue);
}
// Prints the line from the initial board to the solution
void solveBoard::printSolution() const
{
    for (int i = solutionList.size() - 1; i > 0; i--)
    {
        solutionList[i - 1]->printBoard();
    }
}
// Takes in a parent and a queue, creates the new moves from the parent and stores them in the queue
void solveBoard::newMoves(boardType *parent, std::queue<boardType *> &childrenQ)
{
    // searching for where the 0 is in the parent board
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (parent->board[r][c] == 0)
            {
                if (r > 0)
                {
                    addMove(r, c, r - 1, c, parent, childrenQ);
                }
                if (r < 2)
                {
                    addMove(r, c, r + 1, c, parent, childrenQ);
                }
                if (c > 0)
                {
                    addMove(r, c, r, c - 1, parent, childrenQ);
                }
                if (c < 2)
                {
                    addMove(r, c, r, c + 1, parent, childrenQ);
                }
                return;
            }
        }
    }
}
// Function used to simplify newMoves
void solveBoard::addMove(int r0, int c0, int rNew, int cNew, boardType *parent, std::queue<boardType *> &childrenQ)
{
    boardType *child;
    child = new boardType(parent->board, r0, c0, rNew, cNew);
    childrenQ.push(child);
    child->link = parent;
}

bool solveBoard::isKeyNew(int key)
{
    for (int i = 0; i < listOfKeys.size(); i++)
    {
        if (key == listOfKeys[i])
        {
            return false;
        }
    }
    return true;
}
#endif