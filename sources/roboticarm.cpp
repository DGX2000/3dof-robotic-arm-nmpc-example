#include "roboticarm.h"

#include <SFML/Graphics/Glsl.hpp>

RoboticArm::RoboticArm()
    : jointMesh(Mesh::createCylinder(16)), linkMesh(Mesh::createCylinder(16))
{
    linkShader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");
    linkShader.setUniform("color", sf::Glsl::Vec4(0.8F, 0.6F, 0.1F, 1.0F));
    linkShader.setUniform("lightPosition", sf::Glsl::Vec3(-5.0F, 5.0F, -5.0F));
    linkShader.setUniform("diffuseStrength", 0.3F);

    jointShader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");
    jointShader.setUniform("lightPosition", sf::Glsl::Vec3(-5.0F, 5.0F, -5.0F));
    jointShader.setUniform("color", sf::Glsl::Vec4(0.25F, 0.25F, 0.25F, 1.0F));
    jointShader.setUniform("diffuseStrength", 0.1F);

    joint1Transform = std::make_unique<TransformNode>();
    joint2Transform = std::make_unique<TransformNode>();
    joint3Transform = std::make_unique<TransformNode>();

    baseScale = std::make_unique<TransformNode>();
    link1Scale = std::make_unique<TransformNode>();
    link2Scale = std::make_unique<TransformNode>();
    crossbar = std::make_unique<TransformNode>();
    link3Scale = std::make_unique<TransformNode>();

    joint2VisualRotation = std::make_unique<TransformNode>();
    joint3VisualRotation = std::make_unique<TransformNode>();

    link = std::make_unique<MeshNode>(&linkMesh, &linkShader);
    joint = std::make_unique<MeshNode>(&jointMesh, &jointShader);


    // setting up the tree structure for the transformations
    joint1Transform->addNode(baseScale.get());
    joint1Transform->addNode(link1Scale.get());
    joint1Transform->addNode(joint2Transform.get());

    joint2Transform->addNode(link2Scale.get());
    joint2Transform->addNode(joint2VisualRotation.get());
    joint2Transform->addNode(joint3Transform.get());
    joint2Transform->addNode(crossbar.get());

    joint3Transform->addNode(link3Scale.get());
    joint3Transform->addNode(joint3VisualRotation.get());

    // add in meshes at appropriate locations
    baseScale->addNode(joint.get());
    link1Scale->addNode(link.get());

    joint2VisualRotation->addNode(joint.get());
    link2Scale->addNode(link.get());
    crossbar->addNode(link.get());

    joint3VisualRotation->addNode(joint.get());
    link3Scale->addNode(link.get());



    // setting up the relative displacements and scales of the robot arm
    // (rotation of joints can be set via function)
    // TODO: make this parametric, add missing sphere/cylinder at joint 3
    auto link1HalfLength = 1.25F;

    baseScale->setScale(glm::vec3(1.0F, 0.5F, 1.0F));

    link1Scale->setScale(glm::vec3(0.25F, 2.0F, 0.25F));
    link1Scale->setPosition(glm::vec3(0.0F, 0.25F, 0.0F));
    link1Scale->setRotation(glm::vec3(0.0F, 0.0F, glm::radians(90.0F)));

    joint2Transform->setPosition(glm::vec3(link1HalfLength, 0.25F, 0.0F));
    joint2VisualRotation->setScale(glm::vec3(0.3F, 0.5F, 0.3F));
    joint2VisualRotation->setRotation(glm::vec3(glm::radians(90.0F), 0.0F, 0.0F));

    link2Scale->setScale(glm::vec3(0.2F, 2.0F, 0.2F));
    link2Scale->setPosition(glm::vec3(0.0F, 0.0F, -1.0F));
    link2Scale->setRotation(glm::vec3(glm::radians(90.0F), 0.0F, 0.0F));

    crossbar->setScale(glm::vec3(0.15F, 0.8F, 0.15F));
    crossbar->setPosition(glm::vec3(-0.15F, 0.0F, -2.0F));
    crossbar->setRotation(glm::vec3(0.0F, 0.0F, glm::radians(90.0F)));

    joint3Transform->setPosition(glm::vec3(-0.75F, 0.0F, -2.0F));
    joint3VisualRotation->setScale(glm::vec3(0.3F, 0.3F, 0.3F));
    joint3VisualRotation->setRotation(glm::vec3(glm::radians(90.0F), 0.0F, 0.0F));

    link3Scale->setScale(glm::vec3(0.15F, 2.0F, 0.15F));
    link3Scale->setRotation(glm::vec3(glm::radians(90.0F), 0.0F, 0.0F));
    link3Scale->setPosition(glm::vec3(0.0F, 0.0F, -1.0F));



    joint2Transform->setRotation(glm::vec3(glm::radians(45.0F), 0.0F, 0.0F));
    // TODO: Add the rotations to its own function, where you can set the rotation dynamically
//    joint2->move(glm::vec3(1.5F, 0.0F, 0.0F));
//    joint2->rotate(glm::vec3(glm::radians(45.0F), 0.0F, 0.0F));
//    joint3->move(glm::vec3(-0.5F, 0.0F, -1.5F));
//    joint3->rotate(glm::vec3(glm::radians(45.0F), 0.0F, 0.0F));
}

const SceneNode *RoboticArm::getRootNode() const
{
    return joint1Transform.get();
}
