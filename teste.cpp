//g++ teste.cpp -o teste.x -masm=intel -lmysqlcppconn
#include <stdio.h>
#include <iostream>
#include "bdteste.hpp"

int main() {
    Carro *prt = (Carro*) malloc(sizeof(Carro));
    Carro *newPrt = (Carro*) malloc(sizeof(Carro));

    while(true){
        cout << "1-CREATE\n2-DELETE\n3-READ\n4-UPDATE\n0-EXIT" << endl;
        int chc;
        cin >> chc;
        if(chc == 0){
            break;
        }
        
        if(chc == 1){
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
            
            car.consulta();
            car.teste();

        }
        if(chc == 4){
            int id;
            cout << "Id: " << endl;
            cin >> id;
            cout << "newModelo:" << endl;
            string newModelo;
            cin >> newModelo;
            cout << "newMarca: " << endl;
            string newMarca;
            cin >> newMarca;
            int newAno;
            cout << "newAno: " << endl;
            cin >> newAno;
        
            Carro newCar(newModelo, newMarca, newAno);

            *newPrt = newCar;
            
            SqlTT bd;
            bd.update(newPrt, id);
        }
        if(chc != 1 && chc!= 2 && chc != 3 && chc != 4){
            cout << "Bed Opt!" << endl;
            break;
        }
        
        if(chc == 1){
            SqlTT bd;
            bd.create(prt);  
        }
        
        if(chc == 2){
            int id;
            cout << "Id: " << endl;
            cin >> id;
            SqlTT bd;
            bd.delet(id);
        }

        if(chc == 3){
            SqlTT bd;
            bd.read();
        }
    }
    free(prt);
    free(newPrt);
    return 0;
}
