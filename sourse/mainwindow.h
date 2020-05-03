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

//!Класс главного окна игры
class GameWindow : public QMainWindow {
public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();

    //!Все элементы игрового окна
    QSharedPointer<Meditator> m_game_components;

private slots:

    //!Слот изменения стиля игрового пространства
    void changeStyleDark();
    //!Слот изменения стиля игрового пространства
    void changeStyleLight();
    //!Слот изменения стиля игрового пространства
    void changeStyleOcean();

    //!Слот вызова окна информации
    void showHelp();
    //!Слот сброса и перезагрузки игрового процесса
    void restart();
};

#endif // !MAINWINDOW_H

