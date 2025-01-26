#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <math.h>

constexpr int WIDTH = 600;
constexpr int HEIGHT = 600;
constexpr int SCALE = 5; // size of individual pixel
constexpr int SCALESQ = SCALE * SCALE;
constexpr int PIXELSNUMBER = WIDTH * HEIGHT / (SCALESQ);

std::unique_ptr<sf::RenderWindow> window;

extern "C"{
    #include "prng.c"
}

int now(){
// Get the current time from the system clock
    auto now = std::chrono::system_clock::now();

    // Convert the current time to time since epoch
    auto duration = now.time_since_epoch();

    // Convert duration to milliseconds
    auto milliseconds
        = std::chrono::duration_cast<std::chrono::milliseconds>(
              duration)
              .count();
    return milliseconds % 100000;
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

float vals[PIXELSNUMBER];
sf::Vector2i mousePrevPos;
float mouseDelta;
float* calculate(){
    for (int p = 0; p < PIXELSNUMBER; p++){
        // vals[p] = getNext(p); // 1D
        vals[p] = getNext2D(p % WIDTH + mouseDelta, p / WIDTH);
    }
    return vals;
}

int main() {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), "C random visualizer");
    window->setFramerateLimit(60);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition();
        mouseDelta += hypotf(mousePos.x - mousePrevPos.x, mousePos.y - mousePrevPos.y);
        mousePrevPos = mousePos;

        window->clear(sf::Color::Black);
        render(calculate(), PIXELSNUMBER);
        std::cout << now() << std::endl;
        window->display();
    }

    return 0;
}
