#include "MenuButton.h"
#include <SFML/Graphics.hpp>

// Исправлен конструктор
MenuButton::MenuButton(const std::string& btnText, sf::Font& font, sf::Vector2f position, sf::Vector2f size) 
    : shape(size), text(btnText, font, 24), originalSize(size) {
    shape.setPosition(position);
    shape.setFillColor(sf::Color(70, 70, 140));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    updateTextPosition();
}

// Добавлен void
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
        shape.getPosition().x + shape.getSize().x / 2.0f,
        shape.getPosition().y + shape.getSize().y / 2.0f
    );
}