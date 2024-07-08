#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <random>

class PongBall
{
    sf::RenderWindow& window;
    float x, y, radius, velx, vely;

    void Init()
    {
        x = window.getSize().x / 2;
        y = window.getSize().y / 2;
        radius = 10.0f; // ten pixels

        // give the ball a random velocity
        std::random_device rd;
        std::uniform_real_distribution<float> dist(-600.0f, 600.0f);
        velx = dist(rd);
        vely = dist(rd);
    }   

    //if the ball is outside of the window boundry, bounce off in the opposite direction.
    void BoundryCheck() {
        if (x <= 0 || x >= window.getSize().x - (radius*2)) {
            velx = -velx;
        }
        if (y <= 0 || y >= window.getSize().y - (radius * 2)) {
            vely = -vely;
        }
    }

public:
    PongBall(sf::RenderWindow& window) : window(window)
    {
        Init();
    }
    //------------------------------------------------------
    float getRadius() { 
        return radius; 
    }
    
    sf::Vector2f getPos() {
        return sf::Vector2f(x,y);
    }

    sf::Vector2f getVel() {
        return sf::Vector2f(velx, vely);
    }

    void setRadius(float newRadius) {
        if (newRadius > 0.0f) {
            radius = newRadius;
        }
    }

    void setPosition(sf::Vector2f newPos) {
        x = newPos.x;
        y = newPos.y;
    }

    void setVel(sf::Vector2f newSpeed) {
        velx = newSpeed.x;
        vely = newSpeed.y;
    }


    //------------------------------------------------------
    void update(float deltaTime)
    {   
        x += velx * deltaTime;
        y += vely * deltaTime;
        BoundryCheck();
    }
    void draw()
    {
        sf::CircleShape circle;
        circle.setFillColor(sf::Color(255, 255, 255));
        circle.setPosition(sf::Vector2f(x, y));
        circle.setRadius(radius);
        window.draw(circle);
    }
};
//----------------------------------------------------------------------------------------------------------------
class PongBat
{
    sf::RenderWindow& window;
    float x, y, w, h;
public:
    PongBat(sf::RenderWindow& window) : window(window)
    {
        w = 15.0f;
        h = 60.0f;
        x = 40.0f;
        y = window.getSize().y / 2.0f + h / 2.0f;
    }
    //------------------------------------------------------
    sf::Vector2f getSize() {
        return sf::Vector2f(w, h);
    }

    sf::Vector2f getPos() {
        return sf::Vector2f(x, y);
    }

    void setPos(sf::Vector2f newSize) {
        w = newSize.x;
        h = newSize.y;
    }

    void setPos(sf::Vector2f newPos) {
        x = newPos.x;
        y = newPos.y;
    }

    //------------------------------------------------------
    void update(float deltaTime)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (y  > 0 ))
            y -= 300.0f * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (y + (h) < window.getSize().y))
            y += 300.0f * deltaTime;
    }
    void draw()
    {
        //Ancor is located in the top left corner of the bat
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color(255, 255, 255));
        rect.setPosition(sf::Vector2f(x, y));
        rect.setSize(sf::Vector2f(w, h));
        window.draw(rect);

    }
};
//----------------------------------------------------------------------------------------------------------------
bool BallRectangleOverlap(PongBall& ball, const sf::Vector2f& rectPos, const sf::Vector2f& rectSize)
{
    // test for overlap
    sf::Vector2f ballPos = ball.getPos();
    float ballRadius = ball.getRadius();

    // treat the ball as a square for this
    float x0ball, x1ball, y0ball, y1ball;
    float x0rect, x1rect, y0rect, y1rect;
    x0ball = ballPos.x - ballRadius;
    x1ball = ballPos.x + ballRadius;
    y0ball = ballPos.y - ballRadius;
    y1ball = ballPos.y + ballRadius;
    x0rect = rectPos.x;
    x1rect = rectPos.x + rectSize.x;
    y0rect = rectPos.y;
    y1rect = rectPos.y + rectSize.y;

    return !(y0ball > y1rect || x0ball > x1rect || x1ball < x0rect || y1ball < y0rect);
}

void Collision(PongBall& ball, PongBat& bat)
{
    // test for overlap
    if (BallRectangleOverlap(ball, bat.getPos(), bat.getSize()))
    {
        // collision
        sf::Vector2f ballVel = ball.getVel();
        if (ballVel.x < 0.0f)
            ball.setVel(sf::Vector2f(-ballVel.x, ballVel.y));
    }
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Program");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    PongBall ball = PongBall(window);
    PongBat bat = PongBat(window);
    
   

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        ball.update(1.0f / 60.0f);
        ball.draw();

        bat.update(1.0f / 60.0f);
        bat.draw();

        Collision(ball, bat);


        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}

// Load a sprite to display
    //sf::Texture texture;
    //if (!texture.loadFromFile("assets/Cat_Down.png"))
    //    return EXIT_FAILURE;
    //sf::Sprite sprite(texture);

    //// Create a graphical text to display
    //sf::Font font;
    //if (!font.loadFromFile("assets/Arista20AlternateRegular-jy89.ttf"))
    //    return EXIT_FAILURE;
    //sf::Text text("Hello SFML", font, 50);

// within game loop:

//        // Draw the sprite
//window.draw(sprite);
//
//// Draw the string
//window.draw(text);