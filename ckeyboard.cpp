#include "ckeyboard.h"
#include "ui_ckeyboard.h"


CKeyboard::CKeyboard(QWidget *parent,int type) :
    QWidget(parent),
    ui(new Ui::CKeyboard),
    keyButtonCount(0),
    bCapsOn(0),
    ShiftIndex(0)
{
    ui->setupUi(this);
    QDesktopWidget *desktop=QApplication::desktop();
    QRect clientRect = desktop->availableGeometry();
    //获取客户区的宽高
   int width=clientRect.width();
   int height=clientRect.height();
   qDebug()<<"*******width="<<width<<"*********height="<<height<<__LINE__;

    width = 1360;
    height = 900;

    if(desktop->width()>=1024)
    {
        float fsp[2] = {0};
        fsp[0]=(float)width/SYSTEM_WIN_WIDTH;
        fsp[1]=(float)height/SYSTEM_WIN_HEIGHT;
        int KeyboardX = 158*fsp[0];
        int keyboardY =  height -MMS_LOGIN_KEYBOARD_HEIGHT_600P*fsp[1];
        width =MMS_LOGIN_KEYBOARD_WIDTH*fsp[0]+GRAPS_BETWEEN_CONTROLS*2;
        height =MMS_LOGIN_KEYBOARD_HEIGHT*fsp[1]+GRAPS_BETWEEN_CONTROLS*2;


        move(KeyboardX,keyboardY);

    }
    else
    {
        float fsp[2] = {0};
        fsp[0]=(float)width/SYSTEM_WIN_WIDTH_600P;
        fsp[1]=(float)height/SYSTEM_WIN_HEIGHT_600P;
        int KeyboardX = 124*fsp[0];
        int keyboardY =  height -MMS_LOGIN_KEYBOARD_HEIGHT_600P*fsp[1];
        width =MMS_LOGIN_KEYBOARD_WIDTH_600P*fsp[0]+GRAPS_BETWEEN_CONTROLS*2;
        height =MMS_LOGIN_KEYBOARD_HEIGHT_600P*fsp[1]+GRAPS_BETWEEN_CONTROLS*2;
        move(KeyboardX,keyboardY);

    }


    QStringList qss;
    qss.append(QString("%1}").arg(QString::fromLocal8Bit(" font-family:'微软雅黑';")));
    setStyleSheet(qss.join(""));

    resize(width,height);
    if(type==0)
        setWindowFlags(Qt::FramelessWindowHint|Qt::Tool|Qt::WindowDoesNotAcceptFocus);//无边框
    //this->setFocusPolicy(Qt::NoFocus);

    int m_width = 1360;
    int m_height = 900;

    m_buGroup = new QButtonGroup();//按钮组


    CreatKeyBoard();
    connect(m_buGroup, SIGNAL(buttonClicked(int)),this, SLOT(buttonNumslot(int)));
    if(desktop->width()>=1024)
    {
       ResizeControl(m_width,m_height);
//       ResizeControl(clientRect.width(),clientRect.height());

        SetControlStyleSheet();
    }
    else
    {
       ResizeControl_600P(clientRect.width(),clientRect.height());
       SetControlStyleSheet_600P();
    }

    hide();
    this->setFocusPolicy(Qt::NoFocus);
}

CKeyboard::~CKeyboard()
{
    delete ui;
}

