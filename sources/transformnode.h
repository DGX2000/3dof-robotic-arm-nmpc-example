#ifndef TRANSFORMNODE_H
#define TRANSFORMNODE_H

#include "scenenode.h"

#include <optional>

#include <glm/glm.hpp>

class TransformNode : public SceneNode
{
public:
    TransformNode() = default;

    void setPosition(const glm::vec3& translation);
    void setRotation(const glm::vec3& rotation);
    void setScale(const glm::vec3& scaling);

protected:
    virtual void draw(const glm::mat4& camera, const glm::mat4& transformation) const;
    virtual void transform(glm::mat4& transformation) const;
    virtual bool isDrawable() const;

private:
    mutable std::optional<glm::mat4> cachedTransformation;

    glm::vec3 translation{0.0F, 0.0F, 0.0F};
    glm::vec3 rotation{0.0F, 0.0F, 0.0F};     // Euler angles
    glm::vec3 scaling{1.0F, 1.0F, 1.0F};
};

#endif // TRANSFORMNODE_H
