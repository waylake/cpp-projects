#include "node.h"

int main() {
  // Create nodes
  Node *root = new Node(nullptr, "root", 1, 0);
  Node *child1 = new Node(root, "child1", 2, 1);
  Node *child2 = new Node(root, "child2", 3, 1);
  Node *child1_1 = new Node(child1, "child1_1", 4, 2);
  Node *child1_2 = new Node(child1, "child1_2", 5, 2);
  Node *child2_1 = new Node(child2, "child2_1", 6, 2);

  // Add children to parent nodes
  root->add_child(child1);
  root->add_child(child2);
  child1->add_child(child1_1);
  child1->add_child(child1_2);
  child2->add_child(child2_1);

  // Extend depth to 5 levels
  Node *child1_1_1 = new Node(child1_1, "child1_1_1", 7, 3);
  Node *child1_1_2 = new Node(child1_1, "child1_1_2", 8, 3);
  Node *child1_2_1 = new Node(child1_2, "child1_2_1", 9, 3);
  Node *child1_2_2 = new Node(child1_2, "child1_2_2", 10, 3);
  Node *child2_1_1 = new Node(child2_1, "child2_1_1", 11, 3);
  Node *child2_1_2 = new Node(child2_1, "child2_1_2", 12, 3);

  child1_1->add_child(child1_1_1);
  child1_1->add_child(child1_1_2);
  child1_2->add_child(child1_2_1);
  child1_2->add_child(child1_2_2);
  child2_1->add_child(child2_1_1);
  child2_1->add_child(child2_1_2);

  // Print the tree
  root->print_all(0);

  // Clean up memory
  delete root;

  return 0;
}
