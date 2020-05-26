#include"mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QPixmap newImg("img_new.png");
    QPixmap helpImg("img_help.png");
    QPixmap quitImg("img_quit.png");

    QPixmap darkImg("img_dark.png");
    QPixmap lightImg("img_light.png");
    QPixmap oceanImg("img_ocean.jpg");

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
    connect(helpAction, &QAction::triggered, this, &MainWindow::showHelp);
    connect(newGameAction, &QAction::triggered, this, &MainWindow::restart);

    connect(dartStyleAction, &QAction::triggered, this, &MainWindow::changeStyleDark);
    connect(lightStyleAction, &QAction::triggered, this, &MainWindow::changeStyleLight);
    connect(oceanStyleAction, &QAction::triggered, this, &MainWindow::changeStyleOcean);
}


void MainWindow::showHelp() {
    InfoWindow *w = new InfoWindow;
    w->setWindowTitle("INFO");
    w->setWindowIcon(QIcon("img_logo.png"));
    w->setFixedSize(700, 450);
    w->show();
}

void MainWindow::restart() {
    this->m->on_gameReset();
}

void MainWindow::changeStyleDark() {
    QString back = "#000000";
    QString pick = "#6E6E6E";
    this->m->changeColor(back,pick);
}

void MainWindow::changeStyleLight() {
    QString back = "#A9F5BC";
    QString pick = "#A4A4A4";
    this->m->changeColor(back, pick);
} 

void MainWindow::changeStyleOcean() {
    QString back = "#0B4C5F";
    QString pick = "#20B2AA";
    this->m->changeColor(back, pick);
}

MainWindow::~MainWindow() {};