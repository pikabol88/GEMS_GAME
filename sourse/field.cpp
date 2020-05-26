#include "field.h"

Field::Field(QWidget *parent) :QWidget(parent) {
    m_background.append(BACK);
    m_picked_background.append(PICK);
    setStyleSheet(m_background);
    m_isClicked = false;
    points = new Score(this);
    resize(M_WIDTH, M_HEIGHT);
    init_game();
    m_bonusGem = new BonusGem(m_field[0][0]);
}

//отвечает за первичную инициализацию
void Field::init_game() {
    m_inGame = true; 
    QGridLayout *layout = new QGridLayout(this);
    //Генерируется карта до тех пор, пока она не будет удовлетворять условиям игры
    //(на исходном поле должны быть ходы и не должно быть три гема в ряд)
    do {
        for (int i = 0; i < M_GEM_COUNT; ++i) {
            for (int j = 0; j < M_GEM_COUNT; ++j) {
                createGem(i, j, *layout);
            }
        }
    } while((is_three_line())||(!is_available_moves()));    
}

void Field::createGem(int i, int j, QGridLayout &layout) {
    m_field[i][j] = new Gem(i, j, this);
    connect(m_field[i][j], SIGNAL(clicked()), SLOT(buttonClick()));
    layout.addWidget(m_field[i][j], i, j, Qt::AlignLeft);
    layout.setMargin(0);
    layout.setSpacing(0);
    layout.setAlignment(Qt::AlignLeft);
}

void Field::buttonClick() {
    Gem *newGem = (Gem *)sender();
    newGem->setStyleSheet(m_picked_background);
    if (!m_isClicked) {                
        m_savedGem = (Gem*)sender();
        int value_x = newGem->m_i;
        int value_y = newGem->m_j;             
        m_isClicked = true;
    } else {
        m_isClicked = false;
        newGem->setStyleSheet(m_background);
        if (newGem == m_savedGem) {
            newGem->setStyleSheet(m_background);
        } else {
            if (is_possible_move(*newGem)) {
                swipe_gems(m_savedGem, newGem);
                if (!is_three_line()) {
                    swipe_gems(newGem, m_savedGem);
                } 
                m_savedGem = newGem;
                match_three_processing();
            } else {
                m_savedGem->setStyleSheet(m_background);
            }
        }
    }
}

bool Field::is_possible_move(const Gem &gem) {
    if (gem.m_i == m_savedGem->m_i) {
        if(abs(gem.m_j - m_savedGem->m_j) == 1)
            return true;
    }
    else if (gem.m_j == m_savedGem->m_j) {
        if (abs(gem.m_i - m_savedGem->m_i) == 1)
            return true;
    }
    return false;
}

// проверка на возможные ходы по составлению линий на поле     
bool Field::is_available_moves() {

    for (int i = 0;i < M_GEM_COUNT;i++) {
        for (int j = 0;j < M_GEM_COUNT;j++) {
            // воможна горизонтальная, две подряд            
            if (match_pattern(i, j, step[0], pos_step1, num_of_steps1)) {
                return true;
            }
            // воможна горизонтальная, две по разным сторонам 
            if (match_pattern(i, j, step[1], pos_step2, num_of_steps2)) {
                return true;
            }
            // возможна вертикальная, две подряд    
            if (match_pattern(i, j, step[2], pos_step3, num_of_steps3)) {
                return true;
            }
            // воможна вертикальная, две по разным сторонам             
            if (match_pattern(i, j, step[3], pos_step4, num_of_steps4)) {
                return true;
            }
        }
    }
    // не найдено возможных линий        
    return false;
}

bool Field::match_pattern(int col, int row, int *mustHave, int needOne[][2], int size) {
    int type = m_field[col][row]->m_color;
    // убедимся, что есть вторая фишка одного типа        
    for (int i = 0;i < 1;i++) {
        if (!match_type(col + mustHave[0], row + mustHave[1], type)) {
            return false;
        }
    }
    // убедимся, что третья фишка совпадает по типу с двумя другими 
    for (int i = 0;i < size;i++) {
        if (match_type(col + needOne[i][0], row + needOne[i][1], type)) {
            return true;
        }
    }
    return false;
}

