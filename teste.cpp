//g++ teste.cpp -o teste.x -masm=intel
#include <stdio.h>
#include <iostream>
#include "classe.hpp"

using namespace std;

void teste();

int main() {
    
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
    
    free(prt);

    car.consulta();

    car.teste();

    return 0 ;
}
