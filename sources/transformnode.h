#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "scenenode.h"

#include <optional>

#include <glm/glm.hpp>

class TransformNode : public SceneNode
{
public:
    TransformNode() = default;

    void move(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void scale(const glm::vec3& scaling);

protected:
    virtual void draw(const glm::mat4& transformation) const;
    virtual void transform(glm::mat4& transformation) const;
    virtual bool isDrawable() const;

private:
    mutable std::optional<glm::mat4> cachedTransformation;

    glm::vec3 translation{0.0F, 0.0F, 0.0F};
    glm::vec3 rotation{0.0F, 0.0F, 0.0F};     // Euler angles
    glm::vec3 scaling{1.0F, 1.0F, 1.0F};
};

#endif // TRANSFORMNODE_H
