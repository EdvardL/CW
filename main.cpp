#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Network.hpp>

#include <PointToSphere.h>
#include <widget.h>

#include <thread>
#include <vector>
#include <string>

PointToSphere pts1;

float angle1 = 0;

void display(ImVec2 size)
{
    ImGui::Begin("Example1");
    ImGui::Button("Button1");
    ImGui::VisualizationOfPoints("Example1", pts1, {200, 200}, {0,0,0, 1}, {0.5, 0.5, 0.5, 1}, {1,1,1,1}, false, angle1);
    ImGui::SliderFloat("Angle1", &angle1, -180, 180);
    ImGui::End();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Points");
    window.setFramerateLimit(60);

    pts1.loadFromFile("./example.csv");

    if(ImGui::SFML::Init(window))
    {
        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(window, event);
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            ImGui::SFML::Update(window, deltaClock.restart());

            display({(float)window.getSize().x, (float)window.getSize().y});
            

            window.clear();
            ImGui::SFML::Render(window);
            window.display();
        }
        ImGui::SFML::Shutdown();
    }
    return 0;
}
