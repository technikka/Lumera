#pragma once

#include <SFML/Graphics.hpp>

class Deltaframe {
   public:
    Deltaframe(sf::Vector2u window_size);
    void Draw(sf::RenderWindow& window) const;
    void Update();

   private:
    sf::Vector2u window_size;
    sf::CircleShape body;
    void DefineShape();
    void SetPosition();
    void Move();
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f acceleration = {0, 0};
    const float break_speed = 0.1;
    float max_speed = 7.0;
    void Accelerate(sf::Vector2f amount);
    void Break();
};