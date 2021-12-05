#ifndef SPHERECAMERA_H
#define SPHERECAMERA_H

#include "camera.h"

class SphereCamera : public Camera
{
public:
    SphereCamera(float radius);

    void computeTransformationMatrix() const override;

    void moveLongitudinal(float amount);
    void moveLatitudinal(float amount);

private:
    float radius;
    float theta{0.0F};
    float phi{0.0F};
};

#endif // SPHERECAMERA_H
