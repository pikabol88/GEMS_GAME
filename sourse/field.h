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


#define BACK "black" //!< ���� �������� ���� ��� ������� ����
#define PICK "#696969"//!<���� ��������� ���������� ����

class Gem;
class BonusGem;
class Meditator;

//! ������� ����
class Field : public QWidget {

    Q_OBJECT

public:
    Field(QWidget *perent = 0);
    ~Field();

    Score *points = nullptr; //!< ���������� ��������� �����
    QString m_background = "background-color:";  //!< ���� �������� ����
    QString m_picked_background = "background-color:";  //!< ���� ���������� ������ �������� ����
    
private:
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
    QList<Gem*> create_bonus();
    /*! ��������� ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    QList<Gem*> remove_line(int cur_i, int cur_j);
    /*! ��������� �������������� ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    QList<Gem*> remove_horizontal_line(int cur_i, int cur_j);
    /*! ��������� ������������ ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    QList<Gem*> remove_vertical_line(int cur_i, int cur_j);
    /*! ��������� ����� ������������ ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    QList<Gem*> remove_left_diagonal_line(int cur_i, int cur_j);
    /*! ��������� ������ ������������ ����� ������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    QList<Gem*> remove_right_diagonal_line(int cur_i, int cur_j);
    /*! ��������� ���� �������, ������ ����������
    param cur_i,cur_j ���������� ���������� �����
    \return ������ ������, ������� ���� ���������� */
    QList<Gem*> remove_circle(int cur_i, int cur_j);

    /*!��������� ����� � ������� ����������� �� j-�� ����������
    param bonus_list ������ ������
    \return ��������������� ������ ������ */
    QList<Gem*> sort_bonus(QList<Gem*>bonus_list);
    /*!������� ���� � ���������� ��������� j-�� ����������
    param bonus_list ������ ������
    \return ��������� ���� */
    Gem* find_max(QList<Gem*>bonus_list);

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
    /*!���������, �������� �� ��� ������ �����, �� ����� �� ������ �� ������� ���� 
    param gem ������� ���*/
    bool is_possible_move(Gem &gem);

    /*!���������������� ����� ����*/
    void init_game();
    /*!������������ ����*/
    void create_new_field();
    /*!������� ������ ����/�������� ����� ����� ���������� ����� ������*/
    void update_field(QList<QList<Gem*>>matches_list);

    void find_matches_and_update();
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
    QList<QList<Gem*>> look_for_matches();
    /*!����� ������������ ����� �� >= 3x ���������� ������
    param col,row ��������� ������ � �����
    \return ������ ������ �� ��������� �����*/
    QList<Gem*> get_vertical_matches(int col, int row);
    /*!����� �������������� ����� �� >= 3x ���������� ������
    param col,row ��������� ������ � �����
    \return ������ ������ �� ��������� �����*/
    QList<Gem*> get_horizontal_matches(int col, int row);

    /*!���������� ��������� �����
    param score ���������� �����*/
    void update_score(int score);
    /*!����������� ����*/
    void repaintField();

private slots:
    void buttonClick();
            //!< ���� ��������� ������� ������ ������� ����

    friend class Meditator;
};
#endif // FIELD_H

