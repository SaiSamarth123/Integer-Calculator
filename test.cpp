#include <iostream>
#include <string>
#include <cctype>
#include "integer.h"

using namespace std;
int main() {
    Integer add1("1000");
  Integer add2("1");
  add1.add(add2);
  cout << add1.toStr() << endl;
  return 0;
}