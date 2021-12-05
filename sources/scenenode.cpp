#include "scenenode.h"

#include <algorithm>

void SceneNode::traverse(const glm::mat4& camera, glm::mat4 transformation) const
{
    if(isDrawable())
    {
        draw(camera, transformation);
    }
    else
    {
        transform(transformation);
    }

    for(const auto& child : children)
    {
        child->traverse(camera, transformation);
    }
}

void SceneNode::addNode(SceneNode *node)
{
    if(node != this)
    {
        children.emplace_back(node);
    }
}

void SceneNode::removeNode(SceneNode *node)
{
    auto soughtNode = std::find(children.begin(), children.end(), node);
    if(soughtNode != children.end())
    {
        children.erase(soughtNode);
    }
}
