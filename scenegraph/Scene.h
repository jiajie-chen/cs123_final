#ifndef SCENE_H
#define SCENE_H

#include <CS123Common.h>
#include "CS123SceneData.h"

class Camera;
class CS123ISceneParser;
class LSystemGenerator;
struct LSystemData;

/**
 * @class Scene
 *
 * @brief This is the base class for all scenes. Modify this class if you want to provide
 * common functionality to all your scenes.
 */
class Scene
{
public:
    Scene();
    virtual ~Scene();

    static void parse(Scene *sceneToFill, CS123ISceneParser *parser);

protected:

    static void parseTree(Scene *sceneToFill, const CS123SceneNode &node, const glm::mat4x4 &ctm);

    // Adds a primitive to the scene.
    virtual void addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix);
    virtual void addLSystemPrimitive(const CS123LSystemPrimitive &lsystemPrimitive, const glm::mat4x4 &matrix);

    // Adds a light to the scene.
    virtual void addLight(const CS123SceneLightData &sceneLight);

    // Sets the global data for the scene.
    virtual void setGlobal(const CS123SceneGlobalData &global);

    virtual void addLSystemGenerator(std::string id, const LSystemData &ls);

    std::vector<CS123SceneLightData> m_lights;
    std::vector<CS123SceneFlattenedNode> m_primitives;
    std::vector<CS123FlattenedLSystem> m_lsystemPrims;
    CS123SceneGlobalData m_global;
    std::map<std::string, LSystemGenerator *> m_lsystems;
};

#endif // SCENE_H
