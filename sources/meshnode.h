#ifndef MESHNODE_H
#define MESHNODE_H

#include "scenenode.h"

#include <SFML/Graphics/Shader.hpp>

class MeshNode : public SceneNode
{
public:
    MeshNode(class Mesh* mesh, sf::Shader* shader);

protected:
    virtual void draw(const glm::mat4& transformation) const;
    virtual void transform(glm::mat4& initialTransformation) const;
    virtual bool isDrawable() const;

private:
    class Mesh* mesh;
    sf::Shader* shader;
};

#endif // MESHNODE_H
