#ifndef INFOWINDOW_H
#define INFOWINDOW_H
#pragma once

#include <QMainWindow>
#include <QApplication>

//! Класс окна информации
class InfoWindow : public QMainWindow {
public:
    InfoWindow(QWidget *parent = 0);
};

#endif // !INFOWINDOW_H