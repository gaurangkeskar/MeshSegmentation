#include "MeshSegmentation.h"
#include <QFileDialog>
#include <QGridLayout>
#include "STLReader.h"
#include "Surface.h"
using namespace MeshReader;

MeshSegmentation::MeshSegmentation(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &MeshSegmentation::onLoadFileClick);
    connect(segment, &QPushButton::clicked, this, &MeshSegmentation::onSegmentation);
}

MeshSegmentation::~MeshSegmentation()
{}

void MeshSegmentation::setupUi()
{
    loadFile = new QPushButton("Load STL File", this);
    segment = new QPushButton("Segment", this);
    openglWidget = new OpenGlWidget(this);
    openglWidgetOutput = new OpenGlWidget(this);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0);
    layout->addWidget(segment, 0, 1);
    layout->addWidget(openglWidget, 1, 0);
    layout->addWidget(openglWidgetOutput, 1, 1);


    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(layout);
}

void MeshSegmentation::onLoadFileClick()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "", tr("files (*.stl)"));

    if (!fileName.isEmpty())
    {
        inputFilePath = fileName;
        loadSTLFile(inputFilePath, inputTriangulation, openglWidget);

    }
}


void MeshSegmentation::onSegmentation()
{
    Surface surface;
    surface.getPlanarSurfaces(inputTriangulation);
    //surface.getSphericalSurfaces(inputTriangulation);
    OpenGlWidget::Data data;
    for (int i = 0; i < surface.planarSurfaces.size(); i++) {
        Triangulation triangulation = surface.planarSurfaces[i];
        convertTriangulationToGraphicsObject(triangulation, data);
    }
   /* for (int i = 0; i < surface.sphericalSurfaces.size(); i++) {
        Triangulation triangulation = surface.sphericalSurfaces[i];
        convertTriangulationToGraphicsObject(triangulation, data);
    }*/
    openglWidgetOutput->setData(data);
}

void MeshSegmentation::loadSTLFile(const QString& filePath, Triangulation& inputTriangulation, OpenGlWidget* openglWidget)
{
    STLReader reader;
    reader.read(filePath.toStdString(), inputTriangulation);
    OpenGlWidget::Data data;
    convertTriangulationToGraphicsObject(inputTriangulation, data);
    openglWidget->setData(data);
}

void MeshSegmentation::convertTriangulationToGraphicsObject(const Triangulation& triangulation, OpenGlWidget::Data& data)
{
    for (const Triangle& triangle : triangulation.Triangles)
    {
        for (const Point& point : triangle.Points())
        {
            data.vertices.push_back(triangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Z()]);
        }

        const Point& normal = triangle.Normal();

        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(triangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Z()]);
        }
    }

    return;
}