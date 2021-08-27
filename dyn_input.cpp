#include "dyn_input.h"
#include "ui_dyn_input.h"

//定义全局变量
int zdyn;
double Ddyn,dmdyn,alpha0dyn,fidyn,fedyn,Cpdyn,Cgdyn;
double Edyn,vdyn,rhodyn,Ecdyn,vcdyn,rhocdyn;
double nidyn,Fadyn,Frdyn,Mydyn,Mzdy,ORdyn;
double T0dyn,n0dyn,alphadyn,betadyn,Kdyn;
double h0dyn,ktdyn,Ferrdyn,uerrdyn,Tdyn;

Dyn_Input::Dyn_Input(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dyn_Input)
{
    ui->setupUi(this);

    //设置默认页面为第一页
    ui->tabWidget_dyn->setCurrentWidget(ui->tab_opennew);
    ui->tabWidget_parameters->setCurrentWidget(ui->tab_structure);

    //给文本框设置样式，设置边框颜色
    //ui->lineEditsdD->setStyleSheet("QLineEdit{border:red}");
    //具体给设置阴影
    setShadowdyn(ui->lineEditdynD);
    setShadowdyn(ui->lineEditdynE);
    setShadowdyn(ui->lineEditdynK);
    setShadowdyn(ui->lineEditdynT);
    setShadowdyn(ui->lineEditdynv);
    setShadowdyn(ui->lineEditdynz);
    setShadowdyn(ui->lineEditdynCg);
    setShadowdyn(ui->lineEditdynCp);
    setShadowdyn(ui->lineEditdynFa);
    setShadowdyn(ui->lineEditdynFr);
    setShadowdyn(ui->lineEditdynMy);
    setShadowdyn(ui->lineEditdynMz);
    setShadowdyn(ui->lineEditdynT0);
    setShadowdyn(ui->lineEditdyndm);
    setShadowdyn(ui->lineEditdynfe);
    setShadowdyn(ui->lineEditdynfi);
    setShadowdyn(ui->lineEditdynh0);
    setShadowdyn(ui->lineEditdynFerr);
    setShadowdyn(ui->lineEditdynUerr);
    setShadowdyn(ui->lineEditdynbeta);
    setShadowdyn(ui->lineEditdynalpha);
    setShadowdyn(ui->lineEditdynalpha0);
    setShadowdyn(ui->lineEditdynE_kepper);
    setShadowdyn(ui->lineEditdynv_kepper);
    setShadowdyn(ui->lineEditdynrho_kepper);
    setShadowdyn(ui->lineEditdynrho);
    setShadowdyn(ui->lineEditdynni);
    setShadowdyn(ui->lineEditdynn0);
    setShadowdyn(ui->lineEditdynkt);
    //setShadowsta(ui->labeladdress);
    //setShadowsta(ui->labelcurrentcase);

    //设置默认值
    ui->lineEditdynD->setText("53.9");
    ui->lineEditdynE->setText("206000");
    ui->lineEditdynK->setText("0.0966");
    ui->lineEditdynT->setText("0.4");
    ui->lineEditdynv->setText("0.3");
    ui->lineEditdynz->setText("17");
    ui->lineEditdynCg->setText("0.4");
    ui->lineEditdynCp->setText("0.4");
    ui->lineEditdynFa->setText("400");
    ui->lineEditdynFr->setText("200");
    ui->lineEditdynMy->setText("50");
    ui->lineEditdynMz->setText("100");
    ui->lineEditdynT0->setText("30");
    ui->lineEditdyndm->setText("7.3");
    ui->lineEditdynfe->setText("0.57");
    ui->lineEditdynfi->setText("0.52");
    ui->lineEditdynh0->setText("0.00001");
    ui->lineEditdynFerr->setText("0.05");
    ui->lineEditdynUerr->setText("0.01");
    ui->lineEditdynbeta->setText("0.0215");
    ui->lineEditdynalpha->setText("0.0000000128");
    ui->lineEditdynalpha0->setText("15");
    ui->lineEditdynE_kepper->setText("4200");
    ui->lineEditdynv_kepper->setText("0.4");
    ui->lineEditdynrho_kepper->setText("2200");
    ui->lineEditdynrho->setText("7800");
    ui->lineEditdynni->setText("10000");
    ui->lineEditdynn0->setText("0.033");
    ui->lineEditdynkt->setText("0.5");

    //初始化按钮
    ui->pushButtondynsaveas->setEnabled(false);
    ui->pushButtondynconfig->setEnabled(false);
}

Dyn_Input::~Dyn_Input()
{
    delete ui;
}

