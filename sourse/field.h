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

//! ������� ����
class Field : public QWidget {

    Q_OBJECT

public:
    Field(QWidget *perent = 0);
    ~Field();

    //QSharedPointer<Score>points;
    Score *points = nullptr; //!< ���������� ��������� �����
    QString m_background = "background-color:";  //!< ���� �������� ����
    QString m_picked_background = "background-color:";  //!< ���� ���������� ������ �������� ����
    
private:

    using Gem2L = QList<QList<Gem*>>;
    using GemL =  QList<Gem*>;

    bool m_inGame = false;  //!< ��������� �������� ����
    bool m_isClicked = false; //!< ��������� ����������� ������ �������� ����
    Gem *m_savedGem = nullptr; //!< ��������� ��������� ����
    BonusGem *m_bonusGem = nullptr; //!< �������� ����

    static const int M_WIDTH = 300; //!< ������ ����
    static const int M_HEIGHT = 300; //!< ������ ����
    static const int M_GEM_COUNT = 8;  //!< ���������� ������ � ����� ����� ����
    static const int M_POINTS_FOR_GEM = 10; //!< ���������� ����� �� ���� ������������ ���

    Gem* m_field[M_GEM_COUNT][M_GEM_COUNT];  //!< ������� ����


  
    /*! ������ � ������������ �������� ����� 
    \return ������ ������, ������� ���� ����������  */   
    GemL create_bonus();
    /*! ��������� ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    GemL remove_line(int cur_i, int cur_j);
    /*! ��������� �������������� ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    GemL  remove_horizontal_line(int cur_i, int cur_j);
    /*! ��������� ������������ ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    GemL  remove_vertical_line(int cur_i, int cur_j);
    /*! ��������� ����� ������������ ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    GemL  remove_left_diagonal_line(int cur_i, int cur_j);
    /*! ��������� ������ ������������ ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    GemL  remove_right_diagonal_line(int cur_i, int cur_j);
    /*! ��������� ���� �������, ������ ����������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    GemL  remove_circle(int cur_i, int cur_j);

    /*!��������� ����� � ������� ����������� �� j-�� ����������
    param bonus_list ������ ������
    \return ��������������� ������ ������ */
    GemL sort_bonus(GemL bonus_list);
    /*!������� ���� � ���������� ��������� j-�� ����������
    param bonus_list ������ ������
    \return ��������� ���� */
    Gem* find_max(GemL bonus_list);

    /*!������ ������� ��� �����
    param gem1, gem2 ����� */
    void swipe_gems(Gem *gem1, Gem *gem2);
    /*!��������� ����� ���
    param i,j ���������� ������ */
    void add_new_gem(int i, int j);

    /*!���������, ���� �� ��������� ���� �� ��������������� ���� */
    bool is_available_moves();
    /*!���������, ���� �� 3 ����� ������ � ����� ����/����� */
    bool is_three_line();
    bool is_three_line_hor();
    bool is_three_line_ver();
    /*!���������, �������� �� ��� ������ �����, �� ����� �� ������ �� ������� ���� 
    param gem ������� ���*/
    bool is_possible_move(const Gem &gem);

    /*!���������������� ����� ����*/
    void init_game();
    /*!���������� ������ ���� �� ����*/
    void createGem(int i, int j, QGridLayout &layout);
    /*!������������ ����*/
    void create_new_field();
    /*!������� ������ ����/�������� ����� ����� ���������� ����� ������*/
    void update_field(Gem2L matches_list);
    /*!�������� ����������� ������ � �������� ����� �� �� �����*/
    void redraw_field(Gem2L matches_list);

    void bonus_processing();

    void match_three_processing();
    void no_moves_message();
    /*!�������� ���������� ����� ������
    param col,row ��������� ������ � �����
    param type ��� ���� ��� ���������*/
    bool match_type(int col, int row, int type);
    /*!�������� ���������� ����� ������
    param col,row ��������� ������ � �����
    param mustHave ��������� ���������� ������ �����
    param needOne �������� ���������� ������� �����
    param size ������ needOne*/
    bool match_pattern(int col, int row, int *mustHave, int needOne[][2], int size);

    /*!����� ���� ����� �� >= 3x ���������� ������
    \return ������ ���� ��������� �����*/
    Gem2L look_for_matches();
    /*!����� ������������ ����� �� >= 3x ���������� ������
    param col,row ��������� ������ � �����
    \return ������ ������ �� ��������� �����*/
    GemL  get_vertical_matches(int col, int row);
    /*!����� �������������� ����� �� >= 3x ���������� ������
    param col,row ��������� ������ � �����
    \return ������ ������ �� ��������� �����*/
    GemL  get_horizontal_matches(int col, int row);

    /*!���������� ��������� �����
    param score ���������� �����*/
    void update_score(int score);
    /*!����������� ����*/
    void repaintField();


    /*!����������� ��������� ���������� ����� �� ����*/
    //����������� ��������� ����
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
            //!< ���� ��������� ������� ������ ������� ����

    friend class Meditator;
};
#endif // FIELD_H

