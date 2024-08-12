#ifndef VTKWIDGET_H
#define VTKWIDGET_H
#include <QWidget>
#include <QVTKOpenGLWidget.h>  // Use QVTKOpenGLWidget for VTK 9.x

class VTKWidget : public QVTKOpenGLWidget
{
    Q_OBJECT
public:
    explicit VTKWidget(QWidget *parent = nullptr);
    ~VTKWidget() override;
    void initialize();
    void renderModel();

private:
    vtkRenderer *renderer;
    vtkRenderWindow *renderWindow;
    vtkRenderWindowInteractor *renderWindowInteractor;
};
#endif // VTKWIDGET_H
