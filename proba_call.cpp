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
  cout << "num entrades: " <<i << endl;
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
  c.assigna_nom(123456789, "Jesus");
  string nom2 = c.nom(123456789);
  cout << "Nom del tel 123456789: " << nom2 << endl;
  c.registra_trucada(123456789);
  nat l = c.num_trucades(123456789);
  cout << "Num trucades: " << l << endl;

  // Prueba assigna_nom
  c.assigna_nom(987654321, "Marta");
  bool con1 = c.conte(987654321);
  cout << con1 << endl;
  nat e = c.num_entrades();
  cout << "num entrades: " << e << endl;

  // Prueba de Elimina
  c.elimina(626468480);
  bool con = c.conte(626468480);
  cout << con << endl;
  nat x = c.num_entrades();
  cout << "num entrades despres de elimina 626468480: " << x << endl;
  // c.elimina(626468480);

  // Prueba constructor per copia
  call_registry c2(c);
  nat nume = c2.num_entrades();
  cout << "numero d'entrades c2: " << nume << endl;
  bool c2c = c2.conte(123456789);
  cout << c2c << endl;
  nat trucades = c2.num_trucades(123456789);
  cout << "numero de trucades 123456789 en c2: " <<trucades << endl;


  // Proves dump
  vector<phone> v;
  call_registry call;
  call.registra_trucada(123456789);
  call.assigna_nom(123456789, "Jesus");
  call.registra_trucada(626468480);
  call.assigna_nom(626468480, "Marta");
  // call.registra_trucada(987654321);
  // call.assigna_nom(987654321, "Marta");
  call.dump(v);
  cout << v.size() << endl;

  cout << "------------------------------------------------" << endl;

  // Proves operator=
  call_registry reg;
  bool m = reg.es_buit();
  nat ne = reg.num_entrades();
  cout << "numero entrades abans del = es: " << ne << endl;
  cout << m << endl;
  reg = call;
  nat reg_entrades = reg.num_entrades();
  cout << "El numero d'entrades de reg es: " << reg_entrades << endl;
  cout << reg.nom(123456789) << endl;
  cout << reg.nom(626468480) << endl;
  bool reg_conte = reg.conte(123456789);
  cout << reg_conte << endl;
}
