#include "node.h"
#include <iomanip>
#include <iostream>

using namespace std;

void Node::add_child(Node *child) { this->child.push_back(child); }

void Node::get_memory_usage(Node *node) {
  double memoryUsageMB = static_cast<double>(sizeof(*node)) / (1024 * 1024);

  cout << "Memory usage: " << fixed << setprecision(16) << memoryUsageMB
       << " MB" << endl;
}

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

void Node::print_all(int indent = 0) {
  // 출력에 들어갈 노드 정보 출력
  for (int i = 0; i < indent - 1; ++i) {
    cout << "|";
  }
  cout << "+-" << this->col << " : " << this->field << " ("
       << ")" << endl;

  for (size_t i = 0; i < child.size(); ++i) {
    cout << "|";
    if (i == child.size() - 1) {
      child[i]->print_all(indent + 1);
    } else if (i == 0) {
      child[i]->print_all(indent + 1);
    } else {
      for (int j = 0; j < indent - 1; ++j) {
        cout << "|";
      }
      child[i]->print_all(indent + 1);
    }
  }
}
