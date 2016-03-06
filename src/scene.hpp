
#ifndef SCENE_HPP
#define SCENE_HPP

class Scene
{
public:
    virtual ~Scene() {}

    virtual void step() = 0;
    virtual void draw() = 0;

protected:
};

#endif
