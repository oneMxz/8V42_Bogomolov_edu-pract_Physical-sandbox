#include "world.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

World::World() {
    srand(time(0));
    grid = std::vector<std::vector<Element>>(
        Constants::HEIGHT, 
        std::vector<Element>(Constants::WIDTH, AIR)
    );
}

bool World::isValidPosition(int x, int y) const {
    return x >= 0 && x < Constants::WIDTH && y >= 0 && y < Constants::HEIGHT;
}

void World::moveElement(int x, int y, int newX, int newY, std::vector<std::vector<Element>>& newGrid) {
    if (isValidPosition(newX, newY) && newGrid[newY][newX] == AIR) {
        newGrid[newY][newX] = grid[y][x];
        newGrid[y][x] = AIR;
    }
}

void World::handleInput(const sf::Event& event, const sf::Vector2f& mousePos) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Num1) currentElement = SAND;
        if (event.key.code == sf::Keyboard::Num2) currentElement = WATER;
        if (event.key.code == sf::Keyboard::Num3) currentElement = STONE;
        if (event.key.code == sf::Keyboard::Num4) currentElement = WOOD;
        if (event.key.code == sf::Keyboard::Num0) currentElement = AIR;
        if (event.key.code == sf::Keyboard::Up) brushSize = std::min(20, brushSize + 1);
        if (event.key.code == sf::Keyboard::Down) brushSize = std::max(1, brushSize - 1);
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        int gridX = static_cast<int>(mousePos.x) / Constants::CELL_SIZE;
        int gridY = static_cast<int>(mousePos.y) / Constants::CELL_SIZE;

        for (int dy = -brushSize; dy <= brushSize; ++dy) {
            for (int dx = -brushSize; dx <= brushSize; ++dx) {
                if (dx*dx + dy*dy > brushSize*brushSize) continue;
                
                int x = gridX + dx;
                int y = gridY + dy;
                if (isValidPosition(x, y)) {
                    grid[y][x] = currentElement;
                }
            }
        }
    }
}

void World::update(bool paused) {
    if (!paused) {
        updatePhysics();
    }
}

void World::updatePhysics() {
    auto newGrid = grid;
    
    // Обновление снизу вверх для реалистичной физики
    for (int y = Constants::HEIGHT - 2; y >= 0; --y) {
        for (int x = 0; x < Constants::WIDTH; ++x) {
            Element current = grid[y][x];
            
            if (current == SAND) {
                // Песок: падает вниз, затем вбок
                if (grid[y+1][x] == AIR || grid[y+1][x] == WATER) {
                    moveElement(x, y, x, y+1, newGrid);
                } else {
                    int dir = (rand() % 2) ? 1 : -1;
                    int newX = x + dir;
                    if (isValidPosition(newX, y+1) && 
                       (grid[y+1][newX] == AIR || grid[y+1][newX] == WATER)) {
                        moveElement(x, y, newX, y+1, newGrid);
                    } else {
                        newX = x - dir;
                        if (isValidPosition(newX, y+1) && 
                           (grid[y+1][newX] == AIR || grid[y+1][newX] == WATER)) {
                            moveElement(x, y, newX, y+1, newGrid);
                        }
                    }
                }
            }
            else if (current == WATER) {
                // Вода: падает вниз, растекается вбок
                bool moved = false;
                
                // Падение вниз
                if (grid[y+1][x] == AIR) {
                    moveElement(x, y, x, y+1, newGrid);
                    moved = true;
                } 
                // Падение вбок вниз
                else if (!moved) {
                    int dir = (rand() % 2) ? 1 : -1;
                    int newX = x + dir;
                    if (isValidPosition(newX, y+1) && grid[y+1][newX] == AIR) {
                        moveElement(x, y, newX, y+1, newGrid);
                        moved = true;
                    } else {
                        newX = x - dir;
                        if (isValidPosition(newX, y+1) && grid[y+1][newX] == AIR) {
                            moveElement(x, y, newX, y+1, newGrid);
                            moved = true;
                        }
                    }
                }
                else if (!moved) { // Добавить условие проверки
                    int dir = (rand() % 2) ? 1 : -1;
                    if (isValidPosition(x+dir, y) && grid[y][x+dir] == AIR) {
                        moveElement(x, y, x+dir, y, newGrid);
                        moved = true;
                    } else if (isValidPosition(x-dir, y) && grid[y][x-dir] == AIR) {
                        moveElement(x, y, x-dir, y, newGrid);
                        moved = true;
                    }
                }
                
                // Растекание вбок
                if (!moved) {
                    int dir = (rand() % 2) ? 1 : -1;
                    if (isValidPosition(x+dir, y) && grid[y][x+dir] == AIR) {
                        moveElement(x, y, x+dir, y, newGrid);
                        moved = true;
                    } else if (isValidPosition(x-dir, y) && grid[y][x-dir] == AIR) {
                        moveElement(x, y, x-dir, y, newGrid);
                        moved = true;
                    }
                }
            }
        }
    }
    
    grid = newGrid;
}

void World::draw(sf::RenderWindow& window) const {
    for (int y = 0; y < Constants::HEIGHT; ++y) {
        for (int x = 0; x < Constants::WIDTH; ++x) {
            sf::RectangleShape pixel(sf::Vector2f(
                Constants::CELL_SIZE, 
                Constants::CELL_SIZE
            ));
            pixel.setPosition(x * Constants::CELL_SIZE, y * Constants::CELL_SIZE);
            
            switch (grid[y][x]) {
                case SAND: pixel.setFillColor(sf::Color(194, 178, 128)); break;
                case WATER: pixel.setFillColor(sf::Color(64, 164, 223, 200)); break;
                case STONE: pixel.setFillColor(sf::Color(128, 128, 128)); break;
                case WOOD: pixel.setFillColor(sf::Color(139, 69, 19)); break;
                default: pixel.setFillColor(sf::Color::Black);
            }
            
            window.draw(pixel);
        }
    }
}

Element World::getCurrentElement() const {
    return currentElement;
}

int World::getBrushSize() const {
    return brushSize;
}

void World::setElement(Element element) {
    currentElement = element;
}

void World::setBrushSize(int size) {
    brushSize = size;
}