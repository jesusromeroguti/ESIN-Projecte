#include <iostream>
#include "phone.hpp"

using namespace std;

int main(){
  phone p(123,"Marta",3);
  // cout << p.nom() << endl;
  // cout << p.numero()<< endl;
  // cout << p.frequencia() << endl;

  phone l(123,"Alba",2);
  // cout << l.nom() << endl;
  // cout << l.numero()<< endl;
  // cout << l.frequencia() << endl;

  bool b = p <= l;
  // bool t = p != l;
  cout << b << endl;
  // cout << t << endl;

  // string s = "Alba";
  // string a = "Zais";
  // bool b = a > s;
  // cout << b << endl;
}
