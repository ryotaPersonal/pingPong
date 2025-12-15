#include <SFML/Graphics.hpp>

int main()
{
    // Create a window 800x600 pixels
    // "sf::Style::Close" means it has a close button but can't be resized
    sf::RenderWindow window(sf::VideoMode(1000, 800), "2 Player PingPong", sf::Style::Close);

    // Limit the game to 60 frames per second
    window.setFramerateLimit(60);

    sf::Vector2f paddleSize(20.f, 100.f);
    float paddleSpeed = 5.0f;

    sf::RectangleShape leftPaddle(paddleSize);
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(50.f, (800.f - paddleSize.y) / 2.f); 

    sf::RectangleShape rightPaddle(paddleSize);
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(930.f, (800.f - paddleSize.y) / 2.f);

    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::White);
    ball.setPosition((1000.f - ball.getRadius() * 2) / 2.f, (800.f - ball.getRadius() * 2) / 2.f);
    sf::Vector2f ballVelocity(4.f, 4.f); 

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0)
            leftPaddle.move(0.f, -paddleSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + paddleSize.y < 800.f)
            leftPaddle.move(0.f, paddleSpeed);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0)
            rightPaddle.move(0.f, -paddleSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + paddleSize.y < 800.f)
            rightPaddle.move(0.f, paddleSpeed);

        ball.move(ballVelocity);

        if (ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= 800.f)
            ballVelocity.y = -ballVelocity.y;
        
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
        {
            ballVelocity.x = -ballVelocity.x;
        }

        if (ball.getPosition().x < 0 || ball.getPosition().x > 1000.f)
        {
            ball.setPosition((1000.f - ball.getRadius() * 2) / 2.f, (800.f - ball.getRadius() * 2) / 2.f);
            ballVelocity.x = -ballVelocity.x;
        }

        // Clear the screen to black
        window.clear(sf::Color::Black);

        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        // (We will draw game objects here later)

        // Display the frame
        window.display();
    }

    return 0;
}