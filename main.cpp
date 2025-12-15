#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Include our new modular header!
#include "ConfigHandler.h" 

#define LOG(msg) std::cout << msg << std::endl

// (Keep the Game class here for now, but remove the struct definition from it)
class Game {
private:
    sf::RenderWindow mWindow;
    GameConfig mConfig; 

    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;
    
    sf::RectangleShape mLeftPaddle;
    sf::RectangleShape mRightPaddle;
    sf::CircleShape mBall;
    sf::Vector2f mBallVelocity;

    void processEvents() {
        sf::Event event;
        while (mWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) mWindow.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) mWindow.close();
        }
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (mLeftPaddle.getPosition().y > 0)
                mLeftPaddle.move(0.f, -mConfig.paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (mLeftPaddle.getPosition().y + mConfig.paddleHeight < mConfig.windowHeight)
                mLeftPaddle.move(0.f, mConfig.paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (mRightPaddle.getPosition().y > 0)
                mRightPaddle.move(0.f, -mConfig.paddleSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (mRightPaddle.getPosition().y + mConfig.paddleHeight < mConfig.windowHeight)
                mRightPaddle.move(0.f, mConfig.paddleSpeed);
        }
    }

    void update() {
        mBall.move(mBallVelocity);

        if (mBall.getPosition().y <= 0 || mBall.getPosition().y + mBall.getRadius() * 2 >= mConfig.windowHeight) {
            mBallVelocity.y = -mBallVelocity.y;
        }

        if (mBall.getGlobalBounds().intersects(mLeftPaddle.getGlobalBounds()) ||
            mBall.getGlobalBounds().intersects(mRightPaddle.getGlobalBounds())) {
            mBallVelocity.x = -mBallVelocity.x;
        }

        if (mBall.getPosition().x < 0 || mBall.getPosition().x > mConfig.windowWidth) {
            resetBall();
        }
    }

    void render() {
        mWindow.clear(sf::Color::Black);
        mWindow.draw(mBackgroundSprite);
        mWindow.draw(mLeftPaddle);
        mWindow.draw(mRightPaddle);
        mWindow.draw(mBall);
        mWindow.display();
    }

    void resetBall() {
        float centerX = (mConfig.windowWidth - mBall.getRadius() * 2) / 2.f;
        float centerY = (mConfig.windowHeight - mBall.getRadius() * 2) / 2.f;
        mBall.setPosition(centerX, centerY);
        mBallVelocity.x = -mBallVelocity.x; 
    }

public:
    Game(const GameConfig& config) 
        : mConfig(config), 
          mWindow(sf::VideoMode(config.windowWidth, config.windowHeight), config.windowTitle, sf::Style::Close) 
    {
        mWindow.setFramerateLimit(mConfig.frameRate);

        if (!mBackgroundTexture.loadFromFile(mConfig.bgImagePath)) {
            LOG("Warning: Failed to load background: " + mConfig.bgImagePath);
        } else {
            mBackgroundSprite.setTexture(mBackgroundTexture);
            float scaleX = static_cast<float>(mConfig.windowWidth) / mBackgroundTexture.getSize().x;
            float scaleY = static_cast<float>(mConfig.windowHeight) / mBackgroundTexture.getSize().y;
            mBackgroundSprite.setScale(scaleX, scaleY);
        }

        sf::Vector2f size(mConfig.paddleWidth, mConfig.paddleHeight);
        mLeftPaddle.setSize(size);
        mLeftPaddle.setFillColor(sf::Color::White);
        float leftY = (mConfig.leftPaddleStartPos.y == -1.f) ? (mConfig.windowHeight - size.y)/2.f : mConfig.leftPaddleStartPos.y;
        mLeftPaddle.setPosition(mConfig.leftPaddleStartPos.x, leftY);

        mRightPaddle.setSize(size);
        mRightPaddle.setFillColor(sf::Color::White);
        float rightY = (mConfig.rightPaddleStartPos.y == -1.f) ? (mConfig.windowHeight - size.y)/2.f : mConfig.rightPaddleStartPos.y;
        mRightPaddle.setPosition(mConfig.rightPaddleStartPos.x, rightY);

        mBall.setRadius(mConfig.ballRadius);
        mBall.setFillColor(sf::Color::White);
        mBallVelocity = mConfig.ballSpeed;
        resetBall();
    }

    void run() {
        while (mWindow.isOpen()) {
            processEvents();
            handleInput();
            update();
            render();
        }
    }
};

int main() {
    // 1. Call the function from ConfigHandler
    GameConfig mySettings = loadConfigFromToml("config.toml");

    // 2. Pass settings to Game
    Game game(mySettings);
    game.run();

    return 0;
}