#include <SFML/Graphics.hpp>
#include <iostream>

/*
    TODO:
        - Implement Fixed Time Step
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

    // Pac-Man should be "moved" 24 pixels at a time in a direction. 

    int SCALE = 3;
    int mapTileSize = 16; // 16 x 16 pixels
    int entitySize = 8; // 8 x 8 pixels

    sf::RenderWindow window(sf::VideoMode(224 * 3, 248 * 3), "Pac-Man");

    sf::Texture texture; 
    texture.loadFromFile("res/spritesheet.png");

    int mapXSize = 28; // 28 tiles
    int mapYSize = 31; 
    sf::Texture mapTexture;
    mapTexture.loadFromFile("res/mazeParts.png");

    // IntRect(x, y, sizeX, sizeY)
    sf::IntRect rectSourceSprite(16 * 2, 0, 16, 16);
    sf::Sprite pacman(texture, rectSourceSprite);
    pacman.setScale(sf::Vector2f(SCALE, SCALE));
    // Set Pac-Man's starting position
    pacman.setPosition(sf::Vector2f(mapTileSize * SCALE * 6.5, mapTileSize * SCALE * 11.25)); 
    pacman.setPosition(sf::Vector2f(mapTileSize * SCALE * 6, mapTileSize * SCALE * 11.25));  // PacMan moves 24 pixels in any direction at a time

    sf::Time elapsed;
    sf::Clock clock;

    sf::Vector2f speed = sf::Vector2f(4, 4); // float maybe? Vector? 

    sf::Event event;
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float frameTime = 1.0f / 60.0f; // Update game 60 times per second
        if (elapsed.asSeconds() >= frameTime) {
            // Do stuff 60 times a second
            pacman.setPosition((pacman.getPosition().x + speed.x), 0);
            elapsed -= sf::seconds(frameTime); // This is how we reset the cycle and keep running at a constant speed
        }

        //sf::sleep(sf::seconds(1.0f)); 
        /*
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
        */

        window.clear();
        // Update and Draw Map 
        for (int i = 0; i < mapXSize; i++) {
            for (int j = 0; j < mapYSize; j++) {
                // Make IntRect to pick out tile from Texture
                sf::IntRect mapRect(i * entitySize, j * entitySize, entitySize, entitySize);
                sf::Sprite mapPiece(mapTexture, mapRect);

                // Set Position
                mapPiece.setPosition(sf::Vector2f(i * entitySize * SCALE, j * entitySize * SCALE));
                mapPiece.setScale(sf::Vector2f(SCALE, SCALE));
                // Draw mapPiece
                window.draw(mapPiece);

            }
        }
        window.draw(pacman);
        window.display();
        elapsed += clock.restart();
    }
    return 0;
}