#ifndef TARGET_H
#define TARGET_H

#include <memory>

#include <glm/glm.hpp>

#include <SFML/Graphics/Shader.hpp>

#include "mesh.h"
#include "meshnode.h"
#include "transformnode.h"

class Target
{
public:
    Target();

    SceneNode* getRootNode() const;

    void move(const glm::vec3& position);

    void setValid();
    void setInvalid();

private:
    Mesh mesh;
    sf::Shader shader;
    glm::vec3 position{0.0F, 0.0F, -1.5F};

    std::unique_ptr<TransformNode> transformNode;
    std::unique_ptr<MeshNode> meshNode;
};

#endif // TARGET_H
