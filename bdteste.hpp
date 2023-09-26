#include <stdio.h>
#include <iostream>
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

class SqlTT{
    private:
        sql::Connection *con;    
    
    public:
        void create(string modelo, string marca, int ano);
        void connect();
};

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
