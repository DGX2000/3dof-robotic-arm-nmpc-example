#include <fstream>
#include <iostream>
#include <sstream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include "mesh.h"
#include "transformnode.h"
#include "meshnode.h"

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



    // Mesh and Shader
    sf::Shader sfShader;
    sfShader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");
    auto cube = Mesh::createCube();

    TransformNode sceneRoot;
    MeshNode testCube(&cube, &sfShader);
    sceneRoot.addNode(&testCube);


    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraTarget = glm::vec3();
    double cameraTheta = 0.0;

    auto perspective = glm::perspective(glm::radians(75.0F),
                                        static_cast<float>(screenWidth)/
                                        static_cast<float>(screenHeight),
                                        0.1F, 100.0F);

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
                perspective = glm::perspective(glm::radians(75.0F),
                                               static_cast<float>(screenWidth)/static_cast<float>(screenHeight),
                                               0.1F, 100.0F);
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::A)
                {
                    cameraTheta += 0.05;
                }
            }
        }

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        auto cameraPosition = glm::vec3(3.0*glm::cos(cameraTheta), 0.0, 3.0*glm::sin(cameraTheta));
        auto transform = perspective * glm::lookAt(cameraPosition, cameraTarget, cameraUp);

        sceneRoot.rotate(glm::vec3(0.001F, -0.002F, 0.004F));
        sceneRoot.traverse(transform);

        window.display();
    }

    return 0;
}
