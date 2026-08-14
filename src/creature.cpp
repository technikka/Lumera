#include "Creature.hpp"
#include "PerlinNoise.hpp"

#include <iostream>
#include <optional>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

Creature::Creature(float radius, sf::Vector2u window_size,
                   std::optional<sf::Vector2f> position)
    : body(radius), window_size(window_size) {
    body.setFillColor(GetRandomColor());

    // Set the origin to the center of creature
    auto bounds = body.getLocalBounds();
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});
    perlin.reseed(rd());

    body.setPosition(position.value_or(GetRandomPosition(window_size)));
}

sf::FloatRect Creature::GetBounds() const { return body.getGlobalBounds(); }

double MapNoise(double value, double input_min, double input_max,
                double output_min, double output_max) {
    return output_min + (value - input_min) * (output_max - output_min) /
                            (input_max - input_min);
}

sf::Vector2f Creature::GetNextPosition(sf::Vector2u window_size) {
    const double x_noise = perlin.noise1D_01(noise_x);
    const double y_noise = perlin.noise1D_01(noise_y);

    const sf::Vector2f movement{
        static_cast<float>(
            MapNoise(x_noise, 0.0, 1.0, -move_speed, move_speed)),
        static_cast<float>(
            MapNoise(y_noise, 0.0, 1.0, -move_speed, move_speed))};

    sf::Vector2f next_position = body.getPosition() + movement;

    const float width = static_cast<float>(window_size.x);
    const float height = static_cast<float>(window_size.y);

    if (next_position.x > width) {
        next_position.x -= width;
    } else if (next_position.x < 0.f) {
        next_position.x += width;
    }

    if (next_position.y > height) {
        next_position.y -= height;
    } else if (next_position.y < 0.f) {
        next_position.y += height;
    }

    noise_x += 0.01;
    noise_y += 0.01;

    return next_position;
}

void Creature::MoveTo(sf::Vector2f position) {
    trail.push_back(body.getPosition());
    body.setPosition(position);
}

void Creature::DrawTrail(sf::RenderWindow& window) const {
    sf::Color trail_color = body.getFillColor();
    trail_color.a = 80;

    sf::CircleShape trail_point(1.f);
    trail_point.setFillColor(trail_color);

    for (const auto& step : trail) {
        trail_point.setPosition(step);
        window.draw(trail_point);
    }
}

void Creature::Draw(sf::RenderWindow& window) const {
    // DrawTrail(window);
    window.draw(body);
}

sf::Vector2f GetRandomPosition(sf::Vector2u window_size) {
    std::uniform_real_distribution<float> x_dist(
        0.f, static_cast<float>(window_size.x));

    std::uniform_real_distribution<float> y_dist(
        0.f, static_cast<float>(window_size.y));

    return {x_dist(gen), y_dist(gen)};
}

sf::Color GetRandomColor() {
    static std::uniform_int_distribution<int> color_dist(30, 230);

    return {static_cast<std::uint8_t>(color_dist(gen)),
            static_cast<std::uint8_t>(color_dist(gen)),
            static_cast<std::uint8_t>(color_dist(gen))};
}
