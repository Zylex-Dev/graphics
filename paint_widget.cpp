#include "paint_widget.h"

paint_widget::paint_widget(QWidget *parent) : QWidget(parent)
{

}

void paint_widget::paintEvent(QPaintEvent *event)
{
    if(image != nullptr)
    {
        QPainter *painter = new QPainter(this);

        painter->drawImage(0, 0, *image);

        painter->end();
    }

    event->accept();
}

void paint_widget::setImageSize(int width, int height)
{
    if(image != nullptr)
    {
        delete image;
    }

    image = new QImage(width, height, QImage::Format_ARGB32_Premultiplied);
}

void paint_widget::clear()
{
    image->fill(0);
}

