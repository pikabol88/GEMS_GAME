#ifndef MEDITATOR_H
#define MEDITATOR_H
#pragma once
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

#include "field.h"
#include "score.h"
#include "clock.h"

//!��������� ����� ������������ �������� ����
class Meditator :public QWidget {

    Q_OBJECT

public:
    Meditator();
    ~Meditator();
    int m_wind�w_size; //!<������ �������� ����

     //!��������� �������� �������� ����
    void setWind�wSize();

public slots:
    //!���� ������������ ����
    void on_gameReset();
    //!���� ��������� ����� �������� ����
    void changeColor(QString back, QString pick);

protected:

    Field *m_field; //!< ������� ����
    Clock *m_time; //!< �������e��� ������� ����
    QSharedPointer<Score>m_score; //!< �������e��� ����������
    QGridLayout *m_layout; //!< ��������� �������
};

#endif // !MEDITATOR_H
