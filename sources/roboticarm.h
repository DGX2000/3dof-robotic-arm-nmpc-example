#ifndef ROBOTICARM_H
#define ROBOTICARM_H

#include <memory>

#include <SFML/Graphics/Shader.hpp>

#include "transformnode.h"
#include "mesh.h"
#include "meshnode.h"

class RoboticArm
{
public:
    RoboticArm();

    const SceneNode* getRootNode() const;

private:
    Mesh cube;
    sf::Shader shader;

    std::unique_ptr<TransformNode> joint1;
    std::unique_ptr<TransformNode> joint2;
    std::unique_ptr<TransformNode> joint3;

    std::unique_ptr<MeshNode> link1;
    std::unique_ptr<MeshNode> link2;
    std::unique_ptr<MeshNode> link3;
};

#endif // ROBOTICARM_H
