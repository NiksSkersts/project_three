#include "world/chunk.h"
#include <vector>
#include <QApplication>
#include <QVulkanInstance>
#include <scenes/main_menu.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    main_menu window;
    window.show();
    return app.exec();
}
