#ifndef PAINT_WIDGET_H
#define PAINT_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QtGui>
#include <QtCore>

class paint_widget : public QWidget
{
    Q_OBJECT
public:
    explicit paint_widget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event);

signals:

public:
    QImage *image = nullptr;

    void setImageSize(int width, int height);   // function that sets the image dimensions

    void clear();

public slots:
};

#endif // PAINT_WIDGET_H
