#include <random>

#include "Mover.hpp"
#include "PerlinNoise.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

Mover::Mover(sf::Vector2u window_size) : window_size(window_size) {
    DefineShape();
    SetPosition();

    perlin.reseed(rd());
}

void Mover::SetRandomAcceleration() {
    const double x_noise = perlin.noise1D(noise_x);
    const double y_noise = perlin.noise1D(noise_y);

    const double acceleration_scale = 0.05;

    acceleration = {static_cast<float>(x_noise * acceleration_scale),
                    static_cast<float>(y_noise * acceleration_scale)};

    noise_x += 0.1;
    noise_y += 0.1;
}

void Mover::DefineShape() {
    body.setRadius(8.f);

    sf::FloatRect bounds = body.getLocalBounds();
    // Set the origin to the center of creature
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});

    body.setFillColor(sf::Color(44, 82, 62));
}

void Mover::SetPosition() {
    sf::Vector2f center{window_size.x / 2.f, window_size.y / 2.f};
    body.setPosition(center);
}

void Mover::Move() {
    SetRandomAcceleration();
    velocity += acceleration;

    const float width = static_cast<float>(window_size.x);
    const float height = static_cast<float>(window_size.y);

    sf::Vector2f new_position = body.getPosition() + velocity;

    // Check edges
    if (new_position.x > width) {
        new_position.x = 0;
    } else if (new_position.x < 0.f) {
        new_position.x = width;
    }

    if (new_position.y > height) {
        new_position.y = 0;
    } else if (new_position.y < 0.f) {
        new_position.y = height;
    }

    body.setPosition(new_position);
}

void Mover::Draw(sf::RenderWindow& window) const { window.draw(body); }