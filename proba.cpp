#include <iostream>
#include "phone.hpp"

using namespace std;

int main(){
  phone p(123,"Jesus",1);
  cout << p.nom() << endl;
  cout << p.numero()<< endl;
  cout << p.frequencia() << endl;
  return 0;
}
