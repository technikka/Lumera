#include "creature.hpp"

Creature::Creature(float radius, sf::Vector2f position) : body(radius) {
    body.setFillColor(fill_color);

    // Set the origin to the center of creature
    auto bounds = body.getLocalBounds();
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
    body.setPosition(position);
}

void Creature::Move(sf::Vector2f new_position) {
    trail.push_back(body.getPosition());
    body.move(new_position);
}

void Creature::DrawTrail(sf::RenderWindow& window) const {
    sf::CircleShape trail_point(2.f);
    trail_point.setFillColor(sf::Color::Cyan);

    for (const auto& step : trail) {
        trail_point.setPosition(step);
        window.draw(trail_point);
    }
}

void Creature::Draw(sf::RenderWindow& window) const {
    DrawTrail(window);
    window.draw(body);
}