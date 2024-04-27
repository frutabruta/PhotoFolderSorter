#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() <<  Q_FUNC_INFO;

    vectorLineEdits.push_back(ui->lineEdit_path_0);
    vectorLineEdits.push_back(ui->lineEdit_path_1);
    vectorLineEdits.push_back(ui->lineEdit_path_2);
    vectorLineEdits.push_back(ui->lineEdit_path_3);
    vectorLineEdits.push_back(ui->lineEdit_path_4);


    initializePathVectors(vectorDestinationPath,5);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_selectFolder_clicked()
{
    soubor.pathFirstFile=this->loadFromFile();

    ui->label_cestaSlozky->setText(slozka.path());
    //pictureToLabel(soubor.pathFirstFile,ui->label_obrazek);
    //   ui->lineEdit_cestaSouboru->setText(soubor.cestaSouboruHex);
}


QUrl MainWindow::loadFromFile()
{
    qDebug() <<  Q_FUNC_INFO;
    QFileDialog qFileDialog;
    QUrl prazdnaUrl;
    QUrl result;

    slozka.setPath(qFileDialog.getExistingDirectory());

    QStringList filters;
    filters << "*.jpg" << "*.png" << "*.jpeg";
    slozka.setNameFilters(filters);

    soubory.clear();
    soubory=slozka.entryList();
    qDebug()<<"Delka "<<soubory.length()<<" "<<slozka.dirName();

    if(soubory.count()<=0)
    {
        emptyPhoto();
        QMessageBox msgBox;
        msgBox.setText("slozka neobsahuje obrazky");
        msgBox.exec();
    }
    else
    {
        drawImageWithIndex(index);
        for(int i=0;i<soubory.length(); i++)
        {
            qDebug()<<soubory.at(i);
        }

    }
    return result;
}

void MainWindow::pictureToLabel(QUrl input, QLabel* label)
{
    qDebug() <<  Q_FUNC_INFO;
    QPixmap pixmap(input.toLocalFile());
    label->setPixmap( pixmap.scaled( label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation) ); // https://stackoverflow.com/a/61851111
    label->setMask(pixmap.mask());
    label->show();

}

void MainWindow::pictureToLabel2(QString folder, QString soubor, QLabel* label)
{
    qDebug() <<  Q_FUNC_INFO;
    QString cestaObrazku=folder+"/"+soubor;
    qDebug()<<"cesta obrazku "<<cestaObrazku;
    QPixmap pixmap(cestaObrazku);
    label->setPixmap( pixmap.scaled( label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation) ); // https://stackoverflow.com/a/61851111
    label->setMask(pixmap.mask());
    label->show();
    ui->label_fileName->setText(soubory.at(index));
}


QString MainWindow::fileFolderByIndex(QStringList folder, int index)
{
    qDebug() <<  Q_FUNC_INFO;
    return folder.at(index);
}

void MainWindow::drawImageWithIndex(int i)
{
    qDebug() <<  Q_FUNC_INFO;
    if((i>=0)&&(i<soubory.count()))
    {
        pictureToLabel2(slozka.path(),soubory.at(i),ui->label_obrazek);

    }
    else
    {
        qDebug()<<"index mimo rozsah";
    }
}

void MainWindow::emptyPhoto()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->label_obrazek->setText(".");
}

void MainWindow::initializePathVectors(QVector<QDir> &inputVector, int lineCount)
{
    qDebug() <<  Q_FUNC_INFO;
    inputVector.clear();
    for(int i=0;i<lineCount;i++)
    {
        QDir emptyQDir;
        inputVector.push_back(emptyQDir);
    }
}


void MainWindow::loadDestinationPath(int index)
{
    qDebug() <<  Q_FUNC_INFO;
    QDir input=QFileDialog::getExistingDirectory();
    vectorDestinationPath[index]=input;

    vectorLineEdits.at(index)->setText(input.path());
}

