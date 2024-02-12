#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 노드 클래스 정의
class Node {
public:
  string key;
  string value;
  vector<Node *> children; // 자식 노드를 가리키는 포인터들을 저장하는 벡터

  // 생성자
  Node(string k, string v) : key(k), value(v) {}

  // 자식 노드를 추가하는 함수
  void addChild(Node *child) { children.push_back(child); }
};

// JSON 파서 클래스 정의
class JSONParser {
public:
  // JSON 문자열을 파싱하여 노드 구조로 반환하는 함수
  Node *parse(const string &json);

private:
  size_t index;

  // 객체(JSON 객체)를 파싱하는 함수
  Node *parseObject(const string &json);

  // 배열(JSON 배열)을 파싱하는 함수
  Node *parseArray(const string &json);

  // 값(JSON 값)을 파싱하는 함수
  Node *parseValue(const string &json);

  // 문자열(JSON 문자열)을 파싱하는 함수
  string parseString(const string &json);
};

// JSON 파서 클래스의 멤버 함수 정의
Node *JSONParser::parse(const string &json) {
  index = 0;                // 파싱 인덱스 초기화
  return parseObject(json); // JSON 문자열을 객체로 파싱하여 반환
}

Node *JSONParser::parseObject(const string &json) {
  Node *node = new Node("", ""); // 새로운 객체 노드 생성
  while (index < json.size()) { // JSON 문자열을 모두 파싱할 때까지 반복
    if (json[index] == '{') { // 객체의 시작을 나타내는 문자인 경우
      index++;                // 다음 문자로 이동
      continue;
    } else if (json[index] == '}') { // 객체의 끝을 나타내는 문자인 경우
      index++;                       // 다음 문자로 이동
      break;                         // 반복문 종료
    } else if (json[index] == '"') { // 키 문자열을 나타내는 문자인 경우
      string key = parseString(json); // 문자열을 파싱하여 키 값으로 저장
      index++; // ':' 문자를 건너뛰기 위해 인덱스 증가
      Node *value = parseValue(json); // 값에 대한 노드를 파싱
      node->addChild(value);          // 자식 노드로 추가
    }
    index++; // 다음 문자로 이동
  }
  return node; // 객체 노드 반환
}

Node *JSONParser::parseArray(const string &json) {
  Node *node = new Node("", ""); // 새로운 배열 노드 생성
  while (index < json.size()) { // JSON 문자열을 모두 파싱할 때까지 반복
    if (json[index] == '[') { // 배열의 시작을 나타내는 문자인 경우
      index++;                // 다음 문자로 이동
      continue;
    } else if (json[index] == ']') { // 배열의 끝을 나타내는 문자인 경우
      index++;                       // 다음 문자로 이동
      break;                         // 반복문 종료
    } else { // 배열 요소를 나타내는 문자인 경우
      Node *value = parseValue(json); // 값에 대한 노드를 파싱
      node->addChild(value);          // 자식 노드로 추가
    }
    index++; // 다음 문자로 이동
  }
  return node; // 배열 노드 반환
}

Node *JSONParser::parseValue(const string &json) {
  if (json[index] == '{') {                 // 값이 객체인 경우
    return parseObject(json);               // 객체를 파싱하여 반환
  } else if (json[index] == '[') {          // 값이 배열인 경우
    return parseArray(json);                // 배열을 파싱하여 반환
  } else if (json[index] == '"') {          // 값이 문자열인 경우
    return new Node("", parseString(json)); // 문자열을 파싱하여 노드로 반환
  } else { // 값이 숫자 또는 불리언인 경우
    size_t endIndex =
        json.find_first_of(",}", index); // 구분자(쉼표 또는 닫는 괄호)를 찾음
    string value = json.substr(index, endIndex - index); // 값 문자열을 추출
    index = endIndex;           // 다음 문자 인덱스 설정
    return new Node("", value); // 값에 대한 노드를 생성하여 반환
  }
}

string JSONParser::parseString(const string &json) {
  size_t startIndex = json.find_first_of('"', index); // 문자열 시작 인덱스 찾기
  size_t endIndex =
      json.find_first_of('"', startIndex + 1); // 문자열 끝 인덱스 찾기
  index = endIndex;                            // 파싱 인덱스 갱신
  return json.substr(startIndex + 1,
                     endIndex - startIndex - 1); // 문자열 추출하여 반환
}

int main() {
  string json = "{\"name\": \"John\", \"age\": 30, \"city\": \"New York\"}";

  JSONParser parser;               // JSON 파서 객체 생성
  Node *root = parser.parse(json); // JSON 파싱하여 루트 노드 얻기

  cout << "Root Node:" << endl;
  cout << "Key: " << root->key << ", Value: " << root->value << endl;

  // 자식 노드 출력
  for (const auto &child : root->children) {
    cout << "Child Node:" << endl;
    cout << "Key: " << child->key << ", Value: " << child->value << endl;
  }

  return 0;
}
