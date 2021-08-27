#include "simudyn_input.h"
#include "ui_simudyn_input.h"


SimuDyn_Input::SimuDyn_Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimuDyn_Input)
{
    ui->setupUi(this);

    //设置默认页面为第一页
    ui->tabWidgetsd->setCurrentWidget(ui->tabsdnew);
    ui->tabsimudyn->setCurrentWidget(ui->tabsd1);

    //给文本框设置样式，设置边框颜色
    //ui->lineEditsdD->setStyleSheet("QLineEdit{border:red}");
    //具体给设置阴影
    setShadowsta(ui->lineEditsdz);
    setShadowsta(ui->lineEditsdD);
    setShadowsta(ui->lineEditsdrho);
    setShadowsta(ui->lineEditsddm);
    setShadowsta(ui->lineEditsdv);
    setShadowsta(ui->lineEditsdE);
    setShadowsta(ui->lineEditsdFr);
    setShadowsta(ui->lineEditsdFa);
    setShadowsta(ui->lineEditsdM);
    setShadowsta(ui->lineEditsdo);
    setShadowsta(ui->lineEditsdo1);
    setShadowsta(ui->lineEditsdo2);
    //setShadowsta(ui->lineEditsdOR);
    setShadowsta(ui->lineEditsdalpha0);
    setShadowsta(ui->lineEditsdni);
    setShadowsta(ui->lineEditsdfe);
    setShadowsta(ui->lineEditsdfi);
    setShadowsta(ui->lineEditsderro);
    setShadowsta(ui->lineEditsdtimes);
    setShadowsta(ui->labeladdress);
    setShadowsta(ui->labelcurrentcase);

    //设置默认值
    ui->lineEditsdz->setText("19");
    ui->lineEditsdD->setText("12.5");
    ui->lineEditsdrho->setText("7850");
    ui->lineEditsddm->setText("77");
    ui->lineEditsdv->setText("0.3");
    ui->lineEditsdE->setText("206000");
    ui->lineEditsdFr->setText("10000");
    ui->lineEditsdFa->setText("20000");
    ui->lineEditsdM->setText("400");
    ui->lineEditsdo->setText("0.1");
    ui->lineEditsdo1->setText("0.2");
    ui->lineEditsdo2->setText("0.2");
    //ui->lineEditsdOR->setText("0"); //改为combobox模式
    ui->lineEditsdalpha0->setText("25");
    ui->lineEditsdni->setText("30000");
    ui->lineEditsdfe->setText("0.523");
    ui->lineEditsdfi->setText("0.523");
    ui->lineEditsderro->setText("0.000001");
    ui->lineEditsdtimes->setText("200");


    //用定时器监控是否数据都填写进来了
    m_sdtimer = new QTimer(this);
    connect(m_sdtimer,&QTimer::timeout,
            [=]()
            {
            //lamda写法，判断是否都写上了
            QString inputz = ui->lineEditsdz->text();
            QString inputD = ui->lineEditsdD->text();
            QString inputdm = ui->lineEditsddm->text();
            QString inputalpha0 = ui->lineEditsdalpha0->text();
            QString inputfi = ui->lineEditsdfi->text();
            QString inputfe = ui->lineEditsdfe->text();
            QString inputFr = ui->lineEditsdFr->text();
            QString inputFa = ui->lineEditsdFa->text();
            QString inputM = ui->lineEditsdM->text();
            QString inputo = ui->lineEditsdo->text();
            QString inputo1 = ui->lineEditsdo1->text();
            QString inputo2 = ui->lineEditsdo2->text();
            //QString inputOR = ui->lineEditsdOR->text(); //改为combobox模式
            QString inputni = ui->lineEditsdni->text();
            QString inputv = ui->lineEditsdv->text();
            QString inputE = ui->lineEditsdE->text();
            QString inputerro = ui->lineEditsderro->text();
            QString inputrho = ui->lineEditsdrho->text();
            QString inputnumbers = ui->lineEditsdtimes->text();

            if(inputz.isEmpty() || inputD.isEmpty() || inputdm.isEmpty()|| inputalpha0.isEmpty()|| inputfi.isEmpty()|| inputfe.isEmpty()|| inputFr.isEmpty()|| inputFa.isEmpty()|| inputM.isEmpty()|| inputo.isEmpty() || inputo1.isEmpty()|| inputo2.isEmpty()||/* inputOR.isEmpty()||*/ inputni.isEmpty()|| inputv.isEmpty() || inputE.isEmpty()|| inputerro.isEmpty()|| inputnumbers.isEmpty()|| inputrho.isEmpty())
            {
                ui->pBsdyes->setEnabled(false);
            }
            else
            {
                ui->pBsdyes->setEnabled(true);
            }

            }
            );
     m_sdtimer->start(500);

     //初始化按钮
     ui->pushButtonsdsaveas->setEnabled(false);
     ui->pushButtonsdconfig->setEnabled(false);
}

