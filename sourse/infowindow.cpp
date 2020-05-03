#include "infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) : QMainWindow(parent) {
    QPixmap pix;
    QPalette pal;
    pix.load("img\\img_info.jpg");    
    pal.setBrush(this->backgroundRole(), QBrush(pix));
    this->setPalette(pal);
    this->setAutoFillBackground(true);
}