bool Field::match_type(int col, int row, int type) {
    // убедимся, что фишка не выходит за пределы поля        
    if ((col < 0) || (col >= M_GEM_COUNT) || (row < 0) || (row >= M_GEM_COUNT)) {
        return false;
    }
    return (m_field[col][row]->m_color == type);
}

void Field::redraw_field(Gem2L matches_list) {
    for (int i = 0;i < matches_list.size();i++) {
        int numPoints = (matches_list[i].size())*M_POINTS_FOR_GEM;
        for (int j = 0; j < matches_list[i].size();j++) {
            matches_list[i][j]->removeGem();
            matches_list[i][j]->repaint();
            thread_hack::msleep(100);
        }
        update_score(numPoints);
    }
}

void Field::bonus_processing() {
    Gem2L bonus_list;
    Field::GemL bonus;
    bonus = create_bonus();
    bonus = sort_bonus(bonus);
    bonus_list.append(bonus);
    update_field(bonus_list);
    repaint();
    bonus_list.clear();
}

void Field::match_three_processing() {
    // формируем список линий      
    Gem2L matches_list;
    while ((matches_list = look_for_matches()).size() != 0) {
        redraw_field(matches_list);
        update_field(matches_list);
        repaint();
        bonus_processing();
    }
    if (!is_available_moves()) {
        no_moves_message();
    }
}

void Field::no_moves_message() {
    int n = QMessageBox::information(0, "Information", "Unfortunately there are no more moves... \nDo you want to continue the game?", "Yes", "No", QString(), 0, 1);
    if (!n) {
        create_new_field();
        repaint();
    }
}

Field::Gem2L Field::look_for_matches() {
    Gem2L matches_list;
    for (int row = 0; row < M_GEM_COUNT; row++) {
        for (int col = 0; col < M_GEM_COUNT - 2; col++) {
            Field::GemL matches = get_horizontal_matches(col, row);
            if (matches.size() > 2) {
                matches_list.append(matches);
                col += matches.size() - 1;
            }
        }
    }
    for (int col = 0; col < M_GEM_COUNT; col++) {
        for (int row = 0; row < M_GEM_COUNT - 2; row++) {
            Field::GemL matches = get_vertical_matches(col, row);
            if (matches.size() > 2) {
                matches_list.append(matches);
                row += matches.size() - 1;
            }
        }
    }
    return matches_list;
}

bool Field::is_three_line() {
    if (is_three_line_hor() || is_three_line_ver()) {
        return true;
    }
    else return false;
}

bool Field::is_three_line_hor() {
    int count = 0;
    for (int i = 0;i < M_GEM_COUNT;i++) {
        count = 0;
        for (int j = 1;j < M_GEM_COUNT;j++) {
            if (m_field[i][j - 1]->m_type == m_field[i][j]->m_type) {
                count++;
                if (count >= 2) {
                    return true;
                }
            }
            else count = 0;
        }
    }
    return false;
 }

bool Field::is_three_line_ver() {
    int count = 0;
    for (int j = 0;j < M_GEM_COUNT;j++) {
        count = 0;
        for (int i = 1;i < M_GEM_COUNT;i++) {
            if (m_field[i-1][j]->m_type == m_field[i][j]->m_type) {
                count++;
                if (count >= 2) {
                    return true;
                }
            }
            else count = 0;
        }
    }
    return false;
}

void Field::update_score(int score) {
    points->updateScore(score);
}

void Field::swipe_gems(Gem *m_savedGem, Gem *newGem) {
    setStyleSheet(m_background);
    QImage tmp = m_savedGem->m_type;
    int coltmp = m_savedGem->m_color;
    m_field[m_savedGem->m_i][m_savedGem->m_j]->m_type = newGem->m_type;
    m_field[m_savedGem->m_i][m_savedGem->m_j]->m_color = newGem->m_color;
    m_field[newGem->m_i][newGem->m_j]->m_type = tmp;
    m_field[newGem->m_i][newGem->m_j]->m_color = coltmp;
    m_field[m_savedGem->m_i][m_savedGem->m_j]->setStyleSheet(m_background);
    m_field[m_savedGem->m_i][m_savedGem->m_j]->repaint();
    m_field[newGem->m_i][newGem->m_j]->repaint();
    std::cout << "lol";
}

