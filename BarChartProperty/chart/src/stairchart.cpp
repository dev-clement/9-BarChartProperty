#include "stairchart.hpp"

StairChart::StairChart(QQuickItem *po_parent): QQuickPaintedItem{po_parent} {
    setWidth(400);
    setHeight(400);
}

void StairChart::drawStair(QPainter *po_painter, const QRect &o_rect, const QColor &o_color, qreal i_barValue, int i_startingPoint) {
    static constexpr int i_width = 50;
    po_painter->setPen(o_color);
    po_painter->setBrush(o_color);

    po_painter->drawRect(o_rect.bottomLeft().x() + i_startingPoint
                         , o_rect.bottomLeft().y() - i_barValue
                         , i_width
                         , i_barValue);
}

void StairChart::drawStairs(QPainter *po_painter, const QRect &o_rect) {
    static constexpr int i_stairWidth = 50;
    static constexpr int i_stairRectWidth = 25;
    static constexpr int i_stairRectHeight = 25;
    for (Stair *o_stair : _o_stairs) {
        po_painter->setPen(o_stair->color());
        po_painter->setBrush(QBrush{ o_stair->color() });

        QRect o_stairRect{o_rect.bottomLeft().x() + o_stair->from()
                         , o_rect.bottomLeft().y() - o_stair->value()
                         , i_stairWidth
                         , o_stair->value()};
        po_painter->drawRect(o_stairRect);
        po_painter->setPen(Qt::white);
        po_painter->setBrush(QBrush{Qt::white});
        po_painter->drawRect(o_stairRect.topLeft().x() + 10
                             , o_stairRect.topLeft().y() + 10
                             , i_stairRectWidth
                             , i_stairRectHeight);
        po_painter->setFont(QFont{"Consolas", 10, QFont::Bold});
        po_painter->setPen(Qt::black);
        po_painter->drawText(o_stairRect.adjusted(15, 15, 0, 0), o_stair->text());
    }
}

void StairChart::drawScale(QPainter *po_painter, const QRect &o_rect) {
    static constexpr int i_penWidth = 2;
    QPen o_pen{Qt::black, i_penWidth};

    po_painter->setPen(o_pen);
    po_painter->drawLine(o_rect.bottomLeft() + QPoint{0, 0}, o_rect.bottomLeft() + QPoint{20, 0});
    po_painter->drawText(o_rect.bottomLeft() + QPoint{3, -10}, "0");

    po_painter->drawLine(o_rect.bottomLeft() + QPoint{0, -100}, o_rect.bottomLeft() + QPoint{20, -100});
    po_painter->drawText(o_rect.bottomLeft() + QPoint{3, -110}, "100");

    po_painter->drawLine(o_rect.bottomLeft() + QPoint{0, -200}, o_rect.bottomLeft() + QPoint{20, -200});
    po_painter->drawText(o_rect.bottomLeft() + QPoint{3, -210}, "200");

    po_painter->drawLine(o_rect.bottomLeft() + QPoint{0, -300}, o_rect.bottomLeft() + QPoint{20, -300});
    po_painter->drawText(o_rect.bottomLeft() + QPoint{3, -310}, "300");
}

void StairChart::paint(QPainter *po_painter) {
    static const int i_width = width();
    static const int i_height = height();
    QRect o_rect{0, 0, i_width, i_height};

    po_painter->save();
    po_painter->setPen(QPen{Qt::gray, 3});
    po_painter->setBrush(QBrush{bgColor()});
    po_painter->drawRect(o_rect);

    // Draw titles
    po_painter->drawText(o_rect.topLeft() + QPoint{30, 30}, title());
    drawStairs(po_painter, o_rect);

    // Draw scale
    po_painter->setFont(QFont{"Consolas", 10, QFont::Bold});
    drawScale(po_painter, o_rect);
    po_painter->restore();
}

QQmlListProperty<Stair> StairChart::stairs() {
    return QQmlListProperty<Stair>(this
                                   , this
                                   , &StairChart::appendStair
                                   , nullptr
                                   , nullptr
                                   , nullptr);
}

QString StairChart::title() const {
    return _o_title;
}

void StairChart::setTitle(const QString &o_title) {
    if (_o_title == o_title)
        return;
    _o_title = o_title;
    emit titleChanged(_o_title);
}

QColor StairChart::bgColor() const {
    return _o_bgColor;
}

void StairChart::setBgColor(const QColor &o_bgColor) {
    if (_o_bgColor == o_bgColor)
        return;
    _o_bgColor = o_bgColor;
    emit bgColorChanged(_o_bgColor);
}

void StairChart::appendStair(QQmlListProperty<Stair> *po_stairs, Stair *po_stair) {
    StairChart *po_stairChart = qobject_cast<StairChart *>(po_stairs->object);
    if (!po_stairChart) {
        return ;
    }
    po_stair->setParent(po_stairChart);
    po_stairChart->_o_stairs.append(po_stair);
    emit po_stairChart->stairsChanged(po_stairChart->stairs());
}
