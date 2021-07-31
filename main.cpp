#include "world/chunk.h"
#include <QApplication>
#include <QVulkanInstance>
#include <scenes/windows/main_menu.h>

int main(int argc, char *argv[])
{
    QGuiApplication application(argc,argv);
    main_menu window;
    window.resize(500,500);
    window.showNormal();
    return application.exec();
}
