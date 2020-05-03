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

//!����� �������� ���� ����
class GameWindow : public QMainWindow {
public:
    GameWindow(QWidget *parent = 0);
    ~GameWindow();

    //!��� �������� �������� ����
    QSharedPointer<Meditator> m_game_components;

private slots:

    //!���� ��������� ����� �������� ������������
    void changeStyleDark();
    //!���� ��������� ����� �������� ������������
    void changeStyleLight();
    //!���� ��������� ����� �������� ������������
    void changeStyleOcean();

    //!���� ������ ���� ����������
    void showHelp();
    //!���� ������ � ������������ �������� ��������
    void restart();
};

#endif // !MAINWINDOW_H