void CKeyboard::CreatKeyBoard()
{
    CapKey.clear();
    ComKey.clear();
    //------1
    CapKey.push_back('~');
    CapKey.push_back('!');
    CapKey.push_back('@');
    CapKey.push_back('#');
    CapKey.push_back('$');
    CapKey.push_back('%');
    CapKey.push_back('^');
    CapKey.push_back('&');
    CapKey.push_back('*');
    CapKey.push_back('(');
    CapKey.push_back(')');
    CapKey.push_back('_');
    CapKey.push_back('+');
    CapKey.push_back(BSPACE);

    ComKey.push_back('`');
    ComKey.push_back('1');
    ComKey.push_back('2');
    ComKey.push_back('3');
    ComKey.push_back('4');
    ComKey.push_back('5');
    ComKey.push_back('6');
    ComKey.push_back('7');
    ComKey.push_back('8');
    ComKey.push_back('9');
    ComKey.push_back('0');
    ComKey.push_back('-');
    ComKey.push_back('=');
    ComKey.push_back(0x00);

    //-------2
    CapKey.push_back(TAB);
    CapKey.push_back('Q');
    CapKey.push_back('W');
    CapKey.push_back('E');
    CapKey.push_back('R');
    CapKey.push_back('T');
    CapKey.push_back('Y');
    CapKey.push_back('U');
    CapKey.push_back('I');
    CapKey.push_back('O');
    CapKey.push_back('P');
    CapKey.push_back('{');
    CapKey.push_back('}');
    CapKey.push_back('|');

    ComKey.push_back(0x00);
    ComKey.push_back('q');
    ComKey.push_back('w');
    ComKey.push_back('e');
    ComKey.push_back('r');
    ComKey.push_back('t');
    ComKey.push_back('y');
    ComKey.push_back('u');
    ComKey.push_back('i');
    ComKey.push_back('o');
    ComKey.push_back('p');
    ComKey.push_back('[');
    ComKey.push_back(']');
    ComKey.push_back('\\');


    //--------3
    CapKey.push_back(CAPS);
    CapKey.push_back('A');
    CapKey.push_back('S');
    CapKey.push_back('D');
    CapKey.push_back('F');
    CapKey.push_back('G');
    CapKey.push_back('H');
    CapKey.push_back('J');
    CapKey.push_back('K');
    CapKey.push_back('L');
    CapKey.push_back(':');
    CapKey.push_back('\"');
    CapKey.push_back(ENTER);

    ComKey.push_back(0x00);
    ComKey.push_back('a');
    ComKey.push_back('s');
    ComKey.push_back('d');
    ComKey.push_back('f');
    ComKey.push_back('g');
    ComKey.push_back('h');
    ComKey.push_back('j');
    ComKey.push_back('k');
    ComKey.push_back('l');
    ComKey.push_back(';');
    ComKey.push_back('\'');
    ComKey.push_back(0x00);

    //----------4
    CapKey.push_back(SHIFT);
    CapKey.push_back('Z');
    CapKey.push_back('X');
    CapKey.push_back('C');
    CapKey.push_back('V');
    CapKey.push_back('B');
    CapKey.push_back('N');
    CapKey.push_back('M');
    CapKey.push_back('<');
    CapKey.push_back('>');
    CapKey.push_back('?');
    CapKey.push_back(SHIFT2);

    ComKey.push_back(0x00);
    ComKey.push_back('z');
    ComKey.push_back('x');
    ComKey.push_back('c');
    ComKey.push_back('v');
    ComKey.push_back('b');
    ComKey.push_back('n');
    ComKey.push_back('m');
    ComKey.push_back(',');
    ComKey.push_back('.');
    ComKey.push_back('/');
    ComKey.push_back(0x00);

    QPushButton *button;
    for(int i=0;i<4;i++)
    {
        int linenum =i+1;
        if(linenum ==3)
        {
            for(int i=0;i<13;i++)
            {
                button =new QPushButton(ui->widget_KeyBoard);
                keyBoardButton[keyButtonCount]=button;
                keyBoardButton[keyButtonCount]->setFocusPolicy(Qt::NoFocus);
                m_buGroup->addButton(keyBoardButton[keyButtonCount],keyButtonCount);
                keyButtonCount++;
            }
        }
        else if(linenum ==4)
        {
            for(int i=0;i<12;i++)
            {
                button =new QPushButton(ui->widget_KeyBoard);
                keyBoardButton[keyButtonCount]=button;
                keyBoardButton[keyButtonCount]->setFocusPolicy(Qt::NoFocus);
                m_buGroup->addButton(keyBoardButton[keyButtonCount],keyButtonCount);
                keyButtonCount++;
            }
        }
        else
        {
           for(int i=0;i<14;i++)
           {
               button =new QPushButton(ui->widget_KeyBoard);
               keyBoardButton[keyButtonCount]=button;
               keyBoardButton[keyButtonCount]->setFocusPolicy(Qt::NoFocus);
               m_buGroup->addButton(keyBoardButton[keyButtonCount],keyButtonCount);
               keyButtonCount++;
           }
        }

    }

}