SimuDyn_Input::~SimuDyn_Input()
{
    delete ui;
}


//按下保存并且发送数据给主窗口进行处理
void SimuDyn_Input::on_pBsdyes_clicked()
{
    QString mid1 = ui->lineEditsdz->text();
    int z = mid1.toInt();
    QString mid2 = ui->lineEditsdD->text();
    double D = mid2.toDouble();
    QString mid3 = ui->lineEditsdrho->text();
    double rho = mid3.toDouble();
    QString mid4 = ui->lineEditsddm->text();
    double di = mid4.toDouble();
    QString mid5 = ui->lineEditsdv->text();
    double v = mid5.toDouble();
    QString mid6 = ui->lineEditsdE->text();
    double E = mid6.toDouble();
    QString mid7 = ui->lineEditsdFr->text();
    double Fr = mid7.toDouble();
    QString mid8 = ui->lineEditsdFa->text();
    double Fa = mid8.toDouble();
    QString mid9 = ui->lineEditsdM->text();
    double M = mid9.toDouble();
    QString mid10 = ui->lineEditsdo->text();
    double o = mid10.toDouble();
    QString mid11 = ui->lineEditsdo1->text();
    double o1 = mid11.toDouble();
    QString mid12 = ui->lineEditsdo2->text();
    double o2 = mid12.toDouble();
    //QString mid13 = ui->lineEditsdOR->text();
    //int OR = mid13.toInt();  //改为combobox模式
    QString mid14 = ui->lineEditsdalpha0->text();
    double alpha0 = mid14.toDouble();
    QString mid15 = ui->lineEditsdni->text();
    double ni = mid15.toDouble();
    QString mid16 = ui->lineEditsdfe->text();
    double fe = mid16.toDouble();
    QString mid17 = ui->lineEditsdfi->text();
    double fi = mid17.toDouble();
    QString mid18 = ui->lineEditsderro->text();
    double erro = mid18.toDouble();
    QString mid19 = ui->lineEditsdtimes->text();
    int numbers = mid19.toInt();

    emit sdinput(E,v,rho,alpha0,D,di,fe,fi,z,Fr,Fa,M,ni,o,o1,o2,OR,erro,numbers);
    this->hide();
}

