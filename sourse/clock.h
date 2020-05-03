#ifndef CLOCK_H
#define CLOCK_H
#pragma once

#include <QLCDNumber>
#include <QTimer>
#include <QTime>

//! ����� ����������� �������� �����
class Clock :public QLCDNumber {

    Q_OBJECT

public:
    Clock(QWidget *parent = 0);
    ~Clock();

private slots:
    void on_tick(); //!< ���� ��������� ������� �������
    void stop(); //!< ���� ��������� �������

protected:
    QTime m_time; //!< ������� �����
    QTimer *m_timer; //!< ������
};
#endif // CLOCK_H
