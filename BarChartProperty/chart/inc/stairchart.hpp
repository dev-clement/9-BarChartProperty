#ifndef STAIRCHART_HPP
#define STAIRCHART_HPP

#include <QObject>
#include <QPainter>
#include <QQmlEngine>
#include <QQmlListProperty>
#include <QQuickPaintedItem>
#include "stair.hpp"

class StairChart : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QQmlListProperty<Stair> stairs READ stairs NOTIFY stairsChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QColor bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_CLASSINFO("DefaultProperty", "stairs")

public:
    explicit StairChart(QQuickItem *po_parent = nullptr);

    // QQuickPaintedItem interface
    void paint(QPainter *po_painter);

    // Getter and setters
    QQmlListProperty<Stair> stairs();
    QString title() const;
    QColor bgColor() const;

public slots:
    void setTitle(const QString &o_title);
    void setBgColor(const QColor &o_bgColor);

signals:
    void stairsChanged(const QQmlListProperty<Stair> &o_stairs);
    void titleChanged(const QString &o_title);
    void bgColorChanged(const QColor &o_color);

private:
    static void appendStair(QQmlListProperty<Stair> *po_stairs, Stair *po_stair);
    void drawStair(QPainter *po_painter, const QRect &o_rect, const QColor &o_color, qreal i_barValue, int i_startingPoint);
    void drawStairs(QPainter *po_painter, const QRect &o_rect);
    void drawScale(QPainter *po_painter, const QRect &o_rect);

private:
    QList<Stair *> _o_stairs;
    QString _o_title;
    QColor _o_bgColor;
};

#endif // STAIRCHART_HPP
