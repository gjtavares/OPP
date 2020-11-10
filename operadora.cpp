#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "operadora.h"
#include <ctime>
#include <string.h>

using namespace std;

/// Construtor cliente

Cliente::Cliente(string c_cpf, string c_nome, string c_endereco)
{
    CPF = c_cpf;
    nome = c_nome;
    endereco = c_endereco;

}

double Celular::proxNumCelular = 977021;
//double Celular::proxNumCelular = 9770;
void Cliente::imprime_dados()
{
    cout << "Nome do cliente: " << nome << endl << "CPF: "<< CPF << endl
    << "Endereco: " << endereco << endl;
}

///Imprime informacoes do cliente

void Cliente::imprime_celulares()
{
    cout << "Celulares: " << endl;
    for(int i=0; i<celulares.size(); i++)
    {
        celulares[i]->imprime_numero();
        celulares[i]->imprime_plano();
    }
}

/// Adiciona um novo celular para o cliente

void Cliente::AdicionaCelular(Celular* NovoCelular)
{
    celulares.push_back(NovoCelular);
}

///Destrutor cliente

Cliente::~Cliente()
{

}

///Construtor celular para um dispositivos cadastrado em plano pos-pago

Celular::Celular(Cliente* usuario, PosPago* planpos) : cliente(usuario), planopos(planpos)
{
    numero = proxNumCelular;
    proxNumCelular = proxNumCelular + 10;
}

///Construtor celular para um dispositivos cadastrado em plano pre-pago

Celular::Celular(Cliente* usuario, PrePago* planpre) : cliente(usuario), planopre(planpre)
{
    numero = proxNumCelular;
    proxNumCelular = proxNumCelular + 10;
}

///Imprime o numero do celular

void Celular::imprime_numero()
{
    cout << "Numero: " << numero << endl;
}

///Imprime informações do cliente

void Celular::imprime_cliente()
{
    cliente->imprime_dados();
}

///Imprime informações do plano

void Celular::imprime_plano()
{
    if(planopos!=NULL)
        planopos->imprime();
    if(planopre!=NULL)
        planopre->imprime();
}

///Verifica o numero do celular pre-pago para verificar os creditos ou adicionar creditos

void Celular::verifica_numero(double num_cel, double valor)
{
    if(numero==num_cel)
    {
        if(planopre!=NULL)
        {
            if(valor==0.0)
            {
                planopre->verifica_cred();
            }
            else
            {
                planopre->adiciona_cred(valor);
            }
        }
    }
}

///Verifica extrato do pacote de internet para um determinado numero de celular

void Celular::verifica_pacote_internet(double num_cel)
{
    if(numero==num_cel)
    {
        if(planopre!=NULL)
        {
            planopre->verifica_internet();
        }
        if(planopos!=NULL)
        {
            planopos->verifica_internet();
        }
    }
}

///Usuario registra uma ligação simples em um determinado numero de telefone

void Celular::registra_ligacao(double num_cel, string data_hora, double duracao)
{
    double valor_min;
    if(numero==num_cel)
    {
        if(planopos!=NULL)
        {
            valor_min = planopos->val_minuto();
            LigacaoSimples *lig = new LigacaoSimples(data_hora, duracao, valor_min);
            ligacoesS.push_back(lig);
        }
        if(planopre!=NULL)
        {
            int n = data_hora.length();
            char datahorareceb[n + 1];
            strcpy(datahorareceb, data_hora.c_str());
            time_t t1;
            struct tm then;
            int ano, mes;
            sscanf( datahorareceb, "%d.%d.%d - %d:%d:%d", &then.tm_mday, &mes, &ano, &then.tm_hour, &then.tm_min, &then.tm_sec );
            then.tm_year = ano - 1900;
            then.tm_mon = mes - 1;
            t1 = mktime( &then );

            string data_venc = planopre->data_val();
            data_venc = data_venc + " - 00:00:00";
            n = data_venc.length();
            char data_vencimento[n + 1];
            strcpy(data_vencimento, data_venc.c_str());
            time_t t2;
            sscanf( data_vencimento, "%d.%d.%d - %d:%d:%d", &then.tm_mday, &mes, &ano, &then.tm_hour, &then.tm_min, &then.tm_sec );
            then.tm_year = ano - 1900;
            then.tm_mon = mes - 1;
            t2 = mktime( &then );

            double credito = planopre->valor_cred();
            valor_min = planopre->val_minuto();
            double valor_gasto = duracao*valor_min;

            if(valor_gasto <= credito && t1<t2)
            {
                planopre->subtrai_cred(valor_gasto);
                LigacaoSimples *lig = new LigacaoSimples(data_hora, duracao,valor_min);
                ligacoesS.push_back(lig);
            }
            else
            {
                cout << "Saldo Insuficiente" << endl;
            }
        }
    }
}