void CKeyboard::SetControlStyleSheet()
{
    QString text ;
    allButtons = ui->widget_KeyBoard->findChildren<QPushButton *>();
    for( int i=0;i<allButtons.count();i++)
    {
       if(CapKey[i]== BSPACE )
       {
           text ="Backspace";
       }
       else if(CapKey[i]== TAB)
       {
           text ="TAB";
       }
       else if(CapKey[i]== CAPS)
       {
           text ="CapsLock";
       }
       else if(CapKey[i]== ENTER)
       {
           text ="Enter";
       }
       else if(CapKey[i]== SHIFT)
       {
           text ="Shift";
       }
       else if(CapKey[i]== SHIFT2)
       {
           text ="Shift";
       }
       else
       {
           if(CapKey[i]== '&')
           {
                text =QString("%1%2%3").arg("&&").arg("\n").arg(ComKey[i]);
           }
           else
           {
                text =QString("%1%2%3").arg(CapKey[i]).arg("\n").arg(ComKey[i]);
           }
           keyBoardButton[i]->setText(text);
           keyBoardButton[i]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);text-align: left; font-size: 12pt;color:white;border:1px solid rgb(134,134,134);}");
           continue;
       }
       keyBoardButton[i]->setText(text);
       keyBoardButton[i]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);font-size: 12pt;color:white;border:1px solid rgb(134,134,134);}");

    }

}


void CKeyboard::SetControlStyleSheet_600P()
{

    QString text ;
    allButtons = ui->widget_KeyBoard->findChildren<QPushButton *>();
    for( int i=0;i<allButtons.count();i++)
    {
       if(CapKey[i]== BSPACE )
       {
           text ="Backspace";
       }
       else if(CapKey[i]== TAB)
       {
           text ="TAB";
       }
       else if(CapKey[i]== CAPS)
       {
           text ="CapsLock";
       }
       else if(CapKey[i]== ENTER)
       {
           text ="Enter";
       }
       else if(CapKey[i]== SHIFT)
       {
           text ="Shift";
       }
       else if(CapKey[i]== SHIFT2)
       {
           text ="Shift";
       }
       else
       {
           if(CapKey[i]== '&')
           {
                text =QString("%1%2%3").arg("&&").arg("\n").arg(ComKey[i]);
           }
           else
           {
                text =QString("%1%2%3").arg(CapKey[i]).arg("\n").arg(ComKey[i]);
           }
           keyBoardButton[i]->setText(text);
           keyBoardButton[i]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);text-align: left; font-size: 6pt;color:white;border:1px solid rgb(134,134,134);}");
           continue;
       }
       keyBoardButton[i]->setText(text);
       keyBoardButton[i]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);font-size: 6pt;color:white;border:1px solid rgb(134,134,134);}");


    }
}

