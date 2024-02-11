#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class WayInterpreter {
public:
  void interpret(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
      cout << "Error: Cannot open file " << filename << endl;
      return;
    }

    string line;
    while (getline(file, line)) {
      parseLine(line);
    }

    file.close();
  }

private:
  void parseLine(const string &line) {
    vector<string> tokens = tokenize(line);
    if (tokens.empty())
      return;
    if (tokens[0] == "say") {
      if (tokens.size() >= 2) {
        for (size_t i = 1; i < tokens.size(); ++i) {
          cout << tokens[i] << " ";
        }
        cout << endl;
      } else {
        cout << "Error: Invalid say statement" << endl;
      }
    } else {
      cout << "Error: Unknown statement" << endl;
    }
  }

  vector<string> tokenize(const string &str) {
    vector<string> tokens;
    istringstream iss(str);
    string token;
    while (iss >> token) {
      tokens.push_back(token);
    }
    return tokens;
  }
};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << " <way_file.way>" << endl;
    return 1;
  }

  string filename = argv[1];
  WayInterpreter interpreter;
  interpreter.interpret(filename);
  return 0;
}
