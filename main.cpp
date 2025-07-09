#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WIDTH = 200;
const int HEIGHT = 150;
const int CELL_SIZE = 5;

enum Element {
    AIR = 0,    // Прозрачный
    SAND = 1,   // Желтый
    WATER = 2,  // Синий
    STONE = 3,  // Серый
    WOOD = 4    // Коричневый
};

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), "Sandbox Physics");
    window.setFramerateLimit(60);

    std::vector<std::vector<Element>> grid(HEIGHT, std::vector<Element>(WIDTH, AIR));
    std::vector<std::vector<Element>> nextGrid = grid;
    
    Element currentElement = SAND;
    int brushSize = 3;
    bool paused = false;

    sf::Clock physicsClock;
    const float physicsRate = 1.0f / 60.0f;
    float accumulator = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) paused = !paused;
                if (event.key.code == sf::Keyboard::Num1) currentElement = SAND;
                if (event.key.code == sf::Keyboard::Num2) currentElement = WATER;
                if (event.key.code == sf::Keyboard::Num3) currentElement = STONE;
                if (event.key.code == sf::Keyboard::Num4) currentElement = WOOD;
                if (event.key.code == sf::Keyboard::Num0) currentElement = AIR;
                if (event.key.code == sf::Keyboard::Up) brushSize = std::min(10, brushSize + 1);
                if (event.key.code == sf::Keyboard::Down) brushSize = std::max(1, brushSize - 1);
            }
        }

        // Рисование элементов
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int gridX = mousePos.x / CELL_SIZE;
            int gridY = mousePos.y / CELL_SIZE;

            for (int dy = -brushSize; dy <= brushSize; ++dy) {
                for (int dx = -brushSize; dx <= brushSize; ++dx) {
                    int x = gridX + dx;
                    int y = gridY + dy;
                    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
                        grid[y][x] = currentElement;
                    }
                }
            }
        }

        // Обновление физики с фиксированным шагом
        accumulator += physicsClock.restart().asSeconds();
        while (accumulator >= physicsRate && !paused) {
            accumulator -= physicsRate;
            nextGrid = grid;

            // Обновление элементов (снизу вверх)
            for (int y = HEIGHT - 2; y >= 0; --y) {
                for (int x = 0; x < WIDTH; ++x) {
                    Element current = grid[y][x];
                    
                    if (current == SAND || current == WATER) {
                        // Движение вниз
                        if (grid[y + 1][x] == AIR) {
                            nextGrid[y][x] = AIR;
                            nextGrid[y + 1][x] = current;
                        }
                        // Движение вниз-диагональ
                        else {
                            int dir = (rand() % 2 == 0) ? 1 : -1;
                            bool moved = false;
                            
                            if (x + dir >= 0 && x + dir < WIDTH) {
                                if (grid[y + 1][x + dir] == AIR) {
                                    nextGrid[y][x] = AIR;
                                    nextGrid[y + 1][x + dir] = current;
                                    moved = true;
                                }
                            }
                            
                            // Для воды: движение вбок
                            if (!moved && current == WATER) {
                                if (x + dir >= 0 && x + dir < WIDTH && grid[y][x + dir] == AIR) {
                                    nextGrid[y][x] = AIR;
                                    nextGrid[y][x + dir] = WATER;
                                }
                            }
                        }
                    }
                }
            }
            grid = nextGrid;
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                sf::RectangleShape pixel(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                pixel.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                
                switch (grid[y][x]) {
                    case SAND: pixel.setFillColor(sf::Color(194, 178, 128)); break;
                    case WATER: pixel.setFillColor(sf::Color(64, 164, 223)); break;
                    case STONE: pixel.setFillColor(sf::Color(128, 128, 128)); break;
                    case WOOD: pixel.setFillColor(sf::Color(139, 69, 19)); break;
                    default: pixel.setFillColor(sf::Color::Black);
                }
                
                window.draw(pixel);
            }
        }
        
        window.display();
    }

    return 0;
}