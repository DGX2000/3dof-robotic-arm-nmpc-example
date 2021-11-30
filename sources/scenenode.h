#ifndef SCENENODE_H
#define SCENENODE_H

#include <vector>

#include <glm/glm.hpp>

class SceneNode
{
public:
    void traverse(glm::mat4 transformation) const;

    void addNode(class SceneNode* node);
    void removeNode(class SceneNode* node);

protected:
    SceneNode() = default;

    virtual void draw(const glm::mat4& transformation) const = 0;
    virtual void transform(glm::mat4& transformation) const = 0;
    virtual bool isDrawable() const = 0;

private:
    std::vector<class SceneNode*> children;
};

#endif // SCENENODE_H
