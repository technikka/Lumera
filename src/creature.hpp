#pragma once

#include <SFML/Graphics.hpp>

#include "PerlinNoise.hpp"
#include "WorldObject.hpp"

sf::Vector2f GetRandomPosition(sf::Vector2u window_size);
sf::Color GetRandomColor();

class Creature : public WorldObject {
   public:
    Creature(float radius, sf::Vector2u window_size,
             std::optional<sf::Vector2f> position = std::nullopt);

    void Draw(sf::RenderWindow& window) const;
    void MoveTo(sf::Vector2f position);
    sf::FloatRect GetBounds() const override;
    sf::Vector2f GetNextPosition(sf::Vector2u window_size);

   private:
    sf::CircleShape body;
    sf::Vector2u window_size;
    std::vector<sf::Vector2f> trail;
    void DrawTrail(sf::RenderWindow& window) const;

    // Use different starting values so both axes do not follow the same pattern.
    siv::PerlinNoise perlin;
    double noise_x{0.0};
    double noise_y{10000.0};

    const float move_speed = 10.0;
};
