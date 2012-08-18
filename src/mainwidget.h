#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include <cstdio>

namespace Ui {
class MainWidget;
}

struct SLinesInfo
{
    // 为了方便所以构建结构体存储每一行的信息,避免对同一文件中的相同内容的行多次存储
    // 小项目测试,所以直接放在主类文件中
    int count;
    bool isSameset;

};

class MainWidget : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    
private slots:
    void isAllFilesChosen();

    void on_pushButton_reset_clicked();

    void on_pushButton_chooseFile1_clicked();

    void on_pushButton_chooseFile2_clicked();

    void on_pushButton_process_clicked();

private:
    bool backupFile(const QString & origFilePath, const QString & suffix=".bak");
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