///Usuario registra uma ligação de dados em um determinado numero de telefone

void Celular::registra_ligacao_Dados(double num_cel, string data_hora, double duracao, string tipo)
{
    double valor_min;
    double valor_franq;
    double valor_fraq_gasta;
    if(numero==num_cel)
    {
        if(planopos!=NULL)
        {
            valor_min = planopos->val_minuto();
            valor_franq = planopos->valor_franquia();
            valor_fraq_gasta = planopos->valor_franquia_gasta();
            if(valor_franq == 0)
            {
                cout << "Plano não contempla internet" << endl;
            }
            else
            {
                if(valor_fraq_gasta >= valor_franq)
                {

                    double vel = planopos->Valor_velocAlem();
                    double val_gasto = vel*duracao;
                    planopos->franquia_gast(val_gasto);
                    LigacaoDados *lig = new LigacaoDados(data_hora, duracao, valor_min, tipo, val_gasto);
                    ligacoesD.push_back(lig);
                }
                else
                {
                    double vel = planopos->Valor_velocidade();
                    double val_gasto = vel*duracao;
                    planopos->franquia_gast(val_gasto);
                    LigacaoDados *lig = new LigacaoDados(data_hora, duracao, valor_min, tipo, val_gasto);
                    ligacoesD.push_back(lig);
                }
            }
        }

        if(planopre!=NULL)
        {
            int n = data_hora.length();
            char datahorareceb[n + 1];
            strcpy(datahorareceb, data_hora.c_str());
            time_t t3;
            struct tm then;
            int ano, mes;
            sscanf( datahorareceb, "%d.%d.%d - %d:%d:%d", &then.tm_mday, &mes, &ano, &then.tm_hour, &then.tm_min, &then.tm_sec );
            then.tm_year = ano - 1900;
            then.tm_mon = mes - 1;
            t3 = mktime( &then );

            string data_venc = planopre->data_val();
            data_venc = data_venc + " - 00:00:00";
            n = data_venc.length();
            char data_vencimento[n + 1];
            strcpy(data_vencimento, data_venc.c_str());
            time_t t4;
            sscanf( data_vencimento, "%d.%d.%d - %d:%d:%d", &then.tm_mday, &mes, &ano, &then.tm_hour, &then.tm_min, &then.tm_sec );
            then.tm_year = ano - 1900;
            then.tm_mon = mes - 1;
            t4 = mktime( &then );


            valor_min = planopre->val_minuto();
            valor_franq = planopre->valor_franquia();
            valor_fraq_gasta = planopre->valor_franquia_gasta();
            double vel;
            double val_gasto;

            if(t3<t4)
            {
                if(valor_franq == 0)
                {
                    cout << "Plano não contempla internet" << endl;
                }
                else
                {
                    if(valor_fraq_gasta >= valor_franq)
                    {
                        alerta();
                        vel = planopre->Valor_velocAlem();
                        val_gasto = vel*duracao;
                        planopre->franquia_gast(val_gasto);
                        LigacaoDados *lig = new LigacaoDados(data_hora, duracao, valor_min, tipo, val_gasto);
                        ligacoesD.push_back(lig);
                    }
                    else
                    {
                        vel = planopre->Valor_velocidade();
                        val_gasto = vel*duracao;
                        planopre->franquia_gast(val_gasto);
                        LigacaoDados *lig = new LigacaoDados(data_hora, duracao, valor_min, tipo, val_gasto);
                        ligacoesD.push_back(lig);
                    }
                }

            }
            else{
                cout << "Saldo Vencido" << endl;
            }

        }
    }

}

