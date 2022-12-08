#include "Click_button.h"

Click_Button:: Click_Button(QWidget *parent) :  QPushButton(parent)
{/*Empty*/ }

void  Click_Button::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
        emit rightClicked();
    if(event->button()==Qt::LeftButton)
        emit leftClicked();
}
