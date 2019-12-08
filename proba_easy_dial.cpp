#include <iostream>
#include "phone.hpp"
#include "call_registry.hpp"
#include "easy_dial.hpp"

using namespace std;

int main(){
  call_registry c;
  c.assigna_nom(123, "nom1");
  c.assigna_nom(321, "nom2");

  easy_dial e(c);
}
