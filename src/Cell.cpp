#include "Cell.hpp"
#include <iostream>

Cell::Cell()
{
    _mine = false;
    _discovered = false;
    _neighbours = 0;
    _flag = false;
}

Cell::~Cell()
{
}

void Cell::addMine(bool mine)
{
    _mine = mine;
}

int Cell::get_neighbours()
{
    return _neighbours;
}

void Cell::get_neighbours(std::vector<std::vector<Cell>> &grid, size_t x, size_t y)
{
    _neighbours = 0;
    if (_mine)
        return;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (x + i >= 0 && y + j >= 0 && x + i < grid.size() && y + j < grid[x + i].size())
            {
                if (grid[x + i][y + j].is_a_mine())
                    _neighbours++;
            }
        }
    }
}

bool Cell::is_discovered()
{
    return _discovered;
}

bool Cell::is_a_mine()
{
    return _mine;
}

bool Cell::discover(std::vector<std::vector<Cell>> &grid, size_t x, size_t y)
{
    if (is_a_mine())
        return true;
    _discovered = true;
    if (has_neighbours())
        return false;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if ((x + i >= 0) && (y + j >= 0) && (x + i < grid.size()) && (y + j < grid[x + i].size()))
            {
                if (!grid[x + i][y + j].is_a_mine() && !grid[x + i][y + j].is_discovered())
                    grid[x + i][y + j].discover(grid, x + i, y + j);
            }
        }
    }
    return false;
}

bool Cell::has_neighbours()
{
    return _neighbours > 0;
}

bool Cell::is_flagged()
{
    return _flag;
}

void Cell::flag()
{
    _flag = true;
}

void Cell::unflag()
{
    _flag = false;
}