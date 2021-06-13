#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "util/task_helper.h"

void oneback(char *text)
{
	int l=strlen(text);
	text[l] = '\n';
	text[l + 1] ='\0';
}		

void uppercase(char *textuppercase)
{
	int lungime=strlen(textuppercase),i=1;
	
	if(textuppercase[0]>='a' && textuppercase[0]<='z')
		textuppercase[0]=textuppercase[0]-32;
	while( i < lungime )
		{
			if(textuppercase[i-1]!='\n' && textuppercase[i]>='A' && textuppercase[i]<='Z')
				textuppercase[i]=textuppercase[i]+32;
			else if(textuppercase[i-1]=='\n' && textuppercase[i]>='a' && textuppercase[i]<='z')
				textuppercase[i]=textuppercase[i]-32;
			i++;
		}
	return;
}

void trimming(char *texttrimming)
{
	int extra=0;
	for(int i=0 ; i< strlen(texttrimming) ; i++)
		{
			if(texttrimming[i]==' ' && texttrimming[i+1]==' ')
			 	{
			 		memmove(texttrimming+i,texttrimming+(i+1),strlen(texttrimming)-(i+1)+1);	
					i--;
					extra++;
				}
			else if(strchr(".,;!?:",texttrimming[i]) != 0)
				{
			 		memmove(texttrimming+i,texttrimming+(i+1),strlen(texttrimming)-(i+1)+1);	
					i--;
					extra++;
				}
		}
	for (int i = 0; i < extra; ++i)
		{
			--texttrimming;
		}

	return;	
}
void silly(char *prob , char *textsilly)
{
	int lungime = strlen(textsilly) ;
	float probabil=atof((char *)prob);
	
	for(int i=0;i<lungime;i++)
		{
			if( (textsilly[i] >= 'a' && textsilly[i] <= 'z' ) || textsilly[i] >= 'A' && textsilly[i] <= 'Z')
				{
					float randomnr = rand() %100 / 99.0;
					if( randomnr < probabil )
						{
							if( textsilly[i] >= 'a' && textsilly[i] <= 'z')
							textsilly[i]=textsilly[i]-32;
							else if( textsilly[i] >= 'A' && textsilly[i] <= 'Z' )
							textsilly[i]=textsilly[i]+32;
						}
				}
		}
	return;
}

int equal_letter(char a, char b)
{
	if('a' <= a && a <= 'z')
		a -= 32;
	if('a' <= b && b <= 'z')
		b -= 32;
	if(a == b)
		return 1;
	else
		return 0;
}

void make_rhyme(char *s1, char *s2, char *ret1, char *ret2)
{
    int len1, len2;
    len1 = strlen(s1);
    len2 = strlen(s2);

    strcpy(ret1,s1);
    strcpy(ret2,s2);

    if(equal_letter(s1[len1 - 1], s2[len2 - 1]))
        return;

	int n;
	char **lista_sinonime;

	int gasit = 0;
	get_synonym(s1, &n, &lista_sinonime);

    for(int i = 0; i < n; ++i)
    {
        int len = strlen(lista_sinonime[i]);
        if(equal_letter( lista_sinonime[i][len - 1], s2[len2 - 1]))
        {
            if(gasit == 0)
                strcpy(ret1,lista_sinonime[i]);
            else if(strcmp(lista_sinonime[i], ret1) < 0)
                strcpy(ret1, lista_sinonime[i]);
            gasit = 1;
        }
    }

    if(gasit == 1)
        return;

    get_synonym(s2, &n, &lista_sinonime);
    for(int i = 0; i < n; ++i)
    {
        int len = strlen(lista_sinonime[i]);
        if(equal_letter( lista_sinonime[i][len - 1], s1[len1 - 1]))
        {
            if(gasit == 0)
                strcpy(ret2,lista_sinonime[i]);
            else if(strcmp(lista_sinonime[i], ret2) < 0)
                strcpy(ret2, lista_sinonime[i]);
            gasit = 1;
        }
    }
}

