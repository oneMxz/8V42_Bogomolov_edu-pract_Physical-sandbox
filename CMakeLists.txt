cmake_minimum_required(VERSION 3.15)
project(SandboxGame)

set(CMAKE_CXX_STANDARD 17)

# Добавление папки с заголовочными файлами
include_directories(include)

# Настройки SFML
set(SFML_PATH "C:/libraries/SFML-2.6.2")
include_directories(${SFML_PATH}/include)
link_directories(${SFML_PATH}/lib)

# Исходные файлы
file(GLOB SOURCES "src/*.cpp")
add_executable(sandbox ${SOURCES})

# Линковка
target_link_libraries(sandbox
    sfml-graphics
    sfml-window
    sfml-system
)

# Копирование DLL
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-graphics-2.dll"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-window-2.dll"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-system-2.dll"
        $<TARGET_FILE_DIR:sandbox>
)

# Копирование шрифта
add_custom_command(TARGET sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/AnkhSanctuary-PVK0B.ttf"
        $<TARGET_FILE_DIR:sandbox>
)