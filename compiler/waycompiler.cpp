#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class WayCompiler {
public:
  void compile(const string &inputFilename, const string &outputFilename) {
    ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
      cout << "Error: Cannot open file " << inputFilename << endl;
      return;
    }

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
      cout << "Error: Cannot create file " << outputFilename << endl;
      inputFile.close();
      return;
    }

    string line;
    while (getline(inputFile, line)) {
      vector<string> tokens = tokenize(line);
      if (tokens.empty())
        continue;
      if (tokens[0] == "say") {
        if (tokens.size() >= 2) {
          outputFile << "say ";
          for (size_t i = 1; i < tokens.size(); ++i) {
            outputFile << tokens[i] << " ";
          }
          outputFile << endl;
        } else {
          cout << "Error: Invalid say statement" << endl;
        }
      } else {
        cout << "Error: Unknown statement" << endl;
      }
    }

    inputFile.close();
    outputFile.close();
    cout << "Compilation completed. Binary file generated: " << outputFilename
         << endl;
  }

private:
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
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <way_file.way> <output_binary>" << endl;
    return 1;
  }

  string inputFilename = argv[1];
  string outputFilename = argv[2];

  WayCompiler compiler;
  compiler.compile(inputFilename, outputFilename);
  return 0;
}
