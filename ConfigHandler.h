#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <string>
#include <SFML/System/Vector2.hpp> // Needed for sf::Vector2f

// 1. Define the Struct here so other files can see it
struct GameConfig {
    // Window
    int windowWidth = 1000;
    int windowHeight = 800;
    std::string windowTitle = "Pong (Default)";
    int frameRate = 60;
    std::string bgImagePath = "background.jpg";
    std::string fontPath = "font.ttf";

    // Paddles
    float paddleWidth = 20.f;
    float paddleHeight = 100.f;
    float paddleSpeed = 5.0f;
    
    sf::Vector2f leftPaddleStartPos = {50.f, -1.0f}; 
    sf::Vector2f rightPaddleStartPos = {930.f, -1.0f};

    // Ball
    float ballRadius = 10.f;
    sf::Vector2f ballSpeed = {4.f, 4.f};
};

// 2. Declare the function (Promise that it exists)
// We don't write the code here, just the signature.
GameConfig loadConfigFromToml(const std::string& filepath);

#endif