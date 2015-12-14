#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Databinding.h"
#include "Settings.h"
#include "scenegraph/ShapesScene.h"
#include "scenegraph/SceneviewScene.h"
#include "camera/CamtransCamera.h"
#include "CS123XmlSceneParser.h"
#include <QSettings>
#include <math.h>
#include <QFileDialog>
#include <QMessageBox>
#include <assert.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Make sure the settings are loaded before the UI
    settings.loadSettingsOrDefaults();

    QGLFormat qglFormat;
    qglFormat.setVersion(3, 2);
    qglFormat.setProfile(QGLFormat::CoreProfile);
    qglFormat.setSampleBuffers(true);
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(ui->canvas3D);
    m_canvas3D = new Canvas3D(qglFormat, this);

    SceneviewScene *scene = new SceneviewScene;
    if (m_canvas3D->isInitialized()) scene->init();
    m_canvas3D->setScene(scene);

    gridLayout->addWidget(m_canvas3D, 0, 1);

    // Restore the UI settings
    QSettings qtSettings("CS123");
    restoreGeometry(qtSettings.value("geometry").toByteArray());
    restoreState(qtSettings.value("windowState").toByteArray());

    // Resize the window because the window is huge since all docks were visible.
    resize(1000, 600);

    // Bind the UI elements to their properties in the global Settings object, using binding
    // objects to simplify the code.  Each binding object connects to its UI elements and keeps
    // the UI and its setting in sync.

    QList<QAction*> actions;

#define SETUP_ACTION(dock, key) \
    actions.push_back(ui->dock->toggleViewAction()); \
    actions.back()->setShortcut(QKeySequence(key));

    SETUP_ACTION(camtransDock,  "CTRL+1");

    ui->menuToolbars->addActions(actions);
#undef SETUP_ACTION

    ui->camtransDock->raise();

    dataBind();


    // Reset the contents of both canvas widgets (make a new 500x500 image for the 2D one)
    m_canvas3D->update();
    m_canvas3D->showFullScreen();
}

MainWindow::~MainWindow()
{
    foreach (DataBinding *b, m_bindings)
        delete b;
    foreach (QButtonGroup *bg, m_buttonGroups)
        delete bg;
    delete ui;
}

void MainWindow::dataBind()
{
    // Brush dock

#define BIND(b) { \
    DataBinding *_b = (b); \
    m_bindings.push_back(_b); \
    assert(connect(_b, SIGNAL(dataChanged()), this, SLOT(settingsChanged()))); \
}
    /*
    BIND(IntBinding::bindSliderAndTextbox(
        ui->shapeParameterSlider1, ui->shapeParameterTextbox1, settings.shapeParameter1, 1.f, 100.f))
    BIND(IntBinding::bindSliderAndTextbox(
        ui->shapeParameterSlider2, ui->shapeParameterTextbox2, settings.shapeParameter2, 1.f, 100.f))
    BIND(FloatBinding::bindSliderAndTextbox(
        ui->shapeParameterSlider3, ui->shapeParameterTextbox3, settings.shapeParameter3, 1.f, 100.f))
    BIND(BoolBinding::bindCheckbox(ui->useLightingCheckbox, settings.useLighting))
    BIND(BoolBinding::bindCheckbox(ui->drawWireframeCheckbox, settings.drawWireframe))
    BIND(BoolBinding::bindCheckbox(ui->drawNormalsCheckbox, settings.drawNormals))


    // Camtrans dock
    BIND( FloatBinding::bindDial(ui->transX, settings.cameraPosX, -2, 2, true) )
    BIND( FloatBinding::bindDial(ui->transY, settings.cameraPosY, -2, 2, true) )
    BIND( FloatBinding::bindDial(ui->transZ, settings.cameraPosZ, -2, 2, true) )
    BIND( FloatBinding::bindDial(ui->rotU,   settings.cameraRotU, -20, 20, true) )
    BIND( FloatBinding::bindDial(ui->rotV,   settings.cameraRotV, -20, 20, true) )
    BIND( FloatBinding::bindDial(ui->rotW,   settings.cameraRotN, -180, 180, false) )
    */
    BIND( FloatBinding::bindSliderAndTextbox(
              ui->cameraFovSlider, ui->cameraFovTextbox, settings.cameraFov, 1, 179) )
    BIND( FloatBinding::bindSliderAndTextbox(
              ui->cameraNearSlider, ui->cameraNearTextbox, settings.cameraNear, 0.1, 50) )
    BIND( FloatBinding::bindSliderAndTextbox(
              ui->cameraFarSlider, ui->cameraFarTextbox, settings.cameraFar, 0.1, 128) )
    BIND( BoolBinding::bindCheckbox(ui->cameraOrbitCheckbox, settings.useOrbitCamera) )

#undef BIND

    // make sure the aspect ratio updates when m_canvas3D changes size
            connect(m_canvas3D, SIGNAL(aspectRatioChanged()), this, SLOT(updateAspectRatio()));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e); // allow the superclass to handle this for the most part...

    switch (e->type()) {

    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;

    default:
        break;

    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // Save the settings before we quit
    settings.saveSettings();
    QSettings qtSettings("CS123");
    qtSettings.setValue("geometry", saveGeometry());
    qtSettings.setValue("windowState", saveState());

    QMainWindow::closeEvent(event);
}

