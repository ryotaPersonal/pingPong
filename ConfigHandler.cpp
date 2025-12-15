#include "ConfigHandler.h"
#include "toml.hpp"        
#include <iostream>

#define LOG(msg) std::cout << msg << std::endl

// Implement the function we promised in the header
GameConfig loadConfigFromToml(const std::string& filepath) {
    GameConfig config; // Start with defaults
    
    try {
        toml::table tbl = toml::parse_file(filepath);

        // Window
        config.windowWidth = tbl["window"]["width"].value_or(1000);
        config.windowHeight = tbl["window"]["height"].value_or(800);
        config.windowTitle = tbl["window"]["title"].value_or("Pong Game");
        config.frameRate = tbl["window"]["framerate"].value_or(60);
        config.bgImagePath = tbl["window"]["background_image"].value_or("background.jpg");

        // Paddles
        config.paddleWidth = tbl["paddles"]["width"].value_or(20.0f);
        config.paddleHeight = tbl["paddles"]["height"].value_or(100.0f);
        config.paddleSpeed = tbl["paddles"]["speed"].value_or(5.0f);
        
        config.leftPaddleStartPos.x = tbl["paddles"]["left_start_x"].value_or(50.0f);
        config.leftPaddleStartPos.y = tbl["paddles"]["left_start_y"].value_or(-1.0f);
        
        config.rightPaddleStartPos.x = tbl["paddles"]["right_start_x"].value_or(930.0f);
        config.rightPaddleStartPos.y = tbl["paddles"]["right_start_y"].value_or(-1.0f);

        // Ball
        config.ballRadius = tbl["ball"]["radius"].value_or(10.0f);
        float bx = tbl["ball"]["speed_x"].value_or(4.0f);
        float by = tbl["ball"]["speed_y"].value_or(4.0f);
        config.ballSpeed = {bx, by};

        LOG("[CONFIG HANDLER] Loaded config.toml!");

    } catch (const toml::parse_error& err) {
        LOG("[CONFIG HANDLER] Warning: Failed to parse config.toml. Using defaults.");
        LOG("Error: " << err);
    } catch (...) {
        LOG("[CONFIG HANDLER] Unknown error loading config file.");
    }

    return config;
}