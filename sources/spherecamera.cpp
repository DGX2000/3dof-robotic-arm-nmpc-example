#include "spherecamera.h"

#include <glm/gtc/matrix_transform.hpp>

SphereCamera::SphereCamera(glm::vec3 center, float radius)
    : center(center), radius(radius)
{

}

void SphereCamera::computeTransformationMatrix() const
{
    auto cameraPosition = glm::vec3(radius*glm::sin(phi)*glm::sin(theta),
                                    radius*glm::cos(theta),
                                    radius*glm::cos(phi)*glm::sin(theta));

    glm::vec3 cameraUp = glm::vec3(-glm::cos(theta)*glm::sin(phi),
                                   glm::sin(theta),
                                   -glm::cos(theta)*glm::cos(phi));

    cachedTransformation = perspectiveTransformation * glm::lookAt(center + cameraPosition, center, cameraUp);
}

void SphereCamera::moveLongitudinal(float amount)
{
    phi += amount;
    cachedTransformation.reset();
}

void SphereCamera::moveLatitudinal(float amount)
{
    theta += amount;
    theta = glm::clamp(theta, 0.0F, glm::pi<float>());
    cachedTransformation.reset();
}
