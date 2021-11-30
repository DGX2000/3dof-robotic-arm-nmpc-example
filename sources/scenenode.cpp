#include "scenenode.h"

#include <algorithm>

void SceneNode::traverse(glm::mat4 transformation) const
{
    if(isDrawable())
    {
        draw(transformation);
    }
    else
    {
        transform(transformation);
    }

    for(const auto& child : children)
    {
        child->traverse(transformation);
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
