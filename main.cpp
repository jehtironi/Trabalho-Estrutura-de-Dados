#include <iostream>
#include <locale.h>
#include "Lista_DE.h"
#include "Fila.h"
using namespace std;

struct Pessoa
{
    bool socio_torcedor; // se é sócio
    int tempo; // unidade de tempo de atendimento
};

struct Guiche
{
    bool socio_torcedor; // guiche normal ou sócio
    int qnt; // qnt de pessoas
    Fila <Pessoa> fila; // fila do guichê
};

//Função para criar os guiches
bool criar_guiches (int qnt, Lista<Guiche> &guiches, bool socio) // qnt de guichês, lista de guichês, guiche normal ou sócio
{
    if(qnt == 0){
        return true;
    }
    Guiche g; // cria o guichê
    g.qnt = 0;  // seta a qnt para 0
    inicializar(g.fila); // inicializa a fila do guichê
    g.socio_torcedor = socio; // atualiza o tipo do guichê

    for(int i = 0; i < qnt; i++){
        inserir_fim(guiches, g); // insere o guichê no final da lista de guichês
    }
    return true;
}

//Função para estar retornando as porcentagens
int porcentagem(int qnt, int total)
{
    int resultado =  ((float(qnt)/float(total)) * 100);
    return resultado;
}

int verificar_tempo(Lista <Pessoa> lista, int unidade_tempo)
{
    int resultado = 0; //recebe 0
    Elemento <Pessoa> *nav = lista.primeiro; //Ponteiro nav recebe o valor contido no primeiro elemento da lsita
    while(nav != NULL){ //Enquanto nav for diferente de nulo ele permanece no laço
        if(nav -> dado.tempo == unidade_tempo){ //quando dado.tempo for igual a unidade o mesmo ira somar +1 no resultado
            resultado++;
        }
        nav = nav -> prox; //Nav recebe o proximo elemento
    }

    return resultado; // retorna o valor do resultado para a função
}

bool gerar_pessoas(Lista <Pessoa> &pessoa_socio_torcedor, Lista <Pessoa> &pessoa_comum, Lista <Pessoa> &pessoa_socio_torcedor_nAtendido, Lista <Pessoa> &pessoa_comum_nAtendido)
{
    Pessoa p;
    int total = pessoa_comum.qnt + pessoa_socio_torcedor.qnt;

    if(pessoa_socio_torcedor.qnt == 0){//Quando a quantidade de socio torcedor for igual a zero
        p.socio_torcedor = true; //A pessoa socio torcedor recebe verdadeiro
        p.tempo = 1; //A unidade de tempo na espera sera 1
        inserir_fim(pessoa_socio_torcedor, p); //chama a função inserir fim e insere no final da lista de socio torcedor
        inserir_fim(pessoa_socio_torcedor_nAtendido, p);
        return true; // retorna verdadeiro
    }

    else if(pessoa_comum.qnt == 0){ //Quando a quantidade de torcedor comum for igual a zero
        p.socio_torcedor = false; //socio torcedor recebe falso
        p.tempo = 3; // tempo sera 3
        inserir_fim(pessoa_comum, p); // chama a função inserir no final da lista do torcedor comum
        inserir_fim(pessoa_comum_nAtendido, p);
        return true;
    }

    else{ //Caso nenhuma das duas outras condições sejam atendidas
        if(porcentagem(pessoa_socio_torcedor.qnt, total) >= 5){//se a porcentagem dos socios torcedores forem maior ou igual a 5% retorna falso
            p.socio_torcedor = false;
            if(porcentagem(verificar_tempo(pessoa_comum, 3), pessoa_comum.qnt) < 45){ //Se a porcentagem de torcedores comuns for menor que 45%
                p.tempo = 3; //Então o tempo de atendimento sera de 3 unidades
                inserir_fim(pessoa_comum, p); //Chama a função para inserir no final da lista de torcedores comuns
                inserir_fim(pessoa_comum_nAtendido, p);
                return true;
            }

            else if(porcentagem(verificar_tempo(pessoa_comum, 2), pessoa_comum.qnt) < 30){ //Se a porcentagem de torcedores comuns for menor que 30%
                p.tempo = 2; //Então o tempo de atendimento sera de 2 unidades
                inserir_fim(pessoa_comum, p); //Chama a função para inserir no final da lista de torcedores comuns
                inserir_fim(pessoa_comum_nAtendido, p);
                return true;
            }

            else{ // Caso as condições anteriores não sejam atendidas
                p.tempo = 1; //Então o tempo de atendimento sera de 1 unidades
                inserir_fim(pessoa_comum, p);//Chama a função para inserir no final da lista de torcedores comuns
                inserir_fim(pessoa_comum_nAtendido, p);
                return true;
            }
        }

        else{ //Quando a porcentagem for menor que 5%
            p.socio_torcedor = true; //A pessoa socio torcedor recebera true

            if(porcentagem(verificar_tempo(pessoa_socio_torcedor, 1), pessoa_socio_torcedor.qnt) < 85){ //Se a porcentagem for menor que 85%
                p.tempo = 1; //O atendimento será de uma unidade de tempo
                inserir_fim(pessoa_socio_torcedor, p); //Chama a função para inserir no final da lista de socio torcedores
                inserir_fim(pessoa_socio_torcedor_nAtendido, p);
                return true;
            }

            else{ //Caso a outra condição não seja atendida
                p.tempo = 2; //O atendimento será de 2 unidade de tempo
                inserir_fim(pessoa_socio_torcedor, p);
                inserir_fim(pessoa_socio_torcedor_nAtendido, p);

                return true;
            }
        }
    }

}

