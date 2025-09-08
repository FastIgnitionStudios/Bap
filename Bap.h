#pragma once

#include <cstdlib>
#include <string>
#include <cstdarg>

// For code readability while writing
// #define BAP_IMPLEMENTATION

struct Cmd {
  std::string Command;
  
  // Open a terminal and parse Command directly to the command line
  void Run();

  // Append a command/argumen to this command
  // Will automatically create whitespace after the provided string
  void Append(const char* content);

  // Append a variable number of argmenents/commands to this Command string
  // Should not be called by user, instead use AppendCmd macro 
  void AppendVariadic(const char* first, ...);

  // Clear the contents of the command, called automatically after Run
  void Clear();
};


#define AppendCmd(Cmd, first, ...) Cmd.AppendVariadic(first, __VA_ARGS__, nullptr);


#ifdef BAP_IMPLEMENTATION


void Cmd::Run() {
  system(Command.c_str());
  Clear();
}

void Cmd::Append(const char* content) {
  Command.append(content);
  Command.append(" ");
}

void Cmd::AppendVariadic(const char* first, ...) {
#include <string>

  std::va_list list;

  va_start(list, first);

  int count {1};

  while (true) {
    const char* arg{va_arg(list, const char*)};

    if (arg == nullptr){
      break;
    }

    Command.append(arg);
    ++count;
  }

}

void Cmd::Clear() {
  Command.clear();
}

#endif
