#include "fox.h"

Fox::Fox() : QGraphicsItem()
{
    points1[0] = QPoint(0,-40);
    points1[1] = QPoint(0,-60);
    points1[2] = QPoint(50,-80);
    points1[3] = QPoint(70,-120);
    points1[4] = QPoint(80,-140);
    points1[5] = QPoint(80,-90);
    points1[6] = QPoint(80,-30);
    points1[7] = QPoint(0,40);
    points1[8] = QPoint(20,40);
    points1[9] = QPoint(30,40);
    points1[10] = QPoint(0,80);
    points1[11] = QPoint(30,0);
    points1[12] = QPoint(40,-40);
    points1[13] = QPoint(32,-10);




    for(int i = 0; i < 14; i++)
    {
        points2[i].setX(points1[i].x() * -1);
        points2[i].setY(points1[i].y());

    }



}

void Fox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);


    painter->setPen(Qt::NoPen);
    drawPair(painter, 0, 1, 2, QColor(235, 159, 46));
    drawPair(painter, 2, 4, 6, QColor(206, 101, 23));
    drawPair(painter, 7, 9, 10, QColor(0, 0, 0));
    drawPair(painter, 3, 4, 5,  QColor(0, 0, 0));
    drawPair(painter, 0, 2, 11,  QColor(230, 113, 34));
    drawPair(painter, 2, 6, 12,  QColor(200, 113, 34));
    drawPair(painter, 12, 13, 6,  QColor(255, 255, 255));

    drawPair(painter, 0, 11, 8, 7, QColor(235, 139, 75));
    drawPair(painter, 13, 6, 9, 8, QColor(235, 139, 75));


}






QRectF Fox::boundingRect() const
{
    return QRectF(-100, -110, 200, 220);
}

void Fox::drawPair(QPainter *painter, int p1, int p2, int p3, QColor color)
{
    QPolygon pol, pol2;
    pol << points1[p1] << points1[p2] << points1[p3];
    pol2 << points2[p1] << points2[p2] << points2[p3];
    painter->setBrush(color);
    painter->drawPolygon(pol);
    painter->drawPolygon(pol2);
}

void Fox::drawPair(QPainter *painter, int p1, int p2, int p3, int p4, QColor color)
{
    QPolygon pol, pol2;
    pol << points1[p1] << points1[p2] << points1[p3] << points1[p4];
    pol2 << points2[p1] << points2[p2] << points2[p3] << points1[p4];
    painter->setBrush(color);
    painter->drawPolygon(pol);
    painter->drawPolygon(pol2);
}

