#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QGridLayout>

#include "meditator.h"
#include "infowindow.h"

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSharedPointer<Meditator>m;
   // Meditator *m;
private slots:
    void changeStyleDark();
    void changeStyleLight();
    void changeStyleOcean();
    void showHelp();
    void restart();
};

#endif // !MAINWINDOW_H

