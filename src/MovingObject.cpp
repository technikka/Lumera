#include <SFML/Graphics.hpp>

#include "MovingObject.hpp"

MovingObject::MovingObject(sf::Vector2u window_size)
    : window_size(window_size) {}

void MovingObject::SetBodyOrigin(sf::Shape& body) {
    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});  // Center
}

sf::Vector2f MovingObject::GetWrappedPosition(sf::Vector2f position) {
    const float width = static_cast<float>(window_size.x);
    const float height = static_cast<float>(window_size.y);

    if (position.x >= width) {
        position.x = 0;
    } else if (position.x < 0.f) {
        position.x = width - 1.f;
    }

    if (position.y >= height) {
        position.y = 0;
    } else if (position.y < 0.f) {
        position.y = height - 1.f;
    }

    return position;
}