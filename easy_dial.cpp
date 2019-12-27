#include "easy_dial.hpp"

// Afegir els noms per ordre de frequencia
easy_dial::easy_dial(const call_registry& R) throw(error){
  // El prefix al construir el easy_dial es indefinit
  //_prefix = "";
  // vector<phone> v;
  R.dump(_phones);
  for(int i = 0; i < _phones.size(); i++){
    insereix(_phones[i].nom(), i);
    // insereix(_phones[i].nom());
  }
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){
  /*_prefix = D._prefix;
  if (D._arrel != NULL) {
    esborra(D._arrel);
  }
  for(int i = 0; i < D.v.size(); ++i) {
    insereix(D.v[i].nom);
  }*/
}

easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){}

easy_dial::~easy_dial() throw(){
  _prefix = "";
  esborra(_arrel);
}

/* Inicialitza el prefix en curs a buit. Retorna el nom de F(S, '');
si F (S, '') no existeix llavors retorna l'string buit. */
string easy_dial::inici() throw(){
  string res;
  _prefix = "";
  if(_prefix == ""){
    res = _phones[0].nom();
  }
  return res;
}

/* Retorna el nom de F(S, p') on p' és el prefix resultant d'afegir
el caràcter c al final del prefix en curs p i
fa que el nou prefix en curs sigui p'.
Si F(S, p) existeix però F(S, p') no existeix llavors retorna
l'string buit.
Si no existeix F(S, p) (i per tant tampoc pot existir F(S, p'))
llavors es produeix un error i el prefix en curs queda indefinit.
Naturalment, es produeix un error si el prefix en curs inicial p
fos indefinit. */
string easy_dial::seguent(char c) throw(error){
  // if ( c != "\0" ) {
  // 	_prefix = _prefix + c;
  // }
  // else throw(phone::ENDPREF);
}

/* Elimina l'últim caràcter del prefix en curs p = p' · a
(a és el caràcter eliminat). Retorna el nom F(S, p')
i fa que el nou prefix en curs sigui p'.
Es produeix un error si p fos buida i si es fa que el prefix en curs
quedi indefinit. Òbviament, també es produeix un error
si p fos indefinit. */
string easy_dial::anterior() throw(error){}

/* Retorna el número de telèfon de F(S, p), sent p
el prefix en curs. Es produeix un error si p és indefinit o si
no existeix F(S, p). */
nat easy_dial::num_telf() const throw(error){}

/* Retorna en el vector result tots els noms dels contactes de
telèfon que comencen amb el prefix pref, en ordre lexicogràfic creixent. */
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){
  // for(int i = 0; i< _phones.size(); i++){
  //   cout << _phones[i].nom() << endl;
  // }
  // cout << " ---------------------- " << endl;
  // node_tst *res = consulta_r(_arrel, 0, pref, result);

  // Falta ordenar els noms en ordre lexicogràfic creixent
  node_tst *l = consulta_r(_arrel, 0, pref, result);

}

/* Retorna el número mitjà de pulsacions necessàries para obtenir un
telèfon. Formalment, si X és el conjunt de noms emmagatzemats en
el easy_dial i t(s) és el número de pulsacions mínimes
necessàries (= número de crides a l'operació seguent) per
obtenir el telèfon el nom del qual és s. La funció retorna la suma
    Pr(s) · t(s)
per tots els telèfons s del conjunt X, sent Pr(s) la probabilitat de
telefonar a s. La probabilitat s'obté dividint la freqüència de s per
la suma de totes les freqüències. */
double easy_dial::longitud_mitjana() const throw(){
  // A l'hora de construir podem afegir el numero de pulsacions
  // necessaries per que aparegui el nom del telefon
}

typename easy_dial::node_tst* easy_dial::insereix_r(node_tst *n, nat i, string s, int x){
  if(n == NULL){
    n = new node_tst;
    n->_esq = n->_dret = n->_cen = NULL;
    n->_valor = s[i];
    n->_x = -1;
    // cout << n->_x << endl;
    try{
      if(i < s.length()-1){
        n->_cen = insereix_r(n->_cen, i+1, s, x);
      } else { // i == s.length-1 --> s[i] == ENDPREF
        n->_valor = s[i];   // Realmente no hace falta, ya lo haces arriba.
        n->_x = x;      // Si es el node que conte \0 llavors posem la posicio del vector
        // cout << n->_x << endl;
      }
    } catch (...){
      delete n;
      throw;
    }
  } else {
    if(n->_valor > s[i]){
      n->_esq = insereix_r(n->_esq, i, s, x);
    } else if(n->_valor < s[i]){
      n->_dret = insereix_r(n->_dret, i, s, x);
    } else {
      n->_cen = insereix_r(n->_cen, i+1, s, x);
    }
  }
  return n;
}

void easy_dial::insereix(const string &n, int x) throw(error){
  string s = n + phone::ENDPREF;
  // cout << s << endl;
  _arrel = insereix_r(_arrel,0, s, x);
}

void easy_dial::mostrar_trie(node_tst *n, vector<string> &p) const{
  if(n != NULL){
    if(n->_valor == phone::ENDPREF){
      // string res = _phones[n->_x].nom();
      p.push_back(_phones[n->_x].nom());
    }
    mostrar_trie(n->_esq, p);
    mostrar_trie(n->_dret, p);
    mostrar_trie(n->_cen, p);
  }
}

typename easy_dial::node_tst* easy_dial::consulta_r(node_tst *n, nat i, const string& prefix, vector<string>& p) const{
  // vector<phone> result;
  node_tst *res = NULL;
  if(n != NULL){
    if(i <= prefix.length()-1){
      if(n->_valor > prefix[i]){
        res = consulta_r(n->_esq, i, prefix, p);
      }
      else if(n->_valor < prefix[i]){
        res = consulta_r(n->_dret, i, prefix, p);
      }
      else if(n->_valor == prefix[i]){
        res = consulta_r(n->_cen, i+1, prefix, p);
      }
    } else { // i == prefix.length() - 1
      res = n;
      mostrar_trie(res, p);
    }
  }
  return res;
}


void easy_dial::esborra(node_tst *n) {
  if(n->_esq != NULL) {
    esborra(n->_esq);
  }
  else if (n->_dret != NULL) {
    esborra(n->_dret);
  }
  else if (n->_cen != NULL) {
    esborra(n->_cen);
  }
  else {
    delete n;
  }
}
