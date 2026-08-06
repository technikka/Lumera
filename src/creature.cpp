#include "creature.hpp"
#include "PerlinNoise.hpp"

#include <iostream>
#include <random>

Creature::Creature(float radius, sf::Vector2f position) : body(radius) {
    body.setFillColor(fill_color);

    // Set the origin to the center of creature
    auto bounds = body.getLocalBounds();
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
    perlin.reseed(std::random_device{}());

    body.setPosition(position);
}

double MapNoise(double value, double input_min, double input_max,
                double output_min, double output_max) {
    return output_min + (value - input_min) * (output_max - output_min) /
                            (input_max - input_min);
}

void Creature::Move(sf::Vector2u window_size) {
    trail.push_back(body.getPosition());

    const double x_noise = perlin.noise1D_01(noise_x);
    const double y_noise = perlin.noise1D_01(noise_y);

    const sf::Vector2f movement{
        static_cast<float>(
            MapNoise(x_noise, 0.0, 1.0, -move_speed, move_speed)),
        static_cast<float>(
            MapNoise(y_noise, 0.0, 1.0, -move_speed, move_speed))};

    sf::Vector2f next_position = body.getPosition() + movement;
    const float radius = body.getRadius();

    next_position.x = std::clamp(next_position.x, radius,
                                 static_cast<float>(window_size.x) - radius);
    next_position.y = std::clamp(next_position.y, radius,
                                 static_cast<float>(window_size.y) - radius);

    body.setPosition(next_position);

    noise_x += 0.01;
    noise_y += 0.01;
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
