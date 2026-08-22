#include "Deltaframe.hpp"

Deltaframe::Deltaframe(sf::Vector2u window_size) : MovingObject(window_size) {
    DefineShape();
    SetPosition();
}

void Deltaframe::DefineShape() {
    body.setRadius(20);
    body.setPointCount(3);
    SetBodyOrigin(body);
    body.setFillColor(sf::Color::Transparent);
    body.setOutlineColor(sf::Color(95, 135, 175));
    body.setOutlineThickness(5.f);
}

void Deltaframe::SetPosition() {
    sf::Vector2f bottom_center{window_size.x / 2.f, window_size.y - 30.f};
    body.setPosition(bottom_center);
}

void Deltaframe::Draw(sf::RenderWindow& window) const { window.draw(body); }

void Deltaframe::Accelerate(sf::Vector2f amount) { acceleration += amount; }

void Deltaframe::Break() {
    if (std::abs(velocity.x) <= break_speed) {
        velocity.x = 0.f;
    } else if (velocity.x > 0.f) {
        acceleration.x -= break_speed;
    } else if (velocity.x < 0.f) {
        acceleration.x += break_speed;
    }

    if (std::abs(velocity.y) <= break_speed) {
        velocity.y = 0.f;
    } else if (velocity.y > 0.f) {
        acceleration.y -= break_speed;
    } else if (velocity.y < 0.f) {
        acceleration.y += break_speed;
    }
}

void Deltaframe::Move() {
    sf::Vector2f new_position = body.getPosition() + velocity;

    body.setPosition(GetWrappedPosition(new_position));
}

void Deltaframe::Update() {
    acceleration = {0, 0};

    bool key_pressed =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up)) {
        Accelerate({0, -0.1});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right)) {
        Accelerate({0.1, 0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down)) {
        Accelerate({0, 0.1});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left)) {
        Accelerate({-0.1, 0});
    }

    if (!key_pressed) {
        Break();
    }

    velocity += acceleration;

    // velocity.length() == magnitude
    if (velocity.length() > max_speed) {
        velocity = velocity.normalized() * max_speed;
    }

    Move();
}

sf::FloatRect Deltaframe::GetBounds() const { return body.getGlobalBounds(); }

sf::Vector2f Deltaframe::GetPosition() const { return body.getPosition(); }