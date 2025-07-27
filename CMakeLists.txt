cmake_minimum_required(VERSION 3.15)
project(SandboxGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # Все выходные файлы в bin

include_directories(include)

# Настройки SFML
set(SFML_PATH "C:/libraries/SFML-2.6.2")
include_directories(${SFML_PATH}/include)
link_directories(${SFML_PATH}/lib)

file(GLOB SOURCES "src/*.cpp")
add_executable(sandbox ${SOURCES})

target_link_libraries(sandbox
    sfml-graphics sfml-window sfml-system sfml-audio
)

# Копирование DLL и ресурсов в bin
add_custom_command(TARGET sandbox POST_BUILD
    # Копирование DLL из SFML
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-graphics-2.dll"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-window-2.dll"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/sfml-system-2.dll"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy  
        "${SFML_PATH}/bin/sfml-audio-2.dll"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy
        "${SFML_PATH}/bin/openal32.dll"
        $<TARGET_FILE_DIR:sandbox>
    
    # Копирование ресурсов из папки bin проекта
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/bin/3d20874f20174bd.mp3"
        $<TARGET_FILE_DIR:sandbox>
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/bin/AnkhSanctuary-PVK0B.ttf"
        $<TARGET_FILE_DIR:sandbox>
)