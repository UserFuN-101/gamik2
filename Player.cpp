#include "Player.h"
#include <iostream>

Player::Player(float x, float y, const std::string& textureFile) : speed(100.f), health(100) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load player texture!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Player::update(float deltaTime) {
    // Атака
    if (isAttacking) {
        attackTimer += deltaTime;
        if (attackTimer >= 1.0f) { // Время анимации
            // Останавливаем анимацию (заглушка)
        }
        if (attackTimer >= attackCooldown) {
            isAttacking = false;
            attackTimer = 0.0f;
        }
    }

    // Обработка щита
    if (!shieldIsBlocked) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { // Пример: Левый Shift для щита
            if (shieldDurability > 0) {
                shieldIsActive = true;
                shieldDurability -= static_cast<int>(deltaTime * 1.0f); // 1% в секунду
            }
            if (shieldDurability <= 0) {
                shieldDurability = 0;
                shieldIsActive = false;
                shieldIsBlocked = true;
                shieldBlockTimer = 0.0f;
            }
        }
        else {
            shieldIsActive = false;
            shieldRechargeTimer += deltaTime;
            if (shieldRechargeTimer >= shieldRechargeDelay && shieldDurability < 100) {
                shieldDurability += static_cast<int>(deltaTime * shieldRechargeRate);
                if (shieldDurability > 100) shieldDurability = 100;
            }
        }
    }
    else {
        shieldBlockTimer += deltaTime;
        if (shieldBlockTimer >= shieldBlockDuration) {
            if (shieldDurability < 100) {
                shieldDurability += static_cast<int>(deltaTime * shieldBlockRechargeRate);
                if (shieldDurability >= 100) {
                    shieldDurability = 100;
                    shieldIsBlocked = false;
                    shieldBlockTimer = 0.0f;
                }
            }
        }
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::move(float x, float y) {
    sprite.move(x * speed, y * speed);
}

void Player::attack() {
    if (!isAttacking) {
        isAttacking = true;
        attackTimer = 0.0f;
        // Здесь код для анимации атаки (заглушка)
    }
}

void Player::takeDamage(int damage) {
    if (shieldIsActive) {
        shieldDurability -= 30;
        if (shieldDurability < 0) {
            shieldDurability = 0;
            shieldIsActive = false;
            shieldIsBlocked = true;
            shieldBlockTimer = 0.0f;
        }
    }
    else {
        health -= damage;
        if (health < 0) {
            health = 0;
            // Смерть игрока (заглушка)
        }
    }
}

sf::FloatRect Player::getRect() const {
    return sprite.getGlobalBounds();
}
int Player::getShieldDurability() const {
    return shieldDurability;
}
bool Player::isShieldActive() const {
    return shieldIsActive;
}
bool Player::isAttacking() const {
    return isAttacking;
}