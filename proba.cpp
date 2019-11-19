#include <iostream>
#include "phone.hpp"
#include "call_registry.hpp"

using namespace std;

int main(){
  phone p1(972261435,"Maria",15);
  phone p2(934578916,"Josep",50);
  phone p3(934907288,"Mar",5);
  phone p4(666931459,"Miquel",30);
  phone p5(678818034,"Marta",10);

  cout << "El nom del p1 es: " << p1.nom() << endl;
  cout << "El numero del p1 es: " << p1.numero()<< endl;
  cout << "La freq del p1 es: " << p1.frequencia() << endl;
  cout << "----------------------------" << endl;
  cout << "El nom del p2 es: " << p2.nom() << endl;
  cout << "El numero del p2 es: "<< p2.numero()<< endl;
  cout << "La freq del p2 es: " << p2.frequencia() << endl;
  cout << "----------------------------" << endl;
  cout << "El nom del p3 es: " << p3.nom() << endl;
  cout << "El numero del p3 es: "<< p3.numero()<< endl;
  cout << "La freq del p3 es: " << p3.frequencia() << endl;
  cout << "----------------------------" << endl;

  phone p8(p4);
  phone p9(p5);
  cout << "El nom del p8 es: " << p8.nom() << endl;
  cout << "El numero del p8 es: " << p8.numero()<< endl;
  cout << "La freq del p8 es: " << p8.frequencia() << endl;
  cout << "El nom del p9 es: " << p9.nom() << endl;
  cout << "El numero del p9 es: " << p9.numero()<< endl;
  cout << "La freq del p9 es: " << p9.frequencia() << endl;
  cout << "----------------------------" << endl;

  phone p10 = p2;
  cout << "El nom del p10 es: " << p10.nom() << endl;
  cout << "El numero del p10 es: " << p10.numero()<< endl;
  cout << "La freq del p10 es: " << p10.frequencia() << endl;
  cout << "----------------------------" << endl;

  bool b = p1 > p3;
  if(b) cout << "p1 es mes gran que p3" << endl;

  phone p6(972261435,"Maria",15);
  bool b1 = p6 == p1;
  if(b1) cout <<"p1 i p6 son iguals" << endl;
  bool b4 = p1 != p2;
  if(b4) cout << "p1 i p2 son diferents" << endl;
  bool b5 = p6 != p1;
  if(b5) cout << "p6 i p1 son diferents" << endl;
  else cout << "p6 i p1 son iguals" << endl;

  phone p7(972261435,"Alba",15);
  bool b2 = p7 < p6;
  bool b3 = p6 > p7;
  if(b2) cout << "p7 es mes petit que p6" << endl;
  if(b3) cout << "p6 es mes gran que p7" << endl;

  cout <<"Incrementem el comptador de p2" << endl;
  cout <<"Abans del increment freq p2 = " << p2.frequencia() << endl;
  ++p2;
  cout <<"Despres del increment freq p2 = " << p2.frequencia() << endl;
  p2++;
  cout << p2.frequencia() << endl;



}
