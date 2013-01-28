
#include <string>
#include "Event/Event.hpp"

int main(int argc, char *argv[]) {

  Event::Evented<std::string> toto;
  Event::Callback cb;

  toto.on("ready", &cb);
  toto.on("ready", &cb);

  toto.emit("ready");
  return 0;
}
