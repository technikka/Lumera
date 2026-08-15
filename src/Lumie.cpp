#include "Lumie.hpp"
#include "PerlinNoise.hpp"

#include <iostream>
#include <optional>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

Lumie::Lumie(sf::Vector2u window_size, std::optional<sf::Vector2f> position)
    : window_size(window_size), body(16) {
    DefineShape();
    SetPosition(position);
    SetGlow();

    perlin.reseed(rd());
}

void Lumie::DefineShape() {
    body.setPoint(0, {5.f, 0.f});
    body.setPoint(1, {6.f, .5f});
    body.setPoint(2, {6.f, 1.f});
    body.setPoint(3, {7.f, 2.f});
    body.setPoint(4, {7.f, 3.f});
    body.setPoint(5, {6.f, 4.f});
    body.setPoint(6, {6.f, 5.f});
    body.setPoint(7, {6.f, 6.f});
    body.setPoint(8, {5.f, 7.f});
    body.setPoint(9, {4.f, 6.f});
    body.setPoint(10, {4.f, 5.f});
    body.setPoint(11, {4.f, 4.f});
    body.setPoint(12, {3.f, 3.f});
    body.setPoint(13, {3.f, 2.f});
    body.setPoint(14, {4.f, 1.f});
    body.setPoint(15, {4.f, .5f});

    body.setFillColor(GetRandomColor());
    body.setScale({2.f, 2.f});
}

void Lumie::SetGlow() {
    glow = body;
    glow.setScale({2.8f, 2.8f});
    glow.setPosition(body.getPosition());
    sf::Color glow_color = body.getFillColor();
    glow_color.a = 100;
    glow.setFillColor(glow_color);
}

void Lumie::SetPosition(std::optional<sf::Vector2f> position) {
    // Set the origin to the center of creature
    auto bounds = body.getLocalBounds();
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});

    sf::Vector2f start_position =
        position.value_or(GetRandomPosition(window_size));

    body.setPosition(start_position);
}

sf::FloatRect Lumie::GetBounds() const { return body.getGlobalBounds(); }

double MapNoise(double value, double input_min, double input_max,
                double output_min, double output_max) {
    return output_min + (value - input_min) * (output_max - output_min) /
                            (input_max - input_min);
}

sf::Vector2f Lumie::GetNextPosition(sf::Vector2u window_size) {
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

void Lumie::MoveTo(sf::Vector2f position) {
    trail.push_back(body.getPosition());
    body.setPosition(position);
    glow.setPosition(position);
}

void Lumie::DrawTrail(sf::RenderWindow& window) const {
    sf::Color trail_color = body.getFillColor();
    trail_color.a = 80;

    sf::CircleShape trail_point(1.f);
    trail_point.setFillColor(trail_color);

    for (const auto& step : trail) {
        trail_point.setPosition(step);
        window.draw(trail_point);
    }
}

void Lumie::Draw(sf::RenderWindow& window) const {
    // DrawTrail(window);
    window.draw(glow);
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
    sf::Color colors[] = {
        {210, 255, 60},   // yellow-green
        {170, 255, 70},   // lime
        {120, 255, 110},  // green
        {80, 240, 180},   // aqua-green
        {70, 210, 255},   // cyan-blue
    };
    // static std::uniform_int_distribution<int> color_dist(30, 230);

    // return {static_cast<std::uint8_t>(color_dist(gen)),
    //         static_cast<std::uint8_t>(color_dist(gen)),
    //         static_cast<std::uint8_t>(color_dist(gen))};
    std::uniform_int_distribution<int> dist(0, 4);

    sf::Color color = colors[dist(gen)];
    return color;
}