void CKeyboard::ResizeControl(int width,int height)
{
    float fsp[2] = {0};
    fsp[0]=(float)width/SYSTEM_WIN_WIDTH;
    fsp[1]=(float)height/SYSTEM_WIN_HEIGHT;

    ui->widget_KeyBoard->move(GRAPS_BETWEEN_CONTROLS,GRAPS_BETWEEN_CONTROLS);
    ui->widget_KeyBoard->resize(MMS_LOGIN_KEYBOARD_WIDTH*fsp[0],MMS_LOGIN_KEYBOARD_HEIGHT*fsp[1]);

    allButtons = ui->widget_KeyBoard->findChildren<QPushButton *>();
    int keyCount =0;
    int lineNum =0;
    int keyX =0;
    int keyY =0;
    for( int i=0;i<allButtons.count();i++)
    {
        if(i==0)
        {
            lineNum=1;
            keyX =1;
            keyY =32*fsp[1]*(lineNum-1)+lineNum*1;

            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(47*fsp[0],32*fsp[1]);
            keyCount++;
            keyX +=47*fsp[0];
        }
        else if(CapKey.at(i) ==TAB)
        {
            lineNum=2;
            keyCount=0;
            keyX =1;
            keyY =32*fsp[1]*(lineNum-1)+lineNum*1;
            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(67*fsp[0],32*fsp[1]);
            keyCount++;
            keyX +=67*fsp[0];
        }
        else if(CapKey.at(i) ==CAPS)
        {
            lineNum=3;
            keyCount=0;
            keyX =1;
            keyY =32*fsp[1]*(lineNum-1)+lineNum*1;
            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(86*fsp[0],32*fsp[1]);
            keyCount++;
            keyX +=86*fsp[0];
        }
        else if(CapKey.at(i) ==SHIFT)
        {
            lineNum=4;
            keyCount=0;
            keyX =1;
            keyY =32*fsp[1]*(lineNum-1)+lineNum*1;
            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(105*fsp[0],32*fsp[1]);
            keyCount++;
            keyX +=105*fsp[0];
        }
        else
        {
            if(CapKey.at(i)== BSPACE || CapKey.at(i)== '|' || CapKey.at(i)== ENTER ||CapKey.at(i)== SHIFT2)
            {
                int width = MMS_LOGIN_KEYBOARD_NEW_HEIGHT*fsp[0]- keyX-1;
                if(width<=0)
                    width = 47;

                keyBoardButton[i]->move(keyX,keyY);
                keyBoardButton[i]->resize(width,32*fsp[1]);
                keyCount++;
                keyX +=width;
            }
            else
            {

                keyBoardButton[i]->move(keyX,keyY);
                keyBoardButton[i]->resize(47*fsp[0],32*fsp[1]);
                keyCount++;
                keyX +=47*fsp[0];
            }
        }
    }
}

void  CKeyboard::ResizeControl_600P(int width,int height)
{
    float fsp[2] = {0};
    fsp[0]=(float)width/SYSTEM_WIN_WIDTH_600P;
    fsp[1]=(float)height/SYSTEM_WIN_HEIGHT_600P;

    ui->widget_KeyBoard->move(GRAPS_BETWEEN_CONTROLS,GRAPS_BETWEEN_CONTROLS);
    ui->widget_KeyBoard->resize(MMS_LOGIN_KEYBOARD_WIDTH_600P*fsp[0],MMS_LOGIN_KEYBOARD_HEIGHT_600P*fsp[1]);

    allButtons = ui->widget_KeyBoard->findChildren<QPushButton *>();
    int keyCount =0;
    int lineNum =0;
    int keyX =0;
    int keyY =0;
    for( int i=0;i<allButtons.count();i++)
    {
        if(i==0)
        {
            lineNum=1;
            keyX =1;
            keyY =25*fsp[1]*(lineNum-1)+lineNum*1;

            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(38*fsp[0],25*fsp[1]);
            keyCount++;
            keyX +=38*fsp[0];
        }
        else if(CapKey.at(i) ==TAB)
        {
            lineNum=2;
            keyCount=0;
            keyX =1;
            keyY =25*fsp[1]*(lineNum-1)+lineNum*1;
            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(53*fsp[0],25*fsp[1]);
            keyCount++;
            keyX +=53*fsp[0];
        }
        else if(CapKey.at(i) ==CAPS)
        {
            lineNum=3;
            keyCount=0;
            keyX =1;
            keyY =25*fsp[1]*(lineNum-1)+lineNum*1;
            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(68*fsp[0],25*fsp[1]);
            keyCount++;
            keyX +=68*fsp[0];
        }
        else if(CapKey.at(i) ==SHIFT)
        {
            lineNum=4;
            keyCount=0;
            keyX =1;
            keyY =25*fsp[1]*(lineNum-1)+lineNum*1;
            keyBoardButton[i]->move(keyX,keyY);
            keyBoardButton[i]->resize(83*fsp[0],25*fsp[1]);
            keyCount++;
            keyX +=83*fsp[0];
        }
        else
        {
            if(CapKey.at(i)== BSPACE || CapKey.at(i)== '|' || CapKey.at(i)== ENTER ||CapKey.at(i)== SHIFT2)
            {
                int width = MMS_LOGIN_KEYBOARD_WIDTH_600P*fsp[0]- keyX-1;
                if(width<=0)
                    width = 38;

                keyBoardButton[i]->move(keyX,keyY);
                keyBoardButton[i]->resize(width,25*fsp[1]);
                keyCount++;
                keyX +=width;
            }
            else
            {
                keyBoardButton[i]->move(keyX,keyY);
                keyBoardButton[i]->resize(38*fsp[0],25*fsp[1]);
                keyCount++;
                keyX +=38*fsp[0];
            }
        }
    }

}

