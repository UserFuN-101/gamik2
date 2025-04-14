#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player(float x, float y, const std::string& textureFile);
    ~Player() {}

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    void move(float x, float y);
    void attack();
    void activateShield();
    void deactivateShield();
    void takeDamage(int damage);

    sf::FloatRect getRect() const;
    int getShieldDurability() const;
    bool isShieldActive() const;
    bool isAttacking() const;
    int getHealth() const { return health; } // Добавлено получение здоровья

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    int health;

    // Атака
    bool isAttacking = false;
    float attackTimer = 0.0f;
    float attackCooldown = 2.5f;

    // Щит
    int shieldDurability = 100;
    bool shieldIsActive = false;
    float shieldRechargeDelay = 5.0f;
    float shieldRechargeRate = 10.0f; // 10% в секунду
    float shieldBlockDuration = 10.0f;
    float shieldBlockRechargeRate = 5.0f;
    float shieldRechargeTimer = 0.0f;
    float shieldBlockTimer = 0.0f;
    bool shieldIsBlocked = false;
};

#endif