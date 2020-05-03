#include"mainwindow.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent) {

    QPixmap newImg("img\\img_new.png");
    QPixmap helpImg("img\\img_help.png");
    QPixmap quitImg("img\\img_quit.png");

    QPixmap darkImg("img\\img_dark.png");
    QPixmap lightImg("img\\img_light.png");
    QPixmap oceanImg("img\\img_ocean.jpg");

    QAction *helpAction = new QAction(helpImg, "&Help", this);
    QAction *newGameAction = new QAction(newImg, "&New", this);
    QAction *quitAction = new QAction(quitImg, "&Quit", this);

    QAction *dartStyleAction = new QAction(darkImg, "&Dark", this);
    QAction *lightStyleAction = new QAction(lightImg, "&Light", this);
    QAction *oceanStyleAction = new QAction(oceanImg, "&Ocean", this);

    // А здесь мы задаём сочетание горячих клавиш CTRL+Q, которое будет выполнять действие Quit (Выход)
    quitAction->setShortcut(tr("CTRL+Q"));

    QMenu *game;
    QMenu *style;
    game = menuBar()->addMenu("&Game");
    style = menuBar()->addMenu("&Style");

    game->addAction(newGameAction); 
    game->addAction(helpAction);
    game->addSeparator();
    game->addAction(quitAction);

    style->addAction(dartStyleAction);
    style->addAction(lightStyleAction);
    style->addAction(oceanStyleAction);

    // В некоторых средах значки меню по умолчанию не отображаются, поэтому мы можем попробовать отключить атрибут Qt::AA_DontShowIconsInMenus
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);
    statusBar()->showMessage("                                Kill all viruses - save the planet");

    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(helpAction, &QAction::triggered, this, &GameWindow::showHelp);
    connect(newGameAction, &QAction::triggered, this, &GameWindow::restart);

    connect(dartStyleAction, &QAction::triggered, this, &GameWindow::changeStyleDark);
    connect(lightStyleAction, &QAction::triggered, this, &GameWindow::changeStyleLight);
    connect(oceanStyleAction, &QAction::triggered, this, &GameWindow::changeStyleOcean);
}


void GameWindow::showHelp() {
    InfoWindow *w = new InfoWindow;
    w->setWindowTitle("INFO");
    w->setWindowIcon(QIcon("img\\img_logo.png"));
    w->setFixedSize(700, 450);
    w->show();
}

void GameWindow::restart() {
    this->m_game_components->on_gameReset();
}

void GameWindow::changeStyleDark() {
    QString back = "#000000";
    QString pick = "#6E6E6E";
    this->m_game_components->changeColor(back,pick);
}

void GameWindow::changeStyleLight() {
    QString back = "#A9F5BC";
    QString pick = "#A4A4A4";
    this->m_game_components->changeColor(back, pick);
} 

void GameWindow::changeStyleOcean() {
    QString back = "#0B4C5F";
    QString pick = "#20B2AA";
    this->m_game_components->changeColor(back, pick);
}

GameWindow::~GameWindow() {};