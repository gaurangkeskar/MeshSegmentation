#include "MeshSegmentation.h"
#include <QFileDialog>
#include <QGridLayout>
#include "STLReader.h"
using namespace MeshReader;

MeshSegmentation::MeshSegmentation(QWidget *parent)
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
    
    QGridLayout* layout = new QGridLayout(this);
    
    layout->addWidget(loadFile, 0, 0);
    layout->addWidget(segment, 0, 1);
    layout->addWidget(openglWidget, 1, 0,1,2);

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
    
}

void MeshSegmentation::loadSTLFile(const QString& filePath, Triangulation& inputTriangulation, OpenGlWidget* openglWidget)
{
    STLReader reader;
    reader.read(filePath.toStdString(), inputTriangulation);
    OpenGlWidget::Data data = convertTriangulationToGraphicsObject(inputTriangulation);
    openglWidget->setData(data);
}

OpenGlWidget::Data MeshSegmentation::convertTriangulationToGraphicsObject(const Triangulation& inTriangulation)
{
    OpenGlWidget::Data data;
    
    for (const Triangle & triangle : inTriangulation.Triangles)
    {
        for (const Point & point : triangle.Points())
        {
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.X()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Y()]);
            data.vertices.push_back(inTriangulation.UniqueNumbers[point.Z()]);
        }

        const Point& normal = triangle.Normal();

        for (size_t i = 0; i < 3; i++)
        {
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.X()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Y()]);
            data.normals.push_back(inTriangulation.UniqueNumbers[normal.Z()]);
        }
    }

    return data;
}