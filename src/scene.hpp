
#ifndef SCENE_HPP
#define SCENE_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "renderer.hpp"

class SceneObject
{
public:
    SceneObject(SceneObject *parent) : mParent{parent} {}

    int globalX() const {
        int x = localX();
        auto ptr = mParent;
        while (ptr) {
            x += ptr->localX();
            ptr = ptr->mParent;
        }
        return x;
    }
    int globalY() const {
        int y = localY();
        auto ptr = mParent;
        while (ptr) {
            y += ptr->localY();
            ptr = ptr->mParent;
        }
        return y;
    }
    int localX() const { return mX; }
    int localY() const { return mY; }
    int layer() const { return mLayer; }
    std::string tag() const { return mTag; }

    void addChild(SceneObject *so) {
        assert(so != nullptr);
        so->mParent = this;
        mChildren.push_back(std::unique_ptr<SceneObject>(so));
    }

    void removeChild(SceneObject *so) {
        assert(so != nullptr);
        std::remove_if(std::begin(mChildren), std::end(mChildren),
            [=](auto &a) { return a.get() == so; });
    }

    std::vector<SceneObject *> findTags(std::string tag) {
        std::vector<SceneObject *> sos;
        for (auto &so : mChildren) {
            if (so->tag() == tag) {
                sos.push_back(so.get());
            }
        }
        return sos;
    }

    std::vector<SceneObject const *> findTags(std::string tag) const {
        std::vector<SceneObject const *> sos;
        for (auto &so : mChildren) {
            if (so->tag() == tag) {
                sos.push_back(so.get());
            }
        }
        return sos;
    }

    void step() {}
    void draw(Renderer &renderer) {(void)renderer;}

protected:
    int mX;
    int mY;
    int mLayer;
    std::string mTag;
    std::vector<std::unique_ptr<SceneObject>> mChildren;
    SceneObject *mParent;
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
