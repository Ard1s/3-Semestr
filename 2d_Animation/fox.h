#ifndef FOX_H
#define FOX_H

#include <QGraphicsItem>
#include <QPainter>


class Fox : public QGraphicsItem
{
public:
    Fox();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    QPoint points1[14];
    QPoint points2[14];
    void drawPair(QPainter *painter, int p1, int p2, int p3, QColor color);
    void drawPair(QPainter *painter, int p1, int p2, int p3, int p4, QColor color);



};

#endif // FOX_H
