#include "roboticarm.h"

#include <SFML/Graphics/Glsl.hpp>

RoboticArm::RoboticArm()
    : jointMesh(Mesh::createSphere(16)), linkMesh(Mesh::createCylinder(16))
{
    shader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");
    shader.setUniform("lightPosition", sf::Glsl::Vec3(5.0F, 5.0F, -5.0F));

    // TODO: Different shader for the spheres as joints (gray)

    joint1Transform = std::make_unique<TransformNode>();
    joint2Transform = std::make_unique<TransformNode>();
    joint3Transform = std::make_unique<TransformNode>();

    baseScale = std::make_unique<TransformNode>();
    link1Scale = std::make_unique<TransformNode>();
    link2Scale = std::make_unique<TransformNode>();
    link3Scale = std::make_unique<TransformNode>();

    joint2Scale = std::make_unique<TransformNode>();
    joint3Scale = std::make_unique<TransformNode>();

    cylinder = std::make_unique<MeshNode>(&linkMesh, &shader);
    joint = std::make_unique<MeshNode>(&jointMesh, &shader);



    // setting up the tree structure for the transformations
    joint1Transform->addNode(baseScale.get());
    joint1Transform->addNode(link1Scale.get());
    joint1Transform->addNode(joint2Transform.get());

    joint2Transform->addNode(link2Scale.get());
    joint2Transform->addNode(joint2Scale.get());
    joint2Transform->addNode(joint3Transform.get());

    joint3Transform->addNode(link3Scale.get());
    joint3Transform->addNode(joint3Scale.get());

    // add in meshes at appropriate locations
    baseScale->addNode(cylinder.get());
    link1Scale->addNode(cylinder.get());

    joint2Scale->addNode(joint.get());
    link2Scale->addNode(cylinder.get());

    joint3Scale->addNode(joint.get());
    link3Scale->addNode(cylinder.get());



    // setting up the relative displacements and scales of the robot arm
    // (rotation of joints can be set via function)
    // TODO: make this parametric, add missing sphere/cylinder at joint 3
    auto link1HalfLength = 1.25F;

    baseScale->scale(glm::vec3(1.0F, 0.5F, 1.0F));

    link1Scale->scale(glm::vec3(0.25F, 2.0F, 0.25F));
    link1Scale->move(glm::vec3(0.0F, 0.25F, 0.0F));
    link1Scale->rotate(glm::vec3(0.0F, 0.0F, glm::radians(90.0F)));

    joint2Transform->move(glm::vec3(link1HalfLength, 0.25F, 0.0F));
    joint2Scale->scale(glm::vec3(0.35F, 0.35F, 0.35F));

    link2Scale->scale(glm::vec3(0.25F, 2.0F, 0.25F));
    link2Scale->move(glm::vec3(0.0F, 0.0F, -1.0F));
    link2Scale->rotate(glm::vec3(glm::radians(90.0F), 0.0F, 0.0F));

    joint3Transform->move(glm::vec3(-0.75F, 0.0F, -2.0F));
    joint3Scale->scale(glm::vec3(0.35F, 0.35F, 0.35F));

    link3Scale->scale(glm::vec3(0.25F, 2.0F, 0.25F));
    link3Scale->rotate(glm::vec3(glm::radians(90.0F), 0.0F, 0.0F));
    link3Scale->move(glm::vec3(0.0F, 0.0F, -1.0F));



    joint2Transform->rotate(glm::vec3(glm::radians(45.0F), 0.0F, 0.0F));
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
