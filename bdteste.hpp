#include <stdio.h>
#include <iostream>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>

using namespace std;
using namespace sql;

class SqlTT{
    private:
        sql::Connection *con;    
    
    public:
        void create(string modelo, string marca, int ano);
        void connect();
        void delet(string modelo, string marca, int ano);
        void read();
        void update(string modelo, string marca, int ano, string newModelo, string newMarca, int newAno);
};

void SqlTT::update(string modelo, string marca, int ano, string newModelo, string newMarca, int newAno){
    try{
        sql::PreparedStatement *prStm;
        connect();

        con->setSchema("cars");
        //prStm = con->prepareStatement("UPDATE carro SET modelo=?,marca=? WHERE ano=?");
        
        //prStm->setString(1, newModelo);
        //prStm->setString(2, newMarca);
        //prStm->setInt(3, ano);
        
        prStm = con->prepareStatement("UPDATE carro SET ano=? WHERE modelo=? AND marca=?");

        prStm->setString(1, modelo);
        prStm->setString(2, marca);
        prStm->setInt(3, newAno);

        prStm->execute();

        cout << "Updated!" << endl;

        delete prStm;
        delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what();
        cout << "Update Problem!" <<  endl;
    }
    cout << endl;
}

void SqlTT::read(){
    try{
        sql::Statement *stm;
        sql::ResultSet *res;
        connect();

        con->setSchema("cars");
        stm = con->createStatement();
        res = stm->executeQuery("SELECT * FROM carro");

        cout << "Table Data: " << endl;

        while(res->next()){
            cout << "-----------------------------------------" << endl;
            cout << "Modelo: " << res->getString(1) << endl;
            cout << "Marca: " << res->getString(2) << endl;
            cout << "Ano: " << res->getInt(3) << endl;
        }
        cout << "-----------------------------------------" << endl;

        delete res;
        delete stm;
        delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what();
        cout << "Read Problem!" << endl;
    }
    cout << endl;
}

void SqlTT::delet(string modelo, string marca, int ano){
    try{
        sql::PreparedStatement *prStm;
        connect();
        
        con->setSchema("cars");
        prStm = con->prepareStatement("DELETE FROM carro WHERE modelo=? AND marca=? AND ano=?");

    prStm->setString(1, modelo);
    prStm->setString(2, marca);
    prStm->setInt(3, ano);
    
    prStm->execute();

    cout << "Deleted!" << endl;

    delete prStm;
    delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what();
        cout << "Delete Problem!" << endl;
    }
    cout << endl;
}

void SqlTT::create(string modelo, string marca, int ano){
    try{
        sql::PreparedStatement *prStm;
        connect();
        
        con-> setSchema("cars");
        prStm = con->prepareStatement("INSERT INTO carro(modelo, marca, ano) VALUES(?, ?, ?)");
        
        prStm->setString(1, modelo);
        prStm->setString(2, marca);
        prStm->setInt(3, ano);

        prStm->execute();

        cout << "Created!" << endl;
        
        delete prStm;
        delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what();
        cout << "Create problem!" << endl;
    }
}

void SqlTT::connect(){
    cout << "Connecting ... " << endl;

    try{
        sql::Driver *drv;

        drv = get_driver_instance();
        con = drv->connect("localhost", "macedo", "x000");

        cout << "Conected!" << endl;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what(); 
        cout << "Connection problem!" << endl;
    }
    cout << endl;
}
