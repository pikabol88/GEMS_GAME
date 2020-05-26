#ifndef MEDITATOR_H
#define MEDITATOR_H
#pragma once
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

#include "field.h"
#include "score.h"
#include "clock.h"

//! ��������� ����� ����� � ��������
class Meditator :public QWidget {

    Q_OBJECT

public:
    Meditator();
    ~Meditator();
    int m_wind�w_size;
    void setWind�wSize();

public slots:
    void on_gameReset();
    void changeColor(QString back, QString pick);

protected:
   // shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));
    //std::shared_ptr<Field> m_field = std::make_shared<Field>();
    //QSharedPointer<Field>m_field= QSharedPointer<Field>(new Field, &QObject::deleteLater);
    Field *m_field;
    //!< ������� ����
    Clock *m_time;
    //!< ���������� ����� ����
    //Score *m_score;
    QSharedPointer<Score>m_score;
    QGridLayout *m_layout;
    //!< ��������� �������
};

#endif // !MEDITATOR_H
