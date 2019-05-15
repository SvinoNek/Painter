#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Canvas");
    resize(500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCursor_triggered()
{
   ui->draw_area->setCursor();
   ui->actionCursor->setChecked(true);
   ui->actionPen->setChecked(false);
   ui->actionLine->setChecked(false);
   ui->actionRectangle->setChecked(false);
   ui->actionEllipse->setChecked(false);
}

void MainWindow::on_actionPen_triggered()
{
    ui->draw_area->setPen();
    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(true);
    ui->actionLine->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionEllipse->setChecked(false);
}

void MainWindow::on_actionLine_triggered()
{
    ui->draw_area->setLine();
    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(true);
    ui->actionRectangle->setChecked(false);
    ui->actionEllipse->setChecked(false);
}

void MainWindow::on_actionRectangle_triggered()
{
    ui->draw_area->setRectangle();
    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionRectangle->setChecked(true);
    ui->actionEllipse->setChecked(false);
}

void MainWindow::on_actionEllipse_triggered()
{
    ui->draw_area->setEllipse();
    ui->actionCursor->setChecked(false);
    ui->actionPen->setChecked(false);
    ui->actionLine->setChecked(false);
    ui->actionRectangle->setChecked(false);
    ui->actionEllipse->setChecked(true);
}


void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, "Canvas",
                                        "Select pen width:",
                                        ui->draw_area->penWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        ui->draw_area->setPenWidth(newWidth);
}

void MainWindow::on_actionOpen_triggered()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   "Open File", QDir::currentPath());
        if (!fileName.isEmpty())
            ui->draw_area->openImage(fileName);
    }
}


bool MainWindow::maybeSave()
{
    if (ui->draw_area->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, "Canvas",
                          "The image has been modified.\n"
                             "Do you want to save your changes?",
                          QMessageBox::Save | QMessageBox::Discard
                          | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled.png" + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, "Save As",
                               initialPath,
                               tr("png"));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return ui->draw_area->saveImage(fileName, fileFormat.constData());
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::on_actionPen_Width_triggered()
{
    penWidth();
}


void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(ui->draw_area->penColor());
    if (newColor.isValid())
        ui->draw_area->setPenColor(newColor);
}
void MainWindow::on_actionPen_Color_triggered()
{
    penColor();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::on_actionClear_triggered()
{
    ui->draw_area->clearImage();
}
