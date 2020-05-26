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

#define BACK "black"
#define PICK "#696969"

class Gem;
class BonusGem;
class Meditator;

//! игровое поле
class Field : public QWidget {

    Q_OBJECT

public:
    Field(QWidget *perent = 0);
    ~Field();

    //QSharedPointer<Score>points;
    Score *points = nullptr; //!< количество набранных очков
    QString m_background = "background-color:";  //!< цвет игрового поля
    QString m_picked_background = "background-color:";  //!< цвет выделенной ячейки игрового поля
    
private:

    using Gem2L = QList<QList<Gem*>>;
    using GemL =  QList<Gem*>;

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
    GemL create_bonus();
    /*! Разрушает линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    GemL remove_line(int cur_i, int cur_j);
    /*! Разрушает горизонатльную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    GemL  remove_horizontal_line(int cur_i, int cur_j);
    /*! Разрушает вертикальную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    GemL  remove_vertical_line(int cur_i, int cur_j);
    /*! Разрушает левую диагональную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    GemL  remove_left_diagonal_line(int cur_i, int cur_j);
    /*! Разрушает правую диагональную линию гемсов
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    GemL  remove_right_diagonal_line(int cur_i, int cur_j);
    /*! Разрушает круг гемосов, вокруг выбранного
    param cur_i,cur_j координаты выбранного гемса
    \return список гемсов, которые были уничтожены */
    GemL  remove_circle(int cur_i, int cur_j);

    /*!Сортирует гемсы в порядке возрастания их j-ой координаты
    param bonus_list список гемсов
    \return отсортированный список гемсов */
    GemL sort_bonus(GemL bonus_list);
    /*!Находит гемс с наименьшим значением j-ой координаты
    param bonus_list список гемсов
    \return наивысший гемс */
    Gem* find_max(GemL bonus_list);

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
    bool is_three_line_hor();
    bool is_three_line_ver();
    /*!Проверяет, возможен ли ход данным гемом, не будет ли выхода за пределы поля 
    param gem текущий гем*/
    bool is_possible_move(const Gem &gem);

    /*!Инициализируется новое поле*/
    void init_game();
    /*!Добавление одного гема на поле*/
    void createGem(int i, int j, QGridLayout &layout);
    /*!Пересоздание поля*/
    void create_new_field();
    /*!Падение гемсов вниз/создание новых после разрушения линии гемсов*/
    void update_field(Gem2L matches_list);
    /*!Удаление разрушенных гемсов и создание новых на их месте*/
    void redraw_field(Gem2L matches_list);

    void bonus_processing();

    void match_three_processing();
    void no_moves_message();
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
    Gem2L look_for_matches();
    /*!Поиск вертикальных линий из >= 3x одинаковых гемсов
    param col,row координты ячейки с гемом
    \return список гемсов из найденной линии*/
    GemL  get_vertical_matches(int col, int row);
    /*!Поиск горизонтальных линий из >= 3x одинаковых гемсов
    param col,row координты ячейки с гемом
    \return список гемсов из найденной линии*/
    GemL  get_horizontal_matches(int col, int row);

    /*!Обновление набранных очков
    param score количество очков*/
    void update_score(int score);
    /*!Перерисовка поля*/
    void repaintField();


    /*!Перечислены возможные комбинации гемов на поле*/
    //Перечислены возможные ходы
    int step[4][2] = { { 1, 0 } ,{2, 0} ,{0, 1},{0, 2} };
    int pos_step1[6][2] = { {-2, 0},{-1, -1},{-1, 1},{2, -1},{2, 1},{3, 0} };
    int num_of_steps1 = 6;
    int pos_step2[2][2] = { {1, -1}, {1, 1} };
    int num_of_steps2 = 2;
    int pos_step3[6][2] = { {0, -2}, {-1, -1}, {1, -1}, {-1, 2}, {1, 2}, {0, 3} };
    int num_of_steps3 = 2;
    int pos_step4[2][2] = { { -1, 1 }, { 1, 1 } };
    int num_of_steps4 = 6;

private slots:
    void buttonClick();
            //!< слот обработки нажатия клетки кнопкой мыши

    friend class Meditator;
};
#endif // FIELD_H

