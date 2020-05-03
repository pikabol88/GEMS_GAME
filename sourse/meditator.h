#ifndef MEDITATOR_H
#define MEDITATOR_H
#pragma once
#include <QGridLayout>
#include <QWidget>
#include <QLabel>

#include "field.h"
#include "score.h"
#include "clock.h"

//!Посредник между компонентами игрового окна
class Meditator :public QWidget {

    Q_OBJECT

public:
    Meditator();
    ~Meditator();
    int m_windоw_size; //!<Размер игрового окна

     //!Установка размеров игрового окна
    void setWindоwSize();

public slots:
    //!Слот перезагрузки игры
    void on_gameReset();
    //!Слот изменения стиля игрового окна
    void changeColor(QString back, QString pick);

protected:

    Field *m_field; //!< игровое поле
    Clock *m_time; //!< отображeние времени игры
    QSharedPointer<Score>m_score; //!< отображeние результата
    QGridLayout *m_layout; //!< раскладка виджета
};

#endif // !MEDITATOR_H