//清零按钮
void SimuDyn_Input::on_pBsdclear_clicked()
{
    //ui->lineEditsdD->clear();
    //ui->lineEditsdE->clear();
    //ui->lineEditsdM->clear();
    //ui->lineEditsdo->clear();
    //ui->lineEditsdv->clear();
    //ui->lineEditsdz->clear();
    //ui->lineEditsdFa->clear();
    //ui->lineEditsdFr->clear();
    ////ui->lineEditsdOR->clear();
    //ui->lineEditsddm->clear();
    //ui->lineEditsdfe->clear();
    //ui->lineEditsdfi->clear();
    //ui->lineEditsdni->clear();
    //ui->lineEditsdo1->clear();
    //ui->lineEditsdo2->clear();
    //ui->lineEditsdrho->clear();
    //ui->lineEditsderro->clear();
    //ui->lineEditsdtimes->clear();
    //ui->lineEditsdalpha0->clear();

    //设置默认值
    ui->lineEditsdz->setText("19");
    ui->lineEditsdD->setText("12.5");
    ui->lineEditsdrho->setText("7850");
    ui->lineEditsddm->setText("77");
    ui->lineEditsdv->setText("0.3");
    ui->lineEditsdE->setText("206000");
    ui->lineEditsdFr->setText("10000");
    ui->lineEditsdFa->setText("20000");
    ui->lineEditsdM->setText("400");
    ui->lineEditsdo->setText("0.1");
    ui->lineEditsdo1->setText("0.2");
    ui->lineEditsdo2->setText("0.2");
    //ui->lineEditsdOR->setText("0"); //改为combobox模式
    ui->lineEditsdalpha0->setText("25");
    ui->lineEditsdni->setText("30000");
    ui->lineEditsdfe->setText("0.523");
    ui->lineEditsdfi->setText("0.523");
    ui->lineEditsderro->setText("0.000001");
    ui->lineEditsdtimes->setText("200");
    ui->comboBox->setCurrentIndex(0);
}

//按下不保存关闭界面
//void SimuDyn_Input::on_pBsdcancel_clicked()
//{
//    this->hide();
//}

//OR下拉框操作
void SimuDyn_Input::on_comboBox_activated(QString index)
{
    int indexOR = index.right(1).toInt();
    switch (indexOR)
    {
        case 0: OR = 0 ;break;
        case 1: OR = 1 ;break;
        case 2: OR = 2 ;break;
        default:break;
    }
}

