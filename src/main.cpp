#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include "MenuButton.h"
#include "world.h"
#include "Constants.h"
#include "music.h"

// Состояния приложения
enum AppState { MENU, GAME };

int main() {
    // Окно приложения
    sf::RenderWindow window(sf::VideoMode(Constants::MENU_WIDTH, Constants::MENU_HEIGHT), "Sandbox Game");
    window.setFramerateLimit(60);
    
    // Шрифт
    sf::Font font;
    if (!font.loadFromFile("AnkhSanctuary-PVK0B.ttf")) {
        return 1;
    }
    // Менеджер музыки
    MusicManager musicManager;
    if (!musicManager.load("3d20874f20174bd.mp3")) {
        return 1;
    }
    musicManager.setVolume(70.0f);
    musicManager.play();
    bool musicEnabled = true;
    
    // Создание кнопок по центру окна
    std::vector<MenuButton> buttons;
    buttons.push_back(MenuButton("PLAY", font, sf::Vector2f(400, 200), sf::Vector2f(200, 50)));
    buttons.push_back(MenuButton("MUSIC: ON", font, sf::Vector2f(400, 280), sf::Vector2f(200, 50)));
    buttons.push_back(MenuButton("EXIT", font, sf::Vector2f(400, 360), sf::Vector2f(200, 50)));
    
    // Для FPS
    sf::Clock fpsClock;
    int frameCount = 0;
    float fps = 0;
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(10, 10);
    
    // Состояние приложения
    AppState currentState = MENU;
    bool paused = false;
    
    // Игровой мир
    World world;
    
    // Часы для дельта-времени
    sf::Clock deltaClock;
    
    // Главный цикл
    while (window.isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
    
                // Центрируем кнопки при изменении размера
                sf::Vector2f newCenter(event.size.width / 2.0f, 0);
                buttons[0].setPosition(sf::Vector2f(newCenter.x, 200));
                buttons[1].setPosition(sf::Vector2f(newCenter.x, 280));
                buttons[2].setPosition(sf::Vector2f(newCenter.x, 360));
            }
            // Обработка клавиатуры
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (currentState == GAME) {
                        currentState = MENU;
                        window.create(
                            sf::VideoMode(Constants::MENU_WIDTH, Constants::MENU_HEIGHT), 
                            "Sandbox Game"
                        );
                        window.setFramerateLimit(60);
        
                        // Обновление позиций кнопок
                        sf::Vector2u size = window.getSize();
                        for (int i = 0; i < buttons.size(); ++i) {
                            buttons[i].setPosition(sf::Vector2f(size.x/2.0f, 200 + i * 80));
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::Space && currentState == GAME) {
                    paused = !paused;
                }
            }
            
            // Обработка нажатия кнопок в меню
            if (currentState == MENU) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].isClicked(mousePos, event)) {
                        if (i == 0) { // Play
                            currentState = GAME;
                            window.create(
                                sf::VideoMode(
                                    Constants::WIDTH * Constants::CELL_SIZE, 
                                    Constants::HEIGHT * Constants::CELL_SIZE
                                ), 
                                "Sandbox Physics"
                            );
                            window.setFramerateLimit(60);
                        } else if (i == 1) { // Music
                            musicManager.toggle();
                            musicEnabled = musicManager.isPlaying();
                            if (musicEnabled) {
                                buttons[1].setText("MUSIC: ON");
                            } else {
                                buttons[1].setText("MUSIC: OFF");
                            }
                        } else if (i == 2) { // Exit
                            window.close();
                        }
                    }
                }
            }

            // Обработка клавиатуры для управления музыкой
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::M) {
                    musicManager.toggle();
                    musicEnabled = musicManager.isPlaying();
                    if (musicEnabled) {
                        buttons[1].setText("MUSIC: ON");
                    } else {
                        buttons[1].setText("MUSIC: OFF");
                    }
                }
                if (event.key.code == sf::Keyboard::Up) {
                    musicManager.setVolume(musicManager.getVolume() + 10);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    musicManager.setVolume(musicManager.getVolume() - 10);
                }
            }
            
            // Обработка ввода в игре
            if (currentState == GAME) {
                world.handleInput(event, 
                    sf::Vector2f(sf::Mouse::getPosition(window)));
            }
        }
        
        // Обновление состояния
        if (currentState == MENU) {
            // Обновление состояния кнопок
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            for (auto& button : buttons) {
                button.update(mousePos);
            }
        }
        
        // Обновление игры
        if (currentState == GAME) {
            world.update(paused);
        }
        
        // Обновление счетчика FPS
        frameCount++;
        if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {
            fps = frameCount / fpsClock.restart().asSeconds();
            frameCount = 0;
            
            std::ostringstream ss;
            ss << "FPS: " << static_cast<int>(fps);
            fpsText.setString(ss.str());
        }
        
        // Отрисовка
        window.clear();
        
        if (currentState == MENU) {
            // Простой темно-синий фон без обоев
            window.clear(sf::Color(30, 30, 60));
            
            // Отрисовка кнопок
            for (auto& button : buttons) {
                button.draw(window);
            }
            
            // Заголовок
            sf::Text title("SANDBOX", font, 60);
            title.setFillColor(sf::Color(220, 220, 50));
            title.setStyle(sf::Text::Bold);
            sf::FloatRect titleRect = title.getLocalBounds();
            title.setOrigin(titleRect.width/2.0f, titleRect.height/2.0f);
            title.setPosition(window.getSize().x/2.0f, 100);
            window.draw(title);
        }
        else if (currentState == GAME) {
            window.clear(sf::Color::Black);
            world.draw(window);
            
            // Панель информации
            sf::Text infoText;
            infoText.setFont(font);
            infoText.setCharacterSize(16);
            infoText.setFillColor(sf::Color::White);
            infoText.setPosition(10, 10);
            
            std::ostringstream info;
            info << "\n";
            info << "Brush: " << world.getBrushSize() << " (Up/Down to change)\n";
            info << "Element: ";
            switch (world.getCurrentElement()) {
                case SAND: info << "SAND (1)"; break;
                case WATER: info << "WATER (2)"; break;
                case STONE: info << "STONE (3)"; break;
                case WOOD: info << "WOOD (4)"; break;
                case AIR: info << "ERASER (0)"; break;
                default: info << "UNKNOWN";
            }
            info << "\n";
            info << (paused ? "PAUSED (Space)" : "Running (Space to pause)");
            info << "\nESC: Menu";
            
            infoText.setString(info.str());
            window.draw(infoText);
        }
        
        // Всегда отображаем FPS
        window.draw(fpsText);
        
        
        window.display();
    }
    
    return 0;
}