//阴影函数
void Dyn_Input::setShadowdyn(QLineEdit *lineedit)
{
    //设置边框的阴影效果
    m_sdeffect = new QGraphicsDropShadowEffect(lineedit);
    m_sdeffect->setBlurRadius(5);
    m_sdeffect->setColor(Qt::black);
    m_sdeffect->setOffset(0,0);
    //把阴影给需要的lineedit
    lineedit->setGraphicsEffect(m_sdeffect);
}

//应用按钮
void Dyn_Input::on_pushButton_apply_clicked()
{
    //读取数据
    QString mid1 = ui->lineEditdynD->text();
    Ddyn = mid1.toInt();
    QString mid2 = ui->lineEditdynE->text();
    Edyn = mid2.toDouble();
    QString mid3 = ui->lineEditdynK->text();
    Kdyn = mid3.toDouble();
    QString mid4 = ui->lineEditdynT->text();
    Tdyn = mid4.toDouble();
    QString mid5 = ui->lineEditdynv->text();
    vdyn = mid5.toDouble();
    QString mid6 = ui->lineEditdynz->text();
    zdyn = mid6.toDouble();
    QString mid7 = ui->lineEditdynCg->text();
    Cgdyn = mid7.toDouble();
    QString mid8 = ui->lineEditdynCp->text();
    Cpdyn = mid8.toDouble();
    QString mid9 = ui->lineEditdynFa->text();
    Fadyn = mid9.toDouble();
    QString mid11 = ui->lineEditdynFr->text();
    Frdyn = mid11.toInt();
    QString mid12 = ui->lineEditdynMy->text();
    Mydyn = mid12.toDouble();
    QString mid13 = ui->lineEditdynMz->text();
    Mzdy = mid13.toDouble();
    QString mid14 = ui->lineEditdynT0->text();
    T0dyn = mid14.toDouble();
    QString mid15 = ui->lineEditdyndm->text();
    dmdyn = mid15.toDouble();
    QString mid16 = ui->lineEditdynfe->text();
    fedyn = mid16.toDouble();
    QString mid17 = ui->lineEditdynfi->text();
    fidyn = mid17.toDouble();
    QString mid18 = ui->lineEditdynh0->text();
    h0dyn = mid18.toDouble();
    QString mid19 = ui->lineEditdynkt->text();
    ktdyn = mid19.toDouble();
    QString mid22 = ui->lineEditdynn0->text();
    n0dyn = mid22.toDouble();
    QString mid23 = ui->lineEditdynni->text();
    nidyn = mid23.toDouble();
    QString mid24 = ui->lineEditdynrho->text();
    rhodyn = mid24.toDouble();
    QString mid25 = ui->lineEditdynFerr->text();
    Ferrdyn = mid25.toDouble();
    QString mid26 = ui->lineEditdynUerr->text();
    uerrdyn = mid26.toDouble();
    QString mid27 = ui->lineEditdynbeta->text();
    betadyn = mid27.toDouble();
    QString mid28 = ui->lineEditdynalpha->text();
    alphadyn = mid28.toDouble();
    QString mid29 = ui->lineEditdynalpha0->text();
    alpha0dyn = mid29.toDouble();
    QString mid38 = ui->lineEditdynE_kepper->text();
    Ecdyn = mid38.toDouble();
    QString mid39 = ui->lineEditdynv_kepper->text();
    vcdyn = mid39.toDouble();
    QString mid40 = ui->lineEditdynrho_kepper->text();
    rhocdyn = mid40.toDouble();
    //读取完了发送以信号的形式发送数据
    emit dyninput(zdyn,
                  Ddyn,dmdyn,alpha0dyn,fidyn,fedyn,Cpdyn,Cgdyn,
                  Edyn,vdyn,rhodyn,Ecdyn,vcdyn,rhocdyn,
                  nidyn,Fadyn,Frdyn,Mydyn,Mzdy,ORdyn,
                  T0dyn,n0dyn,alphadyn,betadyn,Kdyn,
                  h0dyn,ktdyn,Ferrdyn,uerrdyn,Tdyn);
    //隐藏窗口
    this->hide();
}

