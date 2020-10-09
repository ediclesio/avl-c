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