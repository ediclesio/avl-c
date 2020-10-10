#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no
{
    int chave, bal;
    struct no *esq, *dir;
};

typedef struct no No;

void inicio_no(No **pt, int chave)
{
    (*pt) = malloc(sizeof(No));
    (*pt)->chave = chave;
    (*pt)->bal = 0;
    (*pt)->esq = (*pt)->dir = NULL;
}

void preordem(No *pt)
{
    printf("%d ", pt->chave);

    if (pt->esq != NULL)
        preordem(pt->esq);
    
    if (pt->dir != NULL)
        preordem(pt->dir);
}

void caso1(No **pt, bool *h)
{
    No *ptu = (*pt)->esq;
    
    if (ptu->bal == -1) {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        (*pt)->bal = 0;
        *pt = ptu;
    } else {
        
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = *pt;

        if (ptv->bal == -1) {
            (*pt)->bal = 1;
        } else {
            (*pt)->bal = 0;
        }

        if (ptv->bal == 1) {
            ptu->bal = -1;
        } else {
            ptu->bal = 0;
        }

        *pt = ptv;
    }
    
    (*pt)->bal = 0;
    *h = false;
}

void caso2(No **pt, bool *h)
{
    No *ptu = (*pt)->dir;
    
    if (ptu->bal == 1) {
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        (*pt)->bal = 0;
        *pt = ptu;
    } else {
        No *ptv = ptu->esq;
        
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = *pt;

        if (ptv->bal == 1) {
            (*pt)->bal = -1;
        } else {
            (*pt)->bal = 0;
        }

        if (ptv->bal == -1) {
            ptu->bal = 1;
        } else {
            ptu->bal = 0;
        }

        *pt = ptv;
    }

    (*pt)->bal = 0;
    *h = false;
}

void insAVL(int x, No **pt, bool *h)
{
    if (*pt == NULL) {
        criarNo(&(*pt), x);
        *h = true;
        
    } else {
        if (x == (*pt)->chave) {
            // printf("elemento já existe\n");
            *h = false;
            return;
        }

        if (x < (*pt)->chave) {
            
            insAVL(x, &(*pt)->esq, h);

            if (*h == true) {
                switch ((*pt)->bal) {
                    case 1:
                        (*pt)->bal = 0;
                        *h = false;
                        break;
                    case 0:
                        (*pt)->bal = -1;
                        break;
                    case -1:
                        caso1(pt, h);
                        break;
                }
            }
        } else {
            
            insAVL(x, &(*pt)->dir, h);

            if (*h == true) {
                switch ((*pt)->bal) {
                    case -1:
                        (*pt)->bal = 0;
                        *h = false;
                        break;
                    case 0:
                        (*pt)->bal = 1;
                        break;
                    case 1:
                        caso2(pt, h);
                        break;
                }
            }
        }
    }
}

void caso1R(No **pt, bool *h)
{
    No *ptu = (*pt)->esq;

    if (ptu != NULL && ptu->bal <= 0) {
        (*pt)->esq = ptu->dir;
        ptu->dir = *pt;
        *pt = ptu;
        
        if (ptu->bal == -1) {
            ptu->bal = (*pt)->dir->bal = 0;
            *h = true;
        } else {
            
            ptu->bal = 1;
            (*pt)->dir->bal = -1;
            *h = false;
        }
    } else {
        No *ptu, *ptv;
    
        ptu = (*pt)->esq;
        ptv = ptu->dir;
        ptu->dir = ptv->esq;
        (*pt)->esq = ptv->dir;
        ptv->esq = ptu;
        ptv->dir = *pt;
        *pt = ptv;
        
        switch (ptv->bal) {
            case -1:
                ptu->bal = 0;
                (*pt)->dir->bal = 1;
                break;
            case 0:
                ptu->bal = 0;
                (*pt)->dir->bal = 0;
                break;
            case 1:
                ptu->bal = -1;
                (*pt)->dir->bal = 0;
                break;
        }

        (*pt)->bal = 0;
        *h = true;
    }
}