//重置按钮
void Dyn_Input::on_pushButton_reset_clicked()
{
    //初始化
    ui->lineEditdynD->setText("53.9");
    ui->lineEditdynE->setText("206000");
    ui->lineEditdynK->setText("0.0966");
    ui->lineEditdynT->setText("0.4");
    ui->lineEditdynv->setText("0.3");
    ui->lineEditdynz->setText("17");
    ui->lineEditdynCg->setText("0.4");
    ui->lineEditdynCp->setText("0.4");
    ui->lineEditdynFa->setText("400");
    ui->lineEditdynFr->setText("200");
    ui->lineEditdynMy->setText("50");
    ui->lineEditdynMz->setText("100");
    ui->lineEditdynT0->setText("30");
    ui->lineEditdyndm->setText("7.3");
    ui->lineEditdynfe->setText("0.57");
    ui->lineEditdynfi->setText("0.52");
    ui->lineEditdynh0->setText("0.00001");
    ui->lineEditdynFerr->setText("0.05");
    ui->lineEditdynUerr->setText("0.01");
    ui->lineEditdynbeta->setText("0.0215");
    ui->lineEditdynalpha->setText("0.0000000128");
    ui->lineEditdynalpha0->setText("15");
    ui->lineEditdynE_kepper->setText("4200");
    ui->lineEditdynv_kepper->setText("0.4");
    ui->lineEditdynrho_kepper->setText("2200");
    ui->lineEditdynrho->setText("7800");
    ui->lineEditdynni->setText("10000");
    ui->lineEditdynn0->setText("0.033");
    ui->lineEditdynkt->setText("0.5");
}



void Dyn_Input::on_comboBox_dyn_activated(const QString &arg1)
{
    int indexOR = arg1.right(1).toInt();
    switch (indexOR)
    {
        case 0: ORdyn = 0 ;break;
        case 1: ORdyn = 1 ;break;
        case 2: ORdyn = 2 ;break;
        default:break;
    }
}

