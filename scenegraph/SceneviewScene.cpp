#include "SceneviewScene.h"
#include "GL/glew.h"
#include <QGLWidget>
#include "Camera.h"
#include <iostream>

#include "shape/Shape.h"
#include "shape/ConeShape.h"
#include "shape/CubeShape.h"
#include "shape/CylinderShape.h"
#include "shape/SphereShape.h"
#include "shape/LShape.h"
#include "lsystem/LSystemGenerator.h"
#include "Settings.h"

SceneviewScene::SceneviewScene()
{
    m_shapes.reserve(NUM_PRIMITIVE_TYPES);
}

SceneviewScene::~SceneviewScene()
{
    for (unsigned int i = 0; i < m_shapes.size(); i++) {
        delete m_shapes[i];
    }
}

void SceneviewScene::init()
{
    OpenGLScene::init();

    for (unsigned int i = 0; i < m_shapes.size(); i++) {
        delete m_shapes[i];
    }

    m_shapes[PRIMITIVE_CUBE] = new CubeShape(
                32,
                32,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"),
                glGetAttribLocation(m_shader, "texCoord"));
    m_shapes[PRIMITIVE_CONE] = new ConeShape(
                32,
                32,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"),
                glGetAttribLocation(m_shader, "texCoord"));
    m_shapes[PRIMITIVE_CYLINDER] = new CylinderShape(
                32,
                32,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"),
                glGetAttribLocation(m_shader, "texCoord"));
    m_shapes[PRIMITIVE_SPHERE] = new SphereShape(
                32,
                32,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"),
                glGetAttribLocation(m_shader, "texCoord"));
    m_shapes[PRIMITIVE_LSYSTEM] = new SphereShape(
                10,
                10,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"),
                glGetAttribLocation(m_shader, "texCoord"));
    m_shapes[PRIMITIVE_MESH] = new SphereShape(
                64,
                64,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"),
                glGetAttribLocation(m_shader, "texCoord"));
}

void SceneviewScene::settingsChanged()
{

}

void SceneviewScene::setLights(const glm::mat4 viewMatrix)
{
    // TODO: [SCENEVIEW] Fill this in...
    //
    // Use function(s) inherited from OpenGLScene to set up the lighting for your scene.
    // The lighting information will most likely be stored in CS123SceneLightData structures.
    //
    clearLights();
    for (CS123SceneLightData &l : m_lights) {
        setLight(l);
    }
}

void SceneviewScene::renderGeometry()
{
    for (CS123SceneFlattenedNode prim : m_primitives) {
        if (prim.primitive.type == PRIMITIVE_LSYSTEM) {
            std::string rules = m_lsystems[prim.primitive.lsystemID]->makeLSystem(settings.lsystemDepth, prim.primitive.lsystemDepth);//"FFFF[+++FFF[]------FFF";
            // cout << rules << endl;
            if( m_lshapes.find(rules) == m_lshapes.end()) {
                std::vector<CS123SceneMaterial> materials = m_lsystems[prim.primitive.lsystemID]->getMaterials();
                LShape *lshape = new LShape(rules,
                                            m_lsystems[prim.primitive.lsystemID]->getAngle(),
                                           materials,
                                           glGetAttribLocation(m_shader, "position"),
                                           glGetAttribLocation(m_shader, "normal"),
                                           glGetAttribLocation(m_shader, "texCoord")
                                           );
                m_lshapes[rules] = lshape;
            }

            // apply transforms
            for (LMaterialShape *lmshape : m_lshapes[rules]->getShapes()) {
                //m_lshapes[rules]->prepareShape(lmshape);
                CS123SceneMaterial adjustedMat = lmshape->material;
                adjustedMat.cAmbient.r *= m_global.ka;
                adjustedMat.cAmbient.g *= m_global.ka;
                adjustedMat.cAmbient.b *= m_global.ka;

                adjustedMat.cDiffuse.r *= m_global.kd;
                adjustedMat.cDiffuse.g *= m_global.kd;
                adjustedMat.cDiffuse.b *= m_global.kd;


                applyMaterial(adjustedMat);

                // apply transforms
                glUniformMatrix4fv(m_uniformLocs["m"], 1, GL_FALSE,
                        glm::value_ptr(prim.ctm));
                lmshape->shape->draw();
            }
        }
        else {
            CS123SceneMaterial adjustedMat = prim.primitive.material;

            adjustedMat.cAmbient.r *= m_global.ka;
            adjustedMat.cAmbient.g *= m_global.ka;
            adjustedMat.cAmbient.b *= m_global.ka;

            adjustedMat.cDiffuse.r *= m_global.kd;
            adjustedMat.cDiffuse.g *= m_global.kd;
            adjustedMat.cDiffuse.b *= m_global.kd;

            applyMaterial(adjustedMat);

            // apply global transforms
            glUniformMatrix4fv(m_uniformLocs["m"], 1, GL_FALSE,
                    glm::value_ptr(prim.ctm));
            m_shapes[prim.primitive.type]->draw();
        }
    }

}

