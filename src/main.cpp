#include <SFML/Graphics.hpp>
#include <iostream>

/*
    TODO:
        - Make and Render Map
        - Move Pac-Man in map   
        - Collision with maze pieces
        - Dots to eat and increase score
        - Ghosts AI
*/

int main() {

    // Map is 28 x 31 tiles
    // 1 tile = 8 x 8 in map
    // Sprites are 16 x 16
    
    sf::RenderWindow window(sf::VideoMode(224 * 3, 248 * 3), "Pac-Man");

    sf::Texture texture; 
    texture.loadFromFile("res/spritesheet.png");

    // IntRect(x, y, sizeX, sizeY)
    sf::IntRect rectSourceSprite(0, 0, 16, 16);
    sf::Sprite pacman(texture, rectSourceSprite);
    pacman.setScale(sf::Vector2f(10, 10));
    sf::Clock clock;

    sf::Event event;
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Animate Pacman
        if (clock.getElapsedTime().asSeconds() > 0.1f) {
            if (rectSourceSprite.left == 16 * 2) {
                rectSourceSprite.left = 0;
            } else {
                rectSourceSprite.left += 16;
            }

            pacman.setTextureRect(rectSourceSprite);
            clock.restart();
        }

        window.clear();
        window.draw(pacman);
        window.display();
    }
    return 0;
}