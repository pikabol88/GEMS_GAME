#ifndef GEMS_H
#define GEMS_H
#pragma once

#include <QWidget>
#include <QPushButton>
#include <QPainter>

class Meditator;

//! Класс гема
class Gem : public QPushButton {

    Q_OBJECT

public:
    int m_i = 0; //!< координата строки
    int m_j = 0;//!< координата столбца
    int m_bonusType = 0;//!< тип гемса(если является бонусным)
   
    QImage m_type;//!< Тип гема


    Gem(int i, int j, QWidget *parent = 0);
    ~Gem();

    //! Удалить гем
    void removeGem();
    //! Изменить тип гема 
    void changeGem();

    //! Переопределённый метод paintEvent для виджетов является обработчиком события типа "перерисовка виджета". 
    virtual void paintEvent(QPaintEvent *) override;
    //! Переопределённый оператор сравнения
    friend bool operator==(const Gem &gem1, const Gem &gem2);    

protected:
    
    QVector<QImage> all_types;//!< все типы гемов
    static const int GEMS_TYPE = 5;//!< количество типов гемов
    static const int G_WIDTH = 55;//!< ширина гема
    static const int G_HEIGHT = 55;//!< высота гема

    //! Загрузка картинок типов гема
    virtual void loadImages();
    void img_error();

    friend class Meditator;
};
#endif // !GEMS_H