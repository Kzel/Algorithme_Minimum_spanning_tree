#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
#include<map> 
#include<vector>
#include<time.h>
#define INF 0x3f3f3f3f
#define Max 999
using namespace std;

// nombre de sommet, nombre d'arret, copoidsteur, poids minimal par Prim
int nb_sommet,nb_arret,cpt,poids_mini;

// la structure d'arret avec le sommet u et v , le poids w
struct arret
{
    int u,v,w;
} Arbre[Max];

int poids[Max][Max],dist[Max],visite[Max];
int sortie[Max],entree[Max];
int deja_visite[Max][Max],precedent[Max]; //les arrets qui sont deja visités, les sommets precedents
        
// Afficher les arbres minimaux
void print(int n)           
{ 
    printf("\nLe %de arbre minimum:\n",cpt++);
    for(int j=0;j<n;j++)
        for(int i=0;i<=j;i++)
        {
            if(i==j)
                printf("Le sommet %d -> %d avec poids %d, \n",sortie[i],entree[i],poids[sortie[i]][entree[i]]);
            else 
                printf("Le sommet %d -> %d avec poids %d, ",sortie[i],entree[i],poids[sortie[i]][entree[i]]);
        }
}

// param: u est le sommet initial, s est le status
int prim(int u,int s)
{
    //Initialiser le tableau de balises pour éviter la boucle du arbre
    memset(visite,0,sizeof(visite)); 

    int resultat=0,nn=0;

    //Prenez le sommet u comme point initial et retirez les poids de toutes ses arêtes associées
    for(int i=1;i<=nb_sommet;i++) 
    {
        if(deja_visite[u][i]==s) 
            dist[i]=poids[u][i];  
       
        else 
            dist[i]=INF;//les autres arrets
        precedent[i]=u;
    }
    visite[u]=1; //Marquer que le sommet initial u a été visité pour éviter la boucle du arbre
    
    //Traverser tous les sommets
    for(int i=1;i<=nb_sommet-1;i++)
    {
        //Trouvez le point correspondant à la plus petite arête
        int minn=INF;
        for(int j=1;j<=nb_sommet;j++)
        {
            if(dist[j]<minn&&visite[j]==0)
            {
                minn=dist[j];
                u=j;
            }
        }

        if(minn==INF) return -1;
        visite[u]=1;
        resultat+=dist[u];
        sortie[nn]=precedent[u];
        entree[nn++]=u;

        //Retirez le poids de l'arête correspondant au sommet
        for(int k=1;k<=nb_sommet;k++)
        {
            if(poids[u][k]<dist[k]&&visite[k]==0&&deja_visite[u][k]==s)
            {
                dist[k]=poids[u][k];
                precedent[k]=u;
            }
        }
    }
    return resultat;
}

// Initialisation
void init(){
           
    memset(deja_visite,0,sizeof(deja_visite));
    for(int i=0;i<=nb_sommet;i++)
    {
        for(int j=0;j<=nb_sommet;j++)
        {
            if(i==j) poids[i][j]=0;
            else poids[i][j]=poids[j][i]=INF;
        }
    }
}

//param: l'arret qui est choisi dans l'arbre present et il y a combien d'arret et poids dans l'arbre present
void dfs(int top,int x,int resultat)
{
    if(resultat>poids_mini||x>=nb_sommet) return;
    if(top==nb_arret)
    {
        if(x==nb_sommet-1&&resultat==poids_mini)
        {
            int cpt2=prim(1,1);
            // si les poids sont egaux, retourner n-1 arrets
            if(cpt2==poids_mini)  print(nb_sommet-1);
        }
        return; 
    }

    arret cpt=Arbre[top];

    deja_visite[cpt.u][cpt.v]=deja_visite[cpt.v][cpt.u]=1;// Choisir cet arret entres les sommets
    dfs(top+1,x+1,resultat+cpt.w);

    deja_visite[cpt.u][cpt.v]=deja_visite[cpt.v][cpt.u]=0;// Ne pas remarquer cet arret
    dfs(top+1,x,resultat);//Ne choisir pas cet arret

}

int main(){
    printf("Taper le nombre du sommet et d'arret \n");

    clock_t temp1,temp2,temp3,temp4;

    while(~scanf("%d%d",&nb_sommet,&nb_arret)){
        
        init();
        int u,v,w;

        printf("Taper les points u et v,puis le poids de cet arret\n");

        for(int i=0; i<nb_arret; i++)
        {

            scanf("%d%d%d",&u,&v,&w);
            if(w<poids[u][v]) poids[u][v]=poids[v][u]=w;
            Arbre[i].u=u;
            Arbre[i].v=v;
            Arbre[i].w=w;
        }

        cpt=1;

        temp1=clock();
        poids_mini=prim(1,0);
        temp2=clock();

        printf("Le poids minimal(somme de w) est %d\n",poids_mini);
        printf("Le temps de Prim est %f ms\n",(float)(temp2-temp1)*1000/CLOCKS_PER_SEC);

        if(poids_mini==-1) 
            printf("Il n'y a pas d'arbre minimal, retaper\n");
            else 
                temp3=clock();
                dfs(0,0,0); 
                temp4=clock();
                printf("Le temps de DFS est %f ms\n",(float)(temp2-temp1)*1000/CLOCKS_PER_SEC);
    }
    return 0;
}
