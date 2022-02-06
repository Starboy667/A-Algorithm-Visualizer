/*
** EPITECH PROJECT, 2022
** PathfinderVisualizer
** File description:
** pathfinder
*/

#include <pathfinder.hpp>

/**
 * @brief Construct a new Pathfinder:: Pathfinder object
 * 
 * @param filepath 
 */

Pathfinder::Pathfinder(string filepath, Pos start, Pos end):
_start(start), _end(end)
{
    // store map given in argument
    if (storeMap(filepath))
        exit(84);

    // create first node & add it to the open list
    _current = new Node(start);
    _current->computeCosts(_current, _end);
    _open.push_front(_current);

    // create graphical map and colour it
    int tmp = _height < _width ? _height : _width;

    sf::Vector2f size(860 / tmp * 0.6, 860 / tmp * 0.6);
    for (int i = 0; i < _height; i++) {
        vector<Div> temp;
        for (int j = 0; j < _width; j++) {
            temp.push_back(Div(size, sf::Vector2f(j * size.x * 1.2, i * size.y * 1.2), j, i));
        }
        _nodes.push_back(temp);
    }
    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            if (map[i][j] == 'X') {
                _nodes[i][j]._color = sf::Color(0, 0, 0);
            }
        }
    }
    _nodes[end.y][end.x]._color = sf::Color(0, 0, 200);
    _nodes[start.y][start.x]._color = sf::Color(0, 0, 200);
}

int Pathfinder::storeMap(string filepath)
{
    ifstream file { filepath };
    int width = 0;
    int height = 0; 

    if (!file.is_open()) {
        cout << "Error : file not found" << endl;
        return 1;
    }

    string line;
    while (file >> line) {
        map.emplace_back(line);
        height += 1;
    }

    width = map.front().length();
    setHeight(height);
    setWidth(width);
    return 0;
}

void Pathfinder::printList(list<Node *> toPrint) const
{
    for(auto &node : toPrint) {
        cout << "y " << node->_coordinates.y << " x " << node->_coordinates.x << " f " << node->_fCost << " g " << node->_gCost << " h " << node->_hCost << endl;
    }
}

/**
 * @brief compute all node fCosts in toCompute list
 * 
 * @param toCompute 
 */
void Pathfinder::computeAllCosts(list<Node *> toCompute)
{
    for(auto &node : toCompute) {
        node->computeCosts(_current, _end);
    }
}

/**
 * @brief set current to the node with the lowest F in open list
 * 
 */
void Pathfinder::setLowestF()
{
    _current = _open.front();
    for(auto &node : _open) {
        if (node->_fCost <= _current->_fCost)
            _current = node;
    }
}

/**
 * @brief check if children is in bounds
 * 
 * @param movement 
 * @param origin 
 * @return true 
 * @return false 
 */
bool Pathfinder::checkChildren(Pos movement, Pos origin) const
{
    Pos combined = movement + origin;

    if (combined.x < _width && combined.y < _height &&
    combined.x >= 0 && combined.y >= 0 &&
    map[combined.y][combined.x] == '*' &&
    (map[origin.y][combined.x] == '*') &&
    (map[combined.y][origin.x] == '*')) {
        return true;
    }
    return false;
}

/**
 * @brief generate neighboors nodes
 * 
 */
void Pathfinder::generateChildren()
{
    Pos neighboors[] = {
        {1, 0} , {0, 1}, {-1, 0}, {0, -1}
        , {1, 1,} , {1, -1}, {-1, 1}, {-1, -1}
    };
    for (auto &toCheck : neighboors) {
        if (checkChildren(toCheck, _current->_coordinates))
            _children.push_front(new Node(toCheck + _current->_coordinates, _current));
    }
}

/**
 * @brief check if children nodes are not in open / close list
 * 
 * @param children 
 * @return true 
 * @return false 
 */
bool Pathfinder::isValidChildren(Node *children)
{
    for(auto &open : _open) {
        if (open->_coordinates == children->_coordinates &&
        open->_fCost <= children->_fCost)
            return 0;
    }
    for(auto &close : _close) {
        if (close->_coordinates == children->_coordinates &&
        close->_fCost <= children->_fCost)
            return 0;
    }
    return 1;
}

/**
 * @brief add all valid children in open list
 * 
 */
void Pathfinder::addValidChildren()
{
    computeAllCosts(_open);
    computeAllCosts(_close);
    for(auto &children : _children) {
        if (isValidChildren(children)) {
            if ((children->_coordinates != _start) && (children->_coordinates != _end))
                _nodes[children->_coordinates.y][children->_coordinates.x]._color = sf::Color(0,200,0);
            _open.push_front(children);
        }
    }
    for(auto &open : _open) {
        _children.remove(open);
    }
}

/**
 * @brief go to the next step in the algorithm
 * 
 */
void Pathfinder::doStep()
{
    if (_open.empty()) {
        cout << "Error no nodes left" << endl;
        exit(84);
    }

    computeAllCosts(_open);
    setLowestF();

    // check if arrived
    if (_current->_coordinates == _end) {
        _solved = true;
        drawSolution();
        return;
    }
    _open.remove(_current);
    generateChildren();
    computeAllCosts(_children);
    addValidChildren();
    _close.push_front(_current);

    // color map
    if ((_current->_coordinates != _start) && (_current->_coordinates != _end))
        _nodes[_current->_coordinates.y][_current->_coordinates.x]._color = sf::Color(200, 0, 0);
}

/**
 * @brief draw the path from the first node to the end node
 * 
 */
void Pathfinder::drawSolution()
{

    while (_current) {
        if ((_current->_coordinates != _start) && (_current->_coordinates != _end))
            _nodes[_current->_coordinates.y][_current->_coordinates.x]._color = sf::Color(200,200,0);
        _current = _current->_parent;
    }
}

/**
 * @brief solve the labyrinth completly
 * 
 * @return bool isSolved 
 */
bool Pathfinder::solve()
{
    while (!_open.empty() && (_current->_coordinates.x != _width - 1 ||
    _current->_coordinates.y != _height - 1)) {
        doStep();
    }
    if (isSolved())
        return true;
    return false;
}