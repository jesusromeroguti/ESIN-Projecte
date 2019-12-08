#include "easy_dial.hpp"

easy_dial::easy_dial(const call_registry& R) throw(error){
  // El prefix al construir el easy_dial es indefinit
  _prefix = "";
  vector<phone> v;
  R.dump(v);
  for(int i = 0; i < v.size(); i++){
    cout << v[i].nom() << endl;
  }
  for(int i = 0; i < v.size(); i++){
    insereix(v[i].nom());
  }
}

/* Tres grans. Constructor per còpia, operador d'assignació i destructor. */
easy_dial::easy_dial(const easy_dial& D) throw(error){}
easy_dial& easy_dial::operator=(const easy_dial& D) throw(error){}
easy_dial::~easy_dial() throw(){}

/* Inicialitza el prefix en curs a buit. Retorna el nom de F(S, '');
si F (S, '') no existeix llavors retorna l'string buit. */
string easy_dial::inici() throw(){}

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
void easy_dial::comencen(const string& pref, vector<string>& result) const throw(error){}

/* Retorna el número mitjà de pulsacions necessàries para obtenir un
telèfon. Formalment, si X és el conjunt de noms emmagatzemats en
el easy_dial i t(s) és el número de pulsacions mínimes
necessàries (= número de crides a l'operació seguent) per
obtenir el telèfon el nom del qual és s. La funció retorna la suma
    Pr(s) · t(s)
per tots els telèfons s del conjunt X, sent Pr(s) la probabilitat de
telefonar a s. La probabilitat s'obté dividint la freqüència de s per
la suma de totes les freqüències. */
double easy_dial::longitud_mitjana() const throw(){}

typename easy_dial::node_tst* easy_dial::insereix_r(node_tst *n, nat i, string s){
  if(n == NULL){
    cout << "hola2"<< endl;
    n = new node_tst;
    n->_esq = n->_dret = n->_cen = NULL;
    n->_valor = s[i];
    try{
      if(i < s.length()-1){
        cout << "hola3" << endl;
        n->_cen = insereix_r(n->_cen, i+1, s);
      } else { // i == s.length-1 --> s[i] == ENDPREF
        n->_valor = s[i];
      }
    } catch (...){
      delete n;
      throw;
    }
  } else {
    cout << "hola4" << endl;
    if(n->_valor > s[i]){
      n->_esq = insereix_r(n->_esq, i, s);
    } else if(n->_valor < s[i]){
      n->_dret = insereix_r(n->_dret, i, s);
    } else {
      n->_cen = insereix_r(n->_cen, i+1, s);
    }
  }
  return n;
}

void easy_dial::insereix(const string &n) throw(error){
  string s = n + phone::ENDPREF;
  cout << "hola" << endl;
  _arrel = insereix_r(_arrel,0, s);
}
