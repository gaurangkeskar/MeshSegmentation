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
{
}

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

    if (showPlanar) {
        for (int i = 0; i < segment.planarSurfaces.size(); i++) {
            Triangulation triangulation = segment.planarSurfaces[i];
            OpenGlWidget::Data data= convertTriangulationToGraphicsObject(triangulation, red);
            data.drawStyle = OpenGlWidget::TRIANGLES;
            openglWidgetOutput->addObject(data);
        }
    }


    if (showCylindrical) {
        for (int i = 0; i < segment.cylindricalSurfaces.size(); i++) {
            Triangulation triangulation = segment.cylindricalSurfaces[i];
            OpenGlWidget::Data data = convertTriangulationToGraphicsObject(triangulation, green);
            data.drawStyle = OpenGlWidget::TRIANGLES;
            openglWidgetOutput->addObject(data);
        }
    }


    if (showSpherical) {
        for (int i = 0; i < segment.sphericalSurfaces.size(); i++) {
            Triangulation triangulation = segment.sphericalSurfaces[i];
            OpenGlWidget::Data data = convertTriangulationToGraphicsObject(triangulation, blue);
            data.drawStyle = OpenGlWidget::TRIANGLES;
            openglWidgetOutput->addObject(data);
        }
    }
}

void MeshSegmentation::onPlanarClick()
{
    if (showPlanar)
        showPlanar = false;
    else
        showPlanar = true;
}

void MeshSegmentation::onCylindricalClick()
{
    if (showCylindrical)
        showCylindrical = false;
    else
        showCylindrical = true;
}

void MeshSegmentation::onSphericalClick()
{
    if (showSpherical)
        showSpherical = false;
    else
        showSpherical = true;
}

void MeshSegmentation::loadSTLFile(const QString& filePath, Triangulation& inputTriangulation, OpenGlWidget* openglWidget)
{
    float white[3] = {1.0,1.0,1.0};
    STLReader reader;
    reader.read(filePath.toStdString(), inputTriangulation);
    OpenGlWidget::Data data;
    data = convertTriangulationToGraphicsObject(inputTriangulation, white);
    data.drawStyle = OpenGlWidget::TRIANGLES;
    openglWidget->addObject(data);
}

OpenGlWidget::Data MeshSegmentation::convertTriangulationToGraphicsObject(const Triangulation& triangulation, float clr[3])
{
    OpenGlWidget::Data data;
    for (const Triangle& triangle : triangulation.Triangles)
    {
        const Point& normal = triangle.Normal();
        for (const Point& point : triangle.Points())
        {
            data.vertices.push_back(triangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(triangulation.UniqueNumbers[point.Z()]);
        }

        for (int i = 0; i < 3; i++) {
            data.normals.push_back(triangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(triangulation.UniqueNumbers[normal.Z()]);
        }

        for (int i = 0; i < 3; i++) {
            data.colors.push_back(clr[0]);
            data.colors.push_back(clr[1]);
            data.colors.push_back(clr[2]);
        }

    }
    return data;
}