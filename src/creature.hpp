#pragma once

#include <SFML/Graphics.hpp>

#include "PerlinNoise.hpp"

const sf::Color fill_color = sf::Color::Blue;

class Creature {
   public:
    Creature(float radius, sf::Vector2f position);

    void Move(sf::Vector2u window_size);
    void Draw(sf::RenderWindow& window) const;

   private:
    sf::CircleShape body;

    std::vector<sf::Vector2f> trail;
    void DrawTrail(sf::RenderWindow& window) const;

    // Use different starting values so both axes do not follow the same pattern.
    siv::PerlinNoise perlin;
    double noise_x{0.0};
    double noise_y{10000.0};

    const float move_speed = 10.0;
};
