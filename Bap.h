//
//
//
//  Bap (Build a Project) is not a build system inspired by nobuild and nob by Tsoding
//  Bap is designed for C++ projects first however may work with C and assembly projects as well
//  More language support may be added in the future
//  Bap is designed to be built once and then rand
//  to rebuild the c++ project without the need for external tooling other than the C++ Compiler of your choice.
//  An example on linux with GCC is "cc Bap.cpp -o Bap"
//
//
//
//


#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdarg>
#include <filesystem>
#include <vector>

// For code readability while writing
// #define BAP_IMPLEMENTATION

#if defined (_MSC_VER)

#define PLATFORM_COMPILER "cl"

#elif defined (__GNUC__)

#define PLATFORM_COMPIER "cc"

#elif defined (__clang__)

#define PLATFORM_COMPIER "cc"

#endif


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

#define BAP_REBUILD(argc, argv) Bap_Rebuild(argc, argv);

//
// This function is what automatically rebuilds the project whenever bap is run
//

void Bap_Rebuild(int argc, char** argv);


//
//  This is a class designed to abstract the organisation of a project and its files and generate
//  the compile command without having to use the Cmd struct manually. Using the Cmd struct directly is still valid
//  and this is just an abstraction for those that find it useful
//

class FileCollecton {
  
public:
  FileCollecton() = default;

  std::vector<const char*> GetFiles() { return Files; }
private:

  std::vector<const char*> Files;
};


//
//  This is where any functions/methods defined in this header file are implemented provided BAP_IMPLEMENTATION
//  is defined before this file is included. This follows the stb style of header and source file in one.
//

#ifdef BAP_IMPLEMENTATION

void Bap_Rebuild(int argc, char** argv) {
  Cmd cmd = {};
  cmd.Append(PLATFORM_COMPIER);
  cmd.Append("Bap.cpp");
  cmd.Append("-o");
  cmd.Append("Bap");
  cmd.Run();
}

void Cmd::Run() {
  system(Command.c_str());
#ifdef BAP_DEBUG
  std::cout << "Succesfully ran command: " << Command.c_str() << "\n";
#endif
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