//openfile and read
void SimuDyn_Input::on_pushButtonsdopenfile_clicked()
{
    m_inputopenfile_name2 = QFileDialog::getOpenFileName(this,"读取文件",".","数据输入文件(*.sdin)");
    //路径文件写入
    ui->labeladdress->setText(m_inputopenfile_name2);

    //开始读取
    //读取txt文档中的数据
    QFile File(m_inputopenfile_name2);
    if(!File.open(QIODevice::ReadOnly | QIODevice ::Text))
        return;
    QTextStream in(&File);
    while(!File.atEnd())
    {
        //读取全部，保存为字符串形式
        m_linestring2 = in.readAll();
        m_list_items2 = m_linestring2.split("\n");
        //对读取的行数据进行处理的伪代码
        //process_line(m_linestring);
    }

    //QTableWidget 表格创建
    //设置str编码类型
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    //当前算例写入
    QStringList Fr,Fa,ni;
    Fr = m_list_items2[1].split("\t");
    Fa = m_list_items2[2].split("\t");
    ni = m_list_items2[4].split("\t");
    ui->labelcurrentcase->setText("7008ACB,"" Fr" + Fr[1] + "N,"" Fa" +Fa[1] +"N," " ni"+ni[1]+"rpm");

    //规范行列数
    ui->tableWidgetsd->setColumnCount(3);
    ui->tableWidgetsd->setRowCount(ROWNUMBERS_SIMUDYN);

    //设置可见情况
    ui->tableWidgetsd->verticalHeader()->setVisible(false);
    ui->tableWidgetsd->horizontalHeader()->setVisible(true);

    //第一个表头
    QTableWidgetItem *item0 = new QTableWidgetItem();
    item0->setText("变量名称（常用符号）");
    item0->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setHorizontalHeaderItem(0,item0);
    //第二个水平表头
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item1->setText("值");
    item1->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setHorizontalHeaderItem(1,item1);
    //第三个水平表头
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setText("单位");
    item2->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setHorizontalHeaderItem(2,item2);


    //人为初始化吧，没办法了
    QTableWidgetItem *itemheader1 = new QTableWidgetItem();
    itemheader1->setText("(1)工况条件");
    itemheader1->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(0,0,itemheader1);

    QTableWidgetItem *itemFr = new QTableWidgetItem();
    itemFr->setText("径向载荷(Fr)");
    itemFr->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(1,0,itemFr);

    QTableWidgetItem *itemFa = new QTableWidgetItem();
    itemFa->setText("轴向载荷(Fa)");
    itemFa->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(2,0,itemFa);

    QTableWidgetItem *itemM = new QTableWidgetItem();
    itemM->setText("力矩(M)");
    itemM->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(3,0,itemM);

    QTableWidgetItem *itemni = new QTableWidgetItem();
    itemni->setText("内圈转速(ni)");
    itemni->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(4,0,itemni);

    QTableWidgetItem *itemheader2 = new QTableWidgetItem();
    itemheader2->setText("(2)结构参数");
    itemheader2->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(5,0,itemheader2);

    QTableWidgetItem *itemZ = new QTableWidgetItem();
    itemZ->setText("钢球个数(Z)");
    itemZ->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(6,0,itemZ);

    QTableWidgetItem *itemD = new QTableWidgetItem();
    itemD->setText("钢球直径(D)");
    itemD->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(7,0,itemD);

    QTableWidgetItem *itemdm = new QTableWidgetItem();
    itemdm->setText("内圈直径(dm)");
    itemdm->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(8,0,itemdm);

    QTableWidgetItem *itemalpha0 = new QTableWidgetItem();
    itemalpha0->setText("初始接触角");
    itemalpha0->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(9,0,itemalpha0);

    QTableWidgetItem *itemfi = new QTableWidgetItem();
    itemfi->setText("内圈沟渠率半径系数");
    itemfi->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(10,0,itemfi);

    QTableWidgetItem *itemfe = new QTableWidgetItem();
    itemfe->setText("外圈沟渠率半径系数");
    itemfe->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(11,0,itemfe);

    QTableWidgetItem *itemheader3 = new QTableWidgetItem();
    itemheader3->setText("(3)材料参数");
    itemheader3->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(12,0,itemheader3);

    QTableWidgetItem *itemrho0 = new QTableWidgetItem();
    itemrho0->setText("钢球材料密度");
    itemrho0->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(13,0,itemrho0);

    QTableWidgetItem *itemE = new QTableWidgetItem();
    itemE->setText("弹性模量");
    itemE->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(14,0,itemE);

    QTableWidgetItem *itemv = new QTableWidgetItem();
    itemv->setText("泊松比");
    itemv->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(15,0,itemv);

    QTableWidgetItem *itemheader4 = new QTableWidgetItem();
    itemheader4->setText("(4)引导方式");
    itemheader4->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(16,0,itemheader4);

    QTableWidgetItem *itemOR = new QTableWidgetItem();
    itemOR->setText("引导方式");
    itemOR->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(17,0,itemOR);

    QTableWidgetItem *itemheader5 = new QTableWidgetItem();
    itemheader5->setText("(5)润滑剂/摩擦相关参数");
    itemheader5->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(18,0,itemheader5);

    QTableWidgetItem *itemviscous = new QTableWidgetItem();
    itemviscous->setText("润滑油黏度(η)");
    itemviscous->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(19,0,itemviscous);

    QTableWidgetItem *itemrho = new QTableWidgetItem();
    itemrho->setText("润滑油密度(ρ)");
    itemrho->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(20,0,itemrho);

    QTableWidgetItem *itemalpha = new QTableWidgetItem();
    itemalpha->setText("润滑油黏压系数(α)");
    itemalpha->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(21,0,itemalpha);

    QTableWidgetItem *itembeta = new QTableWidgetItem();
    itembeta->setText("润滑油黏温(β)");
    itembeta->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(22,0,itembeta);

    QTableWidgetItem *itemomiga = new QTableWidgetItem();
    itemomiga->setText("摩擦系数(μ)");
    itemomiga->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(23,0,itemomiga);

    QTableWidgetItem *itemheader6 = new QTableWidgetItem();
    itemheader6->setText("(6)数值计算相关参数");
    itemheader6->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(24,0,itemheader6);

    QTableWidgetItem *itemomigaD = new QTableWidgetItem();
    itemomigaD->setText("位移修正系数(ωD)");
    itemomigaD->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(25,0,itemomigaD);

    QTableWidgetItem *itemomigar = new QTableWidgetItem();
    itemomigar->setText("姿态角修正系数(ωγ)");
    itemomigar->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(26,0,itemomigar);

    QTableWidgetItem *itemerro = new QTableWidgetItem();
    itemerro->setText("规定迭代误差");
    itemerro->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(27,0,itemerro);

    QTableWidgetItem *itemnumbers = new QTableWidgetItem();
    itemnumbers->setText("极限迭代次数");
    itemnumbers->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetsd->setItem(28,0,itemnumbers);

    //单位
    ui->tableWidgetsd->setItem(1,2,new QTableWidgetItem("N"));
    ui->tableWidgetsd->setItem(2,2,new QTableWidgetItem("N"));
    ui->tableWidgetsd->setItem(3,2,new QTableWidgetItem("N*mm"));
    ui->tableWidgetsd->setItem(4,2,new QTableWidgetItem("rpm"));
    ui->tableWidgetsd->setItem(7,2,new QTableWidgetItem("mm"));
    ui->tableWidgetsd->setItem(8,2,new QTableWidgetItem("mm"));
    ui->tableWidgetsd->setItem(9,2,new QTableWidgetItem("°"));
    ui->tableWidgetsd->setItem(13,2,new QTableWidgetItem("kg/m^3"));
    ui->tableWidgetsd->setItem(14,2,new QTableWidgetItem("N/mm^2"));

    for(int row_tableview = 0; row_tableview < ROWNUMBERS_SIMUDYN;row_tableview++)
    {
        QStringList thisrow = m_list_items2[row_tableview].split("\t");
        QString printout = thisrow[1];
        ui->tableWidgetsd->setItem(row_tableview,1,new QTableWidgetItem(printout));
        //设置字符位置
        ui->tableWidgetsd->item(row_tableview,1)->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    }

    //列宽设置
    ui->tableWidgetsd->setColumnWidth(0,200);
    ui->tableWidgetsd->setColumnWidth(1,150);
    ui->tableWidgetsd->setColumnWidth(2,100);

    //读取成功以后释放
    ui->pushButtonsdconfig->setEnabled(true);
    ui->pushButtonsdsaveas->setEnabled(true);
}


