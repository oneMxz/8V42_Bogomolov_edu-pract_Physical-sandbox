#ifndef MENUBUTTON_H
#define MENUBUTTON_H
#include <SFML/Graphics.hpp>
#include <string>

class MenuButton {
public:
    MenuButton(const std::string& btnText, sf::Font& font, 
               sf::Vector2f position, sf::Vector2f size);
    
    void update(const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window) const;
    bool isClicked(const sf::Vector2f& mousePos, sf::Event& event);
    void setText(const std::string& text);
    void setPosition(sf::Vector2f position);

private:
    void updateTextPosition();

    sf::RectangleShape shape;
    sf::Text text;
    bool isHovered = false;
    sf::Vector2f originalSize;
};
#endif