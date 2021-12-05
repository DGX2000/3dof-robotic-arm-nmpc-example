#include "meshnode.h"

#include <SFML/Graphics/Glsl.hpp>

#include "mesh.h"

MeshNode::MeshNode(Mesh* mesh, sf::Shader* shader)
    : mesh(mesh), shader(shader)
{

}

void MeshNode::draw(const glm::mat4& worldToCamera, const glm::mat4& modelToWorld) const
{
    shader->setUniform("camera", sf::Glsl::Mat4(&worldToCamera[0][0]));
    shader->setUniform("model", sf::Glsl::Mat4(&modelToWorld[0][0]));
    mesh->draw(shader);
}

void MeshNode::transform(glm::mat4& transformation) const
{

}

bool MeshNode::isDrawable() const
{
    return true;
}
