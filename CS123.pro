# -------------------------------------------------
# Project created by QtCreator 2010-08-22T14:12:19
# -------------------------------------------------
QT += opengl xml
TARGET = CS123
TEMPLATE = app

unix:!macx {
    LIBS += -lGLU
    QMAKE_CXXFLAGS += -std=c++11
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32 -lgdi32
}

SOURCES += camera/OrbitingCamera.cpp \
    camera/CamtransCamera.cpp \
    scenegraph/SelectionRecorder.cpp \
    lib/CS123XmlSceneParser.cpp \
    lib/ResourceLoader.cpp \
    scenegraph/ShapesScene.cpp \
    scenegraph/SceneviewScene.cpp \
    scenegraph/Scene.cpp \
    scenegraph/OpenGLScene.cpp \
    ui/SupportCanvas3D.cpp \
    ui/Settings.cpp \
    ui/mainwindow.cpp \
    ui/Databinding.cpp \
    ui/Canvas3D.cpp \
    main.cpp \
    glew-1.10.0/src/glew.c \
    shape/OpenGLShape.cpp \
    shape/Shape.cpp \
    shape/CubeShape.cpp \
    shape/CylinderShape.cpp \
    lib/ErrorChecker.cpp \
    shape/ConeShape.cpp \
    shape/SphereShape.cpp \
    lsystem/LSystemGenerator.cpp \
    camera/POVCamera.cpp \
    shape/LShape.cpp


HEADERS += camera/OrbitingCamera.h \
    camera/CamtransCamera.h \
    camera/Camera.h \
    scenegraph/SelectionRecorder.h \
    lib/CS123XmlSceneParser.h \
    lib/CS123SceneData.h \
    lib/CS123ISceneParser.h \
    lib/CS123Common.h \
    lib/ResourceLoader.h \
    scenegraph/ShapesScene.h \
    scenegraph/SceneviewScene.h \
    scenegraph/Scene.h \
    scenegraph/OpenGLScene.h \
    ui/SupportCanvas3D.h \
    ui/Settings.h \
    ui/mainwindow.h \
    ui/Databinding.h \
    ui/Canvas3D.h \
    ui_mainwindow.h \
    glew-1.10.0/include/GL/glew.h \
    shape/OpenGLShape.h \
    shape/Shape.h \
    shape/CubeShape.h \
    shape/CylinderShape.h \
    lib/ErrorChecker.h \
    shape/ConeShape.h \
    shape/SphereShape.h \
    lsystem/LSystemGenerator.h \
    lsystem/LSystemData.h \
    camera/POVCamera.h \
    shape/LShape.h


FORMS += ui/mainwindow.ui
INCLUDEPATH += glm camera lib scenegraph ui glew-1.10.0/include
DEPENDPATH += glm camera lib scenegraph ui glew-1.10.0/include
DEFINES += TIXML_USE_STL
OTHER_FILES += shaders/shader.frag shaders/shader.vert

# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra
# QMAKE_CXX_FLAGS_WARN_ON += -Wunknown-pragmas -Wunused-function -Wmain

macx {
    QMAKE_CXXFLAGS_WARN_ON -= -Warray-bounds -Wc++0x-compat
}

RESOURCES += \
    resources.qrc
#CONFIG += c++11
