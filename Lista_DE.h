#ifndef LISTA_DE_H_INCLUDED
#define LISTA_DE_H_INCLUDED

template <typename Tipo>
struct Elemento
{
    Tipo dado;
    Elemento <Tipo> *prox;
    Elemento <Tipo> *ant;
};

template <typename Tipo>
struct Lista
{
    Elemento <Tipo> *primeiro;
    Elemento <Tipo> *ultimo;

    int qnt;
};

//////////////////////////////

template <typename Tipo>
void iniciar (Lista <Tipo> &lst)
{
    lst.primeiro = NULL;
    lst.ultimo = NULL;
    lst.qnt = 0;
}

////////////////////////////

template <typename Tipo>
bool inserir_fim (Lista <Tipo> &lst, Tipo dado)
{
    if (lst.primeiro == NULL){//1
        Elemento <Tipo> *novo = new Elemento <Tipo>;

        novo->dado = dado;
        novo->ant = NULL;
        novo->prox = NULL;
        lst.primeiro = novo;
        lst.ultimo = novo;

        lst.qnt ++;

        return true;
    }

    else if (lst.primeiro->prox == NULL){//1
        Elemento <Tipo> *novo = new Elemento <Tipo>;

        novo->dado = dado;
        novo->prox = NULL;
        novo->ant = lst.primeiro;

        lst.primeiro->prox = novo;
        lst.ultimo = novo;
        lst.qnt++;

        return true;
    }

    else{
        Elemento <Tipo> *novo = new Elemento <Tipo>;//1

        novo->dado = dado;//1
        novo->prox = NULL;//1
        novo->ant = lst.ultimo;//1

        lst.ultimo->prox = novo;//1
        lst.ultimo = novo;//1
        lst.qnt++;

        return true;
    }

    return false;
}

template <typename Tipo>
bool remover_fim (Lista <Tipo> &lst)
{
    if (lst.primeiro == NULL){//1
        return false;
    }

    else if (lst.primeiro->prox == NULL){//1
        Elemento <Tipo> *aux = lst.primeiro;

        delete aux;

        lst.primeiro = NULL;
        lst.ultimo = NULL;
        lst.qnt--;

        return true;
    }

    else{
        Elemento <Tipo> *apagar = lst.ultimo;//1
        Elemento <Tipo> *aux = lst.ultimo->ant;//1

        aux->prox = NULL;//1
        lst.ultimo = aux;//1

        delete apagar;//1

        lst.qnt--;
        return true;
    }

}

/////////////////////////////////

template <typename Tipo>
bool inserir_inicio (Lista <Tipo> &lst, Tipo dado)
{
    if (lst.primeiro == NULL){//1
        Elemento<Tipo> *novo = new Elemento <Tipo>;

        novo -> dado = dado;
        novo -> prox = NULL;
        novo -> ant = NULL;

        lst.primeiro = novo;
        lst.ultimo = novo;

        lst.qnt++;
        return true;
    }

    else{
        Elemento<Tipo> *novo = new Elemento <Tipo>;//1

        novo -> dado = dado;//1
        novo -> prox = lst.primeiro;//1
        novo -> ant = NULL;//1

        lst.primeiro = novo;//1
        lst.qnt++;
        return true;
    }
}

template <typename Tipo>
bool remover_inicio (Lista <Tipo> &lst)
{
    if (lst.primeiro == NULL){//1
        return false;
    }

    else if (lst.primeiro->prox == NULL){//1
        Elemento <Tipo> *apagar = lst.primeiro;

        delete apagar;

        lst.primeiro = NULL;
        lst.ultimo = NULL;
        lst.qnt--;
        return true;
    }

    else{
        Elemento <Tipo> *apagar = lst.primeiro;//1

        lst.primeiro = apagar -> prox;//1
	apagar -> prox -> ant = NULL;//1
        delete apagar;//1

        lst.qnt--;

        return true;
    }
}

/////////////////////////////////////////

