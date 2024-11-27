#pragma once
#include "Triangulation.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QCheckBox>

#include "OpenglWidget.h"
#include "GraphicsSynchronizer.h"
using namespace Geometry;

class MeshSegmentation : public QMainWindow
{
    Q_OBJECT

public:
    MeshSegmentation(QWidget *parent = nullptr);
    ~MeshSegmentation();

private slots:
    void onLoadFileClick();
    void onSegmentation();
    void onPlanarClick();
    void onSphericalClick();

private:
    bool showPlanar = false;
    bool showSpherical = false;

    void setupUi();
    OpenGlWidget::Data convertTriangulationToGraphicsObject(const Triangulation& inputTriangulation, float clr[3]);

    QPushButton* loadFile;
    QPushButton* segment;
    QCheckBox* planarCheckbox;
    QCheckBox* sphericalCheckbox;

    OpenGlWidget* openglWidget;
    OpenGlWidget* openglWidgetOutput;

    Triangulation inputTriangulation;
    QString inputFilePath;

    GraphicsSynchronizer* graphicSync;

    void loadSTLFile(const QString& filePath, Triangulation& inputTriangulation, OpenGlWidget* openglwidget);
};
