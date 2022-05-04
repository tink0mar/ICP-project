#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_class_diagram_triggered();

    void on_actionNew_sequence_diagram_triggered();

    void on_actionLoad_class_diagram_triggered();

    void on_actionLoad_sequence_diagram_triggered();

    void on_actionSave_diagram_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