//Distribui os torcedores nos guiches
bool distribuir_nos_guiches(Lista <Guiche> &guiches_normais, Lista <Guiche> &guiches_socio, Pessoa p)
{
    if(p.socio_torcedor == false){ //Quando a pessoa socio torcedor for igual a falso
        Elemento <Guiche> *nav = guiches_normais.primeiro; //Então o ponteiro nav recebe o primeiro guiche de torcedores normais
        Elemento <Guiche> *menor = guiches_normais.primeiro; //E o ponteiro menor também recebe o primeiro guiche de torcedores normais
        while(nav != NULL){ //Quando nav for diferente de null ele entra e permanece no laço
            if(nav -> dado.fila.qnt < menor -> dado.fila.qnt){ //Quando nav tiver uma quantidade maior que o menor, então menor recebe nav
                menor = nav;
            }

            nav = nav -> prox; // nav aponta para o proximo dado
        }
        insere(menor -> dado.fila, p); //Chama a função insere e adiciona o menor dado na fila
        menor->dado.qnt++;

        return true;
    }

    else {
        Elemento <Guiche> *nav = guiches_socio.primeiro;  //Então o ponteiro nav recebe o primeiro guiche de socios torcedores
        Elemento <Guiche> *menor = guiches_socio.primeiro;  //E o ponteiro menor também recebe o primeiro guiche de socios torcedores
        while(nav != NULL){
            if(nav -> dado.fila.qnt < menor -> dado.fila.qnt){
                menor = nav;
            }

            nav = nav -> prox; // nav aponta para o proximo dado
        }

        insere(menor -> dado.fila, p); //Chama a função insere e adiciona o menor dado na fila
        menor->dado.qnt++;
        return true;
    }
}

//Imprime a fila
void mostrar_fila(Guiche g)
{
    FElemento <Pessoa> *nav; //Cria o ponteiro nav
    nav = g.fila.primeiro;  //Nav recebe o item primeiro do guiche
    int i = 0;
    while(nav != NULL){
        cout << "\nTorcedor: " << i+1; //nav imprime o dado socio torcedor
        cout << "\tTempo: " << nav -> dado.tempo; // nav imprime o dado tempo
        nav = nav -> prox; //nav aponta para o proximo
        i++;}
    }


void mostrar_fila_guiches(Lista<Guiche> guiches_normais, Lista<Guiche> guiches_socio_torcedor)
{
    Elemento<Guiche> *nav3 = guiches_normais.primeiro;
        int i = 0;
        while(nav3 != NULL){
            cout<<"\n\nGuiche torcedor normal numero: "<<i+1;
            cout<<"\tQuantidade de pessoas na fila: "<<nav3->dado.fila.qnt;
            mostrar_fila(nav3->dado);
            nav3=nav3->prox;
            i++;
        }

        cout<<endl<<endl;

        Elemento <Guiche> *nav4 = guiches_socio_torcedor.primeiro;
        i = 0;
        while(nav4 != NULL){
            cout<<"\nGuiche socio torcedor numero: "<<i+1;
            cout<<"\tQuantidade de pessoas na fila: "<<nav4->dado.fila.qnt;
            mostrar_fila(nav4->dado);
            nav4=nav4->prox;
            i++;
        }
}


