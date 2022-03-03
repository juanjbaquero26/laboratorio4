#include "red.h"

using namespace std;

template <typename T>
T IngDat(T dat, string msg){//verificar tipo de dato y retorna dato
    bool valido=false;
        string cad;
        do{
        cout << msg;
        getline(cin, cad);
        stringstream  mystream(cad);//comprobar sin son mismo dato
        if(mystream >> dat){
            valido = true;
        }
        if(!valido) cout << "error" << endl;
    }while (!valido);
    return dat;
}
template <typename T>
T IngDat(T tipe, T min, T max, string msg){//rango de minimo y maximo para datos
    string cad;
    bool valido = false;
    do {
        cout << msg;
        getline(cin, cad);
        stringstream  mystream(cad);
        if(mystream >> tipe) {
            if(tipe >= min && tipe <= max) valido = true;
        }
        if(!valido) cout << "error" << endl;
    } while(!valido);
    return tipe;
};
//Valida la entrada de un dato: Elim == true el Caracter debe encontrase en Pro
char IngDat(char tipe, set<char> Pro, string msg, bool elim){
    bool valido=false;
    string cad;
    do{
        cout << msg;
        getline(cin, cad);
        stringstream  mystream(cad);
        if(cad.size()==1 && mystream >> tipe) {
            if(Pro.count(tipe)==0 && !elim) valido = true;//cuenta repiticiones
            else if(Pro.count(tipe)>0 && elim) valido = true;//para evitar nodos con el mismo nombre
        }
        if(!valido) cout << "error" << endl;

    }while(!valido);
    return tipe;
}
//Modifica un enlacee y retorna la nueva matriz de adyacencia
vector<vector<int>> ModEnc(int Op, char c1, char c2, int costo, vector<char> NO, vector<vector<int>> MatAdy){
    //la matriz de adyancencia en este caso es un vector dentro de un vector
    int pos1=0, pos2=0;
    for(unsigned long long i=0;i<NO.size();i++){//encuentra la posicion de un nodo en la matriz de adya
        if(NO[i]==c1) pos1 = i;
        if(NO[i]==c2) pos2 = i;
    }
    switch (Op) {
    case(1):{
        if(MatAdy[pos1][pos2]==-1 && c1!=c2 && costo>0){//agrega el enlace
            MatAdy[pos1][pos2]=costo;
            MatAdy[pos2][pos1]=costo;
            cout << "Enlace agregado correctamente\n";
        }
        else{cout << "Nodos o costo Invalidos\n";}
    }break;
    case(2):{
        if(MatAdy[pos1][pos2]!=-1 && c1!=c2){//elimina el enlace, primero verifica que exista
            MatAdy[pos1][pos2]=-1;
            MatAdy[pos2][pos1]=-1;
            cout << "Enlace eliminado correctamente\n";
        }
        else{cout << "Nodos Invalidos\n";}
    }break;
    case(3):{
        if(MatAdy[pos1][pos2]!=-1 && c1!=c2 && costo>0){//verifica que exista el enlace y agrega
            MatAdy[pos1][pos2]=costo;
            MatAdy[pos2][pos1]=costo;
            cout << "Enlace modificado correctamente\n";
        }
        else{cout << "Nodos o costo Invalidos\n";}
    }break;
    }
    return MatAdy;
}

red::red(){
    int opcion=0;
    char n;
    string text;
    cout << "Creando red\n"
    "1- Agregar nodo\n"
    "2- terminar simulacion\n";
    opcion =IngDat(opcion,1,2,"Ingrese su opcion: ");
    switch (opcion){
    case(1):{
        cout << "ingrese un nombre para el nodo: ";
        cin >> n;
        fflush(stdin);//limpiar buffer, limpia entrada de datos
        AddEnrut(n);
    }break;

    }
    if(opcion!=2){menu();}
}

red::red(vector <char> n, vector<vector<int>> matAdya)
{
    for(unsigned long long int i=0;i<n.size();i++){
        AddEnrut(i,n,matAdya);
    }
    matAd=matAdya;
    nodos = n;
    menu();
}

/*red::red(string name){
    CargarRed(name, false);
    ShowshortWayAB('E','B');
}
*/


void red::ActRed(){//actualizar red
    map <char,int> cx;//conexiones
    for(unsigned long long i=0;i<nodos.size();i++){
        for(unsigned long long f=0;f<nodos.size();f++){
            cx.insert(pair<char,int> (nodos[f],matAd[i][f]));//crea las conexiones correspondientes del nodo
        }
        enrutadores[nodos[i]].Actenrut(cx,nodos,nodos[i]);//actualiza el enrrutador, conexiones, nodos, nombre del nodo
        cx.clear();
    }
}

