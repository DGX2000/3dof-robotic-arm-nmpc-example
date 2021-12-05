#ifndef SPHERECAMERA_H
#define SPHERECAMERA_H

#include "camera.h"

class SphereCamera : public Camera
{
public:
    SphereCamera(glm::vec3 center, float radius);

    void computeTransformationMatrix() const override;

    void moveLongitudinal(float amount);
    void moveLatitudinal(float amount);

private:
    glm::vec3 center;

    float radius;
    float theta{0.5F*3.1415F};
    float phi{0.0F};
};

#endif // SPHERECAMERA_H
