#include "binary_io.h"
#include <fstream>
#include <iostream>

using namespace std;

// 데이터를 바이너리 파일에 쓰는 함수 정의
void write_binary(const string &filename, const vector<Data> &data) {
  ofstream file(filename, ios::binary);
  if (!file.is_open()) {
    cerr << "Failed to open file for writing" << endl;
    return;
  }

  for (const auto &d : data) {
    file.write(reinterpret_cast<const char *>(&d.type), sizeof(DataType));
    file.write(reinterpret_cast<const char *>(&d.size), sizeof(size_t));
    file.write(reinterpret_cast<const char *>(d.data), d.size);
  }

  file.close();
}

// 바이너리 파일에서 데이터를 읽는 함수 정의
vector<Data> read_binary(const string &filename) {
  vector<Data> data;

  ifstream file(filename, ios::binary);
  if (!file.is_open()) {
    cerr << "Failed to open file for reading" << endl;
    return data;
  }

  while (!file.eof()) {
    DataType type;
    size_t size;
    file.read(reinterpret_cast<char *>(&type), sizeof(DataType));
    file.read(reinterpret_cast<char *>(&size), sizeof(size_t));

    // 데이터 버퍼 동적 할당
    void *buffer = new char[size];
    file.read(reinterpret_cast<char *>(buffer), size);

    // 데이터 구조 생성하여 벡터에 추가
    Data d(type, size, buffer);
    data.push_back(d);
  }

  file.close();

  return data;
}
