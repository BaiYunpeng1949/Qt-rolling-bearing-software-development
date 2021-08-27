#include "sta_input.h"
#include "ui_sta_input.h"

#include<QString>
#include<QDebug>

//定义几个全局变量，方便参数传值
int sz;
double sD,sdm,salpha0,sfi,sfe,sFr,sFa,sM;



Sta_Input::Sta_Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sta_Input)
{
    ui->setupUi(this);

    //给各个都安装阴影
    setShadowsd(ui->lineEditstaz);
    setShadowsd(ui->lineEditstaalpha0);
    setShadowsd(ui->lineEditstaD);
    setShadowsd(ui->lineEditstadm);
    setShadowsd(ui->lineEditstafi);
    setShadowsd(ui->lineEditstafe);
    setShadowsd(ui->lineEditstaFa);
    setShadowsd(ui->lineEditstaFr);
    setShadowsd(ui->lineEditstaM);
    setShadowsd(ui->labeladdress);
    setShadowsd(ui->labelcurrentcase);

    //设置默认值
    ui->lineEditstaz->setText("16");
    ui->lineEditstaalpha0->setText("40");
    ui->lineEditstaD->setText("22.225");
    ui->lineEditstadm->setText("125.25");
    ui->lineEditstafi->setText("0.523");
    ui->lineEditstafe->setText("0.523");
    ui->lineEditstaFa->setText("17800");
    ui->lineEditstaFr->setText("17800");
    ui->lineEditstaM->setText("892330");

    //设置默认页面为第一页
    ui->tabWidgetsta->setCurrentWidget(ui->tabstanew);
    ui->tab_sta->setCurrentWidget(ui->tabsta1);

    //用定时器监控是否数据都填写进来了
    m_statimer = new QTimer(this);
    connect(m_statimer,&QTimer::timeout,
            [=]()
            {
            //lamda写法，判断是否都写上了
            QString inputz = ui->lineEditstaz->text();
            QString inputD = ui->lineEditstaD->text();
            QString inputdm = ui->lineEditstadm->text();
            QString inputalpha0 = ui->lineEditstaalpha0->text();
            QString inputfi = ui->lineEditstafi->text();
            QString inputfe = ui->lineEditstafe->text();
            QString inputFr = ui->lineEditstaFr->text();
            QString inputFa = ui->lineEditstaFa->text();
            QString inputM = ui->lineEditstaM->text();
            if(inputz.isEmpty() || inputD.isEmpty() || inputdm.isEmpty()|| inputalpha0.isEmpty()|| inputfi.isEmpty()|| inputfe.isEmpty()|| inputFr.isEmpty()|| inputFa.isEmpty()|| inputM.isEmpty())
            {
            ui->pBstayes->setEnabled(false);
            }
            else
            {
                ui->pBstayes->setEnabled(true);
            }

            }
            );
    m_statimer->start(500);

    //建立窗口的时候初始化控件
    ui->pushBottonconfig->setEnabled(false);
    ui->pushBottonsaveas->setEnabled(false);

}


Sta_Input::~Sta_Input()
{
    delete ui;
}

//读取数据界面
void Sta_Input::on_pBstayes_clicked()
{
    //读取数据
    QString mid1 = ui->lineEditstaz->text();
    sz = mid1.toInt();
    QString mid2 = ui->lineEditstaD->text();
    sD = mid2.toDouble();
    QString mid3 = ui->lineEditstadm->text();
    sdm = mid3.toDouble();
    QString mid4 = ui->lineEditstafe->text();
    sfe = mid4.toDouble();
    QString mid5 = ui->lineEditstafi->text();
    sfi = mid5.toDouble();
    QString mid6 = ui->lineEditstaFr->text();
    sFr = mid6.toDouble();
    QString mid7 = ui->lineEditstaFa->text();
    sFa = mid7.toDouble();
    QString mid8 = ui->lineEditstaalpha0->text();
    salpha0 = mid8.toDouble();
    QString mid9 = ui->lineEditstaM->text();
    sM = mid9.toDouble();
    //读取完了发送以信号的形式发送数据
    emit stainput(sz,sD,sdm,salpha0,sfi,sfe,sFr,sFa,sM);
    //然后把自己关了
    this->hide();
}


