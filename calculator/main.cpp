#include <iostream>

using namespace std;

class Calculator {
public:
  Calculator() {}

  double add(double a, double b) { return a + b; }

  double subtract(double a, double b) { return a - b; }

  double multiply(double a, double b) { return a * b; }

  double divide(double a, double b) {
    if (b != 0) {
      return a / b;
    } else {
      cout << "Error: Cannot divide by zero!" << endl;
      return 0;
    }
  }
};

int main() {
  Calculator calc;
  char op;
  double num1, num2;

  cout << "Enter operator (+, -, *, /): ";
  cin >> op;

  cout << "Enter two numbers: ";
  cin >> num1 >> num2;

  switch (op) {
  case '+':
    cout << "Result: " << calc.add(num1, num2) << endl;
    break;
  case '-':
    cout << "Result: " << calc.subtract(num1, num2) << endl;
    break;
  case '*':
    cout << "Result: " << calc.multiply(num1, num2) << endl;
    break;
  case '/':
    cout << "Result: " << calc.divide(num1, num2) << endl;
    break;
  default:
    cout << "Invalid operator!" << endl;
    break;
  }

  return 0;
}
