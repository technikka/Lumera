#pragma once

#include <SFML/Graphics.hpp>

class WorldObject {
   public:
    virtual ~WorldObject() = default;

    virtual sf::FloatRect GetBounds() const = 0;
};