void caso2R(No **pt, bool *h)
{
    No *ptu = (*pt)->dir;

    if (ptu != NULL && ptu->bal >= 0) {

        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        *pt = ptu;
        
        if (ptu->bal == 1) {
            ptu->bal = (*pt)->esq->bal = 0;
            *h = true;
        } else {
            
            ptu->bal = -1;
            (*pt)->esq->bal = 1;
            *h = false;
        }

    } else {

        No *ptu, *ptv;
    
        ptu = (*pt)->dir;
        ptv = ptu->esq;
        ptu->esq = ptv->dir;
        (*pt)->dir = ptv->esq;
        ptv->dir = ptu;
        ptv->esq = *pt;
        *pt = ptv;

        switch (ptv->bal) {
            case -1:
                ptu->bal = 1;
                (*pt)->esq->bal = 0;
                break;
            case 0:
                ptu->bal = 0;
                (*pt)->esq->bal = 0;
                break;
            case 1:
                ptu->bal = 0;
                (*pt)->esq->bal = -1;
                break;
        }

        (*pt)->bal = 0;
        *h = true;
    }
}

void balancear(No **pt, char r, bool *h)
{
    if (*h == true) {
        if (r == 'D') {
            switch ((*pt)->bal) {
                case 1:
                    (*pt)->bal = 0;
                    break;
                case 0:
                    (*pt)->bal = -1;
                    *h = false;
                    break;
                case -1:
                    caso1R(&(*pt), h);
                    break;
            }
        } else {
            switch ((*pt)->bal) {
                case -1:
                    (*pt)->bal = 0;
                    break;
                case 0:
                    (*pt)->bal = 1;
                    *h = false;
                    break;
                case 1:
                    caso2R(&(*pt), h);
                    break;
            }
        }
    }
}

void remAVL(int x, No **pt, bool *h)
{
    if (*pt == NULL) {
        return;
    }

    if (x < (*pt)->chave) {
        remAVL(x, &(*pt)->esq, h);
        balancear(&(*pt), 'E', h);
    
    } else {
        if (x > (*pt)->chave) {
            remAVL(x, &(*pt)->dir, h);
            balancear(&(*pt), 'D', h);
        
        } else {
            No *aux = *pt;

            if ((*pt)->esq == NULL) {
                *pt = (*pt)->dir;
                *h = true;
                free(aux);
            } else {
                
                if ((*pt)->dir == NULL) {
                    *pt = (*pt)->esq;
                    *h = true;
                    free(aux);
                } else {
                    
                    No *s = (*pt)->dir;

                    if (s->esq == NULL) {
                        s->esq = (*pt)->esq;
                        s->bal = (*pt)->bal;
                        *pt = s;
                        *h = true;
                    } else {
                        
                        No *paiS = s;

                        while (s->esq != NULL) {
                            paiS = s;
                            s = s->esq;
                        }
                        No *temp = s->dir;
                        s->esq = (*pt)->esq;
                        s->dir = (*pt)->dir;
                        s->bal = (*pt)->bal;
                        paiS->esq = *pt;
                        (*pt)->dir = temp;
                        (*pt)->esq = NULL;
                        
                        temp = *pt;
                        *pt = s;
                        s = temp;

                        *h = true;
                        remAVL(x, &(*pt)->dir, h);
                    }
                    
                    balancear(&(*pt), 'D', h);
                    
                }
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    int i, c, f, x, AVLs = 10, lenIns = 10000, lenRem = 1000;
    bool h, b;
    No *ptraiz[1000], *pt;


    for (i = 0; i < AVLs; i++) {
        ptraiz[i] = NULL;
        
        b = true;
        c = 0;

        while(c < lenIns) {
            h = false;
            x = rand() % 100000;
            insAVL(x, &ptraiz[i], &h);

            c = contarNos(ptraiz[i]);
        }

        printf("AVL[%d] tem %d nós após inserir as chaves\n", i, c);

        verificarBals(ptraiz[i], &b);

        if (b == true) printf("Continua AVL\n");
        else {
            printf("Não continua AVL\n"); 
            return 0;
        }
        
        c = 0;

        while(c < lenRem) {
            x = rand() % 100000;
            h = false;
            f = -1;
            pt = ptraiz[i];
            buscar(x, &pt, &f);
            
            if (f == 1){
                remAVL(x, &ptraiz[i], &h);
                c++;
            }
        }
        
        c = contarNos(ptraiz[i]);

        printf("AVL[%d] tem %d nós após as %d remoções\n", i, c, lenRem);

        b = true;
        verificarBals(ptraiz[i], &b);

        if (b == true) printf("Continua AVL\n\n");
        else printf("Não continua AVL\n\n");
        
    }

    return 0;
}