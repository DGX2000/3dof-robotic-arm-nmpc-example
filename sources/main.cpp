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

int main()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    glewInit();

    auto cube = Mesh::createCube();

    // SFML Shader
    sf::Shader sfShader;
    sfShader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");

    glm::mat4 trans = glm::mat4(1.0F);

    trans = glm::translate(trans, glm::vec3(0.0, -0.5, 0.0));
    trans = glm::rotate(trans, glm::radians(45.0F), glm::vec3(1.0, 1.0, 1.0));

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
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        sfShader.setUniform("transform", sf::Glsl::Mat4(&trans[0][0]));
        sf::Shader::bind(&sfShader);

        cube.draw(sfShader);

        window.display();
    }

    return 0;
}
