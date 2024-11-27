#include "MeshSegmentation.h"
#include <QFileDialog>
#include <QGridLayout>
#include "STLReader.h"
#include "Segmenter.h"
#include "PlanarSegment.h"
#include "SphericalSegment.h"
#include <random>
using namespace MeshReader;

MeshSegmentation::MeshSegmentation(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(loadFile, &QPushButton::clicked, this, &MeshSegmentation::onLoadFileClick);
    connect(segment, &QPushButton::clicked, this, &MeshSegmentation::onSegmentation);
    connect(planarCheckbox, &QCheckBox::toggled, this, &MeshSegmentation::onPlanarClick);
    connect(sphericalCheckbox, &QCheckBox::toggled, this, &MeshSegmentation::onSphericalClick);
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

    QGridLayout* layout = new QGridLayout(this);

    layout->addWidget(loadFile, 0, 0, 1, 3);
    layout->addWidget(segment, 0, 3, 1, 3);

    layout->addWidget(planarCheckbox, 1, 0, 1, 1);
    layout->addWidget(sphericalCheckbox, 1, 1, 1, 1);
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
    openglWidget->removeObject(1);
    PlanarSegment* planar;
    SphericalSegment* spherical;
    Segmenter segmenter;

    float random[3];
    float white[3] = { 1.0, 1.0, 1.0 };

    // Get planar surfaces as a pointer to vector of Triangulations
    std::vector<Triangulation>* segments = segmenter.processPlanarSurfaces(inputTriangulation);

    if (showPlanar)
    {
        planar = new PlanarSegment(*segments);  // Dereference pointer to pass the vector to PlanarSegment
        segments->clear();  // Clear the memory of the vector after use

        // Iterate through planar surfaces and render
        for (int i = 0; i < planar->planarSurfaces.size(); i++)
        {
            for (int i = 0; i < 3; i++) {
                random[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                random[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                random[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            }
            Triangulation triangulation = planar->planarSurfaces[i];
            OpenGlWidget::Data data = convertTriangulationToGraphicsObject(triangulation, random);
            data.drawStyle = OpenGlWidget::TRIANGLES;
            openglWidget->addObject(data);
        }

        delete planar;  // Free memory after use
    }

    // Get spherical surfaces as a pointer to vector of Triangulations
    segments = segmenter.processSphericalSurfaces(inputTriangulation);

    if (showSpherical)
    {
        spherical = new SphericalSegment(*segments);  // Dereference pointer to pass the vector to SphericalSegment
        segments->clear();  // Clear the memory of the vector after use

        // Iterate through spherical surfaces and render
        for (int i = 0; i < spherical->sphericalSurfaces.size(); i++)
        {
            for (int i = 0; i < 3; i++) {
                random[0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                random[1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
                random[2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            }
            Triangulation triangulation = spherical->sphericalSurfaces[i];
            OpenGlWidget::Data data = convertTriangulationToGraphicsObject(triangulation, random);
            data.drawStyle = OpenGlWidget::TRIANGLES;
            openglWidget->addObject(data);
        }

        delete spherical;  // Free memory after use
    }
    OpenGlWidget::Data data = convertTriangulationToGraphicsObject(inputTriangulation, white);
    data.drawStyle = OpenGlWidget::TRIANGLES;
    openglWidget->addObject(data);

    delete segments;  // Free the dynamically allocated vector memory
}


void MeshSegmentation::onPlanarClick()
{
    if (showPlanar)
        showPlanar = false;
    else
        showPlanar = true;
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
    float white[3] = { 1.0,0.0,0.0 };
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