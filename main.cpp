#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace filesystem;


int read_file(const path& _path, const int argc, char *argv[]) {
    bool count = false;
    int i = 1;
    for (i=1; i < argc; i++) {
        const auto option = string(argv[i]);
        if (!option.starts_with("-")){continue;}
        if (option == "--count" || option == "-c") {
            count = true;
            continue;
        }
        cout << "Unsupported option: " << option << endl;
    }


    ifstream user_file;
    user_file.open(_path.string());

    if (!user_file.is_open()) {
        cout << "Unable to open file " << absolute(_path) << endl;
        return 1;
    }

    string line;
    cout << "Contents of " << absolute(_path) << ":" << endl;

    if (count == true) {
        int _line_num = 1;
        while (getline (user_file, line)) {
            cout << _line_num << "  " << line << endl;
            ++_line_num;
        }
    } else {
        while (getline (user_file, line)) {
            cout << line << endl;
        }
    }

    user_file.close();
    return 0;
}

int main(const int argc, char *argv[]) {
    // Check if any arguments are provided
    if (argc < 2) {
        cout << "Please provide a file path. Usage: kat <filename>" << endl;
        return 1;
    }

    // Find which argument isn't a flag and use it as the path
    path file_path;
    int i = 1;
    bool path = false;
    for (i=1; i < argc; i++) {
        const auto option = string(argv[i]);
        if (!option.starts_with("-")) {
            file_path=option;
            path = true;
        }
    }
    if (!path) {
        cout << "Please provide a file path. Usage: kat <filename>" << endl;
        return 1;
    }

    // Read the file
    return read_file(file_path, argc, argv);

}