void Field::add_new_gem(int i, int j) {
    int i_new = i-1;
    for (i_new; i_new >= 0;i_new--) {
        if (m_field[i_new][j]->m_color != -1) {
            int colornow = m_field[i][j]->m_color;
            int colornew= m_field[i_new][j]->m_color;
            m_field[i][j]->m_color = m_field[i_new][j]->m_color;
            m_field[i][j]->m_type = m_field[i_new][j]->m_type;
            m_field[i_new][j]->removeGem();
            i--;
        }
    } 
    if (i == 0) {
        m_field[i][j]->changeGem();
    }
    m_field[i][j]->repaint();
}

Field::GemL Field::create_bonus() {
    Field::GemL matches_list;
    int tmp = this->points->m_score;
    if (tmp % 50 == 0) {
        this->m_bonusGem->setRandomType();
        QImage img = this->m_bonusGem->m_type;
        m_field[m_savedGem->m_i][m_savedGem->m_j]->m_type = img;
        m_field[m_savedGem->m_i][m_savedGem->m_j]->repaint();
        thread_hack::msleep(500);
        if (this->m_bonusGem->m_color == 1) {
            matches_list = remove_circle(m_savedGem->m_i, m_savedGem->m_j);
            this->update_score(100);
        }
        else if (this->m_bonusGem->m_color == 2) {
            matches_list = remove_line(m_savedGem->m_i, m_savedGem->m_j);
            this->update_score(100);
        }
    }
    return matches_list;
}

Field::GemL Field::get_horizontal_matches(int col, int row) {
    Field::GemL matches;
    matches.append(m_field[col][row]);
    for (int i = 1;col + i < M_GEM_COUNT;i++) {
        if (m_field[col][row]->m_color == m_field[col+i][row]->m_color) {
            matches.append(m_field[col + i][row]);
        } else {
            return matches;
        }
    }
    return matches;
}

Field::GemL Field::get_vertical_matches(int col, int row) {
    Field::GemL matches;
    matches.append(m_field[col][row]);
    for (int i = 1;row + i < M_GEM_COUNT;i++) {
        if (m_field[col][row]->m_color == m_field[col][row + i]->m_color) {
            matches.append(m_field[col][row + i]);
        } else {
            return matches;
        }
    }
    return matches;
}

Field::GemL Field::remove_line(int cur_i, int cur_j) {
    Field::GemL matches_list;
    Field::GemL matches_list2;
    time_t time = std::time(0);
    srand(time);
    int type = rand() % 6 + 1;
    switch (type) {
    case 1:
        matches_list = remove_horizontal_line(cur_i, cur_j);
        break;
    case 2:
        matches_list = remove_vertical_line(cur_i, cur_j);
        break;
    case 3:
        matches_list = remove_left_diagonal_line(cur_i, cur_j);
        break;
    case 4:
        matches_list = remove_right_diagonal_line(cur_i, cur_j);
        break;
    case 5:
        matches_list = remove_horizontal_line(cur_i, cur_j);
        matches_list2 = remove_vertical_line(cur_i, cur_j);
        break;
    case 6:
        matches_list = remove_left_diagonal_line(cur_i, cur_j);
        matches_list2 = remove_right_diagonal_line(cur_i, cur_j);
        break;
    default:
        break;
    }    
    thread_hack::msleep(200);
    m_field[cur_i][cur_j]->removeGem();
    if (!matches_list.contains(m_field[cur_i][cur_j])) {
        matches_list.append(m_field[cur_i][cur_j]);
    }
    for (int i = 0;i < matches_list2.size();i++) {
        if (!matches_list.contains(matches_list2[i])) {
            matches_list.append(matches_list2[i]);
        }
    }
    return matches_list;
}

Field::GemL Field::remove_vertical_line(int cur_i, int cur_j) {
    Field::GemL matches_list;
    for (int i = 0;i < M_GEM_COUNT;i++) {
        if (i == cur_i) {
            continue;
        }
        m_field[i][cur_j]->removeGem();
        m_field[i][cur_j]->repaint();
        matches_list.append(m_field[i][cur_j]);      
    }
    return matches_list;
}

Field::GemL Field::remove_horizontal_line(int cur_i, int cur_j) {
    Field::GemL matches_list;
    for (int j = 0;j < M_GEM_COUNT;j++) {
        if (j == cur_j) {
            continue;
        }
        m_field[cur_i][j]->removeGem();
        m_field[cur_i][j]->repaint();
        matches_list.append(m_field[cur_i][j]);
    }
    return matches_list;
}

