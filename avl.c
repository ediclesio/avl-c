#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct no
{
    int chave, bal;
    struct no *esq, *dir;
};

typedef struct no No;

void criarNo(No *pt, int chave)
{
    pt = malloc(sizeof(No));
    pt->chave = chave;
    pt->bal = 0;
    pt->esq = pt->dir = NULL;
}

void preordem(No *pt)
{
    printf("%d(%d) ", pt->chave, pt->bal);

    if (pt->esq != NULL)
        preordem(pt->esq);
    
    if (pt->dir != NULL)
        preordem(pt->dir);
}

void buscar(int x, No **pt, int *f)
{
    if ((*pt) == NULL) {
        *f = 0;
    } else {
        if (x == (*pt)->chave) {
            *f = 1;
        } else {
            if (x < (*pt)->chave) {
                if ((*pt)->esq == NULL) {
                    *f = 2;
                } else {
                    (*pt) = (*pt)->esq;
                    buscar(x, pt, f);
                }
            } else {
                if ((*pt)->dir == NULL) {
                    *f = 3;
                } else {
                    (*pt) = (*pt)->dir;
                    buscar(x, pt, f);
                }
            }
        }
    }
}

void caso1(No **pt, bool *h)
{
    No *ptu = (*pt)->esq;
    
    if (ptu->bal == -1) {
        (*pt)->esq = ptu->dir;
        ptu->dir = (*pt);
        (*pt)->bal = 0;
        (*pt) = ptu;
    } else {
        
        No *ptv = ptu->dir;
        ptu->dir = ptv->esq;
        ptv->esq = ptu;
        (*pt)->esq = ptv->dir;
        ptv->dir = (*pt);

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
        // printf("[%d]\n", (*pt)->chave);
        (*pt)->dir = ptu->esq;
        ptu->esq = *pt;
        (*pt)->bal = 0;
        *pt = ptu;
    } else {
        No *ptv = ptu->esq;
        
        ptu->esq = ptv->dir;
        ptv->dir = ptu;
        (*pt)->dir = ptv->esq;
        ptv->esq = (*pt);

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
        No *novo = malloc(sizeof(No));
        novo->chave = x;
        novo->bal = 0;
        novo->esq = novo->dir = NULL;
        *pt = novo;
        *h = true;
    } else {
        if (x == (*pt)->chave) {
            printf("elemento já existe\n");
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
                        // printf("(%d) x: %d\n", (*pt)->chave, x);
                        break;
                    case 1:
                        caso2(pt, h);
                        break;
                }
            }
        }
    }
}

int main()
{
    bool h = false;
    No *ptraiz = NULL;
    
    insAVL(8, &ptraiz, &h);
    insAVL(5, &ptraiz, &h);
    insAVL(7, &ptraiz, &h);
    
    if (ptraiz != NULL)
        preordem(ptraiz);
    puts("");

    insAVL(4, &ptraiz, &h);
    insAVL(12, &ptraiz, &h);
    insAVL(14, &ptraiz, &h);

    preordem(ptraiz);
    puts("");

    insAVL(10, &ptraiz, &h);
    insAVL(9, &ptraiz, &h);

    preordem(ptraiz);
    puts("");

    insAVL(3, &ptraiz, &h);
    insAVL(6, &ptraiz, &h);

    preordem(ptraiz);
    puts("");

    insAVL(11, &ptraiz, &h);

    preordem(ptraiz);
    puts("");

    insAVL(13, &ptraiz, &h);

    preordem(ptraiz);
    puts("");

    return 0;
}