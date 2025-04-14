#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game {
public:
    Game();
    ~Game() {}

    void run();

private:
    sf::RenderWindow window;
    Player player1;
    Player player2;
    std::vector<Enemy> enemies;

    void processEvents();
    void update(float deltaTime);
    void render();

    bool checkCollision(sf::FloatRect rect1, sf::FloatRect rect2);
};

#endif