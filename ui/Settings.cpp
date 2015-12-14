/*!

 Settings.h
 CS123 Support Code

 @author  Evan Wallace (edwallac)
 @date    9/1/2010

 This file contains various settings and enumerations that you will need to
 use in the various assignments. The settings are bound to the GUI via static
 data bindings.

**/

#include "Settings.h"
#include <QFile>
#include <QSettings>

Settings settings;


/**
 * Loads the application settings, or, if no saved settings are available, loads default values for
 * the settings. You can change the defaults here.
 */
void Settings::loadSettingsOrDefaults()
{
    // Set the default values below
    QSettings s;

    // Shapes
    shapeType = s.value("shapeType", SHAPE_SPHERE).toInt();
    shapeParameter1 = s.value("shapeParameter1", 15).toInt();
    shapeParameter2 = s.value("shapeParameter2", 15).toInt();
    shapeParameter3 = s.value("shapeParameter3", 15).toDouble();
    useLighting = s.value("useLighting", true).toBool();
    drawWireframe = s.value("drawWireframe", true).toBool();
    drawNormals = s.value("drawNormals", false).toBool();

    // Camtrans
    useOrbitCamera = s.value("useOrbitCamera", true).toBool();
    cameraFov = s.value("cameraFov", 55).toDouble();
    cameraNear = s.value("cameraNear", 0.1).toDouble();
    cameraFar = s.value("cameraFar", 50).toDouble();

    // Ray
    useTextureMapping = s.value("useTextureMapping", false).toBool();
    usePointLights = s.value("usePointLights", true).toBool();
    useDirectionalLights = s.value("useDirectionalLights", true).toBool();
    useSpotLights = s.value("useSpotLights", true).toBool();

    // These are for computing deltas and the values don't matter, so start all dials in the up
    // position
    cameraPosX = 0;
    cameraPosY = 0;
    cameraPosZ = 0;
    cameraRotU = 0;
    cameraRotV = 0;
    cameraRotN = 0;

    lsystemDepth = 0;
}

void Settings::saveSettings()
{
    QSettings s;

    // Shapes
    s.setValue("shapeType", shapeType);
    s.setValue("shapeParameter1", shapeParameter1);
    s.setValue("shapeParameter2", shapeParameter2);
    s.setValue("shapeParameter3", shapeParameter3);
    s.setValue("useLighting", useLighting);
    s.setValue("drawWireframe", drawWireframe);
    s.setValue("drawNormals", drawNormals);

    // Camtrans
    s.setValue("useOrbitCamera", useOrbitCamera);
    s.setValue("cameraFov", cameraFov);
    s.setValue("cameraNear", cameraNear);
    s.setValue("cameraFar", cameraFar);

    // Ray
    s.setValue("useTextureMapping", useTextureMapping);
    s.setValue("usePointLights", usePointLights);
    s.setValue("useDirectionalLights", useDirectionalLights);
    s.setValue("useSpotLights", useSpotLights);
}

int Settings::getSceneMode()
{
    return SCENEMODE_SCENEVIEW;
}

int Settings::getCameraMode()
{
    if (this->useOrbitCamera)
        return CAMERAMODE_ORBIT;
    else
        return CAMERAMODE_CAMTRANS;
}
