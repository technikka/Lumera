#pragma once

#include <SFML/Graphics.hpp>

#include "WorldObject.hpp"

class MovingObject : public WorldObject {
   public:
    MovingObject(sf::Vector2u window_size);

   protected:
    sf::Vector2u window_size;
    void SetBodyOrigin(sf::Shape& body);
    sf::Vector2f GetWrappedPosition(sf::Vector2f position);
};
