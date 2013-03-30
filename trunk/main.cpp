
#include "DaemonManager.hpp"

int main()
{
  DaemonManager manager;
  
  manager.addPort(3030);
  manager.addPort(2020);
  manager.addPort(80);
  while (true)
    manager.update();
}
