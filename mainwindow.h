#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QFileDialog>
#include <QBitmap>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

#include "soubor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void drawImageWithIndex(int i);
private slots:
    void on_pushButton_selectFolder_clicked();

    void on_pushButton_forward_clicked();

    void on_pushButton_last_clicked();

    void on_pushButton_first_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_move_1_clicked();

    void on_pushButton_path_0_clicked();

    void on_pushButton_path_1_clicked();

    void on_pushButton_path_2_clicked();

    void on_pushButton_path_3_clicked();

    void on_pushButton_path_4_clicked();


    void on_pushButton_move_0_clicked();

    void on_pushButton_move_2_clicked();

    void on_pushButton_move_3_clicked();

    void on_pushButton_move_4_clicked();

private:
    Ui::MainWindow *ui;


    Soubor soubor;
    QStringList soubory;
    QUrl loadFromFile();
    QDir slozka;

    int index=0;

    void pictureToLabel(QUrl input, QLabel *label);
    QString test="";
    void pictureToLabel2(QString folder, QString soubor, QLabel *label);
    QString fileFolderByIndex(QStringList folder, int index);

    QVector<QDir> vectorDestinationPath;
    QVector<QLineEdit*> vectorLineEdits;
    void loadDestinationPath(int index);
    void initializePathVectors(QVector<QDir> &inputVector, int lineCount);
    void moveFile(QDir folder, QString soubor, QDir newFolder);
    void nextPhoto(int posun);
    void emptyPhoto();
    void previousPhoto();
    bool fileExists(QDir directory, QString fileName);
};
#endif // MAINWINDOW_H