int main()
{
    setlocale(LC_ALL, "Portuguese");

    Lista<Guiche> guiches_normais; // lista de guichês comuns
    Lista<Guiche> guiches_socio_torcedor; // lista de guichês para sócio torcedores
    Lista<Pessoa> pessoa_socio_torcedor; // lista de pessoas sócio torcedoras
    Lista<Pessoa> pessoa_socio_torcedor_nAtendido;
    Lista<Pessoa> pessoa_comum;
    Lista<Pessoa> pessoa_comum_nAtendido; // lista de pessoas comuns
    char controle;
    do{
        // Inicializa as listas
        iniciar(guiches_normais);
        iniciar(guiches_socio_torcedor);
        iniciar(pessoa_socio_torcedor);
        iniciar(pessoa_comum);
        iniciar(pessoa_comum_nAtendido);
        iniciar(pessoa_socio_torcedor_nAtendido);

        //Solicita ao usuario a quantidade de guichês normais e não aceita numeros negativos
        int qnt, qnt_normais, qnt_socios;
        do{
            cout<<"Insira a quantidade de guichês normais: ";
            cin>>qnt;
            qnt_normais = qnt;
            if(qnt <= 0){
                cout<<"O valor deve ser maior ou igual a 0!"<<endl<<endl;
            }
        }while(qnt < 0);

        //Cria os guichês de torcedores normais
        criar_guiches(qnt, guiches_normais, false);

        //Solicita ao usuario a quantidade de guichês de socios torcedores e não aceita numeros negativos
        do{
            cout<<"Insira a quantidade de guichês para sócios: ";
            cin>>qnt;
            qnt_socios = qnt;
            if(qnt < 0){
                cout<<"O valor deve ser maior ou igual a 0!!"<<endl<<endl;
            }
        }while(qnt < 0);

        //Cria os guiches de socios torcedores
        criar_guiches(qnt, guiches_socio_torcedor, true);

        //Solicita ao usuario a quantidade de pessoas aguardando na fila antes da simulação e não aceita numeros negativos
        int qnt_esperando;
        do{
            cout<<"Insira a quantidade de pessoas aguardando: ";
            cin>>qnt_esperando;
            if(qnt_esperando < 0){
                cout<<"O valor deve ser maior ou igual a 0!"<<endl<<endl;
            }
        }while(qnt_esperando < 0);

        //Solicita ao usuario o tempo de simulação e não aceita numeros negativos
        int tempo_duracao; // duracao que o programa vai executar
        do{
            cout<<"Insira a unidade de tempo que o programa deve durar: ";
            cin>>tempo_duracao;
            if(tempo_duracao <= 0){
                cout<<"O valor deve ser maior do que 0!"<<endl<<endl;
            }
        }while(tempo_duracao <= 0);

        //Solicita ao usuario a quantidade de pessoas que entram na fila por unidade de tempo e não aceita numeros negativos
        int pessoas_por_unidade;
        do{
            cout<<"Insira a quantidade de pessoas que irão procurar um guichê por unidade de tempo: ";
            cin>>pessoas_por_unidade;
            if(pessoas_por_unidade < 0){
                cout<<"O valor deve ser maior ou igual a que 0!"<<endl<<endl;
            }
        }while(pessoas_por_unidade < 0);


        cout << "\n-----------------------------------------------------------------------------------------------------------\n";


          cout << "\n\nInicio da Simulação\n\n";
          for(int i = 0; i < qnt_esperando; i++){
            gerar_pessoas(pessoa_socio_torcedor, pessoa_comum, pessoa_socio_torcedor_nAtendido, pessoa_comum_nAtendido);
            }

            Elemento<Pessoa> *nav = pessoa_comum_nAtendido.primeiro;
            while(nav != NULL){
                distribuir_nos_guiches(guiches_normais, guiches_socio_torcedor, nav->dado);
                remover_inicio(pessoa_comum_nAtendido);
                nav = pessoa_comum_nAtendido.primeiro;
            }

            Elemento<Pessoa> *nav2 = pessoa_socio_torcedor_nAtendido.primeiro;
            while(nav2 != NULL){
                distribuir_nos_guiches(guiches_normais, guiches_socio_torcedor, nav2->dado);
                remover_inicio(pessoa_socio_torcedor_nAtendido);
                nav2 = pessoa_socio_torcedor_nAtendido.primeiro;
            }

            mostrar_fila_guiches(guiches_normais, guiches_socio_torcedor);

            getchar();

        cout << "\n-----------------------------------------------------------------------------------------------------------\n";
        Elemento <Pessoa> *nav_pessoas_normais;
        Elemento <Pessoa> *nav_pessoas_socio;
        getchar();
        cout<<"Tempo duração da simulação:"<<tempo_duracao;
        for(int i = 0; i < tempo_duracao; i++){
            cout<<"Execução "<<i<<endl;
            //GERA AS PESSOAS POR UNIDADE DE TEMPO
            for(int j = 0; j < pessoas_por_unidade; j++){
                gerar_pessoas(pessoa_socio_torcedor, pessoa_comum, pessoa_socio_torcedor_nAtendido, pessoa_comum_nAtendido);
            }
            //DISTRIBUI AS GERADAS NOS GUICHÊS
            //Normais:
            nav_pessoas_normais = pessoa_comum_nAtendido.primeiro;
            while(nav_pessoas_normais != NULL){
                distribuir_nos_guiches(guiches_normais, guiches_socio_torcedor, nav_pessoas_normais->dado);
                remover_inicio(pessoa_comum_nAtendido);
                nav_pessoas_normais = pessoa_comum_nAtendido.primeiro;

            }
            //Sócio:
            nav_pessoas_socio = pessoa_socio_torcedor_nAtendido.primeiro;
            while(nav_pessoas_socio != NULL){
                distribuir_nos_guiches(guiches_normais, guiches_socio_torcedor, nav_pessoas_socio->dado);
                remover_inicio(pessoa_socio_torcedor_nAtendido);
                nav_pessoas_socio = pessoa_socio_torcedor_nAtendido.primeiro;
            }

            mostrar_fila_guiches(guiches_normais, guiches_socio_torcedor);

            //ATENDIMENTO DOS GUICHÊS NORMAIS
            Elemento<Guiche> *nav_guiche_normal = guiches_normais.primeiro;
            while(nav_guiche_normal != NULL){
                if(nav_guiche_normal->dado.fila.qnt != 0){
                    nav_guiche_normal->dado.fila.primeiro->dado.tempo --;
                    if(nav_guiche_normal->dado.fila.primeiro->dado.tempo == 0){
                        retira(nav_guiche_normal->dado.fila);
                    }

                }
                nav_guiche_normal = nav_guiche_normal->prox;
            }

            Elemento<Guiche> *nav_guiche_socio = guiches_socio_torcedor.primeiro;
            while(nav_guiche_socio != NULL){
                if(nav_guiche_socio->dado.fila.qnt != 0){
                    nav_guiche_socio->dado.fila.primeiro->dado.tempo --;
                    if(nav_guiche_socio->dado.fila.primeiro->dado.tempo == 0){
                        retira(nav_guiche_socio->dado.fila);
                    }

                }
                nav_guiche_socio = nav_guiche_socio->prox;
            }

            getchar();
            system("clear||cls");

        }

        cout<<"Simulação terminou!";
        cout<<endl<<"Média de pessoas que esperaram na fila: ";

        int total_esperando = 0;

        Elemento<Guiche> *nav_g = guiches_normais.primeiro;
        while(nav_g != NULL){
            total_esperando += nav_g->dado.qnt;
            nav_g = nav_g->prox;
        }

        nav_g = guiches_socio_torcedor.primeiro;
        while(nav_g != NULL){
            total_esperando += nav_g->dado.qnt;
            nav_g = nav_g->prox;
        }

        float resultado = ( float(total_esperando) / (float(qnt_normais) + float (qnt_socios)));

        cout<<resultado;

        do{
            cout<<"\nReiniciar a simulação (s/n)? ";
            cin>>controle;

            if(controle != 's' and controle != 'n'){
                cout<<"\nInválido\n";
            }
        }while(controle != 's' and controle != 'n');
    }while(controle == 's');

    return 0;
}
