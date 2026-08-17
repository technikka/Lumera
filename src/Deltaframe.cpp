#include "Deltaframe.hpp"

Deltaframe::Deltaframe(sf::Vector2u window_size) : window_size(window_size) {
    DefineShape();
    SetPosition();
}

void Deltaframe::DefineShape() {
    body.setRadius(20);
    body.setPointCount(3);

    sf::FloatRect bounds = body.getLocalBounds();
    // Set the origin to the center of creature
    body.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                    bounds.position.y + bounds.size.y / 2.f});

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