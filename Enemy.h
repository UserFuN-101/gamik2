#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float x, float y, const std::string& textureFile);
    ~Enemy() {}

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::FloatRect getRect() const;
    int getDamage() const { return damage; } // Добавлена функция getDamage

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    int damage;
};

#endif