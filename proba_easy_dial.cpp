#include <iostream>
#include "phone.hpp"
#include "call_registry.hpp"
#include "easy_dial.hpp"

using namespace std;

int main(){
  call_registry c;
  c.assigna_nom(123, "alex");
  c.assigna_nom(321, "Marta");
  c.registra_trucada(321);
  c.registra_trucada(321);
  c.registra_trucada(321);
  c.assigna_nom(983, "Maria");
  c.assigna_nom(789, "Mara");
  c.assigna_nom(777, "Mas");
  c.assigna_nom(999, "Mateo");
  c.assigna_nom(888, "Mar");
  c.assigna_nom(666, "Maru");
  c.assigna_nom(555, "M");
  c.assigna_nom(333, "Jesus");
  c.registra_trucada(333);
  c.registra_trucada(333);
  c.assigna_nom(222, "Jose");
  c.assigna_nom(111, "Jes");
  c.assigna_nom(121, "Jis");
  c.registra_trucada(121);

  easy_dial e(c);
  vector<string> v;
  int pos;
  cout << v.size() << endl;
  e.comencen("J", v);
  cout << v.size() << endl;
  for(int i = 0; i < v.size(); i++){
    cout << v[i] << endl;
  }

  cout << "----------------------" << endl;

  cout << e.inici() <<endl;

  cout << "----------------------" << endl;

  cout << e.seguent('X') << endl;

  cout << "---------------------" << endl;

  cout << e.num_telf() << endl;

}
