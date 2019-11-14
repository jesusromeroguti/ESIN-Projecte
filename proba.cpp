#include <iostream>
#include "phone.hpp"

using namespace std;

int main(){
  phone p(123,"Jesus",2);
  cout << p.nom() << endl;
  cout << p.numero()<< endl;
  cout << p.frequencia() << endl;

  phone l(123,"Jesus",2);
  cout << l.nom() << endl;
  cout << l.numero()<< endl;
  cout << l.frequencia() << endl;

  bool b = p == l;
  cout << b << endl;
}
