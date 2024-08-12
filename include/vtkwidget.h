#ifndef VTKWIDGET_H
#define VTKWIDGET_H
#include <QWidget>
#include <QVTKOpenGLWidget.h>  // Use QVTKOpenGLWidget for VTK 9.x
#include <modelpart.h>
class VTKWidget : public QVTKOpenGLWidget
{
    Q_OBJECT
public:
    explicit VTKWidget(QWidget *parent = nullptr);
    ~VTKWidget() override;
    void initialise();
    void renderModel();
    void updateRender(); // Method to update rendering
    void addActor(ModelPart* part); // Method to add VTK actors

private:
    vtkRenderer *renderer;
    vtkRenderWindow *renderWindow;
    vtkRenderWindowInteractor *renderWindowInteractor;
};
#endif // VTKWIDGET_H
