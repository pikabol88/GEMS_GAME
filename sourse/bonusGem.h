#ifndef BONUSGEM_H
#define BONUSGEM_H
#pragma once
#include "gems.h"
#include "warning.h"

//!Бонусный гем
class BonusGem :public Gem {

    Q_OBJECT

private:

    //!тип видов бонусов
    typedef enum bonus_t {
        LINE_EXPLOSION = 1,
        BOMB = 2,
        VOID = 3
    } bonus_t;

    //!Загрузка кизображений бонусов
    void loadImages() override;
    //!Список всех бонусов
    QList<bonus_t>all_bones = { LINE_EXPLOSION,BOMB,VOID };
   

public:
    //!картинки всех типов
    QVector<QImage> all_types;
    BonusGem(bonus_t type, int i, int j, QWidget *parent);
    BonusGem(Gem *gem);
    ~BonusGem();

    //!тип бонуса
    bonus_t m_bonusType;    

    //!Задает рандомный вид бонусу
    void setRandomType();
};

#endif // !BONUSGEM_H
