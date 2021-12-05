#ifndef CAMERA_H
#define CAMERA_H

#include <optional>

#include <glm/glm.hpp>

class Camera
{
public:
    struct Perspective
    {
        float fieldOfView{75.0F};
        float nearPlane{0.1F};
        float farPlane{100.0F};
        float aspectRatio{4.0F / 3.0F};
        // TODO: add orthogonal mode
    };

public:
    void capture(const class SceneNode* node) const;

    virtual void computeTransformationMatrix() const = 0;

    const Perspective& getPerspective() const;

    void setPerspective(const Perspective& perspective);

protected:
    mutable std::optional<glm::mat4> cachedTransformation;
    glm::mat4 perspectiveTransformation;

private:
    void recomputePerspectiveMatrix();

private:
    Perspective perspective;
};

#endif // CAMERA_H
