#include "node.h"
#include <iostream>

using namespace std;

void Node::add_child(Node *child) { this->child.push_back(child); }

void Node::print_child() {
  for (auto c : child) {
    cout << c->col << endl;
  }
}

void Node::print_field() {
  cout << this->field << endl;
  for (auto c : child) {
    c->print_field();
  }
}

void Node::print_level() {
  cout << this->level << endl;
  for (auto c : child) {
    c->print_level();
  }
}

void Node::print_dtype() {
  cout << this->dtype << endl;
  for (auto c : child) {
    c->print_dtype();
  }
}

void Node::print_all(int indent = 0) {
  // 출력에 들어갈 노드 정보 출력
  for (int i = 0; i < indent - 1; ++i) {
    cout << "|";
  }
  cout << "+-" << this->col << " : " << this->field << " (" << this->dtype
       << ")" << endl;

  for (size_t i = 0; i < child.size(); ++i) {
    cout << "|";
    if (i == child.size() - 1) {
      // 마지막 자식 노드인 경우
      child[i]->print_all(indent + 1); // 자식 노드 출력
    } else if (i == 0) {
      // 첫번째 자식 노드인 경우
      child[i]->print_all(indent + 1);
    } else {
      for (int j = 0; j < indent - 1; ++j) {
        cout << "|";
      }
      child[i]->print_all(indent + 1);
    }
  }
}
