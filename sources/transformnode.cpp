#include "transformnode.h"

#include <glm/gtc/matrix_transform.hpp>

void TransformNode::move(const glm::vec3 &translation)
{
    this->translation += translation;
    cachedTransformation.reset();
}

void TransformNode::rotate(const glm::vec3 &rotation)
{
    this->rotation += rotation;
    cachedTransformation.reset();
}

void TransformNode::scale(const glm::vec3 &scaling)
{
    this->scaling *= scaling;
    cachedTransformation.reset();
}

void TransformNode::draw(const glm::mat4& camera, const glm::mat4 &transformation) const {}

void TransformNode::transform(glm::mat4 &transformation) const
{
    if(!cachedTransformation.has_value())
    {
        auto uncachedTransformation = glm::mat4(1.0F);

        uncachedTransformation = glm::scale(uncachedTransformation, scaling);
        uncachedTransformation = glm::translate(uncachedTransformation, translation);
        uncachedTransformation = glm::rotate(uncachedTransformation, rotation.x, glm::vec3(1.0, 0.0, 0.0));
        uncachedTransformation = glm::rotate(uncachedTransformation, rotation.y, glm::vec3(0.0, 1.0, 0.0));
        uncachedTransformation = glm::rotate(uncachedTransformation, rotation.z, glm::vec3(0.0, 0.0, 1.0));

        cachedTransformation = uncachedTransformation;
    }

    transformation *= cachedTransformation.value();
}

bool TransformNode::isDrawable() const
{
    return false;
}