//save as
void SimuDyn_Input::on_pushButtonsdsaveas_clicked()
{
    //设置标识符判断OR是否合适
    int flag_canI = 0;
    //取值，以防万一
    m_sd_Fr = ui->tableWidgetsd->item(1, 1)->text();
    m_sd_Fa = ui->tableWidgetsd->item(2, 1)->text();
    m_sd_M = ui->tableWidgetsd->item(3, 1)->text();
    m_sd_ni = ui->tableWidgetsd->item(4, 1)->text();
    m_sd_z = ui->tableWidgetsd->item(6, 1)->text();
    m_sd_D = ui->tableWidgetsd->item(7, 1)->text();
    m_sd_dm = ui->tableWidgetsd->item(8, 1)->text();
    m_sd_alpha0 = ui->tableWidgetsd->item(9, 1)->text();
    m_sd_fi = ui->tableWidgetsd->item(10, 1)->text();
    m_sd_fe = ui->tableWidgetsd->item(11, 1)->text();
    m_sd_rho = ui->tableWidgetsd->item(13, 1)->text();
    m_sd_E = ui->tableWidgetsd->item(14, 1)->text();
    m_sd_v = ui->tableWidgetsd->item(15, 1)->text();
    m_sd_OR = ui->tableWidgetsd->item(17, 1)->text();
    if(!(m_sd_OR=="0" || m_sd_OR=="1"||m_sd_OR=="2"))
    {
        QMessageBox::warning(this,"错误","引导方式只能是0，1，2，请重新输入");
        ui->tabWidgetsd->setCurrentWidget(ui->tabsdopenfile);
        flag_canI = 1;
    }
    m_sd_omiga2 = ui->tableWidgetsd->item(23, 1)->text();
    m_sd_omiga = ui->tableWidgetsd->item(25, 1)->text();
    m_sd_omiga1 = ui->tableWidgetsd->item(26, 1)->text();
    m_sd_erro = ui->tableWidgetsd->item(27, 1)->text();
    m_sd_erronumber = ui->tableWidgetsd->item(28, 1)->text();

    //只有or合适的时候才能保存
    if(flag_canI == 0)
    {
        //确认保存路径
        m_inputsavefile_name2 = QFileDialog::getSaveFileName(this,"保存文件",".","数据输入文件(*.sdin)");

        QFile datasavesta_1_file(m_inputsavefile_name2);
        if (!datasavesta_1_file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream stadata_1_out(&datasavesta_1_file);

        //设置输出文字格式，使得中文也能输出
        //QSettings settings(datasavefile_name, QSettings::IniFormat);
        //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
        stadata_1_out.setCodec(QTextCodec::codecForName("utf-8"));

        //开始写入,按照标准格式
        stadata_1_out  <<tr("(1)工况条件")<<"\t"<<tr(" ")<<"\t"<<"\n";
        stadata_1_out  <<tr("径向载荷(Fr) =")<<"\t"<< m_sd_Fr <<"\t"<<tr("N")<< "\n";
        stadata_1_out  <<tr("轴向载荷(Fa) =")<<"\t"<< m_sd_Fa <<"\t"<<tr("N")<< "\n";
        stadata_1_out  <<tr("力矩(M) =")<<"\t"<< m_sd_M <<"\t"<<tr("N*mm")<<"\n";
        stadata_1_out  <<tr("内圈转速(n) =")<<"\t"<< m_sd_ni  <<"\t"<<tr("rpm")<< "\n";
        stadata_1_out  <<tr("(2)结构参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("钢球个数(Z) =")<<"\t"<< m_sd_z <<"\t"<<"\n";
        stadata_1_out  <<tr("钢球直径(D) =")<<"\t"<< m_sd_D <<"\t"<<tr("mm")<< "\n";
        stadata_1_out  <<tr("内圈直径(dm) =")<<"\t"<< m_sd_dm <<"\t"<<tr("mm")<< "\n";
        stadata_1_out  <<tr("初始接触角 =")<<"\t"<< m_sd_alpha0 <<"\t"<<tr("°")<< "\n";
        stadata_1_out  <<tr("内圈沟渠率半径系数 =")<<"\t"<< m_sd_fi  <<"\t"<< "\n";
        stadata_1_out  <<tr("外圈沟渠率半径系数 =")<<"\t"<< m_sd_fe  <<"\t"<< "\n";
        stadata_1_out  <<tr("(3)材料参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("钢球材料密度 =")<<"\t"<< m_sd_rho <<"\t"<<tr("kg/m^3")<< "\n";
        stadata_1_out  <<tr("弹性模量 =")<<"\t"<< m_sd_E  <<"\t"<<tr("N/mm^2")<< "\n";
        stadata_1_out  <<tr("泊松比 =")<<"\t"<< m_sd_v  <<"\t"<< "\n";
        stadata_1_out  <<tr("(4)引导方式")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("引导方式 =")<<"\t"<< m_sd_OR  <<"\t"<< "\n";
        stadata_1_out  <<tr("(5)润滑剂/摩擦相关参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("润滑油黏度(η)")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("润滑油密度(ρ)")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("润滑油黏压系数(α)")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("润滑油黏温(β)")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("摩擦系数(μ) =")<<"\t"<< m_sd_omiga2<<"\t"<<"\n";
        stadata_1_out  <<tr("(6)数值计算相关参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
        stadata_1_out  <<tr("位移修正系数(ωD) =")<<"\t"<< m_sd_omiga<<"\t"<<"\n";
        stadata_1_out  <<tr("姿态角修正系数(ωγ) =")<<"\t"<< m_sd_omiga1<<"\t"<<"\n";
        stadata_1_out  <<tr("规定迭代误差 =")<<"\t"<< m_sd_erro<<"\t"<<"\n";
        stadata_1_out  <<tr("极限迭代次数 =")<<"\t"<< m_sd_erronumber<<"\t"<<"\n";

        datasavesta_1_file.close();
    }
}


//config
void SimuDyn_Input::on_pushButtonsdconfig_clicked()
{
    ui->tabWidgetsd->setCurrentWidget(ui->tabsdnew);
    ui->tabsimudyn->setCurrentWidget(ui->tabsd1);
    //取值，以防万一
    m_sd_Fr = ui->tableWidgetsd->item(1, 1)->text();
    m_sd_Fa = ui->tableWidgetsd->item(2, 1)->text();
    m_sd_M = ui->tableWidgetsd->item(3, 1)->text();
    m_sd_ni = ui->tableWidgetsd->item(4, 1)->text();
    m_sd_z = ui->tableWidgetsd->item(6, 1)->text();
    m_sd_D = ui->tableWidgetsd->item(7, 1)->text();
    m_sd_dm = ui->tableWidgetsd->item(8, 1)->text();
    m_sd_alpha0 = ui->tableWidgetsd->item(9, 1)->text();
    m_sd_fi = ui->tableWidgetsd->item(10, 1)->text();
    m_sd_fe = ui->tableWidgetsd->item(11, 1)->text();
    m_sd_rho = ui->tableWidgetsd->item(13, 1)->text();
    m_sd_E = ui->tableWidgetsd->item(14, 1)->text();
    m_sd_v = ui->tableWidgetsd->item(15, 1)->text();
    m_sd_OR = ui->tableWidgetsd->item(17, 1)->text();
    if(!(m_sd_OR=="0" || m_sd_OR=="1"||m_sd_OR=="2"))
    {
        QMessageBox::warning(this,"错误","引导方式只能是0，1，2，请重新输入");
        ui->tabWidgetsd->setCurrentWidget(ui->tabsdopenfile);
    }
    m_sd_omiga2 = ui->tableWidgetsd->item(23, 1)->text();
    m_sd_omiga = ui->tableWidgetsd->item(25, 1)->text();
    m_sd_omiga1 = ui->tableWidgetsd->item(26, 1)->text();
    m_sd_erro = ui->tableWidgetsd->item(27, 1)->text();
    m_sd_erronumber = ui->tableWidgetsd->item(28, 1)->text();

    //赋值
    ui->lineEditsdD->setText(m_sd_D);
    ui->lineEditsdE->setText(m_sd_E);
    ui->lineEditsdM->setText(m_sd_M);
    ui->lineEditsdo->setText(m_sd_omiga);
    ui->lineEditsdv->setText(m_sd_v);
    ui->lineEditsdz->setText(m_sd_z);
    ui->lineEditsdFa->setText(m_sd_Fa);
    ui->lineEditsdFr->setText(m_sd_Fr);
    //ui->lineEditsdOR->setText();
    ui->lineEditsddm->setText(m_sd_dm);
    ui->lineEditsdfe->setText(m_sd_fe);
    ui->lineEditsdfi->setText(m_sd_fi);
    ui->lineEditsdni->setText(m_sd_ni);
    ui->lineEditsdo1->setText(m_sd_omiga1);
    ui->lineEditsdo2->setText(m_sd_omiga2);
    ui->lineEditsdrho->setText(m_sd_rho);
    ui->lineEditsderro->setText(m_sd_erro);
    ui->lineEditsdtimes->setText(m_sd_erronumber);
    ui->lineEditsdalpha0->setText(m_sd_alpha0);

    //combobox设置
    int indexOR = m_sd_OR.right(1).toInt();
    switch (indexOR)
    {
    case 0: OR = 0 ;ui->comboBox->setCurrentIndex(0);;break;
    case 1: OR = 1 ;ui->comboBox->setCurrentIndex(1);;break;
    case 2: OR = 2 ;ui->comboBox->setCurrentIndex(2);;break;
    default:break;
    }

}

//设置阴影子函数
void SimuDyn_Input::setShadowsta(QLineEdit *lineedit)
{
    //设置边框的阴影效果
    m_staeffect = new QGraphicsDropShadowEffect(lineedit);
    m_staeffect->setBlurRadius(5);
    m_staeffect->setColor(Qt::black);
    m_staeffect->setOffset(0,0);
    //把阴影给需要的lineedit
    lineedit->setGraphicsEffect(m_staeffect);
}