void MainWindow::updateAspectRatio()
{
    // Update the aspect ratio text so the aspect ratio will be correct even if the
    // 3D canvas isn't visible (the 3D canvas isn't resized when it isn't visible)
    QSize activeTabSize = ui->canvas3D->size();
    float aspectRatio = (float)activeTabSize.width() / (float)activeTabSize.height();
    ui->cameraAspectRatio->setText(QString("Aspect ratio: %1").arg(aspectRatio));
}


void MainWindow::settingsChanged()
{
    m_canvas3D->settingsChanged();
}

void MainWindow::setAllRayFeatures(bool checked)
{
}

void MainWindow::fileCopy3Dto2D()
{
    // Make sure OpenGL gets a chance to redraw
    m_canvas3D->update();
    QApplication::processEvents();
}

void MainWindow::fileNew()
{
}

void MainWindow::fileOpenDefaultScene()
{
    QString prePath;
    #ifdef __APPLE__
    prePath = "../../../..";
    #else
    prePath = "..";
    #endif

    QString path = prePath + "/cs123_final/scenes/scene.xml";
    QDir dir(path);
    QString file = dir.absolutePath();

    fileOpen(file);
}


void MainWindow::fileOpen(QString file_path)
{
    activateCanvas3D();
    QString file(QDir::cleanPath(file_path));
    if (!file.isNull())
    {
        if (file.endsWith(".xml"))
        {
            CS123XmlSceneParser parser(file.toLatin1().data());
            if (parser.parse())
            {
                SceneviewScene *scene = new SceneviewScene;
                if (m_canvas3D->isInitialized()) scene->init();

                Scene::parse(scene, &parser);
                m_canvas3D->setScene(scene); // Ownership transfer of scene pointer - the
                                             // old scene is deleted automatically.

                // Set the camera for the new scene
                CS123SceneCameraData camera;
                if (parser.getCameraData(camera))
                {
                    camera.pos[3] = 1;
                    camera.look[3] = 0;
                    camera.up[3] = 0;

                    CamtransCamera *cam = m_canvas3D->getCamtransCamera();
                    cam->orientLook(camera.pos, camera.look, camera.up);
                    cam->setHeightAngle(camera.heightAngle);
                }

                if (settings.useOrbitCamera) {
                    ui->cameraOrbitCheckbox->setChecked(true);
                }

                activateCanvas3D();
            }
            else
            {
                QMessageBox::critical(this, "Error", "Could not load scene \"" + file + "\"");
            }
        }
        else
        {
            QMessageBox::critical(this, "Ayy", "LMAO");
        }
    }
}

void MainWindow::fileOpen()
{
    QString file = QFileDialog::getOpenFileName(this, QString(), "/course/cs123/data/");
    fileOpen(file);
}

void MainWindow::fileSave()
{
}

void MainWindow::checkAllRayFeatures()
{
    setAllRayFeatures(true);
}

void MainWindow::uncheckAllRayFeatures()
{
    setAllRayFeatures(false);
}

void MainWindow::filterImage()
{
    // Disable the UI so the user can't interfere with the filtering
    setAllEnabled(false);

    // Enable the UI again
    setAllEnabled(true);
}

void MainWindow::renderImage()
{
    // Make sure OpenGL gets a chance to update the OrbitCamera, which can only be done when
    // that tab is active (because it needs the OpenGL context for its matrix transforms)
    m_canvas3D->update();
    QApplication::processEvents();
}

void MainWindow::setAllEnabled(bool enabled)
{
    QList<QWidget *> widgets;
    widgets += ui->camtransDock;

    QList<QAction *> actions;
    actions += ui->actionOpen;
    actions += ui->actionQuit;

    foreach (QWidget *widget, widgets)
        widget->setEnabled(enabled);
    foreach (QAction *action, actions)
        action->setEnabled(enabled);
}

void MainWindow::activateCanvas2D() {
}

void MainWindow::activateCanvas3D() {
    m_canvas3D->update();
    ui->canvas3D->update();
}

void MainWindow::clearImage()
{
}

void MainWindow::setCameraAxisX() {
    m_canvas3D->setCameraAxisX();
}

void MainWindow::setCameraAxisY() {
    m_canvas3D->setCameraAxisY();
}

void MainWindow::setCameraAxisZ() {
    m_canvas3D->setCameraAxisZ();
}

void MainWindow::updateCameraTranslation() {
    m_canvas3D->updateCameraTranslation();
}

void MainWindow::updateCameraRotationN() {
    m_canvas3D->updateCameraRotationN();
}

void MainWindow::updateCameraRotationV() {
    m_canvas3D->updateCameraRotationV();
}

void MainWindow::updateCameraRotationU() {
    m_canvas3D->updateCameraRotationU();
}

void MainWindow::resetUpVector() {
    m_canvas3D->resetUpVector();
}

void MainWindow::updateCameraClip() {
    m_canvas3D->updateCameraClip();
}

void MainWindow::updateCameraHeightAngle() {
    m_canvas3D->updateCameraHeightAngle();
}

void MainWindow::setCameraAxonometric() {
    m_canvas3D->setCameraAxonometric();
}