//打开文件按钮
void Dyn_Input::on_pushButtondynopenfile_clicked()
{
    m_inputopenfile_name3 = QFileDialog::getOpenFileName(this,"读取文件",".","数据输入文件(*.dynin)");
    //路径文件写入
    ui->labeladdressdyn->setText(m_inputopenfile_name3);

    //开始读取
    //读取txt文档中的数据
    QFile File(m_inputopenfile_name3);
    if(!File.open(QIODevice::ReadOnly | QIODevice ::Text))
        return;
    QTextStream in(&File);
    while(!File.atEnd())
    {
        //读取全部，保存为字符串形式
        m_linestring3 = in.readAll();
        m_list_items3 = m_linestring3.split("\n");
        //对读取的行数据进行处理的伪代码
        //process_line(m_linestring);
    }

    //QTableWidget 表格创建
    //设置str编码类型
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    //当前算例写入
    QStringList Fr,Fa,ni;
    Fr = m_list_items3[1].split("\t");
    Fa = m_list_items3[2].split("\t");
    ni = m_list_items3[5].split("\t");
    ui->labelcurrentcasedyn->setText("7008ACB,"" Fr" + Fr[1] + "N,"" Fa" +Fa[1] +"N," " ni"+ni[1]+"rpm");

    //QWidgetTable
    //规范行列数
    ui->tableWidgetdyn->setColumnCount(3);
    ui->tableWidgetdyn->setRowCount(ROWNUMBERS_DYN);

    //设置可见情况
    ui->tableWidgetdyn->verticalHeader()->setVisible(false);
    ui->tableWidgetdyn->horizontalHeader()->setVisible(true);

    //第一个表头
    QTableWidgetItem *item0 = new QTableWidgetItem();
    item0->setText("变量名称（常用符号）");
    item0->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setHorizontalHeaderItem(0,item0);
    //第二个水平表头
    QTableWidgetItem *item1 = new QTableWidgetItem();
    item1->setText("值");
    item1->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setHorizontalHeaderItem(1,item1);
    //第三个水平表头
    QTableWidgetItem *item2 = new QTableWidgetItem();
    item2->setText("单位");
    item2->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setHorizontalHeaderItem(2,item2);

    QTableWidgetItem *itemheader1 = new QTableWidgetItem();
    itemheader1->setText("(1)工况条件");
    itemheader1->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(0,0,itemheader1);

    QTableWidgetItem *itemFr = new QTableWidgetItem();
    itemFr->setText("径向载荷(Fr)");
    itemFr->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(1,0,itemFr);

    QTableWidgetItem *itemFa = new QTableWidgetItem();
    itemFa->setText("轴向载荷(Fa)");
    itemFa->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(2,0,itemFa);

    QTableWidgetItem *itemMy = new QTableWidgetItem();
    itemMy->setText("力矩(My)");
    itemMy->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(3,0,itemMy);

    QTableWidgetItem *itemMz = new QTableWidgetItem();
    itemMz->setText("力矩(Mz)");
    itemMz->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(4,0,itemMz);

    QTableWidgetItem *itemni = new QTableWidgetItem();
    itemni->setText("内圈转速(ni)");
    itemni->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(5,0,itemni);

    QTableWidgetItem *itemOR = new QTableWidgetItem();
    itemOR->setText("引导方式");
    itemOR->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(6,0,itemOR);

    QTableWidgetItem *itemheader2 = new QTableWidgetItem();
    itemheader2->setText("(2)结构参数");
    itemheader2->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(7,0,itemheader2);

    QTableWidgetItem *itemZ = new QTableWidgetItem();
    itemZ->setText("钢球个数(Z)");
    itemZ->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(8,0,itemZ);

    QTableWidgetItem *itemD = new QTableWidgetItem();
    itemD->setText("钢球直径(D)");
    itemD->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(9,0,itemD);

    QTableWidgetItem *itemdm = new QTableWidgetItem();
    itemdm->setText("内圈直径(dm)");
    itemdm->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(10,0,itemdm);

    QTableWidgetItem *itemalpha0 = new QTableWidgetItem();
    itemalpha0->setText("初始接触角");
    itemalpha0->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(11,0,itemalpha0);

    QTableWidgetItem *itemfi = new QTableWidgetItem();
    itemfi->setText("内圈沟渠率半径系数");
    itemfi->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(12,0,itemfi);

    QTableWidgetItem *itemfe = new QTableWidgetItem();
    itemfe->setText("外圈沟渠率半径系数");
    itemfe->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(13,0,itemfe);

    QTableWidgetItem *itemCp = new QTableWidgetItem();
    itemCp->setText("保持架兜孔间隙");
    itemCp->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(14,0,itemCp);

    QTableWidgetItem *itemCg = new QTableWidgetItem();
    itemCg->setText("保持架引导间隙");
    itemCg->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(15,0,itemCg);

    QTableWidgetItem *itemheader3 = new QTableWidgetItem();
    itemheader3->setText("(3)材料参数");
    itemheader3->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(16,0,itemheader3);

    QTableWidgetItem *itemrho0 = new QTableWidgetItem();
    itemrho0->setText("钢球材料密度");
    itemrho0->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(17,0,itemrho0);

    QTableWidgetItem *itemE = new QTableWidgetItem();
    itemE->setText("钢球弹性模量");
    itemE->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(18,0,itemE);

    QTableWidgetItem *itemv = new QTableWidgetItem();
    itemv->setText("钢球泊松比");
    itemv->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(19,0,itemv);

    QTableWidgetItem *itemrho0c = new QTableWidgetItem();
    itemrho0c->setText("保持架材料密度");
    itemrho0c->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(20,0,itemrho0c);

    QTableWidgetItem *itemEc = new QTableWidgetItem();
    itemEc->setText("保持架弹性模量");
    itemEc->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(21,0,itemEc);

    QTableWidgetItem *itemvc = new QTableWidgetItem();
    itemvc->setText("保持架泊松比");
    itemvc->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(22,0,itemvc);

    QTableWidgetItem *itemheader5 = new QTableWidgetItem();
    itemheader5->setText("(4)润滑剂/摩擦相关参数");
    itemheader5->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(23,0,itemheader5);

    QTableWidgetItem *itemviscous = new QTableWidgetItem();
    itemviscous->setText("环境温度(T0)");
    itemviscous->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(24,0,itemviscous);

    QTableWidgetItem *itemrho = new QTableWidgetItem();
    itemrho->setText("常温常压下润滑油粘度(η0)");
    itemrho->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(25,0,itemrho);

    QTableWidgetItem *itemalpha = new QTableWidgetItem();
    itemalpha->setText("润滑油黏压系数(α)");
    itemalpha->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(26,0,itemalpha);

    QTableWidgetItem *itembeta = new QTableWidgetItem();
    itembeta->setText("润滑油黏温(β)");
    itembeta->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(27,0,itembeta);

    QTableWidgetItem *itemomiga = new QTableWidgetItem();
    itemomiga->setText("润滑油热传导系数(K)");
    itemomiga->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(28,0,itemomiga);

    QTableWidgetItem *itemheader6 = new QTableWidgetItem();
    itemheader6->setText("(5)数值计算相关参数");
    itemheader6->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(29,0,itemheader6);

    QTableWidgetItem *itemomigaD = new QTableWidgetItem();
    itemomigaD->setText("初始步长(h0)");
    itemomigaD->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(30,0,itemomigaD);

    QTableWidgetItem *itemomigar = new QTableWidgetItem();
    itemomigar->setText("步长修正系数(kt)");
    itemomigar->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(31,0,itemomigar);

    QTableWidgetItem *itemerro = new QTableWidgetItem();
    itemerro->setText("力残差(Ferr)");
    itemerro->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(32,0,itemerro);

    QTableWidgetItem *itemnumbers = new QTableWidgetItem();
    itemnumbers->setText("位移残差(uerr)");
    itemnumbers->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(33,0,itemnumbers);

    QTableWidgetItem *itemT = new QTableWidgetItem();
    itemT->setText("动力学分析时间(T)");
    itemT->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->tableWidgetdyn->setItem(34,0,itemT);

    //数据
    for(int row_tableview = 0; row_tableview < ROWNUMBERS_DYN;row_tableview++)
    {
        QStringList thisrow = m_list_items3[row_tableview].split("\t");
        QString printout = thisrow[1];
        ui->tableWidgetdyn->setItem(row_tableview,1,new QTableWidgetItem(printout));
        //设置字符位置
        ui->tableWidgetdyn->item(row_tableview,1)->setTextAlignment(Qt::AlignRight |Qt::AlignVCenter);
    }

    //单位
    ui->tableWidgetdyn->setItem(1,2,new QTableWidgetItem("N"));
    ui->tableWidgetdyn->setItem(2,2,new QTableWidgetItem("N"));
    ui->tableWidgetdyn->setItem(3,2,new QTableWidgetItem("N*mm"));
    ui->tableWidgetdyn->setItem(4,2,new QTableWidgetItem("N*mm"));
    ui->tableWidgetdyn->setItem(5,2,new QTableWidgetItem("rpm"));
    ui->tableWidgetdyn->setItem(9,2,new QTableWidgetItem("mm"));
    ui->tableWidgetdyn->setItem(10,2,new QTableWidgetItem("mm"));
    ui->tableWidgetdyn->setItem(11,2,new QTableWidgetItem("°"));
    ui->tableWidgetdyn->setItem(14,2,new QTableWidgetItem("mm"));
    ui->tableWidgetdyn->setItem(15,2,new QTableWidgetItem("mm"));
    ui->tableWidgetdyn->setItem(17,2,new QTableWidgetItem("kg/m^3"));
    ui->tableWidgetdyn->setItem(18,2,new QTableWidgetItem("N/mm^2"));
    ui->tableWidgetdyn->setItem(20,2,new QTableWidgetItem("kg/m^3"));
    ui->tableWidgetdyn->setItem(21,2,new QTableWidgetItem("N/mm^2"));
    ui->tableWidgetdyn->setItem(24,2,new QTableWidgetItem("˚C"));
    ui->tableWidgetdyn->setItem(25,2,new QTableWidgetItem("Pa·s"));
    ui->tableWidgetdyn->setItem(26,2,new QTableWidgetItem("Pa-1"));
    ui->tableWidgetdyn->setItem(27,2,new QTableWidgetItem("K-1"));
    ui->tableWidgetdyn->setItem(28,2,new QTableWidgetItem("N/(s·K)"));
    ui->tableWidgetdyn->setItem(30,2,new QTableWidgetItem("s"));
    ui->tableWidgetdyn->setItem(32,2,new QTableWidgetItem("N"));
    ui->tableWidgetdyn->setItem(33,2,new QTableWidgetItem("mm"));
    ui->tableWidgetdyn->setItem(34,2,new QTableWidgetItem("s"));


    //列宽设置
    ui->tableWidgetdyn->setColumnWidth(0,200);
    ui->tableWidgetdyn->setColumnWidth(1,200);
    ui->tableWidgetdyn->setColumnWidth(2,100);

    //读取成功以后释放
    ui->pushButtondynconfig->setEnabled(true);
    ui->pushButtondynsaveas->setEnabled(true);
}