///Retorna as ligações efetuadas por um determinado numero de celular a partir de uma determinada data

void Celular::extrato_ligacao(double num_cel, string data)
{
    string data1 = data + " - 00:00:00";
    if(numero==num_cel)
    {
        for(int i=0; i<ligacoesS.size(); i++)
        {
            ligacoesS[i]->verifica_data(data1);
        }
    }
}

///Retorna o extrato de internet efetuadas por um determinado numero de celular a partir de uma determinada data

void Celular::extrato_ligacao_dados(double num_cel, string data)
{
    string data1 = data + " - 00:00:00";
    if(numero==num_cel)
    {
        for(int i=0; i<ligacoesD.size(); i++)
        {
            ligacoesD[i]->verifica_data(data1);
        }
    }
}

///Alerta o usuario que um determinado numero de celular ultrapassou a franquia

void Celular::alerta()
{
    cout << endl << "Cliente Excedeu limite de dados" << endl;
    cout << "Informacoes: " << endl;
    imprime_numero();
    imprime_cliente();
    imprime_plano();
}

///Retorna ao usuario o valor total da conta

void Celular::verifica_valor_conta(double num_cel)
{
    if(numero==num_cel)
    {
        if(planopos!=NULL)
        {
            string vencimento = planopos->data_vencimento();
            char data_atual[20];
            char data_ant[20];
            time_t agora;
            agora = time(NULL);
            time_t mes_ant = agora - 30*86400;
            strftime(data_atual, sizeof(data_atual), "%m.%Y", localtime( &agora ));
            strftime(data_ant, sizeof(data_ant), "%m.%Y", localtime( &mes_ant ));
            string mes_atual = vencimento + "." + data_atual;
            string mes_anterior = vencimento + "." + data_ant;
            mes_anterior = mes_anterior + " - 00:00:00";
            mes_atual = mes_atual + " - 23:59:59";
            double valor_conta=0.0;
            for(int i=0; i<ligacoesS.size(); i++)
            {
                valor_conta = ligacoesS[i]->valor_ligacao(mes_anterior, mes_atual) + valor_conta;
            }
            if(valor_conta<0.1)
            {
                cout << "Referente a " << mes_anterior << " a " << mes_atual << endl;
                cout << "Valor Total: R$ 0" << endl;
            }
            else
            {
                cout << "Referente a " << mes_anterior << " a " << mes_atual << endl;
                cout << "Valor Total: R$" << valor_conta << endl;
            }

        }
        else
        {
            cout << "Numero nao cadastrado em um plano pos-pago" << endl;
        }
    }

}

/// Destrutor do Ciente

Celular::~Celular()
{

}

/// Construtor Plano

Plano::Plano(string c_nome, double ValMin, double vel, double franq, double veloc)
{
    nome = c_nome;
    valorMinuto = ValMin;
    velocidade = vel;
    franquia = franq;
    velocAlem = veloc;
}

///Imprime informações de um plano qualquer

void Plano::imprime()
{
    cout << "Nome do Plano: " << nome << endl
    << "Valor do Minuto: "<< valorMinuto << " cent" << endl
    << "Velocidade: " << velocidade << " Mbps" << endl
    << "Franquia: " << franquia << " MB" << endl
    << "Velocidade Apos Franquia: " << velocAlem << " Mbps" << endl;
}

///Retorna o valor do minuto de um determinado plano

double Plano::val_minuto()
{
    return valorMinuto;
}

