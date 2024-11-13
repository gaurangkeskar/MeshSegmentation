#pragma once
#include "Triangulation.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "OpenglWidget.h"
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

private:
    void setupUi();
    void convertTriangulationToGraphicsObject(const Triangulation& inputTriangulation, OpenGlWidget::Data&);

    QPushButton* loadFile;
    QPushButton* segment;

    OpenGlWidget* openglWidget;
    OpenGlWidget* openglWidgetOutput;

    Triangulation inputTriangulation;
    QString inputFilePath;

    void loadSTLFile(const QString& filePath, Triangulation& inputTriangulation, OpenGlWidget* openglwidget);
};
