#include <random>

#include "Mover.hpp"
#include "PerlinNoise.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

Mover::Mover(sf::Vector2u window_size) : MovingObject(window_size) {
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
    SetBodyOrigin(body);
    body.setFillColor(sf::Color(44, 82, 62));
}

void Mover::SetPosition() {
    sf::Vector2f center{window_size.x / 2.f, window_size.y / 2.f};
    body.setPosition(center);
}

void Mover::Move() {
    SetRandomAcceleration();
    velocity += acceleration;

    sf::Vector2f new_position = body.getPosition() + velocity;
    body.setPosition(GetWrappedPosition(new_position));
}

void Mover::Draw(sf::RenderWindow& window) const { window.draw(body); }

sf::FloatRect Mover::GetBounds() const { return body.getGlobalBounds(); }

sf::Vector2f Mover::GetPosition() const { return body.getPosition(); }