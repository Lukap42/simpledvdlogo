#include <iostream>
#include <fmt/core.h>
#include <SFML/Graphics.hpp>
#include <cmath>

int main() {

    const auto windowWidth = 800;
    const auto windowHeight = 600;

    const auto objectWidth = 50.0f;
    const auto objectHeight = 50.0f;

    auto window = sf::RenderWindow(sf::VideoMode(windowWidth,windowHeight),"Title");
    auto rectangle = sf::RectangleShape(sf::Vector2f(objectWidth,objectHeight));

//    sf::Texture texture = sf::Texture();
//    if(!texture.loadFromFile("image.png")) fmt::println("image error");
    rectangle.setFillColor(sf::Color::Blue);
    window.setFramerateLimit(144);

    sf::Font font = sf::Font();
    font.loadFromFile("calibri.ttf");
    auto fpsCounter = sf::Text("0",font,30);
//    const auto t1 = &texture;
//    rectangle.setTexture(t1);
    rectangle.setPosition(windowWidth/2,windowHeight/2);

    auto collision = [](const auto& shape,auto& velocity,auto& time) {
        auto currPos = shape.getPosition();
        auto dx = velocity.x * time;
        auto dy = velocity.y * time;
        if(currPos.x + shape.getSize().x + velocity.x * time > windowWidth or currPos.x + velocity.x * time < 0) velocity.x*=-1.0f;
        if(currPos.y + shape.getSize().y + velocity.y * time > windowHeight or currPos.y + velocity.y * time < 0) velocity.y*=-1.0f;
    };

    auto time = sf::Clock();

    auto timeElapsed = 0.0f;
    int numFrames = 0;

    auto velocity = sf::Vector2f(100.0f,100.0f);

    auto fpsMeasurements = 1;
    auto fpsSum=0.0f;
    auto fpsAvr = 0.0f;

    while(window.isOpen()){
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::MouseButtonPressed){

                auto x = event.mouseButton.x;
                auto y = event.mouseButton.y;

                fmt::println("{},{}",x,y);
                if((x > rectangle.getPosition().x and x < rectangle.getPosition().x+objectWidth) and (y > rectangle.getPosition().y and y < rectangle.getPosition().y + objectHeight)){
                    auto num = rand()%3;
                    switch(num){
                        case 0: rectangle.setFillColor(sf::Color::Red); break;
                        case 1: rectangle.setFillColor(sf::Color::Yellow); break;
                        default: rectangle.setFillColor(sf::Color::Blue); break;
                    }
                }

            }
        }

        auto dt = static_cast<float>(time.getElapsedTime().asMicroseconds())/1000000.0f;
        timeElapsed+=dt;

//        auto fps = 1.0f/dt;

//        fpsMeasurements++;
//        fpsSum+=fps;
//
//        if(fpsMeasurements >= 60){
//            fpsAvr=fpsSum/static_cast<float>(fpsMeasurements);
//            fpsMeasurements = 0;
//            fpsSum = 0.0f;
//        }
        if(timeElapsed>=1.0f){
            auto fps = numFrames;
            numFrames=0;
            timeElapsed-=floorf(timeElapsed);
            fpsCounter.setString(std::to_string(fps)+" FPS");
        }


        time.restart();

        collision(rectangle,velocity, dt);
        rectangle.setPosition(rectangle.getPosition()+velocity*dt);
        //fmt::println("{},{},{},{}",rectangle.getPosition().x, rectangle.getPosition().y,velocity.x*dt,velocity.y*dt);
        //std::cout<<dt<<std::endl;

        window.clear();
        window.draw(rectangle);
        window.draw(fpsCounter);
        window.display();

        numFrames++;

    }
}
