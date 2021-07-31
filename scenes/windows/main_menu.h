//
// Created by niks-skersts on 7/31/21.
//

#ifndef PROJECT_TWO_MAIN_MENU_H
#define PROJECT_TWO_MAIN_MENU_H
#include <QWindow>
#include <QtGui>

class main_menu : public QWindow{
    Q_OBJECT
public:
    explicit main_menu(QWindow *parent = 0);
    virtual void render(QPainter *painter);
private:
    QBackingStore *m_backingStore;
public slots:
    void renderNow();
    void renderLater();
protected:
    void resizeEvent(QResizeEvent *resizeEvent);
    void exposeEvent(QExposeEvent *);
    bool event(QEvent *event);
};

#endif //PROJECT_TWO_MAIN_MENU_H
