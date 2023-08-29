#include <iostream>

using namespace std;

class Carro{
    public:
        string modelo;
        string marca;
        int ano;

    public:
        Carro(string mod, string mar, int a){
            modelo = mod;
            marca = mar;
            ano = a;
        }
        void consulta();
        void teste();
};

void Carro::consulta(){
    cout << "Modelo: " << modelo << endl;
    cout << "Marca: " << marca << endl;
    cout << "Ano: " << ano << endl;
}

void Carro::teste(){
    int result = 0, anoAt;
 
    cout << "Ano atual: " << endl;
    cin >> anoAt;
 
    asm("mov eax, %[anoAt];"
        "mov ebx, %[ano];"
        "sub eax, ebx;"
        "mov %[res], eax;"
        :
        :[res] "m" (result), [anoAt] "m" (anoAt), [ano] "m"(ano)
        :"cc", "memory", "rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
    );
  
    cout << "Idade: " << result << endl;
}

