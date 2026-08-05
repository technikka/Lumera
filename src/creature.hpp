#pragma once

#include <SFML/Graphics.hpp>

const sf::Color fill_color = sf::Color::Blue;

class Creature {
   public:
    Creature(float radius, sf::Vector2f position);

    void Move(sf::Vector2f new_position);
    void Draw(sf::RenderWindow& window) const;

   private:
    std::vector<sf::Vector2f> trail;

    sf::CircleShape body;
    void DrawTrail(sf::RenderWindow& window) const;
};
