#include "Sapper.h"
#include <QMessageBox>
#include "Click_button.h"
#include "main.cpp"

Sapper::Sapper(QWidget* pwgt/* = 0*/) : QWidget(pwgt)
{
    Game_over = false;
    createBoard();
    Sapper_Board.generateNew();
    showBoard();

}

void Sapper::createBoard()
{
    QFrame* pfrm = new QFrame;
    pfrm->setFrameStyle(QFrame::Panel|QFrame::Raised);
    pfrm->setLineWidth(3);
    ptopLayout = new QGridLayout;

    QPushButton* pcmdA = new QPushButton("Заново");
    QPushButton* pcmdB = new QPushButton("Выход");
    pcmdA->setStyleSheet("background-color: #cc8899");
    pcmdB->setStyleSheet("background-color: #cc8899;");
    setStyleSheet("background-color:#cc8899");

    ptopLayout->addWidget(pcmdA,0,0,1,6);
    ptopLayout->addWidget(pcmdB,0,6,1,5);

    connect(pcmdA,SIGNAL(clicked()),this,SLOT(New_Game_Click()));
    connect(pcmdB,SIGNAL(clicked()),this,SLOT(close()));

    QFont ButtonFont;
    ButtonFont.setPixelSize(20);
    ButtonFont.setFamily("Times New Roman");
    ButtonFont.setBold(1);

    for (uint8_t y=0 ; y<15 ; y++)
    {
        for (uint8_t x=0 ; x<10 ; x++)
        {
            Visual_Button[y][x] = new Click_Button();
            Visual_Button[y][x]->setObjectName(QVariant(y*10+x).toString());

            Visual_Button[y][x]->setFont(ButtonFont);
            Visual_Button[y][x]->setIconSize(QSize(20, 20));
            Visual_Button[y][x]->setFixedSize(25,25);

            ptopLayout->addWidget(Visual_Button[y][x],y+1,x+1);

            connect(Visual_Button[y][x],SIGNAL(leftClicked() ), this, SLOT(Button_Click()));
            connect(Visual_Button[y][x],SIGNAL(rightClicked()), this,SLOT(Button_Click_Right()));
        }
    }

    ptopLayout->addWidget(pfrm);
    ptopLayout->setSpacing(2);

    setLayout(ptopLayout);
}


void Sapper::showBoard()
{
    for (uint8_t y=0 ; y< 15 ; y++)
    {
    for (uint8_t x=0 ; x< 10 ; x++)
    {
        if (Sapper_Board.get(y,x).isClicked())
            {
            Visual_Button[y][x]->setFlat(1);
            if (Sapper_Board.get(y,x).isMine())
                {
                if (Sapper_Board.get(y,x).getStateDown() == 10)
                    {
                        Visual_Button[y][x]->setIcon(QIcon(":/picture/img/02mine.png"));
                    }
                    else
                    {
                        if (Sapper_Board.get(y,x).getStateUp() == 3)
                        {
                            Visual_Button[y][x]->setIcon(QIcon(":/picture/img/05mine.png"));
                        }
                        else
                        {
                            Visual_Button[y][x]->setIcon(QIcon(":/picture/img/01mine.png"));
                        }
                    }
                }

            if (Sapper_Board.get(y,x).getStateDown()>0 && Sapper_Board.get(y,x).getStateDown()<9)
                {
                    Visual_Button[y][x]->setText(QVariant(Sapper_Board.get(y,x).getStateDown()).toString());
                    Visual_Button[y][x]->setStyleSheet("color: " + Sapper_Board.getColorNumber(y,x) + ";");
                }
        }
    else
        {
            Visual_Button[y][x]->setFlat(0);
            Visual_Button[y][x]->setText("");
            Visual_Button[y][x]->setStyleSheet("background-color: #e4c0df");

            if (Sapper_Board.get(y,x).isFlag())
            {
                if (Game_over && Sapper_Board.get(y,x).isMine()==false)
                    Visual_Button[y][x]->setIcon(QIcon(":/picture/img/06flag.png"));
                else
                    Visual_Button[y][x]->setIcon(QIcon(":/picture/img/03flag.png"));
            }
            else
            {
                Visual_Button[y][x]->setIcon(QIcon(""));
            }
        }
    }
    }
}

unsigned short int Sapper::getNumberButtonX(unsigned short int numberObjectButton)
{
    unsigned short int temp = numberObjectButton / 10;
    return numberObjectButton - 10 * temp;
}

unsigned short int Sapper::getNumberButtonY(unsigned short int numberObjectButton)
{
    return numberObjectButton / 10;
}

void Sapper::Button_Click()
{
    if (!Game_over)
        {
            unsigned short int y = getNumberButtonY(QVariant(((QPushButton*)sender())->objectName()).toInt());
            unsigned short int x = getNumberButtonX(QVariant(((QPushButton*)sender())->objectName()).toInt());

            Sapper_Board.setClick(y,x);

            if (Sapper_Board.get(y,x).getStateDown()==0)
            {
                Sapper_Board.clickNeigbors(y,x);
            }
            else
            {
                if (Sapper_Board.isMine(y,x))
                {
                    Game_over = true;
                    Sapper_Board.clickAllMines();
                    Sapper_Board.setMineBoom(y,x);
                    QMessageBox::information(this, "БAAAAM", "Ты проиграл! :(");
                }
            }
            showBoard();
        }
}

void Sapper::Button_Click_Right()
{
    if (!Game_over)
        {
            unsigned short int y = getNumberButtonY(QVariant(((QPushButton*)sender())->objectName()).toInt());
            unsigned short int x = getNumberButtonX(QVariant(((QPushButton*)sender())->objectName()).toInt());

            if (!Sapper_Board.get(y,x).isClicked())
                {
                    if (Sapper_Board.get(y,x).isFlag())
                        {
                            Sapper_Board.unSetFlag(y,x);
                        }
                    else
                        {
                            if(!Sapper_Board.checkFlag())
                            {
                                Sapper_Board.setFlag(y,x);
                                if (Sapper_Board.isWin())
                                {
                                    Game_over=true;
                                    Sapper_Board.clickAllMines();
                                    QMessageBox::information(this, "ВАУ", "Молодец! Ты выиграл!");
                                }
                            }
                        }
                }
            showBoard();
        }
}

void Sapper::New_Game_Click()
{
    Game_over = false;
    Sapper_Board.clear();
    Sapper_Board.generateNew();
    showBoard();
}
