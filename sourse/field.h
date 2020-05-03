#ifndef FIELD_H
#define FIELD_H
#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QList>
#include <QMessageBox>
#include <iostream>
#include <ctime>

#include "score.h"
#include "bonusGem.h"
#include "gems.h"
#include "thread.h"


#define BACK "black" //!< цвет игрового поля при запуске игры
#define PICK "#696969"//!<цвет выделения кликнутого гема

class Gem;
class BonusGem;
class Meditator;

//! игровое поле
class Field : public QWidget {

    Q_OBJECT

public:
    Field(QWidget *perent = 0);
    ~Field();

    Score *points = nullptr; //!< количество набранных очков
    QString m_background = "background-color:";  //!< цвет игрового поля
    QString m_picked_background = "background-color:";  //!< цвет выделенной ячейки игрового поля
    
private:
    bool m_inGame = false;  //!< состояние игрового поля
    bool m_isClicked = false; //!< состояние определённой ячейки игрового поля
    Gem *m_savedGem = nullptr; //!< последний кликнутый гемс
    BonusGem *m_bonusGem = nullptr; //!< бонусный гемс

    static const int M_WIDTH = 300; //!< ширина поля
    static const int M_HEIGHT = 300; //!< высота поля
    static const int M_GEM_COUNT = 8;  //!< количество гемсов в одной линии поля
    static const int M_POINTS_FOR_GEM = 10; //!< количество очков за один уничтоженный гем

    Gem* m_field[M_GEM_COUNT][M_GEM_COUNT];  //!< игровое поле


  
    /*! Создаёт и обрабатывает бонусные гемсы 
    \return список гемсов, которые были уничтожены  */   
    QList<Gem*> create_bonus();
    /*! Разрушает линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    QList<Gem*> remove_line(int cur_i, int cur_j);
    /*! Разрушает горизонатльную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    QList<Gem*> remove_horizontal_line(int cur_i, int cur_j);
    /*! Разрушает вертикальную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    QList<Gem*> remove_vertical_line(int cur_i, int cur_j);
    /*! Разрушает левую диагональную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    QList<Gem*> remove_left_diagonal_line(int cur_i, int cur_j);
    /*! Разрушает правую диагональную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    QList<Gem*> remove_right_diagonal_line(int cur_i, int cur_j);
    /*! Разрушает круг гемосов, вокруг выбранного
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    QList<Gem*> remove_circle(int cur_i, int cur_j);

    /*!Сортирует гемсы в порядке возрастания их j-ой координаты
    param bonus_list список гемсов
    \return отсортированный список гемсов */
    QList<Gem*> sort_bonus(QList<Gem*>bonus_list);
    /*!Находит гемс с наименьшим значением j-ой координаты
    param bonus_list список гемсов
    \return наивысший гемс */
    Gem* find_max(QList<Gem*>bonus_list);

    /*!Меняет местами два гемса
    param gem1, gem2 гемсы */
    void swipe_gems(Gem *gem1, Gem *gem2);
    /*!Добавляет новый гем
    param i,j координаты ячейки */
    void add_new_gem(int i, int j);

    /*!Проверяет, есть ли доступные ходы на сгенерированном поле */
    bool is_available_moves();
    /*!Проверяет, есть ли 3 гемса подряд в одном ряду/линии */
    bool is_three_line();
    /*!Проверяет, возможен ли ход данным гемом, не будет ли выхода за пределы поля 
    param gem текущий гем*/
    bool is_possible_move(Gem &gem);

    /*!Инициализируется новое поле*/
    void init_game();
    /*!Пересоздание поля*/
    void create_new_field();
    /*!Падение гемсов вниз/создание новых после разрушения линии гемсов*/
    void update_field(QList<QList<Gem*>>matches_list);

    void find_matches_and_update();
    /*!Проверка совпадения типов гемсов
    param col,row координты ячейки с гемом
    param type тип гема для сравнения*/
    bool match_type(int col, int row, int type);
    /*!Проверка совпадения типов гемсов
    param col,row координты ячейки с гемом
    param mustHave возможные координаты второй фишки
    param needOne требуемы координаты третьей фишки
    param size размер needOne*/
    bool match_pattern(int col, int row, int *mustHave, int needOne[][2], int size);

    /*!Поиск всех линий из >= 3x одинаковых гемсов
    \return список всех найденных линий*/
    QList<QList<Gem*>> look_for_matches();
    /*!Поиск вертикальных линий из >= 3x одинаковых гемсов
    param col,row координты ячейки с гемом
    \return список гемсов из найденной линии*/
    QList<Gem*> get_vertical_matches(int col, int row);
    /*!Поиск горизонтальных линий из >= 3x одинаковых гемсов
    param col,row координты ячейки с гемом
    \return список гемсов из найденной линии*/
    QList<Gem*> get_horizontal_matches(int col, int row);

    /*!Обновление набранных очков
    param score количество очков*/
    void update_score(int score);
    /*!Перерисовка поля*/
    void repaintField();

private slots:
    void buttonClick();
            //!< слот обработки нажатия клетки кнопкой мыши

    friend class Meditator;
};
#endif // FIELD_H

