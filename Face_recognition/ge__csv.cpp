#include "ge__csv.h"
#include "ui_ge__csv.h"


Ge__CSV::Ge__CSV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ge__CSV)
{
    ui->setupUi(this);
    connect(ui->tocsv,&QPushButton::clicked,this,&Ge__CSV::callexe);
}

void Ge__CSV::callexe()
{
    QProcess p(0);
    QString command = "./collect_face_tocsv.exe";       //调用外联的.exe程序生成.csv文件
    p.start(command);
    p.waitForFinished();
    string result = "Finished";
    QString Result = QString::fromStdString(result);
    ui->textBrowser->clear();
    ui->textBrowser->setText(Result);
    //cout<<"Finished"<<endl;
}

Ge__CSV::~Ge__CSV()
{
    delete ui;
}

void Ge__CSV::on_pushButton_clicked()
{
    QProcess p(0);
    QString command = "./file.exe";     //调用外联的.exe程序生成.csv文件
    p.start(command);
    p.waitForFinished();
    string result = "Your images have finished";
    QString Result = QString::fromStdString(result);
    ui->textBrowser->clear();
    ui->textBrowser->setText(Result);
    /*
    typedef void (*pdealfile)(string filepath,string distall);
    HINSTANCE hDLL;
    pdealfile dealfile;
    hDLL = LoadLibrary("deal_file.dll");//加载动态链接库deal_file.all文件
    dealfile = (pdealfile)GetProcAddress(hDLL,"dealfile");
    dealfile("E:/The Program/Picture/The1","E:/The Program/Picture/The1/image.csv");
    string result = "Finished";
    QString Result = QString::fromStdString(result);
    ui->textBrowser->clear();
    ui->textBrowser->setText(Result);
    FreeLibrary(hDLL);//卸载deal_file.dll文件；
    */
    /*
    typedef void (*Fun)(string,string); //定义函数指针，以备调用
    QLibrary mylib("./DLL1.dll");
    if(mylib.load())
    {
        Fun open = (Fun)mylib.resolve("dealfile");
        if(open)
        {
            QMessageBox::information(NULL,"OK","DLL load is OK!");
            open("E:/The Program/Picture/The1","E:/The Program/Picture/The1/image.csv");
            string result = "open success!...";
            QString Result = QString::fromStdString(result);
            ui->textBrowser->setText(Result);
        }
        string result = "load DLL success!...";
        QString Result = QString::fromStdString(result);
        ui->textBrowser->clear();
        ui->textBrowser->setText(Result);
    }
    else
    {
        string result = "load DLL failed!...";
        QString Result = QString::fromStdString(result);
        ui->textBrowser->clear();
        ui->textBrowser->setText(Result);
    }
    */
    //dealfile("E:/The Program/Picture/The1","E:/The Program/Picture/The1/image.csv");
    /*
    dealfile("E:/The Program/Picture/The1","E:/The Program/Picture/The1/image.csv");
    string result = "load DLL success!...";
    QString Result = QString::fromStdString(result);
    ui->textBrowser->clear();
    ui->textBrowser->setText(Result);*/
}
