#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct produit
{
	int code;
	char des[20];
	float prix;
	int qt;
};

void ajout();
void affiche();
void suppression(int);
void modification(int);
int recherche(int);
void consultation(int);
void main()
{
	int choix;
	char rep;
	int code_cons;
	int code_modif;
	int code_supp;
	do
    {
	printf("1: ajout d'un produit\n");
	printf("2: affichage de la liste des produits\n");
	printf("3: suppression d'un produit\n");
	printf("4: modification d'un produit\n ");
	printf("5: consultation d'un produit\n");
	printf("7: quitter\n");

	printf("Entrer votre choix \n");
	scanf("%d", &choix);
	system("cls");
	switch(choix)
	{
		case 1:
			ajout();
			break;
		case 2:
			affiche();
			break;
		case 3:
		    printf("donner le code du produit à supprimer\n");
            scanf("%d",&code_supp);
            suppression(code_supp);
			break;
		case 4:
		    printf("donner le code du produit à modifier\n");
            scanf("%d",&code_modif);
            modification(code_modif);
			break;
		case 5:
			printf("donner le code du produit à consulter\n");
            scanf("%d",&code_cons);
            consultation(code_cons);
            break;
        case 7:
            exit(0);
			break;
	    default:
            printf("Choix incorrect\n");
	}
	fflush(stdin);
	//printf("autre opération");
	//scanf("%c",&rep);
    }while (choix !=7); //(rep=='o');
}
void ajout()
{

	FILE *f;
	struct produit p,q;
    f=fopen("prod.txt","a+");

    if (f ==NULL)
        printf("erreur d'ouverture");
    else
    {
        if(fscanf(f,"%d %s %f %d", &q.code, q.des, &q.prix, &q.qt)==EOF)
        p.code=1;
        else
        {
            while(!feof(f))
                fscanf(f,"%d %s %f %d", &q.code, q.des, &q.prix, &q.qt);
            p.code=q.code+1;
        }
        fflush(stdin);
        printf("donner la designation");
        gets(p.des);
        do
        {
            printf("donner le prix");
            scanf("%f",&p.prix);
        }while(p.prix<100 || p.prix>10000);
        do
        {
            printf("donner la quantité");
            scanf("%d",&p.qt);
        }while(p.qt<1);
        fprintf(f,"%d %s %f %d\n",p.code,p.des,p.prix,p.qt );
        fclose(f);
    }
}
void affiche()
{
    FILE *f;
    struct produit p;
    int res;
    f=fopen("prod.txt","r");
    if(f==NULL)
         printf("erreur d'ouverture");
    else
    {
        while (!feof(f))
            {
                res=fscanf(f,"%d %s %f %d", &p.code, p.des, &p.prix, &p.qt);
                if (res != -1)//moin 1: valeur de   EOF
                    printf("%d %s %f %d\n", p.code, p.des, p.prix, p.qt);
            }
        fclose(f);
    }

}
int recherche(int code_rech)
{

	FILE *f;
	int existe;
	struct produit p;
	existe=0;
	f=fopen("prod.txt","r");
	if(f==NULL)
        printf("erreur d'ouverture");
    else
    {
        while (!feof(f) && existe==0)
        {
            fscanf(f,"%d %s %f %d", &p.code, p.des, &p.prix, &p.qt);
                if(p.code==code_rech)
                    existe=1;
        }
        fclose(f);
    }
	if(existe==0)
        return 0;
	else
        return 1;
}
void suppression(int code_supp)
{
    int rep;
    int res;
    FILE *f;
    FILE *ft;
    struct produit p;
    if(recherche(code_supp)==1)
    {
        printf("voule vous vraiment supprimer ce produit 1: oui et 0: non");
        scanf("%d",&rep);
        if(rep==1)
        {
            f=fopen("prod.txt","r");
            if(f==NULL)
                printf("erreur d'ouverture du fichier prod");
            else
            {
                ft=fopen("temp_prod.txt","w");
                if(ft==NULL)
                    printf("erreur d'ouverture du fichier temporaire");
                else
                {
                    while (!feof(f))
                    {
                        res=fscanf(f,"%d %s %f %d", &p.code, p.des, &p.prix, &p.qt);
                        if(p.code!=code_supp && res!=-1)
                            fprintf(ft,"%d %s %f %d\n", p.code, p.des, p.prix, p.qt);
                    }
                    fclose(f);
                    fclose(ft);
                }
			}
			remove("prod.txt");
            rename("temp_prod.txt","prod.txt");
        }
    }
    else
        printf("produit inexistant");

}
void modification(int code_modif)
{
	FILE *f;
	FILE *ft;
	int rep;
	int res;
	struct produit p;
	char n_des[20];
	float n_prix;
	int n_qt;

	if(recherche(code_modif)==1)
    {
        printf("voule vous vraiment modifier ce produit 1: oui et 0: non");
        scanf("%d",&rep);
        if(rep==1)
        {
            f=fopen("prod.txt","r");
            if(f==NULL)
                printf("erreur d'ouverture du fichier prod");
            else
            {
                ft=fopen("temp_prod.txt","w");
                if(ft==NULL)
                    printf("erreur d'ouverture du fichier temporaire");
                else
                {
                    while (!feof(f))
                    {
                        res = fscanf(f,"%d %s %f %d", &p.code, p.des, &p.prix, &p.qt);
                        if (res!=-1)
                        {if(p.code!=code_modif )
                            fprintf(ft,"%d %s %f %d\n", p.code, p.des, p.prix, p.qt);
                        else
                        {
                            fflush(stdin);
                            printf("donner la nouvelle désignation");
                            gets(n_des);
                            printf("donner le nouveau prix");
                            scanf("%f",&n_prix);
                            printf("donner la nouvelle quantité");
                            scanf("%d",&n_qt);
                            fprintf(ft,"%d %s %f %d\n",code_modif,n_des,n_prix,n_qt);
                        }}
                    }
                }
			fclose(f);
			fclose(ft);
			remove("prod.txt");
			rename("temp_prod.txt","prod.txt");
            }
        }
    }
    else
        printf("produit inexistant");

}
void consultation(int code_cons)
{
	FILE *f;
	int existe;
	struct produit p;
	existe=0;
	f=fopen("prod.txt","r");
    if(f==NULL)
        printf("erreur d'ouverture du fichier prod");
    else
    {
        while (!feof(f) && existe==0)
        {
            fscanf(f,"%d %s %f %d", &p.code, p.des, &p.prix, &p.qt);
            if(p.code==code_cons)
                existe=1;
        }
    }
	if(existe==0)
        printf("produit inexistant\n");
	else
        printf("voici les informations du produit recherché: code=%d designation =%s prix=%f quantité=%d",p.code,p.des,p.prix,p.qt);

    fclose(f);

}
