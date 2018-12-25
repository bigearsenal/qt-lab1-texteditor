#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_save,SIGNAL(triggered()), this, SLOT(save()));
}

void MainWindow::save() {
    // Сохранить текст к одному переменному
    QString text = ui->textEdit->toPlainText();

    // Не сохранить в файл если текст пустой
    if (text.isEmpty()) return;

    // Открыть диалог для сохранения в файл
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Сохранить тесктовый файл"), "",
            tr("Тесктовый файл (*.txt)"));

    // Проверить имя файла и сохранить
    printf("%s", fileName.toLatin1().data());
    if (fileName.isEmpty()) return;
    else {
        QFile file(fileName);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            printf("Не мог бы открыть файл");
            return;
        }
        QDataStream out(&file);
        out << text;
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
