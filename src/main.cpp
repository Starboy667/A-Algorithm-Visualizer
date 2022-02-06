/*
** EPITECH PROJECT, 2022
** PathfinderVisualizer
** File description:
** main
*/

#include <pathfinder.hpp>

int main(int ac, char **av)
{
    // check if map given
    if (ac != 2)
        return 0;

    // setup pathfinder
    Pos start = {0, 0};
    Pos end = {29, 24};
    Pathfinder pathfinder(av[1], start, end);
    float stepSpeed = 0.005;

    // setup graphical
    sf::RenderWindow window(sf::VideoMode(1280, 860), "Pathfinder");
    sf::Clock clock;

    while (window.isOpen())
    {
        // get events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
    
        // go to algorithm's next step every stepSpeed
        if (clock.getElapsedTime().asSeconds() >= stepSpeed &&
        pathfinder.isSolved() == false) {   
            pathfinder.doStep();
            clock.restart();
        }

        // draw map
        for(auto &vector : pathfinder._nodes) {
            for(auto &node : vector) {
                node._rectangle.setPosition(node._pos);
                node._rectangle.setFillColor(node._color);
                window.draw(node._rectangle);
            }
        }
        window.display();
    }
    return 0;
}