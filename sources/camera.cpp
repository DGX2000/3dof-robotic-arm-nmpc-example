#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "scenenode.h"

void Camera::capture(const SceneNode *node) const
{
    if(!cachedTransformation.has_value())
    {
        computeTransformationMatrix();
    }

    auto identity = glm::mat4(1.0F);
    node->traverse(cachedTransformation.value(), identity);
}

const Camera::Perspective &Camera::getPerspective() const
{
    return this->perspective;
}

void Camera::setPerspective(const Perspective &perspective)
{
    this->perspective = perspective;
    recomputePerspectiveMatrix();
}

void Camera::recomputePerspectiveMatrix()
{
    perspectiveTransformation = glm::perspective(glm::radians(perspective.fieldOfView),
                                                 perspective.aspectRatio,
                                                 perspective.nearPlane,
                                                 perspective.farPlane);
}
