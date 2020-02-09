#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<string>
#include<QObject>
#include<stack>
#include<stdlib.h>
#include<cmath>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->text->setReadOnly(true);
    setWindowTitle(QString("计算器"));
}
MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::getText(){
    return ui->text->text();
}
void MainWindow::setText(QString text){
    ui->text->setText(text);
}
void MainWindow::on_pushButton_clicked()
{
    QString text = getText();
    setText(text+"7");
}
void MainWindow::on_pushButton_2_clicked()
{
    QString text = getText();
    setText(text+"8");
}
void MainWindow::on_pushButton_3_clicked()
{
    QString text = getText();
    setText(text+"9");
}
void MainWindow::on_pushButton_4_clicked()
{
    QString text = getText();
    setText(text+"*");
}
void MainWindow::on_pushButton_17_clicked()
{
    QString text = getText();
    setText(text+"(");
}
void MainWindow::on_pushButton_5_clicked()
{
    QString text = getText();
    setText(text+"4");
}
void MainWindow::on_pushButton_6_clicked()
{
    QString text = getText();
    setText(text+"5");
}
void MainWindow::on_pushButton_7_clicked()
{
    QString text = getText();
    setText(text+"6");
}
void MainWindow::on_pushButton_8_clicked()
{
    QString text = getText();
    setText(text+"/");
}
void MainWindow::on_pushButton_18_clicked()
{
    QString text = getText();
    setText(text+")");
}
void MainWindow::on_pushButton_9_clicked()
{
    QString text = getText();
    setText(text+"1");
}
void MainWindow::on_pushButton_10_clicked()
{
    QString text = getText();
    setText(text+"2");
}
void MainWindow::on_pushButton_11_clicked()
{
    QString text = getText();
    setText(text+"3");
}
void MainWindow::on_pushButton_12_clicked()
{
    QString text = getText();
    setText(text+"+");
}
void MainWindow::on_pushButton_19_clicked()
{
    QString text = getText();
    setText(text+"^");
}
void MainWindow::on_pushButton_13_clicked()
{
    QString text = getText();
    setText(text+"0");
}
void MainWindow::on_pushButton_14_clicked()
{
    QString text = getText();
    setText(text+".");
}
//判断是不是小数
bool judge(double d)
{
    double res = d - floor(d);
    if(res)
        return true;
    return false;
}
void MainWindow::on_pushButton_23_clicked()
{
    string exp = getText().toStdString();
    char *expr = (char*)exp.c_str();
    int i;
    if(!isMatch(expr)){
        QMessageBox::critical(this, "错误信息","表达式括号不匹配，重新输入",QMessageBox::Ok,QMessageBox::NoButton);
       return ;
    }
    else{
        try{
            double d = calculator(expr);
            char temp[50]={0};
            sprintf(temp,"%.8f",d);
            for(i=0;i<50;i++){
                if(temp[i]=='.')
                    break;
            }
            if(!judge(d)){

                temp[i]='\0';
            }
           setText(QObject::tr(temp));
        }catch(const char *s){
            QMessageBox::critical(this, "错误信息",s,QMessageBox::Ok,QMessageBox::NoButton);
        }
    }
}
void MainWindow::on_pushButton_16_clicked()
{
    QString text = getText();
    setText(text+"-");
}
void MainWindow::on_pushButton_20_clicked()
{
    string text = getText().toStdString();
    string res = text.substr(0,text.size()-1);
    setText(QObject::tr(res.c_str()));
}
void MainWindow::on_pushButton_15_clicked()
{
    setText("");

}
int MainWindow::getPriority(string opt) {
    if(opt=="#")
        return 5;
    else if(opt=="^")
        return 4;
    else if(opt=="*"||opt=="/"||opt=="%")
        return 3;
    else if(opt=="+"||opt=="-")
        return 2;
    else if(opt=="(")
        return 1;

}
void MainWindow::calculate(stack<double> &opdStack,string opt) {
    //先出栈的为右操作数，后出栈的为左操作数
    if(opt=="#") {
        if(opdStack.size()==0)
            throw "操作数数量异常，运算失败";
        double opd = opdStack.top();
        opdStack.pop();
        opdStack.push(0-opd);//进行负号运算
    } else{
        if(opdStack.size()<2)
            throw "操作数数量异常，运算失败";
        if(opt=="+") {
            double rOpd = opdStack.top();
            opdStack.pop();
            double lOpd = opdStack.top();
            opdStack.pop();
            opdStack.push(lOpd + rOpd);//进行加号运算
        } else if(opt=="-") {
            double rOpd = opdStack.top();
            opdStack.pop();
            double lOpd = opdStack.top();
            opdStack.pop();
            opdStack.push(lOpd - rOpd);//进行减号运算
        } else if(opt=="*") {
            double rOpd = opdStack.top();
            opdStack.pop();
            double lOpd = opdStack.top();
            opdStack.pop();
            opdStack.push(lOpd * rOpd);//进行乘号运算
        } else if(opt=="/")	{
            double rOpd = opdStack.top();
            if(rOpd == 0)
                throw "除数不能为零";
            opdStack.pop();
            double lOpd = opdStack.top();
            opdStack.pop();
            opdStack.push(lOpd / rOpd);//进行除号运算
        } else if(opt=="^") {
            double rOpd = opdStack.top();
            opdStack.pop();
            double lOpd = opdStack.top();
            opdStack.pop();
            opdStack.push(pow(lOpd,rOpd));//进行幂运算
        }else if(opt=="%"){
            double rOpd = opdStack.top();
            opdStack.pop();
            double lOpd = opdStack.top();
            opdStack.pop();
            if( judge(rOpd)|| judge(lOpd)|| rOpd<0 || lOpd<0)
                throw "不能对小数或负数求余";
            int left = lOpd,right = rOpd;
            opdStack.push((left%right));//进行幂运算
        }
    }

}
vector<string> MainWindow::prePossess(const char* str) {
    //	cout<<"enter prepossess"<<endl;
    vector<string> tokens;
    char *temp= new char[strlen(str)+1];
    char *token = new char[2];
    string s;
    int i=0,k,j=0,index;
    bool flag;
    strcpy(temp,str);
    i=0;
    int length = strlen(temp);
    while(temp[i]!='\0') {
        switch(temp[i]) {
        case '/':
        case '*':
        case '^':
        case '%':
        case '(':
        case ')': {
            token[0]=temp[i];
            token[1]='\0';
            s=token;
            tokens.push_back(s);
            i++;
            break;
        }
        case '-': {
            k=i-1;
            //将减号用作负号 #代表负号
            // 当前一个字符为')'或者数字 -作为减号使用
            if(  isdigit(temp[k]) || temp[k]==')'  ) {
                token[0]='-';
                token[1]='\0';
                s=token;
                tokens.push_back(s);
            } else {
                token[0]='#';
                token[1]='\0';
                s=token;
                tokens.push_back(s);
            }
            i++;
            break;
        }
        case '+': {
            k=i-1;
            //同样 +作为加号使用时，当前一个字符为‘)’或者数字
            if(  isdigit(temp[k]) || temp[k]==')'  ) {
                token[0]='+';
                token[1]='\0';
                s=token;
                tokens.push_back(s);
            }
            i++;
            // 否则 +号可以直接去掉 如+3 变为 3
            break;
        }
            //数字
        default: {
            index = i;
            flag = false;
            //找到整个数字 可能为小数
            while( ( isdigit(str[index]) || str[index]=='.') && (index<length) )
            {
                //输入两个小数
                if(str[index]=='.')
                {
                    if(flag)
                        throw "表达式有错，请检查表达式";
                    flag = true;
                }
                  index++;

            }
            char *number = new char[20];
            strncpy(number,str+i,index-i);//复制
            number[index-i]='\0';//加\0
            s=number;
            tokens.push_back(s);
            i=index;
            delete []number;
            break;
        }
        }
    }
    delete []temp;
    delete []token;
    return tokens;
}
double MainWindow::getNumber(string source) {
    //	cout<<"enter getnumber"<<endl;
    //整数
    if(source.find(".")==string::npos) {
        return (double)(atoi(source.c_str()));
    }
    //小数
    else {
        double a = atoi( (source.substr(0,source.find("."))).c_str() );
        string s2=source.substr(source.find(".")+1,source.size());
        double b =  (atoi(s2.c_str()))/(pow(10,s2.size())) ;
        return a+b;
    }
}
double MainWindow::calculator(char *exp) {
    //	cout<<"enter calculator"<<endl;
    stack<double> opnd;//操作数栈
    stack<string> optr;//操作符栈
    vector<string> tokens = prePossess(exp);//处理过的表达式
    string token;
    string topOptr;//栈顶运算符
    int pri,//当前优先级
            topPri; //栈顶优先级
    for(int i=0; i<tokens.size(); i++) {
        token = tokens[i];
        if( token=="+" || token=="-" || token=="*"
            || token=="/" || token=="^" || token =="#"
            || token=="%" ) {
            if(optr.size()==0)
                optr.push(token);
            else {
                pri = getPriority(token);
                topPri = getPriority(optr.top());
                //当前优先级高 入栈
                if(pri>topPri)
                    optr.push(token);
                //否则 开始运算
                else {
                    while(pri<=topPri) {
                        topOptr = optr.top();
                        calculate(opnd,topOptr);
                        optr.pop();
                        //如果运算符栈不空 继续判断是否可以运算
                        if(optr.size()>0) {
                            topOptr = optr.top();
                            topPri = getPriority(topOptr);
                        } else break;
                    }
                    //比栈顶优先级低 同样入栈
                    optr.push(token);
                }
            }
        }
        //( 直接入栈
        else if(token=="(")
            optr.push(token);
        // ) 运算直到栈顶为（
        else if(token==")") {
            while(optr.top()!="(") {
                calculate(opnd,optr.top());
                optr.pop();
            }
            optr.pop();//出栈(
        } else {
            opnd.push(getNumber(token));
        }
    }
    //计算到运算符栈为空
    if(optr.size()!=0){
        while(optr.size()!=0) {
            string c = optr.top();
            calculate(opnd,c);
            optr.pop();
        }
    }
    //操作数不为1 而运算符栈已空 表达式有错
    if(optr.size()==0 &&opnd.size()!=1)
        throw "表达式有错误，运算出现异常，请检查表达式";
    return opnd.top();
}
//判断括号是否匹配
bool MainWindow::isMatch(const char* str) {
    stack<char> s;
    int i =0;
    while(str[i]!='\0') {
        if(str[i]=='(')
            s.push(str[i]);
        else if(str[i]==')') {
            //缺少左括号 不匹配
            if(s.empty())
                return false;
            if(s.top()=='(')
                s.pop();
        }
        i++;
    }
    return s.empty();
}
void MainWindow::on_pushButton_21_clicked()
{
    QString text = getText();
    setText(text+"%");
}
