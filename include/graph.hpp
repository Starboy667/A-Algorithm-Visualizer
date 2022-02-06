/*
** EPITECH PROJECT, 2022
** PathfinderVisualizer
** File description:
** sfml
*/

#ifndef GRAPH_HPP_
#define GRAPH_HPP_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Div {
    public:

        Div(sf::Vector2f size, sf::Vector2f pos,
        int x, int y) {
            _rectangle = sf::RectangleShape(size);
            _pos = pos;
            _color = sf::Color(200, 200, 200);
            _rectangle.setFillColor(_color);
            _x = x;
            _y = y;

        };
        ~Div() {};
        sf::RectangleShape _rectangle;
        sf::Vector2f _pos;
        sf::Color _color;
        int _x;
        int _y;
};

#endif /* !GRAPH_HPP_ */
