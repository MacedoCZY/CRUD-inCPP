//g++ teste.cpp -o teste.x -masm=intel -lmysqlcppconn
#include <stdio.h>
#include <iostream>
#include "classe.hpp"
#include "bdteste.hpp"

void teste();

int main() {
 
    cout << endl;

    cout << "Entro aqui" << endl;
    
    cout << "Modelo:" << endl;
    string modelo;
    cin >> modelo;
    cout << "Marca: " << endl;
    string marca;
    cin >> marca;
    int ano;
    cout << "Ano: " << endl;
    cin >> ano;

    Carro car(modelo, marca, ano);
    
    Carro *prt = (Carro*) malloc(sizeof(Carro));
    
    cout << "Size class: "<< sizeof(prt) << endl;

    *prt = car;
    cout << prt->modelo << endl;

    SqlTT bd;

    bd.create(prt->modelo, prt->marca, prt->ano);

    free(prt);

    car.consulta();

    car.teste();   

    return 0 ;
}
