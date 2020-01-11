#include "deal_file.h"
#include "ui_deal_file.h"

Deal_File::Deal_File(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deal_File)
{
    ui->setupUi(this);
}

Deal_File::~Deal_File()
{
    delete ui;
}

void Deal_File::on_readfile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", "./collectface");
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);//以只读的方式打开文件
        if(isok == true)
        {
            QByteArray array;
            while(file.atEnd() == false)
            {
                array += file.readLine();//将文件中的读取的内容保存在字节数组中。
            }
            ui->textEdit->setText(array);
        }
        file.close();//文件读取完毕后关闭文件。
    }
}

void Deal_File::on_pushButton_2_clicked()
{
   QString filename = QFileDialog::getSaveFileName(this, "保存文件", "./collectface");
   if(filename.isEmpty() == false)
   {
       QFile file(filename);
       bool isok = file.open(QIODevice::WriteOnly);
       if(isok == true)
       {
           QString str = ui->textEdit->toPlainText();
           file.write(str.toUtf8());
       }
       file.close();
   }
}
