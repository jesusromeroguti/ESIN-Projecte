#include "phone.hpp"

phone::phone(nat num, const string& name, nat compt) throw(error){
  _num = num;
  _name = name;
  _compt = compt;
}

phone::~phone() throw() {}

nat phone::numero() const throw(){
  return _num;
}


string phone::nom() const throw(){
  return _name;
}

nat phone::frequencia() const throw() {
  return _compt;
}