void MainWindow::nextPhoto(int posun)
{
    qDebug() <<  Q_FUNC_INFO;
     qDebug()<<"index="<<index<<" count:"<<soubory.count();
    if(soubory.isEmpty())
    {
        emptyPhoto();
        return;
    }

    if(index<(soubory.count()-1))
    {
        index+=posun;
        qDebug()<<"index="<<index<<" count:"<<soubory.count();
        drawImageWithIndex(index);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("dalsi soubor neexistuje");
        msgBox.exec();
    }
}

void MainWindow::previousPhoto()
{
    qDebug() <<  Q_FUNC_INFO;

    if(index>0)
    {
        index--;
        drawImageWithIndex(index);
    }
}

bool MainWindow::fileExists(QDir directory, QString fileName)
{
    qDebug() <<  Q_FUNC_INFO;

    QString path=directory.path()+"/"+fileName;
    QFileInfo check_file(path); //zdroj:: https://stackoverflow.com/questions/10273816/how-to-check-whether-file-exists-in-qt-in-c
    if (check_file.exists() && check_file.isFile())
    {
        qDebug()<<"soubor "<<path<<" existuje";
        return true;
    }
    else
    {
        qDebug()<<"soubor "<<path<<" neexistuje";
        return false;
    }
}

void MainWindow::moveFile(QDir folder, QString soubor, QDir newFolder)
{
    qDebug() <<  Q_FUNC_INFO;
    if(soubory.isEmpty())
    {
        return;
    }
    QString oldPath=folder.path()+"/"+soubor;
    QString newPath=newFolder.path()+"/"+soubor;

    qDebug()<<"presouvam z "<<oldPath<<" do "<<newPath;

    if(QFile::rename(oldPath,newPath))
    {
        soubory.removeAt(index);

        nextPhoto(0);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("chyb presunu souboru");
        msgBox.exec();
    }

}


void MainWindow::on_pushButton_forward_clicked()
{
    nextPhoto(1);
}


void MainWindow::on_pushButton_back_clicked()
{
    previousPhoto();
}


void MainWindow::on_pushButton_first_clicked()
{
    if(!soubory.isEmpty())
    {
        index=0;
        drawImageWithIndex(index);
    }
}


void MainWindow::on_pushButton_last_clicked()
{
    if(!soubory.isEmpty())
    {
        index=soubory.count()-1;
        drawImageWithIndex(index);
    }
}


void MainWindow::on_pushButton_path_0_clicked()
{
    int buttonIndex=0;
    loadDestinationPath(buttonIndex);
}


void MainWindow::on_pushButton_path_1_clicked()
{
    int buttonIndex=1;
    loadDestinationPath(buttonIndex);
}


void MainWindow::on_pushButton_path_2_clicked()
{
    int buttonIndex=2;
    loadDestinationPath(buttonIndex);
}


void MainWindow::on_pushButton_path_3_clicked()
{
    int buttonIndex=3;
    loadDestinationPath(buttonIndex);
}


void MainWindow::on_pushButton_path_4_clicked()
{
    int buttonIndex=4;
    loadDestinationPath(buttonIndex);
}


void MainWindow::on_pushButton_move_0_clicked()
{
    if(soubory.isEmpty())
    {
        return;
    }
    int buttonIndex=0;
    moveFile(slozka,soubory.at(index), vectorDestinationPath.at(buttonIndex) );
}


void MainWindow::on_pushButton_move_1_clicked()
{
    int buttonIndex=1;
    if(soubory.isEmpty())
    {
        return;
    }
    moveFile(slozka,soubory.at(index), vectorDestinationPath.at(buttonIndex) );
}


void MainWindow::on_pushButton_move_2_clicked()
{
    if(soubory.isEmpty())
    {
        return;
    }
    int buttonIndex=2;
    moveFile(slozka,soubory.at(index), vectorDestinationPath.at(buttonIndex) );
}


void MainWindow::on_pushButton_move_3_clicked()
{
    if(soubory.isEmpty())
    {
        return;
    }
    int buttonIndex=3;
    moveFile(slozka,soubory.at(index), vectorDestinationPath.at(buttonIndex) );
}


void MainWindow::on_pushButton_move_4_clicked()
{
    if(soubory.isEmpty())
    {
        return;
    }
    int buttonIndex=4;
    moveFile(slozka,soubory.at(index), vectorDestinationPath.at(buttonIndex) );
}

