#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <span>
#include <cstddef>
#include <string>

using namespace std;
using namespace filesystem;

auto read_file(const path &_path, const int argc, span<char*> args) -> int {
  bool count = false;
  for (size_t i = 1; i < argc; i++) {
    const auto option = string(args[i]);
    if (option.empty() || option[0] != '-') {
      continue;
    }
    if (option == "--count" || option == "-c") {
      count = true;
      continue;
    }
    cout << "Unsupported option: " << option << "\n";
  }

  ifstream user_file;
  user_file.open(_path.string());

  if (!user_file.is_open()) {
    cout << "Unable to open file " << absolute(_path) << "\n";
    return 1;
  }

  string line;
  cout << "Contents of " << absolute(_path) << ":" << "\n";

  if (count) {
    int _line_num = 1;
    while (getline(user_file, line)) {
      cout << _line_num << "  " << line << "\n";
      ++_line_num;
    }
  } else {
    while (getline(user_file, line)) {
      cout << line << "\n";
    }
  }

  user_file.close();
  return 0;
}

auto main(const int argc, char *argv[]) -> int {
  // Check if any arguments are provided
  if (argc < 2) {
    cout << "Please provide a file path. Usage: kat <filename>" << "\n";
    return 1;
  }

  span<char*> args(argv, static_cast<size_t>(argc));

  // Find which argument isn't a flag and use it as the path
  path file_path;
  bool _path = false;
  for (size_t i = 1; i < argc; i++) {
    const auto option = string(args[i]);
    if (!option.starts_with("-")) {
      file_path = option;
      _path = true;
    }
  }
  if (!_path) {
    cout << "Please provide a file path. Usage: kat <filename>" << "\n";
    return 1;
  }


  // Read the file
  return read_file(file_path, argc, args);
}