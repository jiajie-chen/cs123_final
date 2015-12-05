#include "Scene.h"
#include "Camera.h"
#include "CS123SceneData.h"
#include "CS123ISceneParser.h"
#include <QtGlobal>


Scene::Scene() //: m_camera(NULL)
{
}

Scene::Scene(const Scene &copy) :
    m_lights(copy.m_lights),
    m_primitives(copy.m_primitives),
    m_global(copy.m_global)
{
}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D

}

void Scene::parse(Scene *sceneToFill, CS123ISceneParser *parser)
{
    // TODO: load scene into sceneToFill using setGlobal(), addLight(), addPrimitive(), and
    //   finishParsing()
    CS123SceneGlobalData g;
    parser->getGlobalData(g);
    sceneToFill->setGlobal(g);

    for (int i = 0; i < parser->getNumLights(); i++) {
        CS123SceneLightData light;
        parser->getLightData(i, light);
        sceneToFill->addLight(light);
    }

    parseTree(sceneToFill, *parser->getRootNode(), glm::mat4x4(1.0));
}

void Scene::parseTree(Scene *sceneToFill, const CS123SceneNode &node, const glm::mat4x4 &ctm)
{
    // build the current ctm
    glm::mat4x4 ctm2 = glm::mat4x4(1.0);
    std::vector<CS123SceneTransformation *> transforms = node.transformations;
    for (CS123SceneTransformation *t : transforms) { // use C++11 style iterators
        switch (t->type) {
        case TRANSFORMATION_TRANSLATE:
            ctm2 *= glm::translate(glm::mat4x4(1.0), t->translate);
            break;
        case TRANSFORMATION_SCALE:
            ctm2 *= glm::scale(glm::mat4x4(1.0), t->scale);
            break;
        case TRANSFORMATION_ROTATE:
            ctm2 *= glm::rotate(glm::mat4x4(1.0), t->angle, t->rotate);
            break;
        case TRANSFORMATION_MATRIX:
            ctm2 *= t->matrix;
            break;
        default:
            assert(false);
            break;
        }
    }

    glm::mat4x4 currCTM = ctm * ctm2;

    // add all primitives with the transforms
    std::vector<CS123ScenePrimitive *> prims = node.primitives;
    for (CS123ScenePrimitive *p : prims) {
        sceneToFill->addPrimitive(*p, currCTM);
    }

    // recur through children
    std::vector<CS123SceneNode *> children = node.children;
    for (CS123SceneNode *c : children) {
        parseTree(sceneToFill, *c, currCTM);
    }
}

void Scene::addPrimitive(const CS123ScenePrimitive &scenePrimitive, const glm::mat4x4 &matrix)
{
    CS123SceneFlattenedNode n = CS123SceneFlattenedNode();
    n.primitive = scenePrimitive;
    n.ctm = matrix;

    // make sure the primitive material is correctly defined
    /*
    n.primitive.material.textureMap = 0;

    n.primitive.material.cAmbient.r *= m_global.ka;
    n.primitive.material.cAmbient.g *= m_global.ka;
    n.primitive.material.cAmbient.b *= m_global.ka;

    n.primitive.material.cDiffuse.r *= m_global.kd;
    n.primitive.material.cDiffuse.g *= m_global.kd;
    n.primitive.material.cDiffuse.b *= m_global.kd;
    */

    m_primitives.push_back(n);
}

void Scene::addLight(const CS123SceneLightData &sceneLight)
{
    m_lights.push_back(sceneLight);
}

void Scene::setGlobal(const CS123SceneGlobalData &global)
{
    m_global = global;
}

