#include "Scene.h"
#include "Camera.h"
#include "CS123SceneData.h"
#include "CS123ISceneParser.h"
#include <QtGlobal>
#include "lsystem/LSystemData.h"
#include "lsystem/LSystemGenerator.h"


Scene::Scene() //: m_camera(NULL)
{
}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D
    for (CS123SceneFlattenedNode n : m_primitives) {
        glDeleteTextures(1, &n.primitive.material.textureMap->texid);
        glDeleteTextures(1, &n.primitive.material.bumpMap->texid);

        delete (n.primitive.material.textureMap);
        delete (n.primitive.material.bumpMap);
    }

    for (std::map<std::string, LSystemGenerator *>::iterator it = m_lsystems.begin();
         it != m_lsystems.end(); it++) {
        delete it->second;
    }
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

    std::vector<std::string> ids = parser->getIDLSystems();
    for (std::string id : ids) {
        LSystemData ls;
        parser->getLSystemData(id, ls);
        sceneToFill->addLSystemGenerator(id, ls);
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

    // copy the material because XmlParser will delete the pointer when it goes out of scope in mainwindow.cpp
    // lol why do we have to manage crappy pointer code using structs?
    // why are we given support code that has structs with pointers in an OO language?
    CS123SceneFileMap *texMap = new CS123SceneFileMap();
    texMap->isUsed = n.primitive.material.textureMap->isUsed;
    texMap->filename = n.primitive.material.textureMap->filename;
    texMap->repeatU = n.primitive.material.textureMap->repeatU;
    texMap->repeatV = n.primitive.material.textureMap->repeatV;

    CS123SceneFileMap *bumpMap = new CS123SceneFileMap();
    bumpMap->isUsed = n.primitive.material.bumpMap->isUsed;
    bumpMap->filename = n.primitive.material.bumpMap->filename;
    bumpMap->repeatU = n.primitive.material.bumpMap->repeatU;
    bumpMap->repeatV = n.primitive.material.bumpMap->repeatV;

    n.primitive.material.textureMap = texMap;
    n.primitive.material.bumpMap = bumpMap;

    // make sure the primitive texture is correctly defined
    if (n.primitive.material.textureMap->isUsed) {
        QString path(n.primitive.material.textureMap->filename.c_str());
        QImage image(path);
        if (image.isNull()) {
            std::cout << "failed loading texture file at: " << n.primitive.material.textureMap->filename << std::endl;
            n.primitive.material.textureMap->isUsed = 0;
        } else {
            glGenTextures(1, &n.primitive.material.textureMap->texid);
            glBindTexture(GL_TEXTURE_2D, n.primitive.material.textureMap->texid);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    if (n.primitive.material.bumpMap->isUsed) {
        QString path(n.primitive.material.bumpMap->filename.c_str());
        QImage image(path);
        if (image.isNull()) {
            std::cout << "failed loading bump file at: " << n.primitive.material.textureMap->filename << std::endl;
            n.primitive.material.bumpMap->isUsed = 0;
        } else {
            glGenTextures(1, &n.primitive.material.bumpMap->texid);
            glBindTexture(GL_TEXTURE_2D, n.primitive.material.bumpMap->texid);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    m_primitives.push_back(n);
}

void Scene::addLight(const CS123SceneLightData &sceneLight)
{
    m_lights.push_back(sceneLight);
}

void Scene::addLSystemGenerator(std::string id, const LSystemData &ls)
{
    m_lsystems[id] = new LSystemGenerator(ls);
}

void Scene::setGlobal(const CS123SceneGlobalData &global)
{
    m_global = global;
}

