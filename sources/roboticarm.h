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
    Mesh jointMesh;
    Mesh linkMesh;
    sf::Shader shader;

    std::unique_ptr<TransformNode> joint1Transform;
    std::unique_ptr<TransformNode> joint2Transform;
    std::unique_ptr<TransformNode> joint3Transform;

    std::unique_ptr<TransformNode> baseScale;

    std::unique_ptr<TransformNode> link1Scale;
    std::unique_ptr<TransformNode> link2Scale;
    std::unique_ptr<TransformNode> link3Scale;

    std::unique_ptr<TransformNode> joint2Scale;
    std::unique_ptr<TransformNode> joint3Scale;

    std::unique_ptr<MeshNode> cylinder;
    std::unique_ptr<MeshNode> joint;
};

#endif // ROBOTICARM_H
