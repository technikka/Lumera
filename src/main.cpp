#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Lumera");
    sf::CircleShape circle(20.f);
    circle.setFillColor(sf::Color::Blue);

    auto size = window.getSize();

    // Set the origin to the center of the circle.
    auto bounds = circle.getLocalBounds();
    circle.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                      bounds.position.y + bounds.size.y / 2.f});

    // Center it in the window.
    auto windowSize = window.getSize();
    circle.setPosition({windowSize.x / 2.f,
                        windowSize.y / 2.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }
}
