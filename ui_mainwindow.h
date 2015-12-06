/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_10;
    QWidget *canvas3D;
    QDockWidget *camtransDock;
    QWidget *camtransDockContents;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *cameraOrbitCheckbox;
    QGroupBox *cameraPosition;
    QGridLayout *gridLayout;
    QLabel *cameraPositionLabelX;
    QLabel *cameraPositionLabelY;
    QLabel *cameraPositionLabelZ;
    QDial *transX;
    QDial *transY;
    QDial *transZ;
    QGroupBox *cameraRotation;
    QVBoxLayout *verticalLayout_13;
    QWidget *cameraRotation_2;
    QGridLayout *gridLayout_15;
    QDial *rotU;
    QDial *rotV;
    QDial *rotW;
    QLabel *cameraRotationLabelYaw;
    QLabel *cameraRotationLabelPitch;
    QLabel *cameraRotationLabelRoll;
    QPushButton *resetUpVector;
    QGroupBox *cameraResetAxis;
    QGridLayout *gridLayout_14;
    QPushButton *xAxisButton;
    QPushButton *yAxisButton;
    QPushButton *zAxisButton;
    QPushButton *axonometricButton;
    QWidget *cameraFrustum;
    QGridLayout *gridLayout_5;
    QLabel *cameraFovLabel;
    QLineEdit *cameraFovTextbox;
    QSlider *cameraFovSlider;
    QLabel *cameraNearLabel;
    QLineEdit *cameraNearTextbox;
    QLabel *cameraFarLabel;
    QLineEdit *cameraFarTextbox;
    QSlider *cameraNearSlider;
    QSlider *cameraFarSlider;
    QLabel *cameraAspectRatio;
    QLabel *label;
    QWidget *cameraDockEmptySpace;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuToolbars;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(600, 3112);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks|QMainWindow::VerticalTabs);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_10 = new QGridLayout(centralWidget);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        canvas3D = new QWidget(centralWidget);
        canvas3D->setObjectName(QStringLiteral("canvas3D"));

        gridLayout_10->addWidget(canvas3D, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        camtransDock = new QDockWidget(MainWindow);
        camtransDock->setObjectName(QStringLiteral("camtransDock"));
        camtransDockContents = new QWidget();
        camtransDockContents->setObjectName(QStringLiteral("camtransDockContents"));
        verticalLayout_10 = new QVBoxLayout(camtransDockContents);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        cameraOrbitCheckbox = new QCheckBox(camtransDockContents);
        cameraOrbitCheckbox->setObjectName(QStringLiteral("cameraOrbitCheckbox"));

        verticalLayout_10->addWidget(cameraOrbitCheckbox);

        cameraPosition = new QGroupBox(camtransDockContents);
        cameraPosition->setObjectName(QStringLiteral("cameraPosition"));
        gridLayout = new QGridLayout(cameraPosition);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(5);
        gridLayout->setContentsMargins(-1, 5, -1, 5);
        cameraPositionLabelX = new QLabel(cameraPosition);
        cameraPositionLabelX->setObjectName(QStringLiteral("cameraPositionLabelX"));
        cameraPositionLabelX->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelX, 1, 0, 1, 1);

        cameraPositionLabelY = new QLabel(cameraPosition);
        cameraPositionLabelY->setObjectName(QStringLiteral("cameraPositionLabelY"));
        cameraPositionLabelY->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelY, 1, 1, 1, 1);

        cameraPositionLabelZ = new QLabel(cameraPosition);
        cameraPositionLabelZ->setObjectName(QStringLiteral("cameraPositionLabelZ"));
        cameraPositionLabelZ->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(cameraPositionLabelZ, 1, 2, 1, 1);

        transX = new QDial(cameraPosition);
        transX->setObjectName(QStringLiteral("transX"));
        transX->setMinimumSize(QSize(60, 60));
        transX->setMaximumSize(QSize(60, 60));
        transX->setMinimum(-360);
        transX->setMaximum(360);
        transX->setSingleStep(10);
        transX->setPageStep(30);
        transX->setOrientation(Qt::Horizontal);
        transX->setInvertedControls(true);
        transX->setWrapping(true);

        gridLayout->addWidget(transX, 0, 0, 1, 1);

        transY = new QDial(cameraPosition);
        transY->setObjectName(QStringLiteral("transY"));
        transY->setMinimumSize(QSize(60, 60));
        transY->setMaximumSize(QSize(60, 60));
        transY->setMinimum(-360);
        transY->setMaximum(360);
        transY->setSingleStep(10);
        transY->setPageStep(30);
        transY->setOrientation(Qt::Horizontal);
        transY->setInvertedControls(true);
        transY->setWrapping(true);

        gridLayout->addWidget(transY, 0, 1, 1, 1);

        transZ = new QDial(cameraPosition);
        transZ->setObjectName(QStringLiteral("transZ"));
        transZ->setMinimumSize(QSize(60, 60));
        transZ->setMaximumSize(QSize(60, 60));
        transZ->setMinimum(-360);
        transZ->setMaximum(360);
        transZ->setSingleStep(10);
        transZ->setPageStep(30);
        transZ->setOrientation(Qt::Horizontal);
        transZ->setInvertedControls(true);
        transZ->setWrapping(true);

        gridLayout->addWidget(transZ, 0, 2, 1, 1);


        verticalLayout_10->addWidget(cameraPosition);

        cameraRotation = new QGroupBox(camtransDockContents);
        cameraRotation->setObjectName(QStringLiteral("cameraRotation"));
        cameraRotation->setEnabled(true);
        verticalLayout_13 = new QVBoxLayout(cameraRotation);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(-1, 5, -1, 5);
        cameraRotation_2 = new QWidget(cameraRotation);
        cameraRotation_2->setObjectName(QStringLiteral("cameraRotation_2"));
        gridLayout_15 = new QGridLayout(cameraRotation_2);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        gridLayout_15->setVerticalSpacing(18);
        gridLayout_15->setContentsMargins(0, 0, 0, 0);
        rotU = new QDial(cameraRotation_2);
        rotU->setObjectName(QStringLiteral("rotU"));
        rotU->setMinimumSize(QSize(60, 60));
        rotU->setMaximumSize(QSize(60, 60));
        rotU->setMinimum(-360);
        rotU->setMaximum(360);
        rotU->setSingleStep(10);
        rotU->setPageStep(30);
        rotU->setOrientation(Qt::Horizontal);
        rotU->setInvertedControls(true);
        rotU->setWrapping(true);

        gridLayout_15->addWidget(rotU, 0, 0, 1, 1);

        rotV = new QDial(cameraRotation_2);
        rotV->setObjectName(QStringLiteral("rotV"));
        rotV->setMinimumSize(QSize(60, 60));
        rotV->setMaximumSize(QSize(60, 60));
        rotV->setMinimum(-360);
        rotV->setMaximum(360);
        rotV->setSingleStep(10);
        rotV->setPageStep(30);
        rotV->setOrientation(Qt::Horizontal);
        rotV->setInvertedControls(true);
        rotV->setWrapping(true);

        gridLayout_15->addWidget(rotV, 0, 1, 1, 1);

        rotW = new QDial(cameraRotation_2);
        rotW->setObjectName(QStringLiteral("rotW"));
        rotW->setMinimumSize(QSize(60, 60));
        rotW->setMaximumSize(QSize(60, 60));
        rotW->setMinimum(-360);
        rotW->setMaximum(360);
        rotW->setSingleStep(10);
        rotW->setPageStep(30);
        rotW->setOrientation(Qt::Horizontal);
        rotW->setInvertedControls(true);
        rotW->setWrapping(true);

        gridLayout_15->addWidget(rotW, 0, 2, 1, 1);

        cameraRotationLabelYaw = new QLabel(cameraRotation_2);
        cameraRotationLabelYaw->setObjectName(QStringLiteral("cameraRotationLabelYaw"));
        cameraRotationLabelYaw->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelYaw, 1, 0, 1, 1);

        cameraRotationLabelPitch = new QLabel(cameraRotation_2);
        cameraRotationLabelPitch->setObjectName(QStringLiteral("cameraRotationLabelPitch"));
        cameraRotationLabelPitch->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelPitch, 1, 1, 1, 1);

        cameraRotationLabelRoll = new QLabel(cameraRotation_2);
        cameraRotationLabelRoll->setObjectName(QStringLiteral("cameraRotationLabelRoll"));
        cameraRotationLabelRoll->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(cameraRotationLabelRoll, 1, 2, 1, 1);


        verticalLayout_13->addWidget(cameraRotation_2);

        resetUpVector = new QPushButton(cameraRotation);
        resetUpVector->setObjectName(QStringLiteral("resetUpVector"));

        verticalLayout_13->addWidget(resetUpVector);


        verticalLayout_10->addWidget(cameraRotation);

        cameraResetAxis = new QGroupBox(camtransDockContents);
        cameraResetAxis->setObjectName(QStringLiteral("cameraResetAxis"));
        cameraResetAxis->setMinimumSize(QSize(0, 0));
        gridLayout_14 = new QGridLayout(cameraResetAxis);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        xAxisButton = new QPushButton(cameraResetAxis);
        xAxisButton->setObjectName(QStringLiteral("xAxisButton"));

        gridLayout_14->addWidget(xAxisButton, 0, 0, 1, 1);

        yAxisButton = new QPushButton(cameraResetAxis);
        yAxisButton->setObjectName(QStringLiteral("yAxisButton"));

        gridLayout_14->addWidget(yAxisButton, 1, 0, 1, 1);

        zAxisButton = new QPushButton(cameraResetAxis);
        zAxisButton->setObjectName(QStringLiteral("zAxisButton"));

        gridLayout_14->addWidget(zAxisButton, 0, 1, 1, 1);

        axonometricButton = new QPushButton(cameraResetAxis);
        axonometricButton->setObjectName(QStringLiteral("axonometricButton"));

        gridLayout_14->addWidget(axonometricButton, 1, 1, 1, 1);


        verticalLayout_10->addWidget(cameraResetAxis);

        cameraFrustum = new QWidget(camtransDockContents);
        cameraFrustum->setObjectName(QStringLiteral("cameraFrustum"));
        gridLayout_5 = new QGridLayout(cameraFrustum);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_5->setVerticalSpacing(5);
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        cameraFovLabel = new QLabel(cameraFrustum);
        cameraFovLabel->setObjectName(QStringLiteral("cameraFovLabel"));

        gridLayout_5->addWidget(cameraFovLabel, 0, 0, 1, 1);

        cameraFovTextbox = new QLineEdit(cameraFrustum);
        cameraFovTextbox->setObjectName(QStringLiteral("cameraFovTextbox"));
        cameraFovTextbox->setMinimumSize(QSize(60, 0));
        cameraFovTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraFovTextbox, 0, 3, 1, 1);

        cameraFovSlider = new QSlider(cameraFrustum);
        cameraFovSlider->setObjectName(QStringLiteral("cameraFovSlider"));
        cameraFovSlider->setMinimumSize(QSize(100, 0));
        cameraFovSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraFovSlider, 0, 1, 1, 1);

        cameraNearLabel = new QLabel(cameraFrustum);
        cameraNearLabel->setObjectName(QStringLiteral("cameraNearLabel"));

        gridLayout_5->addWidget(cameraNearLabel, 1, 0, 1, 1);

        cameraNearTextbox = new QLineEdit(cameraFrustum);
        cameraNearTextbox->setObjectName(QStringLiteral("cameraNearTextbox"));
        cameraNearTextbox->setMinimumSize(QSize(60, 0));
        cameraNearTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraNearTextbox, 1, 3, 1, 1);

        cameraFarLabel = new QLabel(cameraFrustum);
        cameraFarLabel->setObjectName(QStringLiteral("cameraFarLabel"));

        gridLayout_5->addWidget(cameraFarLabel, 2, 0, 1, 1);

        cameraFarTextbox = new QLineEdit(cameraFrustum);
        cameraFarTextbox->setObjectName(QStringLiteral("cameraFarTextbox"));
        cameraFarTextbox->setMinimumSize(QSize(60, 0));
        cameraFarTextbox->setMaximumSize(QSize(60, 16777215));

        gridLayout_5->addWidget(cameraFarTextbox, 2, 3, 1, 1);

        cameraNearSlider = new QSlider(cameraFrustum);
        cameraNearSlider->setObjectName(QStringLiteral("cameraNearSlider"));
        cameraNearSlider->setMinimumSize(QSize(100, 0));
        cameraNearSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraNearSlider, 1, 1, 1, 1);

        cameraFarSlider = new QSlider(cameraFrustum);
        cameraFarSlider->setObjectName(QStringLiteral("cameraFarSlider"));
        cameraFarSlider->setMinimumSize(QSize(100, 0));
        cameraFarSlider->setOrientation(Qt::Horizontal);

        gridLayout_5->addWidget(cameraFarSlider, 2, 1, 1, 1);


        verticalLayout_10->addWidget(cameraFrustum);

        cameraAspectRatio = new QLabel(camtransDockContents);
        cameraAspectRatio->setObjectName(QStringLiteral("cameraAspectRatio"));

        verticalLayout_10->addWidget(cameraAspectRatio);

        label = new QLabel(camtransDockContents);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(false);
        label->setWordWrap(true);

        verticalLayout_10->addWidget(label);

        cameraDockEmptySpace = new QWidget(camtransDockContents);
        cameraDockEmptySpace->setObjectName(QStringLiteral("cameraDockEmptySpace"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraDockEmptySpace->sizePolicy().hasHeightForWidth());
        cameraDockEmptySpace->setSizePolicy(sizePolicy);

        verticalLayout_10->addWidget(cameraDockEmptySpace);

        camtransDock->setWidget(camtransDockContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), camtransDock);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 20));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuToolbars = new QMenu(menuBar);
        menuToolbars->setObjectName(QStringLiteral("menuToolbars"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuToolbars->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), cameraRotation, SLOT(setDisabled(bool)));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), cameraPosition, SLOT(setDisabled(bool)));
        QObject::connect(xAxisButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxisX()));
        QObject::connect(yAxisButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxisY()));
        QObject::connect(axonometricButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxonometric()));
        QObject::connect(transX, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraTranslation()));
        QObject::connect(transY, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraTranslation()));
        QObject::connect(transZ, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraTranslation()));
        QObject::connect(rotU, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraRotationU()));
        QObject::connect(rotW, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraRotationN()));
        QObject::connect(rotV, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraRotationV()));
        QObject::connect(cameraNearSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraNearTextbox, SIGNAL(textChanged(QString)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraFarSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraFarTextbox, SIGNAL(textChanged(QString)), MainWindow, SLOT(updateCameraClip()));
        QObject::connect(cameraFovSlider, SIGNAL(valueChanged(int)), MainWindow, SLOT(updateCameraHeightAngle()));
        QObject::connect(cameraFovTextbox, SIGNAL(textChanged(QString)), MainWindow, SLOT(updateCameraHeightAngle()));
        QObject::connect(actionOpen, SIGNAL(triggered()), MainWindow, SLOT(fileOpen()));
        QObject::connect(resetUpVector, SIGNAL(clicked()), MainWindow, SLOT(resetUpVector()));
        QObject::connect(cameraOrbitCheckbox, SIGNAL(toggled(bool)), cameraResetAxis, SLOT(setDisabled(bool)));
        QObject::connect(zAxisButton, SIGNAL(clicked()), MainWindow, SLOT(setCameraAxisZ()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CS 123: Introduction to Computer Graphics", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open...", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        camtransDock->setWindowTitle(QApplication::translate("MainWindow", "Camtrans", 0));
        cameraOrbitCheckbox->setText(QApplication::translate("MainWindow", "Use orbit camera instead", 0));
        cameraPosition->setTitle(QApplication::translate("MainWindow", "Translation", 0));
        cameraPositionLabelX->setText(QApplication::translate("MainWindow", "X", 0));
        cameraPositionLabelY->setText(QApplication::translate("MainWindow", "Y", 0));
        cameraPositionLabelZ->setText(QApplication::translate("MainWindow", "Z", 0));
        cameraRotation->setTitle(QApplication::translate("MainWindow", "Rotation", 0));
        cameraRotationLabelYaw->setText(QApplication::translate("MainWindow", "U", 0));
        cameraRotationLabelPitch->setText(QApplication::translate("MainWindow", "V", 0));
        cameraRotationLabelRoll->setText(QApplication::translate("MainWindow", "W", 0));
        resetUpVector->setText(QApplication::translate("MainWindow", "Reset up vector", 0));
        cameraResetAxis->setTitle(QApplication::translate("MainWindow", "Reset", 0));
        xAxisButton->setText(QApplication::translate("MainWindow", "X axis", 0));
        yAxisButton->setText(QApplication::translate("MainWindow", "Y axis", 0));
        zAxisButton->setText(QApplication::translate("MainWindow", "Z axis", 0));
        axonometricButton->setText(QApplication::translate("MainWindow", "Axonometric", 0));
        cameraFovLabel->setText(QApplication::translate("MainWindow", "FOV", 0));
        cameraNearLabel->setText(QApplication::translate("MainWindow", "Near", 0));
        cameraFarLabel->setText(QApplication::translate("MainWindow", "Far", 0));
        cameraAspectRatio->setText(QApplication::translate("MainWindow", "Aspect ratio:", 0));
        label->setText(QApplication::translate("MainWindow", "Resize the window to change the aspect ratio.", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuToolbars->setTitle(QApplication::translate("MainWindow", "&Toolbars", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
