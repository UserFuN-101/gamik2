#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "My Game"),
player1(100, 100, "player1.png"),
player2(200, 200, "player2.png") {
    // Создаем несколько врагов для теста
    enemies.emplace_back(300, 100, "enemy.png");
    enemies.emplace_back(400, 200, "enemy.png");
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                player1.attack();
            }
            if (event.key.code == sf::Keyboard::RControl) {
                player2.attack();
            }
        }
    }
}

void Game::update(float deltaTime) {
    // Player 1 movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player1.move(0, -deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player1.move(0, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player1.move(-deltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player1.move(deltaTime, 0);
    }

    // Player 2 movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player2.move(0, -deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player2.move(0, deltaTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player2.move(-deltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player2.move(deltaTime, 0);
    }

    player1.update(deltaTime);
    player2.update(deltaTime);

    // Update enemies
    for (Enemy& enemy : enemies) {
        enemy.update(deltaTime);
    }

    // Collision detection
    for (Enemy& enemy : enemies) {
        if (checkCollision(player1.getRect(), enemy.getRect())) {
            player1.takeDamage(enemy.getDamage());
            std::cout << "Player 1 health: " << player1.getHealth() << std::endl; // Debug
        }
        if (checkCollision(player2.getRect(), enemy.getRect())) {
            player2.takeDamage(enemy.getDamage());
            std::cout << "Player 2 health: " << player2.getHealth() << std::endl; // Debug
        }
    }
}

void Game::render() {
    window.clear();

    player1.render(window);
    player2.render(window);

    for (Enemy& enemy : enemies) {
        enemy.render(window);
    }

    //Индикатор для первого игрока
    sf::RectangleShape shieldBar1(sf::Vector2f(static_cast<float>(player1.getShieldDurability() * 2), 10));
    shieldBar1.setFillColor(sf::Color::Blue);
    shieldBar1.setPosition(player1.getRect().left, player1.getRect().top - 20);
    window.draw(shieldBar1);

    //Индикатор для второго игрока
    sf::RectangleShape shieldBar2(sf::Vector2f(static_cast<float>(player2.getShieldDurability() * 2), 10));
    shieldBar2.setFillColor(sf::Color::Blue);
    shieldBar2.setPosition(player2.getRect().left, player2.getRect().top - 20);
    window.draw(shieldBar2);

    window.display();
}

bool Game::checkCollision(sf::FloatRect rect1, sf::FloatRect rect2) {
    return rect1.intersects(rect2);
}