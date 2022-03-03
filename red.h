#ifndef RED_H
#define RED_H

#include <enrut.h>
#include <map>//contenedor
#include <vector>//contenedor
#include <fstream>//para leer
#include <list>//metodo para encontrar valores
#include <set>//conjunto no repetidos
#include <sstream>//limpiar buffer stringstream
#include <random>//para datos al azar
#include <time.h>//numeros aleatorios
#include <iomanip>//para espacios en la mtriz de adyacencia

using namespace std;

class red
{
private:
    vector <char> nodos;
    map <char,enrut> enrutadores;
    vector<vector<int>> matAd;
public:
    red();
    //red(string Text_name);
    red(vector <char> n, vector<vector<int>> matAdya);
    void CargarRed(string Text_name, bool clear);
    void ActRed();
    void AddEnrut(unsigned int i,vector <char> n , vector<vector<int>> matAdya);
    void AddEnrut(char name);
    void DelEnrut(char name, int PosInV);
    enrut getEnrut(char name);

    void menu();
    void AddDelEnrut(int x, set<char> n);
    void modEnlace(set<char> n);
    void ShowMatAyd();
    void ShowshortWayAB(char A,char B);
    //void AleRed();
};

#endif // RED_H;
