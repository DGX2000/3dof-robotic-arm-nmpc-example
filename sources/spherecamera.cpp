#include "spherecamera.h"

#include <glm/gtc/matrix_transform.hpp>

SphereCamera::SphereCamera(float radius)
    : radius(radius)
{

}

void SphereCamera::computeTransformationMatrix() const
{
    auto cameraPosition = glm::vec3(radius*glm::cos(phi), 0.0, radius*glm::sin(phi));
    glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraTarget = glm::vec3();

    cachedTransformation = perspectiveTransformation * glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void SphereCamera::moveLongitudinal(float amount)
{
    phi += amount;
    cachedTransformation.reset();
}

void SphereCamera::moveLatitudinal(float amount)
{
    theta += amount;
    cachedTransformation.reset();
}
