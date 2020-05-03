#include <QVBoxLayout>

#include "meditator.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QVBoxLayout *layout = new QVBoxLayout;

    GameWindow window;
    Meditator *widget = new Meditator;
    window.m_game_components = QSharedPointer<Meditator>(widget);
    
    widget->setLayout(layout);
    window.setCentralWidget(widget);
    window.setWindowTitle("GEMS");
    window.setWindowIcon(QIcon("img\\img_logo.png"));
    window.setFixedSize(widget->width(), widget->height()*1.1);
    window.show();
    return app.exec();
}
