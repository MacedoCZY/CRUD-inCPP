#include <stdio.h>
#include <iostream>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include "classe.hpp"

using namespace std;
using namespace sql;

class SqlTT{
    private:
        sql::Connection *con;    
    
    public:
        void create(Carro *prt);
        void connect();
        void delet(int id);
        void read();
        void update(Carro *newPrt, int id);
        void order(int id, bool opc);
};

void SqlTT::update(Carro *newPrt, int id){
    try{
        sql::PreparedStatement *prStm;
        connect();

        con->setSchema("cars");
        prStm = con->prepareStatement("UPDATE carro SET modelo=?,marca=?,ano=? WHERE id=?");
        
        prStm->setString(1, newPrt->modelo);
        prStm->setString(2, newPrt->marca);
        prStm->setInt(3, newPrt->ano);
        prStm->setInt(4, id);
        
        /*prStm = con->prepareStatement("UPDATE carro SET ano=? WHERE modelo=? AND marca=?");

        prStm->setString(1, prt->modelo);
        prStm->setString(2, prt->marca);
        prStm->setInt(3, newPrt->ano);
        */
        prStm->execute();

        cout << "Updated!" << endl;

        delete prStm;
        delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what() << endl;
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
            cout << "Id: " << res->getInt(4) << endl;
            cout << "Modelo: " << res->getString(1) << endl;
            cout << "Marca: " << res->getString(2) << endl;
            cout << "Ano: " << res->getInt(3) << endl;
        }
        cout << "-----------------------------------------" << endl;

        delete res;
        delete stm;
        delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what() << endl;
        cout << "Read Problem!" << endl;
    }
    cout << endl;
}

void SqlTT::delet(int id){
    try{
        sql::PreparedStatement *prStm;
        connect();
        
        con->setSchema("cars");
        prStm = con->prepareStatement("DELETE FROM carro WHERE id=?");

        prStm->setInt(1, id);

        prStm->execute();
        
        order(id, false);

        cout << "Deleted!" << endl;

        delete prStm;
        delete con;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what() << endl;
        cout << "Delete Problem!" << endl;
    }
    cout << endl;
}

void SqlTT::order(int id, bool opc){
    try{
        sql::PreparedStatement *prStm;
        connect();
        
        con->setSchema("cars");
        if(opc){       
            prStm = con->prepareStatement("UPDATE carro SET id=id+1 ORDER BY id");
        }else{
            prStm = con->prepareStatement("UPDATE carro SET id=id-1 WHERE id>? ORDER BY id DESC");
            prStm->setInt(1, id);
        }
        prStm->execute();

        delete prStm;
    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what() << endl;
        cout << "Order Problem!" << endl;
    }
}

void SqlTT::create(Carro *prt){
    try{
        sql::PreparedStatement *prStm;
        sql::Statement *stm;
        sql::ResultSet *res;
        connect();
        
        con-> setSchema("cars");
        prStm = con->prepareStatement("INSERT INTO carro(modelo, marca, ano, id) VALUES(?, ?, ?, ?)");
        
        stm = con->createStatement();
        res = stm->executeQuery("SELECT id FROM carro");
        
        order(0, true);

        prStm->setString(1, prt->modelo);
        prStm->setString(2, prt->marca);
        prStm->setInt(3, prt->ano);
        prStm->setInt(4, 0);

        prStm->execute();

        cout << "Created!" << endl;
        
        delete prStm;
        delete con;
        delete stm;
        delete res;

    }catch(sql::SQLException &e){
        cout << "ERRO: " << e.what() << endl;
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
        cout << "ERRO: " << e.what() << endl; 
        cout << "Connection problem!" << endl;
    }
    cout << endl;
}
