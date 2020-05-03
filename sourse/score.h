#ifndef SCORE_H
#define SCORE_H
#pragma once
#include <QLCDNumber>
#include <QLabel>
#include <QVBoxLayout>

//! Класс отображения результата игры (набранных очков)
class Score :public QLCDNumber {

    Q_OBJECT

public:
    Score(QWidget *parent = 0);
    ~Score();
    
    int m_score = 0; //!<Количество набранных очков
    QVBoxLayout *vbox = nullptr; //!< раскладка виджета
    QLabel *label = nullptr; //!< составляющая часть виджета
    QString *str = nullptr; //!< название виджета

public slots:
    //! Слот обновления результата
    void updateScore(int points);
};
#endif // !SCORE_H