template <typename Tipo>
bool inserir_posicao (Lista <Tipo> & lst, int posicao, Tipo dado)
{
    if (posicao < 0 or posicao > lst.qnt){//2
        return false;
    }

    else if (lst.primeiro == NULL){//1
        Elemento <Tipo> *novo = new Elemento <Tipo>;

        novo -> dado = dado;

        lst.primeiro = novo;
        lst.ultimo = novo;

        novo -> prox = NULL;
        novo -> ant = NULL;

        lst.qnt++;

        return true;
    }

    else if (posicao == 0){//1
        Elemento <Tipo> *novo = new Elemento <Tipo>;

        novo -> dado = dado;

        novo -> prox = lst.primeiro;
        novo -> ant = NULL;

        lst.primeiro = novo;
        lst.qnt++;
        return true;
    }

    else if (posicao == lst.qnt){//1
        Elemento <Tipo> *novo = new Elemento <Tipo>;

        novo -> dado = dado;
        novo -> prox = NULL;
        novo -> ant = lst.ultimo;

        lst.ultimo = novo;

        lst.qnt++;

        return true;
    }

    else{
        Elemento <Tipo> * navegador ;//1

       if(posicao < (lst.qnt/2) ){//1
            navegador = lst.primeiro;

            int i = 0;

            while (i < posicao){
                navegador = navegador -> prox;
                i++;
            }
        }

        else{
             navegador = lst.ultimo;//1

            int i = lst.qnt - 1;//1

            while (i > lst.qnt - posicao ){//n-p
                navegador = navegador -> ant;//n-p-1
                i--;
            }
        }

        Elemento <Tipo> * novo = new Elemento <Tipo>;//1

        novo -> dado = dado;//1
        novo -> prox = navegador;//1
        novo -> ant = navegador -> ant;//1
        novo -> ant -> prox = novo;//1
        novo -> prox -> ant = novo;//1

        lst.qnt++;

        return true;
    }
}

template <typename Tipo>
bool remover_posicao (Lista <Tipo> & lst, int posicao)
{
    if (posicao < 0 or posicao > lst.qnt or lst.primeiro == NULL){//3
        return false;
    }

    else if (posicao == 0){//1
        Elemento <Tipo> *aux = lst.primeiro;

        lst.primeiro = aux -> prox;
        delete aux;
        lst.qnt--;
        return true;
    }

    else if (posicao == lst.qnt - 1){//1
        Elemento <Tipo> * apagar = lst.ultimo;

        lst.ultimo = lst.ultimo -> ant;
        lst.qnt --;

        delete apagar;
        return true;
    }

    else{

        Elemento <Tipo> * apagar;//1

        if(posicao < (lst.qnt/2) ){//1
            apagar = lst.primeiro;

            int i = 0;

            while (i < posicao){
                apagar = apagar -> prox;
                i++;
            }
        }

        else{
             apagar = lst.ultimo;//1

            int i = lst.qnt - 1;//1

            while (i > lst.qnt - posicao ){//n - p + 1
                apagar = apagar -> ant;//n - p
                i--;
            }
        }

        apagar -> ant -> prox = apagar -> prox;//1
        apagar -> prox -> ant = apagar -> ant;//1

        delete apagar;//1
        lst.qnt--;

        return true;
    }

    return false;
}


template <typename Tipo>
void bubbleSort(Lista<Tipo> &lst, int n)
{
    Elemento<Tipo> *h;              // ------>   1
    int i, j;                      // ------>   1
    bool swapped;    // -> 1
    Tipo temp;            // ------>   1

    for (i = 0; i < n - 1; i++)    // ------>    1 + N + N - 1 = 2N
    {
        h = lst.primeiro;                 // ------>   1
        swapped = false;          // ------>   1

        for (j = 0; j < n - i - 1; j++)    // ------> ( N - 1 ) + ( X + 1 ) + X
        {

            Elemento<Tipo> *x = h;    // ------> N
            Elemento<Tipo> *y = x->prox;      // ------> N

            if (x->dado > y->dado)  // ------>  3X
            {
                swapped = true;
                temp = y -> dado;
                y -> dado = x->dado;
                x->dado = temp;
            }

            h = h->prox;                   // ------> N
        }

        if (swapped == false)                // ------> N
            break;
    }
}

template <typename Tipo>
Elemento<Tipo> partition(Elemento<Tipo> *c, Elemento<Tipo> *f)
{
    Elemento<Tipo> *pivot = f;
    Elemento<Tipo> *i = c -> ant;

    for (Elemento<Tipo> *ptr = c; ptr -> dado != f-> dado; ptr = ptr->prox)
    {
        if (ptr->dado <= pivot->dado)
        {
            i = (i == NULL ? c : i->prox);
            Tipo temp = i->dado;
            i->dado = ptr->dado;
            ptr->dado = temp;
        }
    }
    i = (i == NULL ? c : i->prox);
    Tipo temp = i->dado;
    i->dado = pivot->dado;
    pivot->dado = temp;
    return *i;
}

template <typename Tipo>
void QuickSort(Elemento<Tipo> *c, Elemento<Tipo> *f)
{
    if (f != NULL && c != f && c != f->prox)
    {
        Elemento<Tipo> p = partition(c, f);
        QuickSort(c, p.ant);
        QuickSort(p.prox, f);
    }
}
#endif // LISTA_DE_H_INCLUDED