void red::AddEnrut (unsigned int i, vector<char> n, vector<vector<int>> matAdya){
    enrut enrutador;
    map <char, int>  conx;
    char peso;
    for(unsigned long long int f=0;f<n.size();f++){
        peso = matAdya[i][f];
        conx.insert(pair<char,int>(n[f],peso));
    }
    enrutador.Actenrut(conx,n,n[i]);
    conx.clear();
    enrutadores.insert(pair<char,enrut>(n[i],enrutador));
}
void red::AddEnrut(char name){
    int tam =matAd.size()+1;
    nodos.push_back(name);
    matAd.resize(tam);//volver a darle un tamaño al contenedor
    for(int i = 0;i<tam;i++){
        matAd[i].resize(tam);
    }
    for(int i = 0;i<tam;i++){
        matAd[tam-1][i]=-1;
        matAd[i][tam-1]=-1;
    }
    matAd[tam-1][tam-1]=0;
    AddEnrut(tam-1,nodos,matAd);
}

void red::DelEnrut(char name, int PosInV){
    enrutadores.erase(name);
    for(unsigned long long i=0;i<nodos.size();i++){
        matAd[i].erase(matAd[i].begin()+PosInV);
    }
    matAd.erase(matAd.begin()+PosInV);
    nodos.erase(nodos.begin()+PosInV);
}

enrut red::getEnrut(char name){
    if(enrutadores.count(name)>0){
        return enrutadores[name];
    }
    else{
        cout << "NO hay enrutadores con ese nombre" << endl;
        enrut aux_enrut;
        return aux_enrut;
    }
}

void red::menu(){
    set <char> n;
    int op=0,op2=0;
    char c1=0,c2=0;
    while(op!=5){
        for(unsigned long long i=0; i<nodos.size();i++){n.insert(nodos[i]);}
        cout << "\n\n/----/ Menu /----/\n";
        cout << "1- Agregar/Eliminar nodo" << endl;
        cout << "2- Modificar enlace" << endl;
        cout << "3- Visualizar la tabla de la red" << endl;
        cout << "4- algoritmo optimo" << endl;
        cout << "5-Terminar simulacion\n\n";
        op = IngDat(op,1,5, "Ingrese su opcion: ");
        switch (op) {
        case(1):{
            cout << "Nodos existentes:\n-";
            for(unsigned long long i=0;i<nodos.size();i++){cout << nodos[i] <<"-";}
            cout<<"\n1- Agregar nodo\n" << "2- Eliminar nodo\n";
            op2 = IngDat(op2,1,2, "Ingrese su opcion ");
            AddDelEnrut(op2,n);
        }break;

        case(2):{
            cout << "Nodos existentes:\n-";
            for(unsigned long long i=0;i<nodos.size();i++){cout << nodos[i] <<"-";}
            modEnlace(n);
        }break;

        case (3):{
            ShowMatAyd();
        }break;
        case (4):{
            c1 = IngDat(c1,n,"Ingrese el nodo inicial: ",true);
            c2 = IngDat(c2,n,"Ingrese el nodo de destino: ", true);
            ShowshortWayAB(c1,c2);
        }break;

        }
        n.clear();
        ActRed();
    }
}

void red::AddDelEnrut(int x, set<char> n){
    char nombre = ' ';
    int pos;
    set <char>::iterator Is;

    if(x==1){
        nombre = IngDat(nombre,n,"Ingrese el nombre del nodo a anadir: ", false);
        AddEnrut(nombre);
        cout << "Nodo anadido correctamente.\n";
    }
    else{
        nombre = IngDat(nombre,n,"Ingrese el nombre del nodo a eliminar: ", true);
        Is = n.find(nombre);
        for(unsigned long long i=0;i<n.size();i++){
            if(nodos[i]==*Is)  pos = i;
        }
        DelEnrut(nombre,pos);
        cout << "Nodo eliminado correctamente.\n";
    }
}

void red::modEnlace(set<char> n){
    //menu de mofiicar enlace
    map <char,int> cx;
    char n1=0,n2=0;
    int x=0, peso =0;

    n1 = IngDat(n1,n,"Ingrese el n1 del nodo a Modificar: ", true);
    cx = enrutadores[n1].GetConex();
    cout << "\nNodo: " << n1 << "\nConexiones:\n";
    for(unsigned long long i=0;i<n.size();i++){cout<< " "<<nodos[i];}
    cout << endl;
    for(unsigned long long i=0;i<n.size();i++){cout<< " "<<cx[nodos[i]];}
    cout << endl;
    cout<<"1- Agregar enlace.\n"
          "2- Eliminar enlace.\n"
          "3- Cambiar el costo del enlace.\n";

    x = IngDat(x,1,3,"Ingrese su opcion: ");
    n2 = IngDat(n2,n,"Ingrese el nobre del nodo que corresponda con el enlace a cambiar: ", true);
    switch (x) {
    case(1):{
        peso= IngDat(peso,"Ingrese costo del enlace a anadir: ");
        matAd = ModEnc(x,n1,n2,peso,nodos,matAd);
    }break;
    case(2):{
        matAd = ModEnc(x,n1,n2,peso,nodos,matAd);
    }break;
    case(3):{
        peso= IngDat(peso,"Ingrese el nuevo costo del enlace");
        matAd = ModEnc(x,n1,n2,peso,nodos,matAd);
    }break;
    }

}

