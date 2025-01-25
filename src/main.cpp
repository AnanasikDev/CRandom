#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

constexpr int WIDTH = 600;
constexpr int HEIGHT = 600;
constexpr int SCALE = 5; // size of individual pixel
constexpr int SCALESQ = SCALE * SCALE;
constexpr int PIXELSNUMBER = WIDTH * HEIGHT / (SCALESQ);

std::unique_ptr<sf::RenderWindow> window;

extern "C"{
    #include "prng.c"
}

sf::Color float2color(float f){
    return sf::Color((sf::Uint32)(255 * f),(sf::Uint32)(255 * f),(sf::Uint32)(255 * f),255);
}

void render(float* values, int number){
    
    for (int i = 0; i < number; i++){
        
        int x = (i % (WIDTH / SCALE)) * SCALE;
        int y = (i / (WIDTH / SCALE)) * SCALE;
        
        auto pixel = sf::RectangleShape(sf::Vector2f(1 * SCALE,1 * SCALE));
        pixel.setFillColor(float2color(values[i]));
        pixel.setPosition(sf::Vector2f(x, y));
        
        window->draw(pixel);
    }
}

int main() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "SFML Window");

    float vals[PIXELSNUMBER];
    for (int p = 0; p < PIXELSNUMBER; p++){
        vals[p] = getNext(p);
    }

    window->clear(sf::Color::Black);
    render(vals, PIXELSNUMBER);
    window->display();

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
    }

    return 0;
}
