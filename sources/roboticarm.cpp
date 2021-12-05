#include "roboticarm.h"

#include <SFML/Graphics/Glsl.hpp>

RoboticArm::RoboticArm()
    : cube(Mesh::createSphere(16))
{
    shader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");
    shader.setUniform("lightPosition", sf::Glsl::Vec3(5.0F, 5.0F, 5.0F));

    joint1 = std::make_unique<TransformNode>();
    joint2 = std::make_unique<TransformNode>();
    joint3 = std::make_unique<TransformNode>();
    link1 = std::make_unique<MeshNode>(&cube, &shader);
    link2 = std::make_unique<MeshNode>(&cube, &shader);
    link3 = std::make_unique<MeshNode>(&cube, &shader);

    joint1->addNode(link1.get());
    joint1->addNode(joint2.get());
    joint2->addNode(link2.get());
    joint2->addNode(joint3.get());
    joint3->addNode(link3.get());

    joint2->move(glm::vec3(1.5F, 0.0F, 0.0F));
    joint2->rotate(glm::vec3(glm::radians(45.0F), 0.0F, 0.0F));
    joint3->move(glm::vec3(-0.5F, 0.0F, -1.5F));
    joint3->rotate(glm::vec3(glm::radians(45.0F), 0.0F, 0.0F));
}

const SceneNode *RoboticArm::getRootNode() const
{
    return joint1.get();
}
