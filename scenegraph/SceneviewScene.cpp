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

SceneviewScene::SceneviewScene()
{
    // TODO: [SCENEVIEW] Set up anything you need for your Sceneview scene here...
    m_shapes.reserve(NUM_PRIMITIVE_TYPES);
}

SceneviewScene::~SceneviewScene()
{
    // TODO: [SCENEVIEW] Don't leak memory!
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
                8,
                8,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"));
    m_shapes[PRIMITIVE_CONE] = new ConeShape(
                8,
                8,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"));
    m_shapes[PRIMITIVE_CYLINDER] = new CylinderShape(
                8,
                8,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"));
    m_shapes[PRIMITIVE_SPHERE] = new SphereShape(
                10,
                10,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"));
    m_shapes[PRIMITIVE_TORUS] = new SphereShape(
                10,
                10,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"));
    m_shapes[PRIMITIVE_MESH] = new SphereShape(
                10,
                10,
                0,
                glGetAttribLocation(m_shader, "position"),
                glGetAttribLocation(m_shader, "normal"));
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
    // TODO: [SCENEVIEW] Fill this in...
    //
    // This is where you should render the geometry of the scene. Use what you
    // know about OpenGL and leverage your Shapes classes to get the job done.
    //
    for (CS123SceneFlattenedNode prim : m_primitives) {
        CS123SceneMaterial adjustedMat = prim.primitive.material;

        adjustedMat.textureMap = 0;

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

        m_shapes[prim.primitive.type]->draw();
    }
}


void SceneviewScene::setSelection(int x, int y)
{
    // TODO: [MODELER LAB] Fill this in...
    //
    // Using m_selectionRecorder, set m_selectionIndex to the index in your
    // flattened parse tree of the object under the mouse pointer.  The
    // selection recorder will pick the object under the mouse pointer with
    // some help from you, all you have to do is:

    // 1) Set this to the number of objects you will be drawing.
    int numObjects = 0;

    // 2) Start the selection process
    m_selectionRecorder.enterSelectionMode(x, y, numObjects);

    // 3) Draw your objects, calling m_selectionRecorder.setObjectIndex() before drawing each one.

    // 4) Find out which object you selected, if any (-1 means no selection).
    m_selectionIndex = m_selectionRecorder.exitSelectionMode();
}
