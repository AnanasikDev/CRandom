#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

constexpr int WIDTH = 1000;
constexpr int HEIGHT = 1000;

std::unique_ptr<sf::RenderWindow> window;

sf::Vector2f mousePos(){
    auto pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    return sf::Vector2f(pos.x, HEIGHT - pos.y);
}

int main()
{
    // Create the window
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "PRNG Shader visualization");

    // Define vertex data for a fullscreen quad
    sf::VertexArray quad(sf::TrianglesFan, 4);
    quad[0].position = sf::Vector2f(0.0f,  0.0f);
    quad[1].position = sf::Vector2f(WIDTH, 0.0f);
    quad[2].position = sf::Vector2f(WIDTH, HEIGHT);
    quad[3].position = sf::Vector2f(0.0f,  HEIGHT);

    // Load the shader
    sf::Shader shader;
    if (!shader.loadFromFile("prng.glsl", sf::Shader::Fragment)) {
        return -1; // Failed to load shader
    }
    shader.setUniform("u_scale", 100.0f);

    // Main rendering loop
    sf::Clock clock;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        // Clear the screen with black
        window->clear(sf::Color::Black);

        // Draw the quad with the procedural shader
        float time = clock.getElapsedTime().asSeconds();
        shader.setUniform("u_time", time);
        shader.setUniform("u_resolution", sf::Glsl::Vec2(window->getSize()));
        shader.setUniform("u_mouse", mousePos());
        window->draw(quad, &shader);

        // Display the contents of the window
        window->display();
    }

    return 0;
}
