#include "target.h"

Target::Target()
    : mesh(Mesh::createSphere(16))
{
    shader.loadFromFile("vertex_shader.glslv", "fragment_shader.glslf");
    shader.setUniform("color", sf::Glsl::Vec4(1.0F, 0.0F, 0.0F, 1.0F));
    shader.setUniform("lightPosition", sf::Glsl::Vec3(-5.0F, 5.0F, -5.0F));
    shader.setUniform("diffuseStrength", 0.0F);

    transformNode = std::make_unique<TransformNode>();
    meshNode = std::make_unique<MeshNode>(&mesh, &shader);

    transformNode->addNode(meshNode.get());

    transformNode->setScale(glm::vec3(0.25F, 0.25F, 0.25F));
    transformNode->setPosition(this->position);
}

SceneNode *Target::getRootNode() const
{
    return transformNode.get();
}

void Target::move(const glm::vec3 &position)
{
    this->position += position;
    transformNode->setPosition(this->position);
}

void Target::setValid()
{
    shader.setUniform("color", sf::Glsl::Vec4(0.0F, 1.0F, 0.0F, 1.0F));
}

void Target::setInvalid()
{
    shader.setUniform("color", sf::Glsl::Vec4(1.0F, 0.0F, 0.0F, 1.0F));
}
