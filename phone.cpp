#include "phone.hpp"

phone::phone(nat num, const string& name, nat compt) throw(error){
  _num = num;
  for(int i = 0; i < name.size(); i++){
    if(name[i] == DELETECHAR || name[i] == ENDCHAR || name[i] == ENDPREF){
      throw error(ErrNomIncorrecte);
    }
  }
  _name = name;
  _compt = compt;
}

phone::phone(const phone& T) throw(error){
  _num = T._num;
  _name = T._name;
  _compt = T._compt;
}

phone& phone::operator=(const phone& T) throw(error){
  if(this != &T){
    _num = T._num;
    _name = T._name;
    _compt = T._compt;
  }
  return *this;
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

phone& phone::operator++() throw(){
  _compt++;
  return *this;
}

phone phone::operator++(int) throw(){
  phone aux(*this);
  _compt++;
  return aux;
}

bool phone::operator>(const phone& T) const throw(){
  bool t = true;
  if(_compt > T._compt) return true;
  else if(_compt == T._compt){
    for(int i = 0; i < _name.size(); i++){
      if(_name[i] < T._name[i]) return false;
    }
  }
  return t;

}

bool phone::operator==(const phone& T) const throw(){
  bool t = true;
  if(_compt != T._compt) return false;
  else {
    if(_name.size() != T._name.size()) return false;
    for(int i = 0; i < _name.size(); i++){
      if(_name[i] != T._name[i]) return false;
    }
  }
  return t;
}

bool phone::operator!=(const phone& T) const throw(){
  return !(*this == T);
}