bool CKeyboard::IsSpecialButton(char but)
{
    bool bRet =false;
    if(but == '~' || but =='!' || but =='@' || but =='#' || but =='$' ||but =='%' ||
            but =='^' || but =='&' || but =='*' || but == '('|| but== ')' || but=='_' ||
            but =='+')
    {
        bRet =true;
    }

    return bRet;

}

void CKeyboard::buttonNumslot(int btn)
{

    if(CapKey[btn] ==TAB)
    {
       emit KeyboardPressKeySignal(CapKey[btn] );

    }
    else if(CapKey[btn] ==CAPS)
    {
       if(bCapsOn)
       {
            keyBoardButton[btn]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);font-size: 12pt;color:white;border:1px solid rgb(134,134,134);}");
            bCapsOn =0;
       }
       else
       {

            keyBoardButton[btn]->setStyleSheet("QPushButton{background-color:white;font-size: 12pt;color:black;border:1px solid rgb(134,134,134);}");
            bCapsOn =1;
       }
    }
    else if(CapKey[btn] ==SHIFT ||CapKey[btn] ==SHIFT2)
    {

       if(ShiftIndex ==0)
       {
            keyBoardButton[btn]->setStyleSheet("QPushButton{background-color:white;font-size: 12pt;color:black;border:1px solid rgb(134,134,134);}");
            ShiftIndex =btn;
       }

    }
    else if(CapKey[btn] == BSPACE)
    {

        emit KeyboardPressKeySignal(CapKey[btn] );

    }
    else if(CapKey[btn] == ENTER)
    {
        emit KeyboardPressKeySignal(CapKey[btn] );
    }
    else
    {
        if(IsSpecialButton(CapKey[btn]))
        {
            if(ShiftIndex)
            {
               emit KeyboardPressKeySignal(CapKey[btn]);
               keyBoardButton[ShiftIndex]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);font-size: 12pt;color:white;border:1px solid rgb(134,134,134);}");
               ShiftIndex =0;
            }
            else
            {
             emit KeyboardPressKeySignal(ComKey[btn]);
            }

        }
        else
        {
            if(bCapsOn)
            {
                if(ShiftIndex)
                {
                   emit KeyboardPressKeySignal(ComKey[btn]);
                   keyBoardButton[ShiftIndex]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);font-size: 12pt;color:white;border:1px solid rgb(134,134,134);}");
                   ShiftIndex =0;
                }
                else
                {
                   emit KeyboardPressKeySignal(CapKey[btn]);
                }
            }
            else
            {
                if(ShiftIndex)
                {
                  // SetEdit(CapKey[btn]);
                    emit KeyboardPressKeySignal(CapKey[btn]);
                   keyBoardButton[ShiftIndex]->setStyleSheet("QPushButton{background-color:rgb(48,48,48);font-size: 12pt;color:white;border:1px solid rgb(134,134,134);}");
                   ShiftIndex =0;
                }
                else
                {
                  // SetEdit(ComKey[btn]);
                    emit KeyboardPressKeySignal(ComKey[btn]);
                }
            }
        }
    }

}

