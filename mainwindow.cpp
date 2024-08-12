
/* Project headers */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optiondialog.h"

/* Qt headers */
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QPushButton>
#include <QStatusBar>

#include <QDirIterator>

/* Vtk headers */
#include <vtkSmartPointer.h>
#include <vtkCylinderSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSTLReader.h>
#include <vtkwidget.h>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    connect(ui->actionOpen_File, &QAction::triggered, this, &MainWindow::openFile);

    /* Initialize VTKWidget */
    vtkWidget = new VTKWidget(this); // Create a new VTKWidget instance

    /* Set the VTKWidget as the central widget or place it in a layout */
    setCentralWidget(vtkWidget); // This will set the VTKWidget as the main display area
     

    vtkWidget->initialise();
    


    /* Link TreeView to Model */
    this->partList = new ModelPartList("PartsList");
    ui->treeView->setModel(this->partList);

    /* Create a root item in the tree. */
    QModelIndex root = partList->index(0,0,QModelIndex());
    QModelIndex childIndex = partList->appendChild(root, { QVariant("Model"), QVariant("true")});


    /* Setup Renderer */
}

MainWindow::~MainWindow()
{
    delete ui;
    delete vtkWidget; // Clean up VTKWidget
}

void MainWindow::addNewItem() {
    // Get index of currently selected item
    QModelIndex index = ui->treeView->currentIndex();

    // Add a child
    QModelIndex childIndex = partList->appendChild(index, { QVariant("New"), QVariant("true") });

}


void MainWindow::editSelectedItem() {
    
    /* Get selected item */
    QModelIndex index = ui->treeView->currentIndex();

    /* Check that something was actually selected before right click ... */
    if (!index.isValid()) {
        return;
    }

    /* Get pointer to selected part */
    ModelPart* part = static_cast<ModelPart*>(index.internalPointer());

    /* Run a dialog to change colour ... */
}


/* These two functions can be used to add all items in the tree view to the VTK view */
void MainWindow::updateRender() {

    // Remove all items from VTK Renderer
    // NEEDS IMPLEMENTING

    updateRenderFromTree(partList->index(0, 0, QModelIndex()));
    vtkWidget->updateRender(); // Call a method from VTKWidget to refresh the view
}


void MainWindow::updateRenderFromTree( const QModelIndex& index ){
    
    if( index.isValid() ) {
        /* Get item at this stage of the tree */
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());
        vtkWidget->addActor(selectedPart);
        
        /* Add it to the VTK renderer */
        // NEEDS COMPLETING
    }


    if( !partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren) )
    {
        return;
    }

    int rows = partList->rowCount( index );
    for (int i = 0; i < rows; i++) {
        updateRenderFromTree(partList->index(i, 0, index));
    }
        
}

void MainWindow::openFile() {
    // Open a file dialog to select an STL file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "", tr("STL Files (*.stl)"));

    if (fileName.isEmpty()) {
        return; // If no file was selected, return
    }

    // Add the filename to the treeview
    QModelIndex root = partList->index(0, 0, QModelIndex());
    partList->appendChild(root, { QVariant(fileName), QVariant("true") });

    // Create a ModelPart and load the STL file
    ModelPart* newPart = new ModelPart({ QVariant(fileName) });
    newPart->loadSTL(fileName);

    // Add the ModelPart to the VTKWidget and render it
    vtkWidget->addActor(newPart);
    vtkWidget->renderModel();
}

/* These two functions can be used to add all items in the tree view to the VR view */
void MainWindow::addActorsToVR() {
    addActorsToVR_recursive(partList->index(0, 0, QModelIndex()));
}


void MainWindow::addActorsToVR_recursive(const QModelIndex& index)
{
    if (index.isValid()) {
        /* Get item at this stage of the tree */
        ModelPart* selectedPart = static_cast<ModelPart*>(index.internalPointer());

        /* Add it to the VTK renderer */
        // NEEDS COMPLETING
        
    }

    if (!partList->hasChildren(index) || (index.flags() & Qt::ItemNeverHasChildren)) {
        return;
    }


    int rows = partList->rowCount(index);
    for (int i = 0; i < rows; i++) {
        addActorsToVR_recursive(partList->index(i, 0, index));
    }
}


