# 8V42_Bogomolov_edu-pract_Physical-sandbox
# Sandbox Game - Физическая песочница

# Описание проекта
Sandbox Game - это интерактивная физическая песочница, где вы можете создавать и взаимодействовать с различными элементами: песком, водой, камнем и деревом. Каждый элемент обладает уникальной физикой и поведением, создавая реалистичные взаимодействия. Проект реализован на C++ с использованием библиотеки SFML.

## Ключевые особенности
- Реалистичная физика элементов:
  - Песок падает вниз и растекается по диагонали
  - Вода течет вниз и растекается в стороны
  - Камень и дерево остаются статичными
- Гибкие инструменты создания:
  - 5 типов элементов (песок, вода, камень, дерево, ластик)
  - Регулируемый размер кисти (от 1 до 20 пикселей)
  - Круглая область рисования
- Аудиосистема:
  - Фоновая музыка
  - Регулировка громкости
  - Включение/выключение звука
- Интуитивный интерфейс:
  - Главное меню с кнопками
  - Анимация кнопок при наведении
  - Информационная панель в режиме игры
- Технические возможности:
  - Отображение FPS в реальном времени
  - Пауза/продолжение симуляции
  - Адаптация к изменению размера окна

## Системные требования
- ОС: Windows
- Оперативная память: 512 MB+
- Зависимости: SFML 2.6.2, OpenAL
- Рекомендуемый редактор кода: Visual Studio Code.

## Управление
### В режиме игры:
- ЛКМ: Рисовать выбранным элементом
- 0: Ластик
- 1: Песок
- 2: Вода
- 3: Камень
- 4: Дерево
- Стрелки вверх/вниз: Изменить размер кисти
- Пробел: Пауза/продолжить симуляцию
- ESC: Вернуться в главное меню
- M: Включить/выключить музыку

### В главном меню:
- ЛКМ: Выбор пунктов меню
- Наведение: Анимация кнопок

## Сборка проекта
Для сборки проекта необходимы:
- CMake (версия 3.15 или выше)
- Библиотека SFML (версия 2.6.2)

