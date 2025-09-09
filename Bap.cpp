#define BAP_IMPLEMENTATION
#define BAP_DEBUG
#include "Bap.h"

int main(int argc, char* argv[]) {
  Cmd cmd = {};

  BAP_REBUILD(argc, argv)

  return 0;
}
