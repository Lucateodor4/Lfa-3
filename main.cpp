#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

struct NodNeterminal
{
    char cuvant[10];
    int nrAlternative;
    char alternative[5][10];
};

struct Gramatica
{
    int nrNeterminale;
    int nrTerminale;
    char Terminale[5][10];
    NodNeterminal Neterminale[5];

}G;

bool CFG(Gramatica G,char *cuvant,char *cuvFunctie){
    bool apartine = false;
    char auxiliar[30],auxiliar2[10],auxiliar3[15];
    strcpy(auxiliar3,cuvFunctie);
    if(strcmp (cuvant,cuvFunctie)==0)
    {
        apartine=true;
    }
    if( (strlen(cuvFunctie)<=strlen(cuvant)+1 ) && !apartine)
    {
        if(cuvFunctie[0]=='0')
        {
            for(int i=0;i<G.nrNeterminale && !apartine;i++)
            {
                for(int j=0;j<G.Neterminale[i].nrAlternative && !apartine ;j++)
                {
                    apartine=CFG(G,cuvant,G.Neterminale[i].alternative[j]);
                }
            }
        }
        else{
            bool gasit=false;
            for(int i=0;i<strlen(cuvFunctie);i++)
            {
                if( isupper(cuvFunctie[i]) )
                {
                    for(int j=0;j<G.nrNeterminale && !apartine ;j++)
                    {
                        strcpy(auxiliar3,cuvFunctie);
                        if(G.Neterminale[j].cuvant[0]==cuvFunctie[i])
                        {
                            gasit=true;
                            strncpy(auxiliar2,cuvFunctie,i);
                            auxiliar2[i]='\0';
                            strcpy(auxiliar3,cuvFunctie+i+1);
                            for(int k=0;k<G.Neterminale[j].nrAlternative && !apartine ;k++)
                            {
                                strcpy(auxiliar,auxiliar2);
                                if(G.Neterminale[j].alternative[k][0]=='x')
                                {
                                    strcat(auxiliar,auxiliar3);
                                    apartine=CFG(G,cuvant,auxiliar);
                                }
                                else
                                {
                                    strcat(auxiliar,G.Neterminale[j].alternative[k]);
                                    strcat(auxiliar,auxiliar3);
                                    apartine=CFG(G,cuvant,auxiliar);
                                }
                            }
                        }
                    }
                }
                if(gasit)
                {
                    break;
                }
            }
        }
    }
    return apartine;
}

int main()
{
    fstream f("Date.txt");
    bool apartenenta;
    string auxiliar;
    char cuvant[10];
    char cuvFunctie[10]="0";
    f>>G.nrNeterminale;
    f>>G.nrTerminale;
    getline(f,auxiliar);
    cout<<"Terminalele:"<<endl;
    for(int i=0;i<G.nrTerminale;i++)
    {
        getline(f,auxiliar);
        strcpy(G.Terminale[i],auxiliar.c_str());
        cout<<G.Terminale[i]<<endl;
    }
    cout<<"Neterminalele cu ramurile lor:"<<endl;
    for(int i=0;i<G.nrNeterminale;i++)
    {
        getline(f,auxiliar);
        strcpy(G.Neterminale[i].cuvant,auxiliar.c_str());
        cout<<G.Neterminale[i].cuvant<<endl;
        f>>G.Neterminale[i].nrAlternative;
        getline(f,auxiliar);
        for(int j=0;j<G.Neterminale[i].nrAlternative;j++)
        {
            getline(f,auxiliar);
            strcpy(G.Neterminale[i].alternative[j],auxiliar.c_str());
            cout<<G.Neterminale[i].alternative[j]<<" ";
        }
        cout<<endl;
    }
    getline(f,auxiliar);
    strcpy(cuvant,auxiliar.c_str());
    cout<<"Cuvantul ce va fi testat: "<<cuvant<<endl;
    apartenenta=CFG(G,cuvant,cuvFunctie);
    if(!apartenenta)
    {
        cout<<"Cuvantul nu apartine";

    }
    else
    {
        cout<<"Cuvantul apartine";
    }

    return 0;
}