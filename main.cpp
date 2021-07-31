#include <QApplication>
#include <QVulkanInstance>
#include <scenes/main_menu.h>

int main(int argc, char *argv[])
{
    QApplication application(argc,argv);
    main_menu mainMenu;
    mainMenu.resize(500,500);
    mainMenu.showNormal();
    return application.exec();
}
