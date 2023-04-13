#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) : // constructor
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    ui->comboBox_Menu_Color->setCurrentIndex(0);
    ui->comboBox_Menu_Time->setCurrentIndex(0);


    ui->label_Image_PixMap->hide();
    ui->label_Image_Cloud1->hide();
    ui->label_Image_Cloud2->hide();
    ui->label_Menu_Error->hide();

    ui->spinBox_Stars->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_Stars->setRange(0,10000);


}

MainWindow::~MainWindow() // destructor
{
    delete ui;
}

void MainWindow::on_comboBox_Menu_Color_currentIndexChanged(int index) // house color
{
    combobox_house = ui->comboBox_Menu_Color->currentIndex();

}

void MainWindow::on_comboBox_Menu_Time_currentIndexChanged(int index) // day/night
{
    combobox_time = ui->comboBox_Menu_Time->currentIndex();
    if (index == 0)
    {
        ui->label_Menu_Stars->show();
        ui->spinBox_Stars->show();
    }
    if (index == 1)
    {
        ui->label_Menu_Stars->hide();
        ui->spinBox_Stars->hide();
    }
}


void MainWindow::on_pushButton_Image_BackToMenu_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    update();

    ui->widget_Image->repaint();

}

void MainWindow::on_pushButton_Menu_Draw_clicked() // draw
{
    ui->stackedWidget->setCurrentIndex(1);

    int w = ui->widget_Image->width();
    int h = ui->widget_Image->height();

    ui->widget_Image->setImageSize(w, h);

    QImage *img = ui->widget_Image->image;    // указатель на изображение, на котором рисует виджет

    QPainter *painter = new QPainter(img);

    QPen *pen = new QPen;
    pen->setWidth(5);
    pen->setColor(Qt::black);

    painter->setPen(*pen);
    // house
    pen->setJoinStyle(Qt::MiterJoin);
    pen->setStyle(Qt::SolidLine);
    painter->setPen(*pen);
    painter->drawRect(377,200,400,290); // x, y, width, height - rectangle
    painter->drawRect(550,400,60,90); // door
    painter->drawRect(410,250,50,100); // window 1
    painter->drawRect(694,250,50,100); // window 2
    painter->drawLine(377,200,577,100); // roof first part
    painter->drawLine(577,100,777,200); // roof second part

    // horizont
    painter->drawLine(0,400,377,400);
    painter->drawLine(777,400,1131,400);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);

    // dark green roof (with adding a polygon to color it)
    brush.setColor(QColor::fromRgb(30,89,69));
    painter->setBrush(brush);
    QPolygonF polygon_roof;
    polygon_roof << QPointF(377,200) << QPointF(577,100) << QPointF(777,200);
    painter->drawPolygon(polygon_roof,Qt::OddEvenFill);

    // light green grass (with 3 polygons)
    brush.setColor(QColor::fromRgb(124,252,0));
    pen->setColor(QColor::fromRgb(124,252,0));
    painter->setPen(*pen);
    painter->setBrush(brush);
    QPolygonF polygon_grass1,polygon_grass2,polygon_grass3;
    polygon_grass1 << QPointF(0,405) << QPointF(372,405) << QPointF(372,501) << QPointF(0,501);
    polygon_grass2 << QPointF(782,405) << QPointF(1131,405) << QPointF(1131,501) << QPointF(782,501);
    polygon_grass3 << QPointF(377,495) << QPointF(777,495) << QPointF(777,501) << QPointF(377,501);
    painter->drawPolygon(polygon_grass1,Qt::OddEvenFill);
    painter->drawPolygon(polygon_grass2,Qt::OddEvenFill);
    painter->drawPolygon(polygon_grass3,Qt::OddEvenFill);




    switch (combobox_house) // house color
    {

    case 0: // yellow
    {

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(QColor::fromRgb(253,233,16)); // yellow house
        painter->setPen(Qt::black);
        painter->drawRect(377,200,400,290);

        painter->setBrush(QColor::fromRgb(128,166,255)); // blue windows
        painter->setPen(Qt::black);
        painter->drawRect(410,250,50,100);
        painter->drawRect(694,250,50,100);

        painter->setBrush(QColor::fromRgb(128,64,48)); // brown door
        painter->setPen(Qt::black);
        painter->drawRect(550,400,60,90);


        break;
    }
    case 1: // white
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(Qt::NoBrush); // white house
        painter->setPen(Qt::black);
        painter->drawRect(377,200,400,290);

        painter->setBrush(QColor::fromRgb(128,166,255)); // blue windows
        painter->setPen(Qt::black);
        painter->drawRect(410,250,50,100);
        painter->drawRect(694,250,50,100);

        painter->setBrush(QColor::fromRgb(128,64,48)); // brown door
        painter->setPen(Qt::black);
        painter->drawRect(550,400,60,90);

        break;
    }
    case 2: // red
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(QColor::fromRgb(196,30,58)); // red house
        painter->setPen(Qt::black);
        painter->drawRect(377,200,400,290);

        painter->setBrush(QColor::fromRgb(128,166,255)); // blue windows
        painter->setPen(Qt::black);
        painter->drawRect(410,250,50,100);
        painter->drawRect(694,250,50,100);

        painter->setBrush(QColor::fromRgb(128,64,48)); // brown door
        painter->setPen(Qt::black);
        painter->drawRect(550,400,60,90);

        break;
    }


    }

    bool day_flag = true;
    switch (combobox_time) // day/night
    {
    case 0: // night
    {
        day_flag = false;
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(QColor::fromRgb(16,44,84)); // dark night blue sky
        painter->setPen(QColor::fromRgb(16,44,84));
        painter->drawRect(0,0,1131,200);
        painter->drawRect(0,200,375,197);
        painter->drawRect(780,200,500,197);


        // dark green roof (with adding a polygon to color it)
        brush.setColor(QColor::fromRgb(30,89,69));
        painter->setBrush(brush);
        QPolygonF polygon_roof;
        polygon_roof << QPointF(377,200) << QPointF(577,100) << QPointF(777,200);
        painter->drawPolygon(polygon_roof,Qt::OddEvenFill);

        //QPixMap Moon
        QPixmap moon(":/Images/Moon.jpg.png");
        QPixmap scaledMoon = moon.scaled(200,200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_Image_PixMap->setPixmap(scaledMoon);
        ui->label_Image_PixMap->show();
        ui->label_Image_Cloud1->hide();
        ui->label_Image_Cloud2->hide();

        ui->widget_Image->repaint();

        break;
    }
    case 1: // day
    {
       day_flag = true;

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        painter->setBrush(QColor::fromRgb(127,199,255)); // light day blue sky
        painter->setPen(QColor::fromRgb(127,199,255));

        painter->drawRect(0,0,1131,200);
        painter->drawRect(0,200,375,197);
        painter->drawRect(780,200,500,197);


        pen->setWidth(2);
        pen->setJoinStyle(Qt::MiterJoin);
        pen->setStyle(Qt::SolidLine);
        pen->setColor(QColor::fromRgb(127,199,255));
        painter->setPen(*pen);
        painter->drawLine(300,100,250,200); // (300,100)
        painter->drawLine(250,200,350,150);
        painter->drawLine(350,150,230,150);
        painter->drawLine(230,150,330,200);
        painter->drawLine(330,200,300,100);

        // dark green roof (with adding a polygon to color it)
        brush.setColor(QColor::fromRgb(30,89,69));
        painter->setBrush(brush);
        QPolygonF polygon_roof;
        polygon_roof << QPointF(377,200) << QPointF(577,100) << QPointF(777,200);
        painter->drawPolygon(polygon_roof,Qt::OddEvenFill);


        //QPixMap Sun
        QPixmap sun(":/Images/sun.png.png");
        QPixmap scaledSun = sun.scaled(200,200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_Image_PixMap->setPixmap(scaledSun);
        ui->label_Image_PixMap->show();

        //QPixMap Cloud1
        QPixmap Cloud1(":/Images/Cloud1.png.png");
        QPixmap Cloud1Scaled = Cloud1.scaled(200,150, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_Image_Cloud1->setPixmap(Cloud1Scaled);
        ui->label_Image_Cloud1->show();

        //QPixMap Cloud2
        QPixmap Cloud2(":/Images/Cloud2.png");
        QPixmap Cloud2Scaled = Cloud2.scaled(200,200, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        ui->label_Image_Cloud2->setPixmap(Cloud2Scaled);
        ui->label_Image_Cloud2->show();
        break;
    }
    }

    if (!day_flag)
        switch (combobox_stars)
    {

//    case 0:
//    {
//        QBrush brush;
//        //brush.setStyle(Qt::SolidPattern);
//        brush.setColor(Qt::yellow);

//        QPainterPath star; // path for star

//        int x, y;  //coord star
//        int count = 1000;

//        for (int i = 0; i < count; i++)
//        {
//            x = 0 + rand() % 1100;
//            y = 0 + rand() % 360;


//            if ((y > -0.5*x + 350 and x > 360 and x <= 577) or (y > 0.5*x - 230 and x < 800 and x >= 577))
//            {
//                count += 1;
//            }
//            else {
//                star.moveTo(x, y);
//                star.lineTo(x + 5, y + 14);
//                star.lineTo(x + 20, y + 14);
//                star.lineTo(x + 6, y + 23);
//                star.lineTo(x + 13, y + 37);
//                star.lineTo(x, y + 28);
//                star.lineTo(x - 13, y + 37);
//                star.lineTo(x - 7, y + 23);
//                star.lineTo(x - 20, y + 14);
//                star.lineTo(x - 4, y + 14);
//                star.lineTo(x, y);
//                painter->setPen(Qt::yellow);
//                painter->setBrush(brush);
//                painter->drawPath(star);

//            }

//        }



//        break;

//    }

//    case 1:
//    {
//    QBrush brush;
//    //brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::yellow);

//    QPainterPath star; // path for star

//    int x, y;  //coord star
//    int count = 2000;

//    for (int i = 0; i < count; i++)


//    {
//        x = 0 + rand() % 1100;
//        y = 0 + rand() % 360;


//        if ((y > -0.5*x + 350 and x > 360 and x <= 577) or (y > 0.5*x - 230 and x < 800 and x >= 577))
//        {
//            count += 1;
//        }
//        else {
//            star.moveTo(x, y);
//            star.lineTo(x + 5, y + 14);
//            star.lineTo(x + 20, y + 14);
//            star.lineTo(x + 6, y + 23);
//            star.lineTo(x + 13, y + 37);
//            star.lineTo(x, y + 28);
//            star.lineTo(x - 13, y + 37);
//            star.lineTo(x - 7, y + 23);
//            star.lineTo(x - 20, y + 14);
//            star.lineTo(x - 4, y + 14);
//            star.lineTo(x, y);
//            painter->setPen(Qt::yellow);
//            painter->setBrush(brush);
//            painter->drawPath(star);

//        }
//    }





//        break;
//    }
//    case 2:
//    {
//    QBrush brush;
//    //brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::yellow);

//    QPainterPath star; // path for star

//    int x, y;  //coord star
//    int count = 3000;

//    for (int i = 0; i < count; i++)
//    {
//        x = 0 + rand() % 1100;
//        y = 0 + rand() % 360;


//        if ((y > -0.5*x + 350 and x > 360 and x <= 577) or (y > 0.5*x - 230 and x < 800 and x >= 577))
//        {
//            count += 1;
//        }
//        else {
//            star.moveTo(x, y);
//            star.lineTo(x + 5, y + 14);
//            star.lineTo(x + 20, y + 14);
//            star.lineTo(x + 6, y + 23);
//            star.lineTo(x + 13, y + 37);
//            star.lineTo(x, y + 28);
//            star.lineTo(x - 13, y + 37);
//            star.lineTo(x - 7, y + 23);
//            star.lineTo(x - 20, y + 14);
//            star.lineTo(x - 4, y + 14);
//            star.lineTo(x, y);
//            painter->setPen(Qt::yellow);
//            painter->setBrush(brush);
//            painter->drawPath(star);

//        }



//    }



//        break;
//    }
//    case 3:
//    {
//            QBrush brush;
//            //brush.setStyle(Qt::SolidPattern);
//            brush.setColor(Qt::yellow);

//            QPainterPath star; // path for star

//            int x, y;  //coord star
//            int count = 4000;

//            for (int i = 0; i < count; i++)
//            {
//                x = 0 + rand() % 1100;
//                y = 0 + rand() % 360;


//                if ((y > -0.5*x + 350 and x > 360 and x <= 577) or (y > 0.5*x - 230 and x < 800 and x >= 577))
//                {
//                    count += 1;
//                }
//                else {
//                    star.moveTo(x, y);
//                    star.lineTo(x + 5, y + 14);
//                    star.lineTo(x + 20, y + 14);
//                    star.lineTo(x + 6, y + 23);
//                    star.lineTo(x + 13, y + 37);
//                    star.lineTo(x, y + 28);
//                    star.lineTo(x - 13, y + 37);
//                    star.lineTo(x - 7, y + 23);
//                    star.lineTo(x - 20, y + 14);
//                    star.lineTo(x - 4, y + 14);
//                    star.lineTo(x, y);
//                    painter->setPen(Qt::yellow);
//                    painter->setBrush(brush);
//                    painter->drawPath(star);

//                }



//        }





//    }
        QBrush brush;
        //brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::yellow);

        QPainterPath star; // path for star

        int x, y;  //coord star


        for (int i = 0; i < countstar; i++)
        {
            x = 0 + rand() % 1100;
            y = 0 + rand() % 360;


            if ((y > -0.5*x + 350 and x > 360 and x <= 577) or (y > 0.5*x - 230 and x < 800 and x >= 577))
            {
                countstar += 1;
            }
            else {
                star.moveTo(x, y);
                star.lineTo(x + 5, y + 14);
                star.lineTo(x + 20, y + 14);
                star.lineTo(x + 6, y + 23);
                star.lineTo(x + 13, y + 37);
                star.lineTo(x, y + 28);
                star.lineTo(x - 13, y + 37);
                star.lineTo(x - 7, y + 23);
                star.lineTo(x - 20, y + 14);
                star.lineTo(x - 4, y + 14);
                star.lineTo(x, y);
                painter->setPen(Qt::yellow);
                painter->setBrush(brush);
                painter->drawPath(star);

            }

        }


    }


    painter->end();

    ui->widget_Image->repaint();

    //dont forget to clean memory
    delete pen;
    delete painter;

    pen = nullptr;
    painter = nullptr;
}


void MainWindow::on_spinBox_Stars_valueChanged(int arg1)
{
    countstar = arg1;
}
