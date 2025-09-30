#include <iostream>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

int main(int argc, char* argv []){

    unsigned int wWidth = 1920;
    unsigned int wHeight = 1080;

    sf::Vector2u dim(wWidth, wHeight);
    sf::RenderWindow window(sf::VideoMode(dim), "SFML Works!");
    window.setFramerateLimit(60);

    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SFML" << std::endl;
        return -1;
    }

    sf::Clock deltaClock;

    ImGui::GetStyle().ScaleAllSizes(2.0f);
    ImGui::GetIO().FontGlobalScale = 2.0f;

    float c[3] = {0.0f, 1.0f, 1.0f};

    float circleRadius = 50;
    int circleSegments = 32;
    float circleSpeedX = 1.0f;
    float circleSpeedY = 0.5f;
    bool drawCircle = true;

    sf::CircleShape circle(circleRadius, circleSegments);
    sf::Vector2f position(10.0f, 10.0f);
    sf::Vector2f origin(0.0f, 0.0f);
    circle.setPosition(position);

    sf::Font myFont;

    if (!myFont.openFromFile("assets/arial.ttf")) {
        std::cerr << "Couldn't load the Font!\n";
        exit(-1);
    }

    sf::Text text(myFont, "Sample Text", 24);

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }
        
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Window Title");
        ImGui::Text("Window Text!");
        ImGui::Checkbox("Draw Cicle", &drawCircle);
        ImGui::SameLine();
        // ImGui::Checkbox("Draw Text", &drawText);
        ImGui::SliderFloat("Radius", &circleRadius, 0.0f, 300.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 64);
        ImGui::ColorEdit3("Color Circle", c);
        if (ImGui::Button("Reset Cicle")){
            circle.setPosition(origin);
        }
        ImGui::End();


        circle.setPointCount(circleSegments);
        circle.setRadius(circleRadius);
        circle.setFillColor(sf::Color(c[0]*255, c[1]*255, c[2]*255));
        sf::Vector2f newP(circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY);
        circle.setPosition(newP);

        window.clear();
        if (drawCircle){
            window.draw(circle);
        }
        ImGui::SFML::Render(window);
        window.display();
    }

    return 0;
    
}