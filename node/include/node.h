#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

class Node {
public:
  Node *parent;
  string col;
  int field;
  vector<Node *> child;
  string dtype;
  int level;

  ~Node() {
    for (auto c : child) {
      delete c;
    }
  }

  Node(Node *parent, string col, int field, int level)
      : parent(parent), col(col), field(field), level(level) {}

  void get_memory_usage(Node *node);
  void add_child(Node *child);
  void print_child();
  void print_field();
  void print_level();
  void print_dtype();
  void print_all(int indent);
};

#endif
