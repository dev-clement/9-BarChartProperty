#include "stair.hpp"

Stair::Stair(QObject *po_parent): QObject{po_parent} {}

QColor Stair::color() const {
    return _o_color;
}

int Stair::value() const {
    return _i_value;
}

QString Stair::text() const {
    return _o_text;
}

int Stair::from() const {
    return _i_from;
}

void Stair::setColor(const QColor &o_color) {
    if (_o_color == o_color)
        return;
    _o_color = o_color;
    emit colorChanged(_o_color);
}

void Stair::setValue(int i_value) {
    if (_i_value == i_value)
        return;
    _i_value = i_value;
    emit valueChanged(_i_value);
}

void Stair::setText(const QString &o_text) {
    if (_o_text == o_text)
        return;
    _o_text = o_text;
    emit textChanged(_o_text);
}

void Stair::setFrom(int i_from) {
    if (_i_from == i_from)
        return;
    _i_from = i_from;
    emit fromChanged(_i_from);
}
