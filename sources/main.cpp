#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "mesh.h"
#include "transformnode.h"
#include "meshnode.h"
#include "roboticarm.h"
#include "camera.h"
#include "spherecamera.h"

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;

    sf::Window window(sf::VideoMode(screenWidth, screenHeight), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    glewInit();
    glEnable(GL_DEPTH_TEST);

    // Class for robot arm
    RoboticArm roboticArm;
    SphereCamera sphereCam(3.0F);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if(event.type == sf::Event::Resized)
            {
                screenWidth = event.size.width;
                screenHeight = event.size.height;

                glViewport(0, 0, screenWidth, screenHeight);

                Camera::Perspective perspective;
                perspective.aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
                sphereCam.setPerspective(perspective);
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::A:
                    sphereCam.moveLongitudinal(0.05F);
                    break;
                case sf::Keyboard::D:
                    sphereCam.moveLongitudinal(-0.05F);
                    break;
                default:
                    break;
                }
            }
        }

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        sphereCam.capture(roboticArm.getRootNode());

        window.display();
    }

    return 0;
}
