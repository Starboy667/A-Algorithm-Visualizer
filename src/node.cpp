/*
** EPITECH PROJECT, 2022
** PathfinderVisualizer
** File description:
** node
*/

#include "pathfinder.hpp"

bool Pos::operator == (const Pos &coordinates) const
{
    return (x == coordinates.x && y == coordinates.y);
};

bool Pos::operator != (const Pos &coordinates) const
{
    if ((x != coordinates.x) || (y != coordinates.y))
        return true;
    return false;
    // return (x != coordinates.x && y != coordinates.y);
};

Pos operator + (const Pos& first, const Pos& second)
{
    return {first.x + second.x, first.y + second.y};
}


Node::Node()
{
    _coordinates.x = 0;
    _coordinates.y = 0;
    _parent = nullptr;
}

Node::Node(Pos coords, Node *parent):
_parent(parent)
{
    _coordinates.x = coords.x;
    _coordinates.y = coords.y;
    _fCost = 0;
    _gCost = 0;
    _hCost = 0;
}

/**
 * @brief calculate all costs
 * gCost being distance between the node and his parent
 * hCost being distance between the node and the end node
 * fCost being gCost + hCost
 * 
 * @param start 
 * @param height 
 * @param width 
 */

/**
 * @brief Get the difference of coordinates between source and target
 * 
 * @param source 
 * @param target 
 * @return Pos 
 */
Pos getDelta(Pos source, Pos target)
{
    return {abs(source.x - target.x), abs(source.y - target.y)};
}

// heuristics
int manhattan(Pos source, Pos target)
{
    Pos delta = std::move(getDelta(source, target));
    return static_cast<int>(10 * (delta.x + delta.y));
}

int euclidean(Pos source, Pos target)
{
    Pos delta = std::move(getDelta(source, target));
    return static_cast<int>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

int octagonal(Pos source, Pos target)
{
    Pos delta = std::move(getDelta(source, target));
    return 10 * (delta.x + delta.y) - 6 * std::min(delta.x, delta.y);
}

void Node::computeCosts(Node *start, Pos end)
{
    // if node is diagonal
    if ((_coordinates.x - start->_coordinates.x + _coordinates.y - start->_coordinates.y) == 0 ||
    (_coordinates.x - start->_coordinates.x + _coordinates.y - start->_coordinates.y) == -2 ||
    (_coordinates.x - start->_coordinates.x + _coordinates.y - start->_coordinates.y) == 2)
        _gCost = 14 + start->_gCost;

    // else
    if (((_coordinates.x - start->_coordinates.x + _coordinates.y - start->_coordinates.y) == -1 ||
    (_coordinates.x - start->_coordinates.x + _coordinates.y - start->_coordinates.y) == 1) ||
    (start->_coordinates == _coordinates))
        _gCost = 10 + start->_gCost;

    // get heuristic
    _hCost = manhattan(_coordinates, end);

    _fCost = _gCost + _hCost;
}