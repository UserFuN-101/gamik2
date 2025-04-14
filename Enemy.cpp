#include "Enemy.h"
#include <iostream>

Enemy::Enemy(float x, float y, const std::string& textureFile) : speed(50.f), damage(10) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load enemy texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Enemy::update(float deltaTime) {
    //TODO: Implement enemy movement logic
    // For now, let's make the enemy move left
    sprite.move(-speed * deltaTime, 0);
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Enemy::getRect() const {
    return sprite.getGlobalBounds();
}