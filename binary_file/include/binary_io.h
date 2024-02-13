#ifndef BINARY_IO_H
#define BINARY_IO_H

#include <string>
#include <vector>

// 데이터 타입을 나타내는 열거형
enum class DataType { INTEGER, FLOAT, STRING, ARRAY };

// 데이터 구조
struct Data {
  DataType type; // 데이터 타입
  size_t size;   // 데이터 크기
  void *data;    // 데이터 포인터

  // 생성자
  Data(DataType t, size_t s, void *d) : type(t), size(s), data(d) {}
};

// 데이터를 바이너리 파일에 쓰는 함수 선언
void write_binary(const std::string &filename, const std::vector<Data> &data);

// 바이너리 파일에서 데이터를 읽는 함수 선언
std::vector<Data> read_binary(const std::string &filename);

#endif
