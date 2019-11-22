#include <iostream>
#include "phone.hpp"
#include "call_registry.hpp"

using namespace std;
using util::nat;

int main(){
  call_registry c;
  bool a = c.es_buit();
  cout << a << endl;
  bool t = c.conte(123456789);
  cout << t << endl;
  c.registra_trucada(123456789);
  t = c.conte(123456789);
  cout << t << endl;
  c.registra_trucada(626468480);
  nat i = c.num_entrades();
  cout << i << endl;
  bool b = c.es_buit();
  cout << b << endl;
  nat f = c.num_trucades(123456789);
  cout << "num trucades: " << f << endl;
  bool d = c.conte(626468480);
  cout << d << endl;
  string nom1 = c.nom(123456789);
  cout << nom1 << endl;
  c.registra_trucada(123456789);
  nat f2 = c.num_trucades(123456789);
  cout << "num trucades: " << f2 << endl;
}
