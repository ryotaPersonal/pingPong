#include <SFML/Graphics.hpp>

int main()
{
    // Create a window 800x600 pixels
    // "sf::Style::Close" means it has a close button but can't be resized
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "2 Player PingPong", sf::Style::Close);

    // Limit the game to 60 frames per second
    window.setFramerateLimit(60);

    sf::Vector2f paddleSize(20.f, 100.f);
    float paddleSpeed = 5.0f;

    sf::RectangleShape leftPaddle(paddleSize);
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(50.f, (1200.f - paddleSize.y) / 2.f); 

    sf::RectangleShape rightPaddle(paddleSize);
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(1530.f, (1200.f - paddleSize.y) / 2.f);

    // The Game Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the window if the 'X' button is pressed
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Also close if Escape is pressed
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (leftPaddle.getPosition().y > 0)
                leftPaddle.move(0.f, -paddleSpeed);
        }
            
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (leftPaddle.getPosition().y + paddleSize.y < 1200.f)
                leftPaddle.move(0.f, paddleSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (rightPaddle.getPosition().y > 0)
                rightPaddle.move(0.f, -paddleSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (rightPaddle.getPosition().y + paddleSize.y < 1200.f)
                rightPaddle.move(0.f, paddleSpeed);
        }

        // Clear the screen to black
        window.clear(sf::Color::Black);

        window.draw(leftPaddle);
        window.draw(rightPaddle);

        // (We will draw game objects here later)

        // Display the frame
        window.display();
    }

    return 0;
}