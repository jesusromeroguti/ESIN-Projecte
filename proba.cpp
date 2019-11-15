#include <iostream>
#include "phone.hpp"
#include "call_registry.hpp"

using namespace std;

int main(){
  phone p(231,"Marta",3);
  // cout << p.nom() << endl;
  // cout << p.numero()<< endl;
  // cout << p.frequencia() << endl;

  phone l(123,"Alba",2);
  // cout << l.nom() << endl;
  // cout << l.numero()<< endl;
  // cout << l.frequencia() << endl;

  //  ------------ Proba call_registry ------------ //
  call_registry c;
  c.registra_trucada(123);
  c.registra_trucada(231);
  bool c1 = c.conte(123);
  bool c2 = c.conte(231);
  bool c3 = c.conte(111);
  cout << "Proba de conte";
  cout << c1 << " " << c2 << " " << c3 << endl;
  cout << "num entradas: " << c.num_entrades() << endl;


  // bool b = p <= l;
  // bool t = p != l;
  // cout << b << endl;
  // p++;
  // cout << p.frequencia() << endl;
  // cout << t << endl;
  // ++l;
  // cout << l.frequencia() << endl;
  // string s = "Alba";
  // string a = "Zais";
  // bool b = a > s;
  // cout << b << endl;
}
