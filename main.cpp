#include "operadora.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

int main() {

    ///Clientes

    vector<Cliente*> clientes;

    ///Planos

    vector<Plano*> planos;

    ///Celulares

    vector<Celular*> celulares;

    ///Usuario Adiciona Clientes

    Cliente *A = new Cliente("123.456.789-10", "Satoshi", "Japan");
    clientes.push_back(A);
    Cliente *B = new Cliente("111.222.333-44", "Mitinick", "USA");
    clientes.push_back(B);

    ///Usuario Adiciona Planos

    Plano *PreLigacao = new Plano("Pre-Pago Ligacao", 0.50, 1.0, 100, 0.1);
    planos.push_back(PreLigacao);
    Plano *PreInternet = new Plano("Pre-Pago Internet", 0.80, 5.0, 1000, 0.5);
    planos.push_back(PreInternet);
    Plano *PosControle = new Plano("Pos-Pago Controle", 0.30, 10.0, 5000, 1.0);
    planos.push_back(PosControle);
    Plano *PosInfinity = new Plano("Pos-Pago Infinite", 0.15, 50.0, 50000, 10.0);
    planos.push_back(PosInfinity);

    ///Usuario habilita um novo celular em plano pós-pago

    PosPago plano3("Pos-Pago Infinite", 0.15, 50.0, 50000, 10.0, "23");
    Celular *clt1 = new Celular(clientes[0], &plano3);
    celulares.push_back(clt1);
    clientes[0]->AdicionaCelular(celulares[0]);

    ///Usuario habilita um novo celular em plano pré-pago

    PrePago plano1("Pre-Pago Internet", 0.80, 5.0, 1000, 0.5);
    Celular *clt2 = new Celular(clientes[1], &plano1);
    celulares.push_back(clt2);
    clientes[1]->AdicionaCelular(celulares[1]);

    ///Usuario Adicina creditos a um celular pre-pago

    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->verifica_numero(977031,35);
    }

    ///Usuario Verifica o valor e a validade dos creditos de um celular pre-pago

    cout << "Cliente (Sr. Mitinick) verifica credito: " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->verifica_numero(977031);
    }

    ///Usuario pos-pago Registra ligação simples

    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->registra_ligacao(977021, "23.06.2019 - 18:30:00", 10);
        celulares[i]->registra_ligacao(977021, "23.06.2019 - 21:30:00", 40);
    }

    ///Usuario pre-pago Registra ligação simples

    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->registra_ligacao(977031, "23.06.2019 - 20:30:00", 20);
    }

    ///Usuario pos-pago Registra ligação de dados

    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->registra_ligacao_Dados(977021, "23.06.2019 - 07:30:00", 100, "dowload");
    }

    ///Usuario pre-pago Registra ligação de dados

    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->registra_ligacao_Dados(977031, "23.06.2019 - 10:40:00", 200, "dowload");
    }

    ///Usuario ultrapassa limite da franquia de dados

    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->registra_ligacao_Dados(977031, "23.06.2019 - 13:20:00", 10, "upload");
    }


    ///Usuario Verifica o pacote de internet

    cout << endl <<"Cliente (Sr. Satoshi) verifica pacote de internet: " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->verifica_pacote_internet(977021);
    }

    ///Extrato Ligacoes Simples usuario pos-pago

    cout << endl << "Extrato Ligacoes (Sr. Satoshi): " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->extrato_ligacao(977021, "20.06.2019");
    }

    ///Extrato Ligacoes Dados usuario pos-pago

    cout << endl << "Extrato Consumo de Dados (Sr. Satoshi): " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->extrato_ligacao_dados(977021, "20.06.2019");
    }

    ///Extrato Ligacoes Simples usuario pre-pago

    cout << endl << "Extrato Ligacoes (Sr. Mitinick): " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->extrato_ligacao(977031, "20.06.2019");
    }

    ///Extrato Ligacoes Dados usuario pre-pago

    cout << endl << "Extrato Consumo de Dados (Sr. Mitinick): " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->extrato_ligacao_dados(977031, "20.06.2019");
    }

    ///Usuario Verifica o pacote de internet

    cout << endl <<"Cliente (Sr. Mitinick) verifica pacote de internet: " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->verifica_pacote_internet(977031);
    }

    ///Usuario verifica valor da conta de celular pos-pago
    cout << endl <<"Cliente (Sr. Satoshi) verifica valor da conta: " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->verifica_valor_conta(977021);
    }


    ///Listar todos clientes
    cout << endl << "Lista de todos os clientes: " << endl;
    for(int i=0; i<clientes.size(); i++)
    {
        cout << endl;
        clientes[i]->imprime_dados();
        clientes[i]->imprime_celulares();
    }

    ///Listar todos Planos
    cout << endl << "Lista de todos os planos: " << endl;
    for(int i=0; i<planos.size(); i++)
    {
        cout << endl;
        planos[i]->imprime();
    }

    ///Listar todos Celulares
    cout << endl << "Lista de todos os celulares: " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        cout << endl;
        celulares[i]->imprime_numero();
        celulares[i]->imprime_cliente();
        celulares[i]->imprime_plano();
    }

    delete A;
    delete B;

    delete PreLigacao;
    delete PreInternet;
    delete PosControle;
    delete PosInfinity;

    delete clt1;
    delete clt2;

    return 0;

}
