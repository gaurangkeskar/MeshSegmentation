#include "MeshSegmentation.h"
#include <QFileDialog>
#include <QGridLayout>
#include "STLReader.h"
#include "Segment.h"
#include "Segmenter.h"
using namespace MeshReader;

MeshSegmentation::MeshSegmentation(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &MeshSegmentation::onLoadFileClick);
    connect(segment, &QPushButton::clicked, this, &MeshSegmentation::onSegmentation);
    connect(planarCheckbox, &QCheckBox::toggled, this, &MeshSegmentation::onPlanarClick);
    connect(sphericalCheckbox, &QCheckBox::toggled, this, &MeshSegmentation::onSphericalClick);
    connect(cylindricalCheckbox, &QCheckBox::toggled, this, &MeshSegmentation::onCylindricalClick);
}

MeshSegmentation::~MeshSegmentation()
{}

void MeshSegmentation::setupUi()
{
    loadFile = new QPushButton("Load STL File", this);
    segment = new QPushButton("Segment", this);
    openglWidget = new OpenGlWidget(this);
    openglWidgetOutput = new OpenGlWidget(this);
    graphicSync = new GraphicsSynchronizer(openglWidget, openglWidgetOutput);
    planarCheckbox = new QCheckBox("Planar Surfaces", this);
    sphericalCheckbox = new QCheckBox("Spherical Surfaces", this);
    cylindricalCheckbox = new QCheckBox("Cylindrical Surfaces", this);

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0, 1, 3);
    layout->addWidget(segment, 0, 3, 1, 3);

    layout->addWidget(planarCheckbox, 1, 0, 1, 1);
    layout->addWidget(cylindricalCheckbox, 1, 1, 1, 1);
    layout->addWidget(sphericalCheckbox, 1, 2, 1, 1);
    layout->addWidget(openglWidget, 2, 0, 1, 3);
    layout->addWidget(openglWidgetOutput, 2, 3, 1, 3);
 

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
    Segment segment;
    Segmenter segmenter;

    float red[3] = { 1.0,0.0,0.0 };
    float green[3] = { 0.0,1.0,0.0 };
    float blue[3] = { 0.0,0.0,1.0 };
    
    segmenter.processPlanarSurfaces(inputTriangulation, segment);
    segmenter.processSphericalSurfaces(inputTriangulation, segment);
    segmenter.processCylindricalSurfaces(inputTriangulation, segment);

    QVector<OpenGlWidget::Data> data;
    if (showPlanar) {
        for (int i = 0; i < segment.planarSurfaces.size(); i++) {
            Triangulation triangulation = segment.planarSurfaces[i];
            convertTriangulationToGraphicsObject(triangulation, data, red);
        }
    }


    if (showCylindrical) {
        for (int i = 0; i < segment.cylindricalSurfaces.size(); i++) {
            Triangulation triangulation = segment.cylindricalSurfaces[i];
            convertTriangulationToGraphicsObject(triangulation, data, green);
        }
    }


    if (showSpherical) {
        for (int i = 0; i < segment.sphericalSurfaces.size(); i++) {
            Triangulation triangulation = segment.sphericalSurfaces[i];
            convertTriangulationToGraphicsObject(triangulation, data, blue);
        }
    }
    openglWidgetOutput->setData(data);
}

void MeshSegmentation::onPlanarClick()
{
    showPlanar = true;
}

void MeshSegmentation::onCylindricalClick()
{
    showCylindrical = true;
}

void MeshSegmentation::onSphericalClick()
{
    showSpherical = true;
}

void MeshSegmentation::loadSTLFile(const QString& filePath, Triangulation& inputTriangulation, OpenGlWidget* openglWidget)
{
    STLReader reader;
    reader.read(filePath.toStdString(), inputTriangulation);
    QVector<OpenGlWidget::Data> data;
    convertTriangulationToGraphicsObject(inputTriangulation, data);
    openglWidget->setData(data);
}

void MeshSegmentation::convertTriangulationToGraphicsObject(const Triangulation& triangulation, QVector<OpenGlWidget::Data>& data, float clr[3])
{
    OpenGlWidget::Data data1;
    for (const Triangle& triangle : triangulation.Triangles)
    {
        const Point& normal = triangle.Normal();
        for (const Point& point : triangle.Points())
        {
            data1.vertices.push_back(triangulation.UniqueNumbers[point.X()]);
            data1.vertices.push_back(triangulation.UniqueNumbers[point.Y()]);
            data1.vertices.push_back(triangulation.UniqueNumbers[point.Z()]);

            data1.normals.push_back(triangulation.UniqueNumbers[normal.X()]);
            data1.normals.push_back(triangulation.UniqueNumbers[normal.Y()]);
            data1.normals.push_back(triangulation.UniqueNumbers[normal.Z()]);

            data1.colors.push_back(clr[0]);
            data1.colors.push_back(clr[1]);
            data1.colors.push_back(clr[2]);
        }
    }
    data1.drawStyle = OpenGlWidget::LINES;
    data.push_back(data1);
    return;
}

void MeshSegmentation::convertTriangulationToGraphicsObject(const Triangulation& triangulation, QVector<OpenGlWidget::Data>& data)
{
    OpenGlWidget::Data data1;
    for (const Triangle& triangle : triangulation.Triangles)
    {
        const Point& normal = triangle.Normal();
        for (const Point& point : triangle.Points())
        {
            data1.vertices.push_back(triangulation.UniqueNumbers[point.X()]);
            data1.vertices.push_back(triangulation.UniqueNumbers[point.Y()]);
            data1.vertices.push_back(triangulation.UniqueNumbers[point.Z()]);

            data1.normals.push_back(triangulation.UniqueNumbers[normal.X()]);
            data1.normals.push_back(triangulation.UniqueNumbers[normal.Y()]);
            data1.normals.push_back(triangulation.UniqueNumbers[normal.Z()]);
        }
    }
    data1.drawStyle = OpenGlWidget::TRIANGLES;
    data.push_back(data1);
    return;
}
