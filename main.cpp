#include "world/chunk.h"
#include <vector>
#include "scenes/window.hpp"
#include <QApplication>
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  std::vector<chunk> chunkarr = chunk::create_chunks(0,0); // temp - 0,0. coords will be put based on camera later
  main_screen mainScreen;
  mainScreen.show();
  app.exec();
}