//清零按钮
void Sta_Input::on_pBstaclear_clicked()
{
    //ui->lineEditstaz->clear();
    //ui->lineEditstaalpha0->clear();
    //ui->lineEditstaD->clear();
    //ui->lineEditstadm->clear();
    //ui->lineEditstafi->clear();
    //ui->lineEditstafe->clear();
    //ui->lineEditstaFa->clear();
    //ui->lineEditstaFr->clear();
    //ui->lineEditstaM->clear();

    //设置默认值
    ui->lineEditstaz->setText("16");
    ui->lineEditstaalpha0->setText("40");
    ui->lineEditstaD->setText("22.225");
    ui->lineEditstadm->setText("125.25");
    ui->lineEditstafi->setText("0.523");
    ui->lineEditstafe->setText("0.523");
    ui->lineEditstaFa->setText("17800");
    ui->lineEditstaFr->setText("17800");
    ui->lineEditstaM->setText("892330");
}

//退出不保存按钮
//void Sta_Input::on_pBstacancel_clicked()
//{
//    this->hide();
//}

//打开文档按钮，浏览
void Sta_Input::on_pushButtonopenfile_clicked()
{
    //设置str编码类型
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    m_inputopenfile_name = QFileDialog::getOpenFileName(this,"读取文件",".","数据输入文件(*.stain)");
    //路径文件写入
    ui->labeladdress->setText(m_inputopenfile_name);

    //开始读取
    //读取txt文档中的数据
    QFile File(m_inputopenfile_name);
    if(!File.open(QIODevice::ReadOnly | QIODevice ::Text))
        return;
    QTextStream in(&File);
    while(!File.atEnd())
    {
        //读取全部，保存为字符串形式
        m_linestring = in.readAll();
        m_list_items = m_linestring.split("\n");
        //对读取的行数据进行处理的伪代码
        //process_line(m_linestring);
    }

    //当前算例写入
    QStringList Fr,Fa;
    Fr = m_list_items[1].split("\t");
    Fa = m_list_items[2].split("\t");
    ui->labelcurrentcase->setText("7008ACB,"" Fr" + Fr[1] + "N,"" Fa" +Fa[1] +"N");

    //QTableWidget 表格创建

    //规范行列数
    ui->tableWidgetsta->setColumnCount(3);
    ui->tableWidgetsta->setRowCount(ROWNUMBERS);

    //设置可见情况
    ui->tableWidgetsta->verticalHeader()->setVisible(false);
    ui->tableWidgetsta->horizontalHeader()->setVisible(true);

    //第一个表头
    QTableWidgetItem *item0 = new QTableWidgetItem();
    item0->setText("变量名称（常用符号）");
    item0->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    ui->tableWidgetsta->setHorizontalHeaderItem(0,item0);
    //第二个水平表头
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item1->setText("值");
    item1->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setHorizontalHeaderItem(1,item1);
    //第三个水平表头
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setText("单位");
    item2->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    ui->tableWidgetsta->setHorizontalHeaderItem(2,item2);


    //人为初始化吧，没办法了
    QTableWidgetItem *itemheader1 = new QTableWidgetItem();
    itemheader1->setText("(1)工况条件");
    itemheader1->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(0,0,itemheader1);

    QTableWidgetItem *itemFr = new QTableWidgetItem();
    itemFr->setText("径向载荷(Fr)");
    itemFr->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(1,0,itemFr);

    QTableWidgetItem *itemFa = new QTableWidgetItem();
    itemFa->setText("轴向载荷(Fa)");
    itemFa->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(2,0,itemFa);

    QTableWidgetItem *itemM = new QTableWidgetItem();
    itemM->setText("力矩(M)");
    itemM->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(3,0,itemM);

    QTableWidgetItem *itemheader2 = new QTableWidgetItem();
    itemheader2->setText("(2)结构参数");
    itemheader2->setTextAlignment(Qt::AlignLeft |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(4,0,itemheader2);

    QTableWidgetItem *itemZ = new QTableWidgetItem();
    itemZ->setText("钢球个数(Z)");
    itemZ->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(5,0,itemZ);

    QTableWidgetItem *itemD = new QTableWidgetItem();
    itemD->setText("钢球直径(D)");
    itemD->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(6,0,itemD);

    QTableWidgetItem *itemdm = new QTableWidgetItem();
    itemdm->setText("内圈直径(dm)");
    itemdm->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(7,0,itemdm);

    QTableWidgetItem *itemalpha0 = new QTableWidgetItem();
    itemalpha0->setText("初始接触角");
    itemalpha0->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(8,0,itemalpha0);

    QTableWidgetItem *itemfi = new QTableWidgetItem();
    itemfi->setText("内圈沟渠率半径系数");
    itemfi->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(9,0,itemfi);

    QTableWidgetItem *itemfe = new QTableWidgetItem();
    itemfe->setText("外圈沟渠率半径系数");
    itemfe->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    ui->tableWidgetsta->setItem(10,0,itemfe);


    ui->tableWidgetsta->setItem(1,2,new QTableWidgetItem("N"));
    ui->tableWidgetsta->setItem(2,2,new QTableWidgetItem("N"));
    ui->tableWidgetsta->setItem(3,2,new QTableWidgetItem("N*mm"));
    ui->tableWidgetsta->setItem(6,2,new QTableWidgetItem("mm"));
    ui->tableWidgetsta->setItem(7,2,new QTableWidgetItem("mm"));
    ui->tableWidgetsta->setItem(8,2,new QTableWidgetItem("°"));

    for(int row_tableview = 0; row_tableview < ROWNUMBERS;row_tableview++)
    {
        QStringList thisrow = m_list_items[row_tableview].split("\t");
        QString printout = thisrow[1];
        ui->tableWidgetsta->setItem(row_tableview,1,new QTableWidgetItem(printout));
        //设置字符位置
        ui->tableWidgetsta->item(row_tableview,1)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }

    //列宽设置
    ui->tableWidgetsta->setColumnWidth(0,200);
    ui->tableWidgetsta->setColumnWidth(1,150);
    ui->tableWidgetsta->setColumnWidth(2,100);

    //读取成功以后释放按钮
    ui->pushBottonconfig->setEnabled(true);
    ui->pushBottonsaveas->setEnabled(true);

}

//点击了配置转到实时输入界面部分，并且更改数据到界面
void Sta_Input::on_pushBottonconfig_clicked()
{
    ui->tabWidgetsta->setCurrentWidget(ui->tabstanew);
    ui->tab_sta->setCurrentWidget(ui->tabsta1);
    //取值
    m_sta_Fr = ui->tableWidgetsta->item(1, 1)->text();
    m_sta_Fa = ui->tableWidgetsta->item(2, 1)->text();
    m_sta_M = ui->tableWidgetsta->item(3, 1)->text();
    m_sta_z = ui->tableWidgetsta->item(5, 1)->text();
    m_sta_D = ui->tableWidgetsta->item(6, 1)->text();
    m_sta_dm = ui->tableWidgetsta->item(7, 1)->text();
    m_sta_alpha0 = ui->tableWidgetsta->item(8, 1)->text();
    m_sta_fi = ui->tableWidgetsta->item(9, 1)->text();
    m_sta_fe = ui->tableWidgetsta->item(10, 1)->text();

    //赋值
    ui->lineEditstaz->setText(m_sta_z);
    ui->lineEditstaalpha0->setText(m_sta_alpha0);
    ui->lineEditstaD->setText(m_sta_D);
    ui->lineEditstadm->setText(m_sta_dm);
    ui->lineEditstafi->setText(m_sta_fi);
    ui->lineEditstafe->setText(m_sta_fe);
    ui->lineEditstaFa->setText(m_sta_Fa);
    ui->lineEditstaFr->setText(m_sta_Fr);
    ui->lineEditstaM->setText(m_sta_M);
}

//点击了另存为按钮，存储成不能编辑只能读取的excel文件
void Sta_Input::on_pushBottonsaveas_clicked()
{
    //取值，以防万一
    m_sta_Fr = ui->tableWidgetsta->item(1, 1)->text();
    m_sta_Fa = ui->tableWidgetsta->item(2, 1)->text();
    m_sta_M = ui->tableWidgetsta->item(3, 1)->text();
    m_sta_z = ui->tableWidgetsta->item(5, 1)->text();
    m_sta_D = ui->tableWidgetsta->item(6, 1)->text();
    m_sta_dm = ui->tableWidgetsta->item(7, 1)->text();
    m_sta_alpha0 = ui->tableWidgetsta->item(8, 1)->text();
    m_sta_fi = ui->tableWidgetsta->item(9, 1)->text();
    m_sta_fe = ui->tableWidgetsta->item(10, 1)->text();

    //确认保存路径
    m_inputsavefile_name = QFileDialog::getSaveFileName(this,"保存文件",".","数据输入文件(*.stain)");

    QFile datasavesta_1_file(m_inputsavefile_name);
    if (!datasavesta_1_file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
    QTextStream stadata_1_out(&datasavesta_1_file);

    //设置输出文字格式，使得中文也能输出
    //QSettings settings(datasavefile_name, QSettings::IniFormat);
    //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    stadata_1_out.setCodec(QTextCodec::codecForName("utf-8"));

    //开始写入,按照标准格式
    stadata_1_out  <<tr("(1)工况条件")<<"\t"<<tr(" ")<<"\t"<<tr(" ")<<"\n";
    stadata_1_out  <<tr("径向载荷(Fr) =")<<"\t"<<m_sta_Fr <<"\t"<<tr("N")<< "\n";
    stadata_1_out  <<tr("轴向载荷(Fa) =")<<"\t"<< m_sta_Fa <<"\t"<<tr("N")<< "\n";
    stadata_1_out  <<tr("力矩(M) =")<<"\t"<< m_sta_M <<"\t"<<tr("N*mm")<<"\n";
    stadata_1_out  <<tr("(2)结构参数 ")<<"\t"<<tr(" ")<<"\t"<<tr(" ")<< "\n";
    stadata_1_out  <<tr("钢球个数(Z) =")<<"\t"<< m_sta_z <<"\t"<<tr(" ")<<"\n";
    stadata_1_out  <<tr("钢球直径(D) =")<<"\t"<< m_sta_D <<"\t"<<tr("mm")<< "\n";
    stadata_1_out  <<tr("内圈直径(dm) =")<<"\t"<< m_sta_dm <<"\t"<<tr("mm")<< "\n";
    stadata_1_out  <<tr("初始接触角 =")<<"\t"<< m_sta_alpha0 <<"\t"<<tr("°")<< "\n";
    stadata_1_out  <<tr("内圈沟渠率半径系数 =")<<"\t"<< m_sta_fi  <<"\t"<<tr(" ")<< "\n";
    stadata_1_out  <<tr("外圈沟渠率半径系数 =")<<"\t"<< m_sta_fe  <<"\t"<<tr(" ")<< "\n";

    datasavesta_1_file.close();
}

//设置阴影子函数
void Sta_Input::setShadowsd(QLineEdit *lineedit)
{
    //设置边框的阴影效果
    m_sdeffect = new QGraphicsDropShadowEffect(lineedit);
    m_sdeffect->setBlurRadius(5);
    m_sdeffect->setColor(Qt::black);
    m_sdeffect->setOffset(0,0);
    //把阴影给需要的lineedit
    lineedit->setGraphicsEffect(m_sdeffect);
}
