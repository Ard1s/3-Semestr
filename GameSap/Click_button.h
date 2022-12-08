#ifndef CLICK_BUTTON_H
#define CLICK_BUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class  Click_Button : public QPushButton
{
    Q_OBJECT

public:
    explicit  Click_Button(QWidget* parent = 0);

public slots:
    void mousePressEvent(QMouseEvent* e);

signals:
    void rightClicked();
    void leftClicked();
};

#endif // CLICK_BUTTON.H
