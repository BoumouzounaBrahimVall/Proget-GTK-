//
// Created by Brahim Vall on 4/18/22.
//

#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int x;
    int y;
}coordonees;

typedef struct cel
{
    coordonees val;
    struct cel *suivant;
}cellulePliste;



cellulePliste *creer_cellulePliste(coordonees elem)
{
    cellulePliste *ne;
    ne=(cellulePliste*)malloc(sizeof(cellulePliste));
    if(!ne)
    {
        printf("\nerreur d'allocation");
        exit(-1);
    }
    ne->val=elem;
    ne->suivant=NULL;
    return ((cellulePliste*)ne);
}

cellulePliste*supprimerelemcellulePliste(cellulePliste*L,coordonees Elem)
{
    cellulePliste*tmp,*elemsupp;
    if(!L) return((cellulePliste*)NULL);
    tmp=L;
    if((L->val.x==Elem.x)&&(L->val.y==Elem.y))//suppression en tete
    {
        elemsupp=L;
        L=L->suivant;
        //free(elemsupp);
        return((cellulePliste*)L);
    }
    else
    {
        while(tmp)
        {
            if(tmp->suivant)
            {
                if((tmp->suivant->val.x==Elem.x)&&(tmp->suivant->val.y==Elem.y))
                {
                    elemsupp=tmp->suivant;
                    tmp->suivant=elemsupp->suivant;
                    //free(elemsupp);
                    return((cellulePliste*)L);
                }
            }
            tmp=tmp->suivant;
        }
    }
    return((cellulePliste*)L);

}



int nombreocccellulePliste(cellulePliste *L,coordonees valeur)
{
    cellulePliste *crt=L;
    int repet=0;
    while(crt){
        if((crt->val.x==valeur.x)&&(crt->val.y==valeur.y)) repet++;
        crt=crt->suivant;
    }
    return repet;//nombre d’occurrence retourne
}



cellulePliste* supprimerocccellulePliste(cellulePliste*L)
{
    cellulePliste*crt1;
    crt1=L;
    if(!L)
    {
        printf("la liste n'existe pas");
        return ((cellulePliste*)NULL);
    }

    while(crt1->suivant)
    {
        if(nombreocccellulePliste(L,crt1->val)>1)
        {
            L=supprimerelemcellulePliste(L,crt1->val);
        }
        crt1=crt1->suivant;
    }
    return((cellulePliste*)L);
}

cellulePliste *InsererTetePListe(cellulePliste *Pliste , coordonees Elem)
{
    cellulePliste *NE;
    NE = creer_cellulePliste(Elem);
    NE->suivant= Pliste;
    return ((cellulePliste*)NE);
}

void afficher_pliste(cellulePliste *maliste)
{
    cellulePliste *courant;
    if(!maliste) printf("la liste n'existe pas");
    else{
        courant=maliste;
        while (courant)
        {
            printf("\n    l'abscisse:%d, et l'ordonnée:%d   ",courant->val.x,courant->val.y );
            courant = courant->suivant;
        }
    }
}

cellulePliste *listeEntour(int surface[60][60],int pas,coordonees elem)
{
    cellulePliste *Liste=NULL;
    int i,j;
    coordonees k={0,0};
    if(elem.x>59||elem.y>59||elem.x<0||elem.y<0) return NULL;
    for(i=1;i<=pas;i++)
    {
        if(elem.x+i<=59)
        {
            if((surface[elem.x+i][elem.y])==1)
            {
                k.x=elem.x+i;
                k.y=elem.y;
                Liste=InsererTetePListe(Liste,k);
            }
            for(j=1;j<=pas;j++){
                if(elem.y+j<=59)
                {
                    if(surface[elem.x+i][elem.y+j]==1)
                    {
                        k.x=elem.x+i;
                        k.y=elem.y+j;
                        Liste=InsererTetePListe(Liste,k);
                    }
                }
            }
            for(j=1;j<=pas;j++)
            {
                if(elem.y-j>=0)
                {
                    {
                        if(surface[elem.x+i][elem.y-j]==1)
                        {
                            k.x=elem.x+i;
                            k.y=elem.y-j;
                            Liste=InsererTetePListe(Liste,k);
                        }
                    }
                }
            }
        }

        if(elem.x-i>=0)
        {
            if(surface[elem.x-i][elem.y]==1)
            {
                k.x=elem.x-i;
                k.y=elem.y;
                Liste=InsererTetePListe(Liste,k);
            }
            for(j=1;j<=pas;j++){
                if(elem.y-j>=0)
                {
                    if(surface[elem.x-i][elem.y-j]==1)
                    {
                        k.x=elem.x-i;
                        k.y=elem.y-i;
                        Liste=InsererTetePListe(Liste,k);
                    }
                }
                if(elem.y+j<=59)
                {
                    if(surface[elem.x-i][elem.y+j]==1)
                    {
                        k.x=elem.x-i;
                        k.y=elem.y+j;
                    }
                }
            }
        }

        if(elem.y+i<=59)
        {
            if(surface[elem.x][elem.y+i]==1)
            {
                k.x=elem.x;
                k.y=elem.y+i;
                Liste=InsererTetePListe(Liste,k);
            }
            for(j=1;j<=pas;j++){
                if(elem.x-j>=0)
                {
                    if(surface[elem.x-j][elem.y+i]==1)
                    {
                        k.x=elem.x-j;
                        k.y=elem.y+i;
                        Liste=InsererTetePListe(Liste,k);
                    }

                }
            }
        }
        if(elem.y-i>=0)
        {
            if(surface[elem.x][elem.y-i]==1)
            {
                k.x=elem.x;
                k.y=elem.y-i;
                Liste=InsererTetePListe(Liste,k);
            }
            for(j=1;j<=pas;j++)
            {
                if(elem.x+j<=59)
                {
                    if(surface[elem.x+j][elem.y-i]==1)
                    {
                        k.x=elem.x+j;
                        k.y=elem.y-i;
                        Liste=InsererTetePListe(Liste,k);
                    }
                }

                if(elem.x-j>=0)
                {
                    if(surface[elem.x-j][elem.y-i]==1)
                    {
                        k.x=elem.x-j;
                        k.y=elem.y-i;

                        Liste=InsererTetePListe(Liste,k);
                    }
                }
            }
        }
    }
    Liste=supprimerocccellulePliste(Liste);
    return ((cellulePliste*)Liste);
}