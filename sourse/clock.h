#ifndef CLOCK_H
#define CLOCK_H
#pragma once

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

//! класс отображения цифровых часов
class Clock :public QLCDNumber {

    Q_OBJECT

public:
    Clock(QWidget *parent = 0);
    ~Clock();

private slots:
    void on_tick(); //!< слот обработки сигнала таймера
    void stop(); //!< слот остановки таймера

protected:
    QTime m_time; //!< текущее время
    QTimer *m_timer; //!< таймер
};
#endif // CLOCK_H