//另存为
void Dyn_Input::on_pushButtondynsaveas_clicked()
{
    //设置标识符判断OR是否合适
        int flag_canI = 0;
        //取值，以防万一
        m_dyn_Fr = ui->tableWidgetdyn->item(1, 1)->text();
        m_dyn_Fa = ui->tableWidgetdyn->item(2, 1)->text();
        m_dyn_My = ui->tableWidgetdyn->item(3, 1)->text();
        m_dyn_Mz = ui->tableWidgetdyn->item(4, 1)->text();
        m_dyn_ni = ui->tableWidgetdyn->item(5, 1)->text();
        m_dyn_OR = ui->tableWidgetdyn->item(6, 1)->text();
        if(!(m_dyn_OR=="0" || m_dyn_OR=="1"||m_dyn_OR=="2"))
        {
            QMessageBox::warning(this,"错误","引导方式只能是0，1，2，请重新输入");
            ui->tabWidget_dyn->setCurrentWidget(ui->tab_readfiles);
            //ui->tabWidget_parameters->setCurrentWidget(ui->tab_working);
            flag_canI = 1;
        }

        m_dyn_z = ui->tableWidgetdyn->item(8, 1)->text();
        m_dyn_D = ui->tableWidgetdyn->item(9, 1)->text();
        m_dyn_dm = ui->tableWidgetdyn->item(10, 1)->text();
        m_dyn_alpha0 = ui->tableWidgetdyn->item(11, 1)->text();
        m_dyn_fi = ui->tableWidgetdyn->item(12, 1)->text();
        m_dyn_fe = ui->tableWidgetdyn->item(13, 1)->text();
        m_dyn_Cp = ui->tableWidgetdyn->item(14, 1)->text();
        m_dyn_Cg = ui->tableWidgetdyn->item(15, 1)->text();

        m_dyn_rho = ui->tableWidgetdyn->item(17, 1)->text();
        m_dyn_E = ui->tableWidgetdyn->item(18, 1)->text();
        m_dyn_v = ui->tableWidgetdyn->item(19, 1)->text();
        m_dyn_rhoc = ui->tableWidgetdyn->item(20, 1)->text();
        m_dyn_Ec = ui->tableWidgetdyn->item(21, 1)->text();
        m_dyn_vc = ui->tableWidgetdyn->item(22, 1)->text();

        m_dyn_T0 = ui->tableWidgetdyn->item(24, 1)->text();
        m_dyn_n0 = ui->tableWidgetdyn->item(25, 1)->text();
        m_dyn_alpha = ui->tableWidgetdyn->item(26, 1)->text();
        m_dyn_beta = ui->tableWidgetdyn->item(27,1)->text();
        m_dyn_K = ui->tableWidgetdyn->item(28, 1)->text();

        m_dyn_h0 = ui->tableWidgetdyn->item(30, 1)->text();
        m_dyn_kt = ui->tableWidgetdyn->item(31, 1)->text();
        m_dyn_Ferr = ui->tableWidgetdyn->item(32, 1)->text();
        m_dyn_Uerr = ui->tableWidgetdyn->item(33, 1)->text();
        m_dyn_T = ui->tableWidgetdyn->item(34, 1)->text();

        //只有or合适的时候才能保存
        if(flag_canI == 0)
        {
            //确认保存路径
            m_inputsavefile_name3 = QFileDialog::getSaveFileName(this,"保存文件",".","数据输入文件(*.dynin)");

            QFile datasavesta_1_file(m_inputsavefile_name3);
            if (!datasavesta_1_file.open(QIODevice::WriteOnly | QIODevice::Text))
                    return;
            QTextStream stadata_1_out(&datasavesta_1_file);

            //设置输出文字格式，使得中文也能输出
            //QSettings settings(datasavefile_name, QSettings::IniFormat);
            //settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
            stadata_1_out.setCodec(QTextCodec::codecForName("utf-8"));

            //开始写入,按照标准格式
            stadata_1_out  <<tr("(1)工况条件")<<"\t"<<tr(" ")<<"\t"<<"\n";
            stadata_1_out  <<tr("径向载荷(Fr) =")<<"\t"<< m_dyn_Fr <<"\t"<<tr("N")<< "\n";
            stadata_1_out  <<tr("轴向载荷(Fa) =")<<"\t"<< m_dyn_Fa <<"\t"<<tr("N")<< "\n";
            stadata_1_out  <<tr("力矩(My) =")<<"\t"<< m_dyn_My <<"\t"<<tr("N*mm")<<"\n";
            stadata_1_out  <<tr("力矩(Mz) =")<<"\t"<< m_dyn_Mz <<"\t"<<tr("N*mm")<<"\n";
            stadata_1_out  <<tr("内圈转速(n) =")<<"\t"<< m_dyn_ni  <<"\t"<<tr("rpm")<< "\n";
            stadata_1_out  <<tr("引导方式 =")<<"\t"<< m_dyn_OR  <<"\t"<< "\n";

            stadata_1_out  <<tr("(2)结构参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
            stadata_1_out  <<tr("钢球个数(Z) =")<<"\t"<< m_dyn_z <<"\t"<<"\n";
            stadata_1_out  <<tr("钢球直径(D) =")<<"\t"<< m_dyn_D <<"\t"<<tr("mm")<< "\n";
            stadata_1_out  <<tr("内圈直径(dm) =")<<"\t"<< m_dyn_dm <<"\t"<<tr("mm")<< "\n";
            stadata_1_out  <<tr("初始接触角 =")<<"\t"<< m_dyn_alpha0 <<"\t"<<tr("°")<< "\n";
            stadata_1_out  <<tr("内圈沟渠率半径系数 =")<<"\t"<< m_dyn_fi  <<"\t"<< "\n";
            stadata_1_out  <<tr("外圈沟渠率半径系数 =")<<"\t"<< m_dyn_fe  <<"\t"<< "\n";
            stadata_1_out  <<tr("保持架兜孔间隙(Cp) =")<<"\t"<< m_dyn_Cp <<"\t"<<tr("mm")<< "\n";
            stadata_1_out  <<tr("保持架引导间隙(Cg) =")<<"\t"<< m_dyn_Cg <<"\t"<<tr("mm")<< "\n";

            stadata_1_out  <<tr("(3)材料参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
            stadata_1_out  <<tr("钢球材料密度 =")<<"\t"<< m_dyn_rho <<"\t"<<tr("kg/m^3")<< "\n";
            stadata_1_out  <<tr("钢球弹性模量 =")<<"\t"<< m_dyn_E  <<"\t"<<tr("N/mm^2")<< "\n";
            stadata_1_out  <<tr("钢球泊松比 =")<<"\t"<< m_dyn_v  <<"\t"<< "\n";
            stadata_1_out  <<tr("保持架材料密度 =")<<"\t"<< m_dyn_rhoc <<"\t"<<tr("kg/m^3")<< "\n";
            stadata_1_out  <<tr("保持架弹性模量 =")<<"\t"<< m_dyn_Ec  <<"\t"<<tr("N/mm^2")<< "\n";
            stadata_1_out  <<tr("保持架泊松比 =")<<"\t"<< m_dyn_vc  <<"\t"<< "\n";

            stadata_1_out  <<tr("(4)润滑剂/摩擦相关参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
            stadata_1_out  <<tr("环境温度(T0) =")<<"\t"<< m_dyn_T0<<tr(" ")<<"\t"<<tr("˚C")<< "\n";
            stadata_1_out  <<tr("常温常压下润滑油粘度(η0) =")<<"\t"<< m_dyn_n0<<tr(" ")<<"\t"<<tr("Pa·s")<< "\n";
            stadata_1_out  <<tr("润滑油黏压系数(α) =")<<"\t"<< m_dyn_alpha<<tr(" ")<<"\t"<<tr("Pa-1 ")<< "\n";
            stadata_1_out  <<tr("润滑油黏温(β) =")<<"\t"<< m_dyn_beta<<tr(" ")<<"\t"<<tr("K-1 ")<< "\n";
            stadata_1_out  <<tr("润滑油热传导系数(K) =")<<"\t"<< m_dyn_K<<"\t"<<tr("N/(s·K)")<<"\n";

            stadata_1_out  <<tr("(5)数值计算相关参数")<<"\t"<<tr(" ")<<"\t"<< "\n";
            stadata_1_out  <<tr("初始步长(h0) =")<<"\t"<< m_dyn_h0<<"\t"<<tr("s")<<"\n";
            stadata_1_out  <<tr("步长修正系数(kt) =")<<"\t"<< m_dyn_kt<<"\t"<<"\n";
            stadata_1_out  <<tr("力残差(Ferr) =")<<"\t"<< m_dyn_Ferr<<"\t"<<tr("N")<<"\n";
            stadata_1_out  <<tr("位移残差(uerr) =")<<"\t"<< m_dyn_Uerr<<"\t"<<tr("mm")<<"\n";
            stadata_1_out  <<tr("动力学分析时间(T) =")<<"\t"<< m_dyn_T<<"\t"<<tr("s")<<"\n";

            datasavesta_1_file.close();
}

}

//配置数据
void Dyn_Input::on_pushButtondynconfig_clicked()
{
    //界面配置
    ui->tabWidget_dyn->setCurrentWidget(ui->tab_opennew);
    ui->tabWidget_parameters->setCurrentWidget(ui->tab_structure);
    //取值
    m_dyn_Fr = ui->tableWidgetdyn->item(1, 1)->text();
    m_dyn_Fa = ui->tableWidgetdyn->item(2, 1)->text();
    m_dyn_My = ui->tableWidgetdyn->item(3, 1)->text();
    m_dyn_Mz = ui->tableWidgetdyn->item(4, 1)->text();
    m_dyn_ni = ui->tableWidgetdyn->item(5, 1)->text();
    m_dyn_OR = ui->tableWidgetdyn->item(6, 1)->text();
    if(!(m_dyn_OR=="0" || m_dyn_OR=="1"||m_dyn_OR=="2"))
    {
        QMessageBox::warning(this,"错误","引导方式只能是0，1，2，请重新输入");
        ui->tabWidget_dyn->setCurrentWidget(ui->tab_readfiles);
        //ui->tabWidget_parameters->setCurrentWidget(ui->tab_working);
    }

    m_dyn_z = ui->tableWidgetdyn->item(8, 1)->text();
    m_dyn_D = ui->tableWidgetdyn->item(9, 1)->text();
    m_dyn_dm = ui->tableWidgetdyn->item(10, 1)->text();
    m_dyn_alpha0 = ui->tableWidgetdyn->item(11, 1)->text();
    m_dyn_fi = ui->tableWidgetdyn->item(12, 1)->text();
    m_dyn_fe = ui->tableWidgetdyn->item(13, 1)->text();
    m_dyn_Cp = ui->tableWidgetdyn->item(14, 1)->text();
    m_dyn_Cg = ui->tableWidgetdyn->item(15, 1)->text();

    m_dyn_rho = ui->tableWidgetdyn->item(17, 1)->text();
    m_dyn_E = ui->tableWidgetdyn->item(18, 1)->text();
    m_dyn_v = ui->tableWidgetdyn->item(19, 1)->text();
    m_dyn_rhoc = ui->tableWidgetdyn->item(20, 1)->text();
    m_dyn_Ec = ui->tableWidgetdyn->item(21, 1)->text();
    m_dyn_vc = ui->tableWidgetdyn->item(22, 1)->text();

    m_dyn_T0 = ui->tableWidgetdyn->item(24, 1)->text();
    m_dyn_n0 = ui->tableWidgetdyn->item(25, 1)->text();
    m_dyn_alpha = ui->tableWidgetdyn->item(26, 1)->text();
    m_dyn_beta = ui->tableWidgetdyn->item(27,1)->text();
    m_dyn_K = ui->tableWidgetdyn->item(28, 1)->text();

    m_dyn_h0 = ui->tableWidgetdyn->item(30, 1)->text();
    m_dyn_kt = ui->tableWidgetdyn->item(31, 1)->text();
    m_dyn_Ferr = ui->tableWidgetdyn->item(32, 1)->text();
    m_dyn_Uerr = ui->tableWidgetdyn->item(33, 1)->text();
    m_dyn_T = ui->tableWidgetdyn->item(34, 1)->text();
    //赋值
    ui->lineEditdynD->          setText(m_dyn_D);
    ui->lineEditdynE->          setText(m_dyn_E);
    ui->lineEditdynK->          setText(m_dyn_K);
    ui->lineEditdynT->          setText(m_dyn_T);
    ui->lineEditdynv->          setText(m_dyn_v);
    ui->lineEditdynz->          setText(m_dyn_z);
    ui->lineEditdynCg->         setText(m_dyn_Cg);
    ui->lineEditdynCp->         setText(m_dyn_Cp);
    ui->lineEditdynFa->         setText(m_dyn_Fa);
    ui->lineEditdynFr->         setText(m_dyn_Fr);
    ui->lineEditdynMy->         setText(m_dyn_My);
    ui->lineEditdynMz->         setText(m_dyn_Mz);
    ui->lineEditdynT0->         setText(m_dyn_T0);
    ui->lineEditdyndm->         setText(m_dyn_dm);
    ui->lineEditdynfe->         setText(m_dyn_fe);
    ui->lineEditdynfi->         setText(m_dyn_fi);
    ui->lineEditdynh0->         setText(m_dyn_h0);
    ui->lineEditdynFerr->       setText(m_dyn_Ferr);
    ui->lineEditdynUerr->       setText(m_dyn_Uerr);
    ui->lineEditdynbeta->       setText(m_dyn_beta);
    ui->lineEditdynalpha->      setText(m_dyn_alpha);
    ui->lineEditdynalpha0->     setText(m_dyn_alpha0);
    ui->lineEditdynE_kepper->   setText(m_dyn_Ec);
    ui->lineEditdynv_kepper->   setText(m_dyn_vc);
    ui->lineEditdynrho_kepper-> setText(m_dyn_rhoc);
    ui->lineEditdynrho->        setText(m_dyn_rho);
    ui->lineEditdynni->         setText(m_dyn_ni);
    ui->lineEditdynn0->         setText(m_dyn_n0);
    ui->lineEditdynkt->         setText(m_dyn_kt);
    //combobox设置
    int indexOR = m_dyn_OR.right(1).toInt();
    switch (indexOR)
    {
    case 0: ORdyn = 0 ;ui->comboBox_dyn->setCurrentIndex(0);;break;
    case 1: ORdyn = 1 ;ui->comboBox_dyn->setCurrentIndex(1);;break;
    case 2: ORdyn= 2 ;ui->comboBox_dyn->setCurrentIndex(2);;break;
    default:break;
    }
}
