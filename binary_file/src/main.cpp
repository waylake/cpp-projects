#include "binary_io.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 예시 데이터 생성
  int intValue = 42;
  float floatValue = 3.14f;
  string stringValue = "Hello, world!";
  int arrayValue[] = {1, 2, 3, 4, 5};

  // 데이터 구조 생성
  vector<Data> data;
  data.push_back(Data(DataType::INTEGER, sizeof(intValue), &intValue));
  data.push_back(Data(DataType::FLOAT, sizeof(floatValue), &floatValue));
  data.push_back(Data(DataType::STRING, stringValue.size(), &stringValue[0]));
  data.push_back(Data(DataType::ARRAY, sizeof(arrayValue), arrayValue));

  // 바이너리 파일에 쓰기
  write_binary("data.bin", data);

  // 바이너리 파일 읽기
  vector<Data> loadedData = read_binary("data.bin");

  // 읽은 데이터 출력
  for (const auto &d : loadedData) {
    if (d.type == DataType::INTEGER) {
      cout << "Integer: " << *static_cast<int *>(d.data) << endl;
    } else if (d.type == DataType::FLOAT) {
      cout << "Float: " << *static_cast<float *>(d.data) << endl;
    } else if (d.type == DataType::STRING) {
      cout << "String: " << static_cast<char *>(d.data) << endl;
    } else if (d.type == DataType::ARRAY) {
      cout << "Array: ";
      int *arr = static_cast<int *>(d.data);
      for (size_t j = 0; j < d.size / sizeof(int); ++j) {
        cout << arr[j] << " ";
      }
      cout << endl;
    }
  }

  // 메모리 해제
  for (auto &d : loadedData) {
    delete[] static_cast<char *>(d.data);
  }

  return 0;
}