Field::GemL Field::remove_left_diagonal_line(int cur_i, int cur_j) {
    Field::GemL matches_list;
    int i, j;
    matches_list.append(m_field[cur_i][cur_j]);
    for (i = cur_i - 1,j = cur_j - 1; i >=0 && j >= 0; i--, j--) {
        m_field[i][j]->removeGem();
        m_field[i][j]->repaint();
        matches_list.append(m_field[i][j]);
    }
    for (i = cur_i + 1, j = cur_j + 1; i < M_GEM_COUNT && j < M_GEM_COUNT;i++, j++) {
        m_field[i][j]->removeGem();
        m_field[i][j]->repaint();
        matches_list.append(m_field[i][j]);
    }
    return matches_list;
}

Field::GemL Field::remove_right_diagonal_line(int cur_i, int cur_j) {
    Field::GemL matches_list;
    int i, j;
    matches_list.append(m_field[cur_i][cur_j]);
    for (i = cur_i - 1, j = cur_j + 1;i >= 0 && j < M_GEM_COUNT;i--, j++) {
        m_field[i][j]->removeGem();
        m_field[i][j]->repaint();
        matches_list.append(m_field[i][j]);
    }
    for (i = cur_i + 1, j = cur_j - 1; i < M_GEM_COUNT && j >= 0;i++, j--) {
        m_field[i][j]->removeGem();
        m_field[i][j]->repaint();
        matches_list.append(m_field[i][j]);        
    }
    return matches_list;
}

Field::GemL Field::remove_circle(int cur_i, int cur_j) {
    Field::GemL matches_list;
    for (int i = cur_i - 1;i <= cur_i + 1; i++) {
        for (int j = cur_j - 1;j <= cur_j + 1;j++) {
            if (i == cur_i && j == cur_j) {
                matches_list.append(m_field[i][j]);
                continue;
            }
            if (i >= 0 && j >= 0 && i < M_GEM_COUNT&&j < M_GEM_COUNT) {
                m_field[i][j]->removeGem();
                m_field[i][j]->repaint();
                matches_list.append(m_field[i][j]);
            }
        }
    }
    thread_hack::msleep(200);
    m_field[cur_i][cur_j]->removeGem();
    if (!matches_list.contains(m_field[cur_i][cur_j])) {
        matches_list.append(m_field[cur_i][cur_j]);
    }
    return matches_list;
}

Field::GemL Field::sort_bonus(Field::GemL bonus_list) {
    Field::GemL new_list;
    Gem*tmp;
    int size = bonus_list.size();
    for (int i = 0;i < size; i++) {
        tmp = find_max(bonus_list);
        new_list.append(tmp);
        bonus_list.removeOne(tmp);
    }
    return new_list;
}

Gem*Field::find_max(Field::GemL bonus_list) {
    Gem*tmp = bonus_list[0];
    int size = bonus_list.size();
    for (int i = 1;i < size;i++) {
        if (bonus_list[i]->m_i < tmp->m_i)
            tmp = bonus_list[i];
    }
    return tmp;
}

void Field::create_new_field() {
    Gem2L matches_list;
    Field::GemL matches;
    for (int i = 0; i < M_GEM_COUNT; i++) {
        for (int j = 0;j < M_GEM_COUNT;j++) {
            matches.append(m_field[i][j]);
            m_field[i][j]->removeGem();
        }
    }
    matches_list.append(matches);
    do {
        update_field(matches_list);
    } while ((look_for_matches()).size() != 0 || (!is_available_moves()));
}

void Field::update_field(Gem2L matches_list) {
    for (int i = 0;i < matches_list.size();i++) {
        for (int j = 0; j < matches_list[i].size();j++) {
            add_new_gem(matches_list[i][j]->m_i, matches_list[i][j]->m_j);
        }
    }
}

void Field::repaintField() {
    for (int i = 0;i < this->M_GEM_COUNT;i++) {
        for (int j = 0;j < this->M_GEM_COUNT;j++) {
            m_field[i][j]->setStyleSheet(m_background);
        }
    }
}

Field::~Field() {}