/// Retorna a franquia de internet de um determinado plano

double Plano::valor_franquia()
{
    return franquia;
}

///Retorna o valor da franquia gasto por um telefone

double Plano::valor_franquia_gasta()
{
    return franquia_gasta;
}

///Retorna o valor da velocidade de uma determinado plano

double Plano::Valor_velocidade()
{
    return velocidade;
}

///Retorna o valor da velocidade de um plano ao exceder a franquia

double Plano::Valor_velocAlem()
{
    return velocAlem;
}

///Adiciona o valor de uma ligação de dados ao valor já gasto por um telefone

void Plano::franquia_gast(double valor)
{
    franquia_gasta = franquia_gasta + valor;
}

///Retorna o extrato de internet ao usuario

void Plano::verifica_internet()
{
    if(franquia_gasta >= franquia)
    {
        cout << "Franquia: " << "Franquia excedida" << endl
        << "Velocidade Atual " << velocAlem << "Mbps" <<endl;
    }
    else
    {
        cout << "Franquia: " << (franquia - franquia_gasta) << "MB" << endl
        << "Velocidade Atual: " << velocidade << "Mbps" << endl;

    }
}
///Destrutor plano

Plano::~Plano()
{

}


/// Construtor Ligaçao

Ligacao::Ligacao(string data, double c_duracao, double valor_minuto)
{
    dataHora = data;
    duracao = c_duracao;
    custo = valor_minuto*duracao;
}

/// Destruto Ligação

Ligacao::~Ligacao()
{

}

///Construtor da classe derivado Ligacao Simples

LigacaoSimples::LigacaoSimples(string data, double c_duracao, double valor_minuto) : Ligacao(data,c_duracao, valor_minuto) {}

///Retorna Extrato de ligações de um numero para o usuario

