#ifndef ENRUT_H
#define ENRUT_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class enrut
{
private:
    map <char,int> conexiones;
    map <char, int>::iterator I;
public:
    enrut(char n,map <char,int> conx, vector <char> nodos);
    enrut(char n, vector <char> nodos, vector<int> conx);
    enrut();
    void Actenrut(map <char,int> conx, vector <char> nodos,char name);
    map <char,int> GetConex();

};

#endif // ENRUT_H
