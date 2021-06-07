#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

template <typename tipo>
struct FElemento
{
    tipo dado;
    FElemento<tipo> *prox;
};

template <typename tipo>
struct Fila
{
    FElemento<tipo> *primeiro;
    int qnt;
};

///////////////////////////

template <typename tipo>
bool inicializar (Fila <tipo> &f)
{
    f.primeiro = NULL;
    f.qnt = 0;

    return true;
}

template <typename tipo>
bool insere (Fila <tipo> &f, tipo dado)
{
    if (f.primeiro == NULL){ // caso a lista esteja vazia
        FElemento <tipo> * novo = new FElemento <tipo>; // cria um novo elemento

        novo -> dado = dado; // o dado novo aponta para o dado recebido
        novo -> prox = NULL; // como ele é o último da lista, seu próximo será NULL
        f.primeiro = novo; // seta o primeiro da lista como o novo dado recem criado;
        f.qnt ++;

        return true;
    }

    else{ // caso a lista não esteja vazia, será necessário navegar pela memsma até encontrar a última posição
        FElemento <tipo> * navegador = f.primeiro; // cria-se um ponteiro navegador que recebe o endereço do primeiro elemento

        while (navegador -> prox != NULL){ // se o próximo == NULL, significa que é a última posição
           navegador = navegador -> prox; // navegador aponta para a próxima posição;
        }

        FElemento <tipo> * novo = new FElemento <tipo>;

        novo -> dado = dado; // novo recebe o dado
        novo -> prox = NULL; // e NULL como próximo
        navegador -> prox = novo; // como o vavegador estava apontando pra posição anteriorao novo, muda-se o próximo de NULL para o novo
        f.qnt ++;

        return true;
    }

    return false;
}

template <typename tipo>
tipo retira (Fila<tipo> &f)
{

     if (f.qnt == 1){
        tipo copia = f.primeiro -> dado;
        FElemento <tipo> *aux = f.primeiro;

        delete aux;

        f.primeiro = NULL;
        f.qnt --;

        return copia;
    }

    else{
        tipo copia = f.primeiro -> dado;
        FElemento <tipo> *aux = f.primeiro;
        f.primeiro = aux -> prox;

        delete aux;

        f.qnt --;

        return copia;
    }
}

template <typename tipo>
FElemento<tipo> consulta_primeiro(Fila<tipo> f)
{
    return *f.primeiro;
}

#endif // FILA_H_INCLUDED
