#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void penWidth();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    void penColor();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionCursor_triggered();

    void on_actionPen_triggered();

    void on_actionLine_triggered();

    void on_actionRectangle_triggered();

    void on_actionEllipse_triggered();

   // void on_actionset_Width_triggered();

    void on_actionOpen_triggered();

    //void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionPen_Width_triggered();

    void on_actionPen_Color_triggered();

    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
