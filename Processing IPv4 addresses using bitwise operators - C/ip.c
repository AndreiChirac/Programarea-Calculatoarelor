#include <stdio.h>
int constructiemasca(int msk){   //functie pe care o voi apela cand am nevoie sa imi construiesc o masca
    unsigned int constructie=0,b=((sizeof(int)*8-1)-msk);    
    for(unsigned int i=sizeof(int)*8-1;i>b;i--)
    constructie=((constructie)|(1<<i));
    return constructie;
}
int msk2tozecimal(int msk){ //functia care imi transforma un numar intr-o masca cu octetii zecimali  
    unsigned int m1=255;    
    for(int i=3;i>=0;i--){
    if(i>0)    
    printf("%d.",((constructiemasca(msk)>>(i*8))&m1));//Se sifteaza la dreapta pentru a avea doar cele 8 pozitii care ne trbuie de comparat
    else
    printf("%d \n",((constructiemasca(msk)>>(i*8))&m1));
    }
return 0;
} 
int adresaderetea( unsigned int ip ,int msk){ 
    unsigned int construct=0,m1=255;    
    construct=constructiemasca(msk);    
    for(int i=3;i>=0;i--){
    if(i>0)    
    printf("%d.",((((construct>>(i*8))&(ip>>(i*8))))&m1));//Se realizeaza operatia de si logic intre masca ip si m1 astfel incat sa pot  afisa direct  
    else
    printf("%d \n",((((construct>>(i*8))&(ip>>(i*8))))&m1));
    }
    return 0;        
}
int adresadebroadcast(unsigned int ip ,int msk){
    unsigned int constructcompl=0,m1=255;    
    constructcompl=constructcompl|~(constructiemasca(msk));    
    for(int i=3;i>=0;i--){
    if(i>0)    
    printf("%d.",((((constructcompl>>(i*8))|(ip>>(i*8))))&m1));//Se realizeaza operatia de sau logic intre masca si ip si relatia de si logic cu m1 astfel incat sa pot afisa direct
    else
    printf("%d \n",((((constructcompl>>(i*8))|(ip>>(i*8))))&m1));
    }
    return 0;
}
int comparareadrese(unsigned int ip_1, unsigned int ip_2 ,int msk){ 
    if((constructiemasca(msk)&ip_1)==(constructiemasca(msk)&ip_2)) // Se realizeaza compararea intre cele doua adrese oferite carora li se aplica masca de retea , se compara adresele de restea 
    printf("DA \n");//Fac parte din aceeasi adresa 
    else
    printf("NU \n");//Nu fac parte din aceeasi adresa
    return 0;
}
int corectitudine(unsigned int msk_1){//Se parcurge seria de biti pana la succesiuea lui 0 de 1 unde valoarea variabilei seafor se schimba, prin valoarea acesteia vom sti daca masca este corecta sau nu      
    unsigned int ok=1;    
    for(int i=sizeof(int)*8-1;i>0;i--)
    if(((((msk_1)&(1<<i))?1:0)==0) && ((((msk_1)&(1<<(i-1)))?1:0)==1))
    {
    ok=0;
    break;
    }    
    return ok;
}
int pozitie0(unsigned int msk_1){    //Se parcurge seria de biti pana la succesiuea lui 0 de 1 astfel vaiabila b imi va afla pozitia primei aparitii de acest tip 
    int b;    
    for(int i=sizeof(int)*8-1;i>0;i--)
    if(((((msk_1)&(1<<i))?1:0)==0) && ((((msk_1)&(1<<(i-1)))?1:0)==1)){
    b=i;
    break;
    }    
    return b;
}
int corectare(unsigned int msk){   
    int m1=255;    
    if(corectitudine(msk)==1) // Daca masca a fost corecta aceasta va fi afsata 
    for(int i=3;i>=0;i--){
    if(i>0)    
    printf("%d.",((msk>>(i*8))&m1));
    else
    printf("%d \n",((msk>>(i*8))&m1));
    }
    else{ // In cazul in care masca a fost gresita se modifica 
    for(int i=pozitie0(msk)-1;i>=0;i--) // de lavaloarea primei aparitii si pana la final se modifica cu 0          
    msk=(msk&~(1<<i));
    for(int i=3;i>=0;i--){
    if(i>0)    
    printf("%d.",((msk>>(i*8))&m1));
    else
    printf("%d \n",((msk>>(i*8))&m1));
    }
    }
return 0;
}
int reprezentbinarip(unsigned int ip){ //Se afla bitul (get the bit) de pe fiecare pozitie si se afiseaza
    for(int i=sizeof(int)*8-1;i>=0;i--){
    printf("%d",((ip&(1<<i))?1:0));
    if(i%8==0 && i>0)// Daca au fost parcurese 8 pozitii si nu ne aflam pe ultima punem si . pentru a separa octetii
    printf(".");}
    printf("\n");
return 0;
}
int constructie(unsigned int ip ,int msk){ //Se aplica masca pe ip , se realizeaza adresa de retea 
    unsigned int construct=0,ip_msk;    
    construct=constructiemasca(msk);
    ip_msk=((construct)&(ip));
    return ip_msk;
}
int gasirecompatibilitate(unsigned int ip_2,unsigned int ip_3 ,int msk_3){
    if(constructie(ip_2,msk_3)==constructie(ip_3,msk_3))// Se verifica daca cele dou retele fac parte din aceeasi retea
    return 1;
    else
    return 0;    
}
    int main (){
    int nrseturi,N;
    unsigned int msk1,msk2,msk3,ip1,ip2,ip3;
    unsigned int msk1a,msk1b,msk1c,msk1d;
    unsigned int ip1a,ip1b,ip1c,ip1d;     
    unsigned int ip2a,ip2b,ip2c,ip2d;    
    unsigned int ip3v[1000]={0};
    unsigned int msk3v[1000]={0};    
    unsigned int ip3a,ip3b,ip3c,ip3d;     
    scanf("%d",&nrseturi); // Se citeste numarul de seturi
    for(int i=1;i<=nrseturi;i++){
    scanf("%d.%d.%d.%d",&msk1a,&msk1b,&msk1c,&msk1d);// Se citeste prima masca
    msk1=((msk1a<<24)+(msk1b<<16)+(msk1c<<8)+msk1d);//Se configureaza masca pentru a avea o insiruire de biti 
    scanf("%d",&msk2);//Se citeste a doua masca
    scanf("%d.%d.%d.%d",&ip1a,&ip1b,&ip1c,&ip1d);//Se citeste primul ip 
    ip1=((ip1a<<24)+(ip1b<<16)+(ip1c<<8)+ip1d);//Se configureaza ip-ul pentru a fi doar o insiruire de biti
    scanf("%d.%d.%d.%d",&ip2a,&ip2b,&ip2c,&ip2d);
    ip2=((ip2a<<24)+(ip2b<<16)+(ip2c<<8)+ip2d);
    scanf("%d",&N);//Se citeste numarul de adrese    
    for(int i=0;i<N;i++)//Se pun in vectori adresele de ip si mastile
    {          
    scanf("%d.%d.%d.%d%*c%d",&ip3a,&ip3b,&ip3c,&ip3d,&msk3);
    ip3=((ip3a<<24)+(ip3b<<16)+(ip3c<<8)+ip3d);     
    ip3v[i]=ip3;
    msk3v[i]=msk3;
    }    
    printf("%d \n",i);//Se afiseaza numarul curent al setului   
    printf("-0 %d.%d.%d.%d/%d \n",ip1a,ip1b,ip1c,ip1d,msk2);    
    printf("-1 ");
    msk2tozecimal(msk2);   
    printf("-2 ");
    printf("%o.%o.%o.%o ",msk1a,msk1b,msk1c,msk1d);
    printf("%x.%x.%x.%x \n",msk1a,msk1b,msk1c,msk1d); 
    printf("-3 ");    
    adresaderetea(ip1,msk2);    
    printf("-4 ");    
    adresadebroadcast(ip1,msk2);
    printf("-5 ");
    comparareadrese(ip1,ip2,msk2);           
    printf("-6 ");
    if((corectitudine(msk1))==1)
    printf("DA \n");
    else
    printf("NU \n");   
    printf("-7 ");
    corectare(msk1);   
    printf("-8 ");
    reprezentbinarip(ip1);
    printf("-9 ");
    for(int i=0;i<N;i++)//Se parcurge cu un for toate adresele din vector pentru a afla compatibilitatea  
    if(gasirecompatibilitate(ip2,ip3v[i],msk3v[i])==1)
    printf("%d ",i);//adiseaza indicele mastii care a fost compatibila  
    printf("\n");    
    }
}


