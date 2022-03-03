#include "enrut.h"
enrut::enrut(){//enrutador aux de matriz aleatoria

}
enrut::enrut(char n,map <char,int> conx, vector <char> nodos)
{
   Actenrut(conx,nodos,n);
}
enrut::enrut(char n, vector <char> nodos, vector<int> conx){//agrega nuevo enrrutador
    unsigned long int S = nodos.size();
    conexiones.insert(pair<char,int>(n,0));
    for(unsigned long int i=0;i<S;i++){
        conexiones.insert(pair<char,int>(nodos[i], conx[i]));
    }
}
void enrut::Actenrut(map <char,int> conx, vector <char> nodos,char n){//actualizar enrrutador
    conexiones.clear();
    unsigned long int S = nodos.size();
    conexiones.insert(pair<char,int>(n, 0));
    for(unsigned long int i=0;i<S;i++){
        if(conx.count(nodos[i])>0){
            conexiones.insert(pair<char,int>(nodos[i],conx[nodos[i]]));
        }
        else{
            conexiones.insert(pair<char,int>(nodos[i], -1));
        }
    }
}
map <char,int> enrut::GetConex(){//retorna las conexiones
    return conexiones;
}
