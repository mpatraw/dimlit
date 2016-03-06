
#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>

#include "renderer.hpp"

class SceneObject
{
public:
    SceneObject(std::shared_ptr<SceneObject> parent) : mParent{parent} {}

    int x() const { return mX; }
    int y() const { return mY; }
    int layer() const { return mLayer; }

    void step();
    void draw(Renderer &renderer);

protected:
    int mX;
    int mY;
    int mLayer;
    std::weak_ptr<SceneObject> mParent;
    std::vector<std::shared_ptr<SceneObject>> mChildren;
};

class Scene
{
public:
    virtual ~Scene() {}

    virtual void step() = 0;
    virtual void draw() = 0;

protected:
};

#endif
