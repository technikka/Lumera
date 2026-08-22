#include <random>

#include "PerlinNoise.hpp"
#include "Seekra.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

Seekra::Seekra(sf::Vector2u window_size) : MovingObject(window_size) {
    DefineShape();
    SetPosition();

    perlin.reseed(rd());
}

void Seekra::SetRandomAcceleration() {
    const double x_noise = perlin.noise1D(noise_x);
    const double y_noise = perlin.noise1D(noise_y);

    const double acceleration_scale = 0.05;

    acceleration = {static_cast<float>(x_noise * acceleration_scale),
                    static_cast<float>(y_noise * acceleration_scale)};

    noise_x += 0.1;
    noise_y += 0.1;
}

std::vector<sf::Vector2f> points{
    {3.f, 0.f},  {3.2f, 1.f},  {2.5f, 2.f},  {2.5f, 3.f}, {1.5f, 3.5f},
    {2.f, 4.5f}, {1.8f, 5.5f}, {2.5f, 6.5f}, {3.f, 7.5f}, {4.f, 8.5f},
    {5.f, 7.5f}, {5.5f, 6.5f}, {6.2f, 5.5f}, {6.f, 4.5f}, {6.5f, 3.5f},
    {5.5f, 3.f}, {5.5f, 2.f},  {4.8f, 1.f},  {5.f, 0.f}};

void Seekra::DefineShape() {
    body.setPointCount(points.size());

    for (std::size_t i = 0; i < points.size(); ++i) {
        body.setPoint(i, points[i]);
    }

    SetBodyOrigin(body);
    body.setFillColor(sf::Color(44, 82, 62));
    body.setScale({3.f, 3.f});
}

void Seekra::SetPosition() {
    sf::Vector2f center{window_size.x / 2.f, window_size.y / 2.f};
    body.setPosition(center);
}

void Seekra::Move() {
    SetRandomAcceleration();
    velocity += acceleration;

    sf::Vector2f new_position = body.getPosition() + velocity;

    sf::Vector2f current_position = body.getPosition();
    sf::Vector2f movement = new_position - current_position;
    if (movement != sf::Vector2f{0.f, 0.f}) {
        auto angle = movement.angle();
        body.setRotation(angle + sf::degrees(90.f));
    }

    body.setPosition(GetWrappedPosition(new_position));
}

void Seekra::Draw(sf::RenderWindow& window) const { window.draw(body); }

sf::FloatRect Seekra::GetBounds() const { return body.getGlobalBounds(); }

sf::Vector2f Seekra::GetPosition() const { return body.getPosition(); }