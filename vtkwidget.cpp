#include "vtkwidget.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPolyData.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>

VTKWidget::VTKWidget(QWidget *parent) : QVTKOpenGLWidget(parent)
{
    // Initialize VTK components
    renderer = vtkRenderer::New();
    renderWindow = vtkRenderWindow::New();
    renderWindowInteractor = vtkRenderWindowInteractor::New();

    renderWindow->AddRenderer(renderer);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Set up the render window
    SetRenderWindow(renderWindow);

    initialise()
}

VTKWidget::~VTKWidget()
{
    // Clean up VTK objects
    renderer->Delete();
    renderWindow->Delete();
    renderWindowInteractor->Delete();
}

void VTKWidget::initialise()
{
    // Perform any additional initialization here
}

void VTKWidget::renderModel()
{
    // Render your VTK model here
    renderer->Render();
}

void VTKWidget::updateRender() {
    // Code to update the rendering based on the current state
    renderWindow->Render();
}

void VTKWidget::addActor(ModelPart* part) {
    vtkSmartPointer<vtkActor> actor = part->getActor();

    // Check if the actor is valid before adding it to the renderer
    if (actor) {
        // Add the actor to the renderer
        renderer->AddActor(actor);
    } else {
        // Handle the error or log it as needed
        qWarning("Failed to add actor: Invalid actor from ModelPart.");
    }
    
}