void rhimy(char *textrhimy , char *tiprima)
{
	char separatori[] = "; ,.!?\n\0";

	char clona[10001];
	strcpy(clona, textrhimy);

	char catren[4][10001];
	char new_catren[4][10001];

	char *last_pos = textrhimy;

	char *start;
	char aux_txt[10001];

	int curr_pos = 0;
	char* p = strtok(clona, "\n");
	
	while(p != NULL)
    {

        if(curr_pos < 4)
        {
            strcpy(catren[curr_pos], p);
            ++curr_pos;
            p = strtok(NULL, "\n");
        }
        else
        {

            curr_pos = 0;

            for(int i = 0; i < 4; ++i)//retinem ultimul cuvant din vers
            {
                start = catren[i] + strlen(catren[i]);
                --start;
                while(strchr(separatori, *start)){

                    *start = '\0';
                    --start;
                }
                while(!strchr(separatori, *start))
                    --start;
                ++start;// acesrt lucru il fac pentru a putea sa ajung exact pe prima litera 

                strcpy(catren[i], start);
            }

            if(strcmp(tiprima, "imperecheata") == 0)
            {
                make_rhyme(catren[0], catren[1], new_catren[0], new_catren[1]);
                make_rhyme(catren[2], catren[3], new_catren[2], new_catren[3]);
            }
            else if(strcmp(tiprima, "incrucisata") == 0)
            {
                make_rhyme(catren[0], catren[2], new_catren[0], new_catren[2]);
                make_rhyme(catren[1], catren[3], new_catren[1], new_catren[3]);
            }
            else if(strcmp(tiprima, "imbratisata") == 0)
            {
                make_rhyme(catren[0], catren[3], new_catren[0], new_catren[3]);
                make_rhyme(catren[1], catren[2], new_catren[1], new_catren[2]);
            }

            for(int i = 0; i < 4; ++i)
            {
               if(strcmp(catren[i], new_catren[i]) == 0)
                    continue;
                
                start = strstr(last_pos, catren[i]);
                strcpy(aux_txt, start + strlen(catren[i]));
                strcpy(start, new_catren[i]);
                last_pos = textrhimy + strlen(textrhimy);
                strcat(textrhimy, aux_txt);
            }
        }
	}
    for(int i = 0; i < 4; ++i)
        {
 	        start = catren[i] + strlen(catren[i]);
            --start;
  	        while(strchr(separatori, *start))
  	            {

                    *start = '\0';
                    --start;
                }
            while(!strchr(separatori, *start))
                    --start;
            ++start;

            strcpy(catren[i], start);
            
        }

    if(strcmp(tiprima, "imperecheata") == 0)
        {
            make_rhyme(catren[0], catren[1], new_catren[0], new_catren[1]);
            make_rhyme(catren[2], catren[3], new_catren[2], new_catren[3]);
        }
    else if(strcmp(tiprima, "incrucisata") == 0)
        {
            make_rhyme(catren[0], catren[2], new_catren[0], new_catren[2]);
            make_rhyme(catren[1], catren[3], new_catren[1], new_catren[3]);
        }
    else if(strcmp(tiprima, "imbratisata") == 0)
        {
            make_rhyme(catren[0], catren[3], new_catren[0], new_catren[3]);
        	make_rhyme(catren[1], catren[2], new_catren[1], new_catren[2]);
        }

    for(int i = 0; i < 4; ++i)
        {
               
            if(strcmp(catren[i], new_catren[i]) == 0)
           		continue;

            start = strstr(last_pos, catren[i]);
            strcpy(aux_txt, start + strlen(catren[i]));
            strcpy(start, new_catren[i]);
            last_pos = textrhimy + strlen(textrhimy);
            strcat(textrhimy, aux_txt);
          	
        }
	if(textrhimy[strlen(textrhimy)-1] != '\n')
		strcat(textrhimy,"\n");
}

void friendly(char *textfriendly)
{
	
	char separatori[] = "; ,.!?\n\0";
	char *friendlyword[100001],*pozitie;
	char clona[100001],auxfriendlytxt[100001];
	const char *decupaj;
	
	strcat(clona,textfriendly);
	decupaj = strtok(clona, separatori );

	char *last_pos = textfriendly;

	while( decupaj != NULL )
		{
			
			get_friendly_word(decupaj,friendlyword);
			
			if(  *friendlyword != NULL )
				{

					while(1)
						{
							pozitie=strstr(last_pos,decupaj);//pozitie pe care mi-a gasit cuvantul care are un diminutiv

							if(strchr(separatori,*(pozitie-1)) != 0 && strchr( separatori , *(pozitie+strlen(decupaj)) ) !=0 )
								{
									strcpy(auxfriendlytxt,pozitie+strlen(decupaj));//copiaza in auxfriendly sirul de dupa cuvantul ce trebuie inlocuit
									strcpy(pozitie, *friendlyword);
									last_pos = textfriendly + strlen(textfriendly);// se modifica pozitia pentru a nu lua de la capat textul
									strcat(textfriendly, auxfriendlytxt);
									break;
								}
							else
								{
									last_pos= pozitie + strlen(decupaj);
								}
						}
				}
			
			decupaj = strtok(NULL, separatori );
		}
	return;
}

void print(char *textprintare)
{
	printf("%s\n",textprintare);
	return;
}

int main(void)
{
   int contorback=0;
   srand(42);
   
    while(1)
	{
		char argument1[100],argument2[100];
		char stocare[10001];
		
		scanf("%s",argument1);
		
		if(strcmp(argument1,"load") == 0 || strcmp(argument1,"make_it_silly") == 0 || strcmp(argument1,"make_it_rhyme") == 0)
		scanf("%s",argument2);	
		
		if(strcmp(argument1,"load") == 0)
		{ 
			const char *file=argument2;
			load_file(file,stocare);
			
		}
		else if(strcmp(argument1,"uppercase") == 0)
		{
			uppercase(stocare);
			if( contorback == 0)
			{
				oneback(stocare);
				contorback++;
			}
		}
		else if(strcmp(argument1,"trimming") == 0)
		{
			trimming(stocare);
			if( contorback == 0)
			{
				oneback(stocare);
				contorback++;
			}
		}
		else if(strcmp(argument1,"make_it_silly") == 0)
		{
			silly(argument2,stocare);
			if( contorback == 0)
				{
					oneback(stocare);
					contorback++;
				}
		}
		else if(strcmp(argument1,"make_it_friendlier") == 0)
		{
			
			friendly(stocare);
			if( contorback == 0)
				{
					oneback(stocare);
					contorback++;
				}
		}
		else if(strcmp(argument1,"make_it_rhyme") == 0)
		{
			rhimy(stocare,argument2);
				contorback++;
			
		}
		else if(strcmp(argument1,"print") == 0)
		{
			if( contorback == 0)
				{
					oneback(stocare);
					contorback++;
				}
			print(stocare);
		
		}
		else if(strcmp(argument1,"quit") == 0)
		{		
	
			break;	
		}		
	}	
   
    return 0;
}