void red::ShowMatAyd(){//muestra matriz de adyacencia
    unsigned long int S = nodos.size();
    cout << setw(5) << ' ';
    for(unsigned long int n=0;n<S;n++){
        //cout << " "<< nodos[n] ;
        cout << setw(5) << nodos[n] << ' ';
    }
    cout << endl;
    for(unsigned long int n=0;n<S;n++){
       // cout << nodos[n] ;
        cout << setw(5) << nodos[n];
        for(unsigned long int no=0;no<S;no++){
            cout <<setw(5)<<matAd[n][no]<<" ";
        }
        cout << endl;
    }
}

//Algoritmo optimo
void red::ShowshortWayAB(char A,char B){
    set <char> Ncheck;//Nodos revisados
    map <char,int> grafo;//mapa para guardar los valores y luego sumarlos, incian todos en cero
    map <char,int> cx;//mapa para las conexiones
    map <char, string> caminos;//toma los caminos ya recorridos
    set<char> c;//complemento de la cola, para ver si hay datos repetidos
    vector <char> cola;//nodos a revisar
    char nAct=A, nProx;
    for(unsigned long long i=0;i<nodos.size();i++){
        grafo.insert(pair<char,int>(nodos[i],0));
        caminos.insert(pair<char,string>(nodos[i],""));
        caminos[nodos[i]].push_back(nAct);
    }
    cout << "Procesando..\n";
    c.insert(nAct);
    cola.push_back(nAct);
    for(unsigned long long i=0;i<nodos.size();i++){
        nAct = cola[i];
        if(Ncheck.size()==nodos.size()) break;//condicional que verifica si ya se revisaron todos los nodos
        cx = enrutadores[nAct].GetConex();
        for(unsigned long long i=0;i<cx.size();i++){
            nProx=nodos[i];
            if(cx[nProx]>0 && Ncheck.count(nProx)==0) {//revisa si nProx esta en los nodos revisados
                if(grafo[nAct]+cx[nProx]<grafo[nProx]||grafo[nProx]==0){//compara cual peso es menor
                    grafo[nProx]=grafo[nAct]+cx[nProx];//va sumando el nodo actual con la conexion del nodo proximo
                    caminos[nProx].clear();
                    caminos[nProx].append(caminos[nAct]);
                    caminos[nProx].push_back(nProx);
                }
                //si el nProx no esta en c lo anadimos a la cola
                if(c.count(nProx)==0){c.insert(nProx);cola.push_back(nProx);}
            }
        }
        Ncheck.insert(nAct);
        cx.clear();
    }
    cout << "El costo del camino mas corto es: " << grafo[B] << endl;
    cout << "Y su camino es: "<< caminos[B] << endl;
}

/*void red::AleRed(){
    enrutadores.clear();
    nodos.clear();
    matAd.clear();
    enrut aux;

    int Nnodos=0, costo=0;
    double Penl=0;//propabilidad de que prevalezca el enlace
    Nnodos=IngDat(Nnodos,2,54,"Ingrese el numero de Nodos a generar: ");
    Penl = IngDat(Penl,0.0,1.0,"Ingrese la P de que prevalezca el enlace: ");
    matAd.resize(Nnodos);//moficamos el tamanio de la matriz
    for(int i = 0;i<Nnodos;i++){
        if(i<26){//primeras matusculas desde A
            nodos.push_back(i+65);
            //matAd[i-65].resize(Nnodos);//para la posicion del nodo
            enrutadores.insert(pair<char,enrut>(i+65,aux));
        }
        else if(i>=26 && i<52){//desde a hasta z
            nodos.push_back(i+71);
            enrutadores.insert(pair<char,enrut>(i+71,aux));
        }
        else if(i>=52){//las dos Ññ
           nodos.push_back(i+112);
           enrutadores.insert(pair<char,enrut>(i+112,aux));
        }
        matAd[i].resize(Nnodos);
    }

    srand(time(NULL));//semilla aleatoria
    for(unsigned long long i=0;i<nodos.size();i++){
        for(unsigned long long f=0;f<nodos.size();f++){
            if(i>f){//verifica que no sean nodos con el mismo enlace
                costo = 1 + rand() % (101 - 1);//dado del uno al 100, se guarda en costo
                if((rand() % (20001 - 1))<=(Penl*20000)){//rango aleatorio
                    matAd[i][f] = costo;
                    matAd[f][i] = costo;
                }
                else{
                    matAd[i][f] = -1;//enlaces sin conexion
                    matAd[f][i] = -1;
                }
            }
            else if(i==f){
                matAd[i][f] = 0;
            }
        }
    }

    ActRed();//actualizar red
    cout << "Red creada exitosamente.\n";
}
*/
