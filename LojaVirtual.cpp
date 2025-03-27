/*
 * Sistema de Loja Virtual - Jaymes Soares Ribeiro
 * 
 * Este programa implementa um sistema de loja virtual com dois tipos de usuários:
 * - Funcionários: podem acessar seus dados com login protegido por senha
 * - Clientes: podem visualizar e selecionar produtos para compra

*/

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
using namespace std;

class Pessoa {
protected:
    string nomeCompleto;
    string numeroCPF;
    string numeroTelefone;
public:
    Pessoa(string nome, string cpf, string telefone) : nomeCompleto(nome), numeroCPF(cpf), numeroTelefone(telefone) {}
    string getNome() { return nomeCompleto; }
    string getCPF() { return numeroCPF; }
    string getTelefone() { return numeroTelefone; }
};

class Funcionario : public Pessoa {
private:
    int numeroRegistro;
    string senhaAcesso;
    float salarioMensal;
public:
    Funcionario(string nome, string cpf, string telefone, int registro, string senha, float salario) 
        : Pessoa(nome, cpf, telefone), numeroRegistro(registro), senhaAcesso(senha), salarioMensal(salario) {}

    bool validarSenha(string senhaDigitada) {
        return senhaDigitada == senhaAcesso;
    }

    void imprimirDados() {
        cout << fixed << setprecision(2);
        cout << "Dados do Funcionario:" << endl;
        cout << "- Nome: " << nomeCompleto << endl;
        cout << "- CPF: " << formatarCPF(numeroCPF) << endl;
        cout << "- Telefone: " << formatarTelefone(numeroTelefone) << endl;
        cout << "- Registro: " << numeroRegistro << endl;
        cout << "- Salario: R$ " << salarioMensal << endl;
    }

private:
    string formatarCPF(string cpf) {
        if (cpf.length() == 11) {
            return cpf.substr(0, 3) + "." + cpf.substr(3, 3) + "." + cpf.substr(6, 3) + "-" + cpf.substr(9);
        }
        return cpf;
    }
    
    string formatarTelefone(string tel) {
        if (tel.length() == 11) {
            return "(" + tel.substr(0, 2) + ") " + tel.substr(2, 5) + "-" + tel.substr(7);
        }
        return tel;
    }
};

class Cliente : public Pessoa {
private:
    string produtoEscolhido;
    float valorProduto;
public:
    Cliente(string nome, string cpf, string telefone) : Pessoa(nome, cpf, telefone), produtoEscolhido(""), valorProduto(0.0f) {}

    void escolherProduto(string produto, float valor) {
        produtoEscolhido = produto;
        valorProduto = valor;
    }

    void imprimirDados() {
        cout << fixed << setprecision(2);
        cout << "Dados do Cliente:" << endl;
        cout << "- Nome: " << nomeCompleto << endl;
        cout << "- CPF: " << formatarCPF(numeroCPF) << endl;
        cout << "- Telefone: " << formatarTelefone(numeroTelefone) << endl;
        if (!produtoEscolhido.empty()) {
            cout << "- Produto: " << produtoEscolhido << endl;
            cout << "- Valor: R$ " << valorProduto << endl;
        }
    }

private:
    string formatarCPF(string cpf) {
        if (cpf.length() == 11) {
            return cpf.substr(0, 3) + "." + cpf.substr(3, 3) + "." + cpf.substr(6, 3) + "-" + cpf.substr(9);
        }
        return cpf;
    }
    
    string formatarTelefone(string tel) {
        if (tel.length() == 11) {
            return "(" + tel.substr(0, 2) + ") " + tel.substr(2, 5) + "-" + tel.substr(7);
        }
        return tel;
    }
};

float lerSalario() {
    string entrada;
    cin >> entrada;
    
    for (char &c : entrada) {
        if (c == ',') {
            c = '.';
        }
    }
    
    stringstream ss(entrada);
    float valor;
    ss >> valor;
    return valor;
}

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    string nome, cpf, telefone;
    int registro;
    string senha;
    float salario;

    cout << "Cadastro de Funcionario" << endl;
    cout << "Nome: ";
    getline(cin, nome);
    cout << "CPF (apenas numeros): ";
    getline(cin, cpf);
    cout << "Telefone (apenas numeros): ";
    getline(cin, telefone);
    cout << "Registro na empresa: ";
    cin >> registro;
    cout << "Senha: ";
    cin >> senha;
    cout << "Salario (ex: 3500.00): ";
    salario = lerSalario();
    limparBuffer();

    Funcionario funcionario(nome, cpf, telefone, registro, senha, salario);

    cout << endl << "Cadastro de Cliente" << endl;
    cout << "Nome: ";
    getline(cin, nome);
    cout << "CPF (apenas numeros): ";
    getline(cin, cpf);
    cout << "Telefone (apenas numeros): ";
    getline(cin, telefone);

    Cliente cliente(nome, cpf, telefone);

    cout << endl << "Acesso ao Sistema" << endl;
    string senhaDigitada;
    bool senhaCorreta = false;
    
    do {
        cout << "Funcionario " << funcionario.getNome() << ", digite sua senha: ";
        cin >> senhaDigitada;
        
        if (funcionario.validarSenha(senhaDigitada)) {
            senhaCorreta = true;
            cout << "Acesso concedido!" << endl;
            funcionario.imprimirDados();
        } else {
            cout << "Senha incorreta! Digite novamente." << endl;
        }
    } while (!senhaCorreta);

    cout << endl << "Cliente " << cliente.getNome() << ", escolha um produto:" << endl;
    cout << "1 - Celular - R$ 1500.00" << endl;
    cout << "2 - Notebook - R$ 3200.00" << endl;
    cout << "3 - Fone Bluetooth - R$ 200.00" << endl;

    int escolha;
    bool opcaoValida;
    
    do {
        cout << "Escolha (1-3): ";
        cin >> escolha;
        opcaoValida = true;
        
        switch (escolha) {
            case 1:
                cliente.escolherProduto("Celular", 1500.00);
                break;
            case 2:
                cliente.escolherProduto("Notebook", 3200.00);
                break;
            case 3:
                cliente.escolherProduto("Fone Bluetooth", 200.00);
                break;
            default:
                cout << "Opcao invalida! Tente novamente." << endl;
                opcaoValida = false;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!opcaoValida);

    cout << endl << "Compra realizada!" << endl;
    cliente.imprimirDados();

    return 0;
}