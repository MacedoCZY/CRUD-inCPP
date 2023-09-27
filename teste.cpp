//g++ teste.cpp -o teste.x -masm=intel -lmysqlcppconn
#include <stdio.h>
#include <iostream>
#include "classe.hpp"
#include "bdteste.hpp"

int main() {
    while(true){
        cout << "1-CREATE\n2-DELETE\n3-READ\n0-EXIT" << endl;
        int chc;
        cin >> chc;
        if(chc == 0){
            break;
        }
        Carro *prt = (Carro*) malloc(sizeof(Carro));

        if(chc == 1 || chc == 2){
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
       
            cout << "Size class: "<< sizeof(prt) << endl;

            *prt = car;
            cout << prt->modelo << endl;
            
            car.consulta();
            car.teste();

        }
        if(chc != 1 && chc!= 2 && chc != 3){
            cout << "Bed Opt!" << endl;
            break;
        }
        
        if(chc == 1){
            SqlTT bd;
            bd.create(prt->modelo, prt->marca, prt->ano);  
        }
        
        if(chc == 2){
            SqlTT bd;
            bd.delet(prt->modelo, prt->marca, prt->ano);
        }

        if(chc == 3){
            SqlTT bd;
            bd.read();
        }

        free(prt);
    }
    return 0;
}
