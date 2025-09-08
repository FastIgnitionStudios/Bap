#define BAP_IMPLEMENTATION
#include "Bap.h"

int main(int argc, char* argv[]) {
  Cmd cmd = {};

  AppendCmd(cmd, "g++", "Bap.cpp");
  return 0;
}
