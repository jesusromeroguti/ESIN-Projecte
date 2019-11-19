#include "phone.hpp"


/*  1.-Preguntar si el throw(error) s'ha de llançar també en comprovacions del num i del compt
    2.-Revisar el tractament dels negatius per no permesos, ara mateix es poden ficar*/
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

// Preguntar quan s'ha de llençar el error si amb el name o amb els altres tambe
phone::phone(const phone& T) throw(error){
  _num = T._num;
  _name = T._name;
  _compt = T._compt;
}

// Preguntar quan s'ha de llençar el error si amb el name o amb els altres tambe
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

// Preguntar si esta be el return aixi
phone& phone::operator++() throw(){
  _compt++;
  return *this;
}
// Preguntar si aixi es retorna l'objecte sense incrementar
phone phone::operator++(int) throw(){
  phone aux(*this);
  _compt++;
  return aux;
}

bool phone::operator>(const phone& T) const throw(){
  if(_compt > T._compt) return true;
  else if(_compt == T._compt){
    if(_name > T._name) return true;
  } else return false;
}

bool phone::operator<(const phone& T) const throw(){
  if(_compt < T._compt) return true;
  else if(_compt == T._compt){
    if(_name < T._name) return true;
  } else return false;
}

bool phone::operator<=(const phone& T) const throw(){
  if(_compt <= T._compt) return true;
  else if(_compt == T._compt){
    if(_name <= T._name) return true;
  } else return false;
}

bool phone::operator>=(const phone& T) const throw(){
  if(_compt >= T._compt) return true;
  else if(_compt == T._compt){
    if(_name >= T._name) return true;
  } else return false;
}

// Preguntar si a igual frequencia es true o si han de ser name iguals
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