void LigacaoSimples::verifica_data(string data)
{
    int n = data.length();
    char datahorarecebida[n + 1];
    strcpy(datahorarecebida, data.c_str());
    string databuffer = dataHora;
    n = databuffer.length();
    char datahoraarmazenada[n + 1];
    strcpy(datahoraarmazenada, databuffer.c_str());

    time_t segundosrecebidos;
    time_t segundosarmazenados;
    struct tm tm;
    int ano, mes;


    sscanf( datahorarecebida, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    segundosrecebidos = mktime( &tm );

    sscanf( datahoraarmazenada, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    segundosarmazenados = mktime( &tm );

    if(segundosrecebidos < segundosarmazenados)
    {
        cout << endl << "Data do Consumo: " << dataHora << endl
        << "Duracao da ligacao: " << duracao << "min" << endl
        << "Custo da ligacao: R$ " << custo << endl;
    }

}

///Verifica quais ligações estão dentro do prazo vigente da fatura

double LigacaoSimples::valor_ligacao(string mes_anterior, string mes_posterior)
{
    int n = mes_anterior.length();
    char mesant[n + 1];
    strcpy(mesant, mes_anterior.c_str());
    n = mes_posterior.length();
    char mespost[n + 1];
    strcpy(mespost, mes_posterior.c_str());
    string databuffer = dataHora;
    n = databuffer.length();
    char datahoraarmazenada[n + 1];
    strcpy(datahoraarmazenada, databuffer.c_str());

    time_t seg_mes_ant;
    time_t seg_mes_post;
    time_t segarmazenados;
    struct tm tm;
    int ano, mes;


    sscanf( mesant, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    seg_mes_ant = mktime( &tm );

    sscanf( mespost, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    seg_mes_post = mktime( &tm );

    sscanf( datahoraarmazenada, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    segarmazenados = mktime( &tm );

    if(segarmazenados > seg_mes_ant && segarmazenados < seg_mes_post)
    {
        return custo;
    }
}



///Destrutor sub classe ligação

LigacaoSimples::~LigacaoSimples()
{

}

///Cosntrutor da classe derivada LigacaoDados

LigacaoDados::LigacaoDados(string data, double c_duracao, double valor_minuto, string tipo_dados, double dados_gast) : Ligacao(data,c_duracao, valor_minuto)
{
    tipoDeDados = tipo_dados;
    dados_gasto = dados_gast;
}

///Retorna extrado do consumo de dados de um celular ao usuario

void LigacaoDados::verifica_data(string data)
{
    int n = data.length();
    char datahorarecebida[n + 1];
    strcpy(datahorarecebida, data.c_str());
    string databuffer = dataHora;
    n = databuffer.length();
    char datahoraarmazenada[n + 1];
    strcpy(datahoraarmazenada, databuffer.c_str());

    time_t segrecebidos;
    time_t segarmazenados;
    struct tm tm;
    int ano, mes;


    sscanf( datahorarecebida, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    segrecebidos = mktime( &tm );

    sscanf( datahoraarmazenada, "%d.%d.%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    tm.tm_year = ano - 1900;
    tm.tm_mon = mes - 1;

    segarmazenados = mktime( &tm );

    if(segrecebidos < segarmazenados)
    {
        cout << endl << "Data da Ligacao: " << dataHora << endl
        << "Duracao da ligacao: " << duracao << "min" << endl
        << "Dados comsumidos:" << dados_gasto << "MB" << endl
        << "Tipo: " << tipoDeDados << endl;
    }

}

///Destrutor subclasse LigacaoDados

LigacaoDados::~LigacaoDados()
{

}

///Construtor classe derivado PrePago

PrePago::PrePago(string c_nome, double ValMin, double vel, double franq, double veloc, double cred, string dataval) : Plano(c_nome, ValMin, vel, franq, veloc)
{
    credito = cred;
    data_validade = dataval;
}

///Imprime informações de um plano pré-pago

void PrePago::imprime()
{
    cout << "Nome do Plano: " << nome << endl
    << "Valor do Minuto: "<< valorMinuto << " cent" << endl
    << "Velocidade: " << velocidade << " Mbps" << endl
    << "Franquia: " << franquia << " MB" << endl
    << "Velocidade Apos Franquia: " << velocAlem << " Mbps" << endl
    << "Creditos: R$ " << credito << endl
    << "Validade dos Creditos: " << data_validade << endl;
}

///Adiciona credito à um celular pré-pago

void PrePago::adiciona_cred(double valor)
{
    char data[20];
    time_t agora;
    agora = time(NULL);
    agora = agora + 180*86400;
    strftime(data, sizeof(data), "%d.%m.%Y", localtime( &agora ));
    credito = credito + valor;
    data_validade =  data;
}

///Subtrai valor da ligação do total de creditos de um celular

void PrePago::subtrai_cred(double valor)
{
    credito = credito - valor;
}

///Retorna valor de creditos de um celular ao usuario

void PrePago::verifica_cred()
{
    cout << "Creditos: R$ " << credito << endl
    << "Validade dos Creditos: " << data_validade << endl;
}

double PrePago::valor_cred()
{
    return credito;
}

string PrePago::data_val()
{
    return data_validade;
}

///Destrutor da subclasse

PrePago::~PrePago()
{

}

///Costrutor da classe derivado PosPago
PosPago::PosPago(string c_nome, double ValMin, double vel, double franq, double veloc, string venc) : Plano(c_nome, ValMin, vel, franq, veloc) {

    vencimento = venc;
}

///Imprime informações de um plano pos-pago
void PosPago::imprime()
{
    cout << "Nome do Plano: " << nome << endl
    << "Valor do Minuto: "<< valorMinuto << " cent" << endl
    << "Velocidade: " << velocidade << " Mbps" << endl
    << "Franquia: " << franquia << " MB" << endl
    << "Velocidade Apos Franquia: " << velocAlem << " Mbps" << endl
    << "Dia de vecimento da fatura: " << vencimento << endl;
}

string PosPago::data_vencimento()
{
    return vencimento;
}

///Destrutor

PosPago::~PosPago()
{

}
