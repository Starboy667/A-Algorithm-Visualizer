/*
** EPITECH PROJECT, 2022
** PathfinderVisualizer
** File description:
** pathfinder
*/

#ifndef PATHFINDER_HPP_
#define PATHFINDER_HPP_

#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <graph.hpp>
#include <cstdlib>
#include <math.h>
#include <cmath>
using namespace std;

struct Pos
{
    int x;
    int y;
    bool operator == (const Pos &coordinates) const;
    bool operator != (const Pos &coordinates) const;
};  

Pos operator + (const Pos& first, const Pos& second);

class Node {

    public:
        // ctor / dctor
        Node(Pos coords, Node *parent = NULL);
        Node();
        ~Node() {};

        // node managing methods
        void computeCosts(Node *start, Pos end);
        bool operator == (const Node &compare) const { return _coordinates == compare._coordinates; }

        // node content
        Pos _coordinates;
        int _fCost;
        int _gCost;
        int _hCost;
        Node *_parent = NULL;
};

class Pathfinder {

    public:

        //ctor / dctor
        Pathfinder(string filepath, Pos start, Pos end);
        ~Pathfinder() {};
        int pathfinder(string);

        // map
        vector<string> map;
        int storeMap(string filepath);
        void printList(list<Node *> toPrint) const ;
        void drawSolution();
        bool checkChildren(Pos movement, Pos origin) const;

        // getters
        int getHeight() const { return _height; };
        int getWidth() const { return _width; };
        bool isSolved() const { return _solved; }; 
        
        // setters
        void setHeight(int height) { _height = height;};
        void setWidth(int width) { _width = width;};
    
        // solver
        bool solve();
        void computeAllCosts(list<Node *> toCompute);
        void setLowestF();
        void generateChildren();
        bool isValidChildren(Node *children);
        void addValidChildren();
        void doStep();
    
        vector<vector<Div>> _nodes;
        Node *_current;

    private:
        int _height = 0;
        int _width = 0;
        list<Node *> _open;
        list<Node *> _close;
        list<Node *> _children;
        bool _solved = false;
        Pos _start;
        Pos _end;
};


#endif /* !PATHFINDER_HPP_ */
