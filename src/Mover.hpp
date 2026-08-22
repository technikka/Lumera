#pragma once

#include <SFML/Graphics.hpp>

#include "MovingObject.hpp"
#include "PerlinNoise.hpp"

class Mover : public MovingObject {
   public:
    Mover(sf::Vector2u window_size);
    sf::FloatRect GetBounds() const override;
    sf::Vector2f GetPosition() const override;
    void Draw(sf::RenderWindow& window) const;
    void Move();

   private:
    sf::Vector2f velocity = {0, 0};
    sf::Vector2f acceleration;
    sf::CircleShape body;
    void DefineShape();
    void SetPosition();
    void SetRandomAcceleration();

    siv::PerlinNoise perlin;
    double noise_x{0.0};
    double noise_y{5000.0};
};