## Инструкция по сборке:
Перед тем, как начать компиляцию проекта, необходимо установить библиотеку SFML.
### Установка SFML
Для Windows — скачать и установить SFML с официального сайта библиотеки (https://www.sfml-dev.org/download/sfml/2.6.2/).
Выберите версию, совместимую с вашим компилятором, в случае проекта это 64-битная версия. Так как проект был разработан с использованием компилятора GCC, скачиваем GCC 13.1.0 MinGW (SEH). Далее, создайте в любом удобном для вас месте на компьютере папку, куда вы сможете разархивировать библиотеки (например: C:\libraries). Затем распакуйте скачанный архив SFML в эту папку. Путь к данной директории стоит запомнить для последующей настройки. В VS Code установить расширение C/C++. При последующей попытке запуска программы возникнет ошибка, связанная с тем, что программа не видит SFML. Для того, чтобы исправить данную ошибку, необходимо настроить путь к директории include библиотеки SFML: открыть файл .vscode/c_cpp_properties.json и указать пути к заголовочным файлам SFML. Более детально ознакомиться с настройкой библиотеки SFML можно по ссылкам ниже в разделе дополнительных ресурсов.

### Клонирование репозитория
`git clone https://github.com/yourusername/sandbox-game.git`
`cd sandbox-game`

### Создание директории для сборки
`mkdir build`
`cd build`

### Генерация проектных файлов
`cmake ..`

### Сборка проекта
`cmake --build `

### Запуск приложения (Windows)
`./Debug/sandbox.exe`



## Технические детали реализации
- Физическая модель: симуляция на сетке 200x150 пикселей
- Рендеринг: Оптимизированная отрисовка через SFML
- Архитектура: Объектно-ориентированный подход с разделением на компоненты
- Оптимизация: Ограничение FPS для стабильной работы
## Решение проблем
Если возникают ошибки:

1. Не загружается шрифт: проверьте путь в main.cpp: "AnkhSanctuary-PvKoB.ttf"
2. Ошибки линковки SFML: проверьте пути в CMakeLists.txt
3. Музыка не играет: проверьте наличие openal32.dll в папке bin, а также убедитесь в наличии аудиофайла bin/3d20874f20174bd.mp3

## Дополнительные ресурсы
Установка SFML в VSCode:
- https://rutube.ru/video/e1e15c9869d445fe6c4b6b20a83ea990/
- http://www.youtube.com/watch?v=rZE700aaT5I

Документация SFML:
- https://www.sfml-dev.org/documentation/2.6.2/

## Личная информация
Maxim Bogomolov - https://github.com/oneMxz  



# 8V42_Bogomolov_edu-practicalphysical-sandbox
# Sandbox Game - Physical Sandbox

# Project Description
Sandbox Game is an interactive physical sandbox where you can create and interact with various elements: sand, water, stone and wood. Each element has unique physics and behavior, creating realistic interactions. The project is implemented in C++ using the SFML library.

## Key Features
- Realistic physics of the elements:
- Sand falls down and spreads diagonally
- Water flows down and spreads sideways
  - Stone and wood remain static
- Flexible creation tools:
- 5 types of elements (sand, water, stone, wood, eraser)
- Adjustable brush size (from 1 to 20 pixels)
- Round drawing area
- Audio System:
- Background music
  - Volume control
  - Turn on/off the sound
- Intuitive interface:
- Main menu with buttons
- Button animation when pointing
- Information panel in game mode
- Technical features:
- Real-time FPS display
- Pause/continue simulation
- Adaptation to window size change

## System requirements
- OS: Windows
- RAM: 512 MB+
- Dependencies: SFML 2.6.2, OpenAL
- Recommended code editor: Visual Studio Code.

## Management
### In game mode:
- LMB: Draw with the selected element
- 0: Eraser
- 1: Sand
- 2: Water
- 3: Stone
- 4: Wood
- Up/down arrows: Change the brush size
- Space bar: Pause/continue simulation
- ESC: Return to the main menu
- M: Turn on/off music

### In the main menu:
- LMB: Selection of menu items
- Hover: Button animation

## Building a project
To build a project, you need:
- CMake (version 3.15 or higher)
- SFML library (version 2.6.2)

## Assembly instructions:
Before you can start compiling a project, you need to install the SFML library.
### Installing SFML
For Windows — download and install SFML from the library's official website (https://www.sfml-dev.org/download/sfml/2.6.2 /).
Choose a version that is compatible with your compiler. In the case of a project, it is a 64-bit version. Since the project was developed using the GCC compiler, download GCC 13.1.0 MinGW (SEH). Next, create a folder on your computer where you can unzip the libraries (for example: C:\libraries ). Then unzip the downloaded SFML archive to this folder. The path to this directory should be remembered for subsequent configuration. Install the C/C++ extension in VS Code. A subsequent attempt to run the program will result in an error due to the fact that the program does not see SFML. In order to fix this error, you need to configure the path to the include directory of the SFML library: open the file.vscode/c_cpp_properties.json and specify the paths to the SFML header files. To learn more about configuring the SFML library, follow the links below.

### Cloning the repository
`git clone https://github.com/yourusername/sandbox-game.git`
`cd sandbox-game`

### Creating a directory for the build
`mkdir build`
`cd build`

### Generating project files
`cmake ..`

### Building a project
`cmake --build `

### Launching the application (Windows)
`./Debug/sandbox.exe `



## Technical details of the implementation
- Physical model: simulation on a 200x150 pixel grid
- Rendering: Optimized rendering via SFML
- Architecture: An object-oriented approach with separation into components
- Optimization: FPS limitation for stable operation
## Problem solving
If errors occur:

1. The font won't load: check the path in main.cpp : "AnkhSanctuary-PvKoB.ttf"
2. SFML linking errors: check the paths in CMakeLists.txt
3. Music is not playing: check for availability openal32.dll in the bin folder, and also make sure that the audio file bin/3d20874f20174bd.mp3 is available.

## Additional resources
Installing SFML in VSCode:
- https://rutube.ru/video/e1e15c9869d445fe6c4b6b20a83ea990/
- http://www.youtube.com/watch?v=rZE700aaT5I

SFML documentation:
- https://www.sfml-dev.org/documentation/2.6.2/

## Personal information
Maxim Bogomolov - https://github.com/oneMxz
