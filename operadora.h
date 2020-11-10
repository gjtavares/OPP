#ifndef OPERADORA_H_INCLUDED
#define OPERADORA_H_INCLUDED

#include <iostream>
#include<string>
#include <vector>

using namespace std;

class Celular;

class Plano{

protected:

    string nome;
    double valorMinuto;
    double velocidade;
    double franquia;
    double velocAlem;
    double franquia_gasta=0;

public:

    Plano(string c_nome, double ValMin, double vel, double franq, double veloc);
    virtual void imprime();
    virtual double val_minuto();
    double valor_franquia();
    double valor_franquia_gasta();
    double Valor_velocidade();
    double Valor_velocAlem();
    void franquia_gast(double valor);
    void verifica_internet();
    ~Plano();
};

class PrePago: public Plano{

    double credito=0.0;
    string data_validade;

public:

    PrePago(string c_nome, double ValMin, double vel, double franq, double veloc, double cred = 0.0, string dataval = "Vencido");
    void imprime();
    void adiciona_cred(double valor);
    void verifica_cred();
    double valor_cred();
    string data_val();
    void subtrai_cred(double valor);
    ~PrePago();
};

class PosPago: public Plano{

    string vencimento;

public:
    PosPago(string c_nome, double ValMin, double vel, double franq, double veloc, string venc);
    void imprime();
    string data_vencimento();
    ~PosPago();
};

class Ligacao{

protected:
    string dataHora;
    double duracao;
    double custo;

public:
    Ligacao(string data, double c_duracao, double valor_minuto);
    virtual void verifica_data(string data) = 0;
    ~Ligacao();
};

class LigacaoDados: public Ligacao{
    string tipoDeDados; //upload ou download
    double dados_gasto;
public:
    LigacaoDados(string data, double c_duracao, double valor_minuto, string tipo_dados, double dados_gast);
    void verifica_data(string data);
    ~LigacaoDados();
};

class LigacaoSimples: public Ligacao{
public:
    LigacaoSimples(string data, double c_duracao, double valor_minuto);
    void verifica_data(string data);
    double valor_ligacao(string mes_anterior, string mes_posterior);
    ~LigacaoSimples();
};



class Cliente{

    string CPF;
    string nome;
    string endereco;
    vector<Celular*> celulares;

public:

    Cliente(string c_cpf, string c_nome, string c_endereco);
    void imprime_dados();
    void imprime_celulares();
    void AdicionaCelular(Celular* NovoCelular);
    ~Cliente();

};

class Celular{


    Cliente* cliente;
    PosPago* planopos = NULL;
    PrePago* planopre = NULL;
    double numero;
    static double proxNumCelular;
    vector<LigacaoSimples*> ligacoesS;
    vector<LigacaoDados*> ligacoesD;
public:
    Celular (Cliente* usuario, PosPago* planpos);
    Celular (Cliente* usuario, PrePago* planpre);
    void imprime_cliente();
    void imprime_plano();
    void imprime_numero();
    void verifica_numero(double num_cel, double valor=0.0);
    void verifica_pacote_internet(double num_cel);
    void registra_ligacao(double num_cel, string data_hora, double duracao);
    void extrato_ligacao(double num_cel, string data);
    void registra_ligacao_Dados(double num_cel, string data_hora, double duracao, string tipo);
    void extrato_ligacao_dados(double num_cel, string data);
    void verifica_valor_conta(double num_cel);
    void alerta();
    ~Celular();
};

#endif // OPERADORA_H_INCLUDED
