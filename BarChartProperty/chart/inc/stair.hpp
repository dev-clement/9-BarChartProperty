#ifndef STAIR_HPP
#define STAIR_HPP

#include <QColor>
#include <QObject>
#include <QQmlEngine>

class Stair : public QObject {
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int from READ from WRITE setFrom NOTIFY fromChanged)
public:
    explicit Stair(QObject *po_parent = nullptr);

    // Getter and Setters
    QColor color() const;
    void setColor(const QColor &o_color);
    int value() const;
    void setValue(int i_value);
    QString text() const;
    void setText(const QString &o_text);

    int from() const;
    void setFrom(int i_from);

signals:
    void colorChanged(const QColor &o_color);
    void valueChanged(int i_value);
    void textChanged(const QString &o_text);
    void fromChanged(int i_from);

private:
    QColor  _o_color;
    int     _i_value;
    QString _o_text;
    int     _i_from;
};

#endif // STAIR_HPP
