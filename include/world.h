#ifndef WORLD_H
#define WORLD_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"
#include "Element.h"

class World {
public:
    World();
    void handleInput(const sf::Event& event, const sf::Vector2f& mousePos);
    void update(bool paused);
    void draw(sf::RenderWindow& window) const;
    void setElement(Element element);
    void setBrushSize(int size);
    Element getCurrentElement() const;
    int getBrushSize() const;

private:
    void updatePhysics();
    bool isValidPosition(int x, int y) const;
    void moveElement(int x, int y, int newX, int newY, std::vector<std::vector<Element>>& newGrid);

    std::vector<std::vector<Element>> grid;
    Element currentElement = SAND;
    int brushSize = 3;
};
#endif