#include "node.h"
#include <cstring>
#include <fstream>
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

void Node::save(string filename) {
  ofstream ofs(filename, ios::binary);
  Serialize(ofs);
  ofs.close();
}

Node *Node::load(string filename) {
  ifstream ifs(filename, ios::binary);
  Node *root = Deserialize(ifs);
  ifs.close();
  return root;
}

void Node::Serialize(ofstream &out) {
  // Write data in binary format
  out.write(reinterpret_cast<char *>(&level), sizeof(level));
  out.write(reinterpret_cast<char *>(&field), sizeof(field));
  uint32_t col_length = col.length();
  out.write(reinterpret_cast<char *>(&col_length), sizeof(col_length));
  out.write(col.c_str(), col_length);

  // Recursively serialize child nodes
  uint32_t child_count = child.size();
  out.write(reinterpret_cast<char *>(&child_count), sizeof(child_count));
  for (auto child_node : child) {
    child_node->Serialize(out);
  }
}

Node *Node::Deserialize(ifstream &in) {
  // Create a new Node to store deserialized data
  Node *newNode = new Node(nullptr, "", 0, 0);

  // Read data in binary format
  in.read(reinterpret_cast<char *>(&newNode->level), sizeof(newNode->level));
  in.read(reinterpret_cast<char *>(&newNode->field), sizeof(newNode->field));

  // Read and allocate memory for string data
  uint32_t col_length;
  in.read(reinterpret_cast<char *>(&col_length), sizeof(col_length));
  char *col_buffer = new char[col_length + 1];
  in.read(col_buffer, col_length);
  col_buffer[col_length] = '\0';
  newNode->col = col_buffer;
  delete[] col_buffer; // Ensure proper memory management

  // Read the number of child nodes
  uint32_t child_count;
  in.read(reinterpret_cast<char *>(&child_count), sizeof(child_count));

  // Recursively deserialize child nodes, handling potential nullptr parent
  for (size_t i = 0; i < child_count; i++) {
    Node *childNode = Deserialize(in);
    if (childNode) { // Check for successful deserialization
      childNode->parent =
          newNode; // Set parent reference for deserialized child
      newNode->child.push_back(childNode);
    }
  }

  return newNode;
}
