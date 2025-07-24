#include "MenuButton.h"
#include <SFML/Graphics.hpp>

MenuButton::MenuButton(const std::string& btnText, sf::Font& font, sf::Vector2f position, sf::Vector2f size) 
    : shape(size), text(btnText, font, 24), originalSize(size) {
    
    // Центрируем кнопку
    shape.setOrigin(size.x / 2, size.y / 2);
    shape.setPosition(position);
    
    // Центрируем текст внутри кнопки
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, 
                 textRect.top + textRect.height / 2.0f);
    text.setPosition(position);
    
    shape.setFillColor(sf::Color(70, 70, 140));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
}

void MenuButton::update(const sf::Vector2f& mousePos) {
    bool wasHovered = isHovered;
    isHovered = shape.getGlobalBounds().contains(mousePos);

    if (isHovered && !wasHovered) {
        shape.setSize(originalSize * 1.1f);
        shape.setFillColor(sf::Color(100, 100, 180));
        updateTextPosition();
    } else if (!isHovered && wasHovered) {
        shape.setSize(originalSize);
        shape.setFillColor(sf::Color(70, 70, 140));
        updateTextPosition();
    }
}

void MenuButton::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    window.draw(text);
}

bool MenuButton::isClicked(const sf::Vector2f& mousePos, sf::Event& event) {
    return (event.type == sf::Event::MouseButtonPressed && 
        event.mouseButton.button == sf::Mouse::Left &&
        shape.getGlobalBounds().contains(mousePos));
}

void MenuButton::setText(const std::string& text) {
    this->text.setString(text);
    updateTextPosition();
}

void MenuButton::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
    updateTextPosition();
}

void MenuButton::updateTextPosition() {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition(
        shape.getPosition().x,
        shape.getPosition().y
    );
}