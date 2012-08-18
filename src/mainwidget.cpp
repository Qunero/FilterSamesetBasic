#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::isAllFilesChosen()
{
    // 检查是否两个文件都已经指定,设置好两个文件后才可以process
    if(this->ui->lineEdit_file1->text().isEmpty() ||
            this->ui->lineEdit_file2->text().isEmpty()){
        this->ui->pushButton_process->setEnabled(false);
    }else{
        this->ui->pushButton_process->setEnabled(true);
    }
}

void MainWidget::on_pushButton_reset_clicked()
{
    // 清理已选文件
    this->ui->lineEdit_file1->clear();
    this->ui->lineEdit_file2->clear();
}

void MainWidget::on_pushButton_chooseFile1_clicked()
{
    // 弹出文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("choose the first File"),
                                                    ".",
                                                    tr("One file(*.1.txt);;All files(*)"));
    if(! fileName.isNull()){
        // 选择了文件,更新显示并执行状态检查
        // 路径变化后,由设置的信号槽机制调用isAllFilesChosen函数进行检查
        this->ui->lineEdit_file1->setText(fileName);
    }


}

void MainWidget::on_pushButton_chooseFile2_clicked()
{
    // 弹出文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("choose the second File"),
                                                    ".",
                                                    tr("One file(*.2.txt);;All files(*)"));
    if(! fileName.isNull()){
        // 选择了文件,更新显示并执行状态检查
        // 路径变化后,由设置的信号槽机制调用isAllFilesChosen函数进行检查
        this->ui->lineEdit_file2->setText(fileName);
    }
}

void MainWidget::on_pushButton_process_clicked()
{
    // 文件核心处理过程
    // 01: 进行文件备份操作
    QString firstFilePath = this->ui->lineEdit_file1->text();
    QString secondFilePath = this->ui->lineEdit_file2->text();
    backupFile(firstFilePath, ".bak");
    backupFile(secondFilePath, ".bak");

    // 02: 读入文件并去除第二个文件中相同内容
    QHash<QString, SLinesInfo> hashFirstFileInfo;
    QFile firstFileIn(firstFilePath + ".bak");
    QFile firstFileOut(firstFilePath);
    QFile secondFileIn(secondFilePath + ".bak");
    QFile secondFileOut(secondFilePath);
    QString strLine;
    //SLinesInfo sOneLine;
    //sOneLine.isSameset = false;

    if(firstFileIn.open(QIODevice::ReadOnly | QIODevice::Text)){
        // 读取文件, 存入hash
        QTextStream in(&firstFileIn);
        while(! in.atEnd()){
            strLine = in.readLine();
            if(strLine.isEmpty()){
                // 忽略空白行
                continue;
            }

            hashFirstFileInfo[strLine].count ++ ;
            hashFirstFileInfo[strLine].isSameset = false;
        }
        firstFileIn.close(); // 读完数据后关闭
    }else{
        // 读取失败, 记录错误
        std::cerr << "Can't read file: "
                  << qPrintable(firstFileIn.errorString()) << std::endl;
        return;
    } // end if firstFileIn


    // 在读取第二个文件的时候判断是否为重复的行,非重复的直接输出,降低内存消耗
    if(secondFileIn.open(QIODevice::ReadOnly | QIODevice::Text)){
        // 打开输出文件
        if(secondFileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
            // 成功打开, 继续后续操作
        }else{
            // 读取失败, 记录错误
            std::cerr << "Can't write file: "
                      << qPrintable(secondFileOut.errorString()) << std::endl;
            return;
        }
        QTextStream in(&secondFileIn);
        QTextStream out(&secondFileOut);
        while(! in.atEnd()){
            strLine = in.readLine();
            if(strLine.isEmpty()){
                // 忽略空白行
                continue;
            }

            if(hashFirstFileInfo.contains(strLine)){
                // 此行为文件1中重复出现的, 记录重复信息, 忽略该行
                hashFirstFileInfo[strLine].isSameset = true;
            }else{
                out << strLine << endl;
            }
        } // end while
        secondFileIn.close();
        secondFileOut.close();
    }else{
        // 读取失败, 记录错误
        std::cerr << "Can't read file: "
                  << qPrintable(secondFileIn.errorString()) << std::endl;
        return;
    } // end if secondFileIn


    // 03: 输出第一个文件的非重复结果
    if(firstFileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
        // 成功打开, 继续后续操作
    }else{
        // 读取失败, 记录错误
        std::cerr << "Can't write file: "
                  << qPrintable(firstFileOut.errorString()) << std::endl;
        return;
    }

    QTextStream out(&firstFileOut);
    QHashIterator<QString, SLinesInfo> it(hashFirstFileInfo);
    while(it.hasNext()){
        it.next();
        if(it.value().isSameset){
            // 忽略该行
        }else{
            // 输出文件一中出现多次的行;主要对两个文件去除共有的,但各文件内部可能有重复
            for(int i=0; i<it.value().count; i++){
                out << it.key() << endl;
            }
        }
    }
    firstFileOut.close();

    // 成功处理文件后,临时将其设为不可用,除非选取了新的文件
    this->ui->pushButton_process->setEnabled(false);
}

bool MainWidget::backupFile(const QString & origFilePath, const QString & suffix){
    QString backupPath = origFilePath + suffix;
    // 检查备份文件是否存在,若存在则先删除,防止备份失败
    // TODO: 对已经存在备份文件的情况设计其他可选方案;
    if(QFile::exists(backupPath)){
        QFile::remove(backupPath);
    }

    if(! QFile::copy(origFilePath, backupPath)){
        // TODO: 备份失败,可能需要产生提示供用户选择是否继续;或者实现其他方案;
        // 当前demo暂时不实现特殊处理方案;
        fprintf(stderr,"failed to backup file : %s\n", origFilePath.toAscii().data());
        return false;
    }
    return true;
}
