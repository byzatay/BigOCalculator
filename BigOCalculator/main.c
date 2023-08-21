#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Space complexity fonksiyonlar�
void dosyadan_oku();
void space_complexity();
void yer_bilgisi_ekle(char *,int,char *);
int parantez_say(char *);
void birlestir(char *,char *);
int tekrar_adedi(char [],char []);
int virgul_say(char *);
void format_duzenle(char *);
void fonksiyon_bilgisi(char *,char *);
int recursive_control();

// Hangi de�i�kenden ka� tane oldu�unu bulmak i�in kullan�lan de�i�kenler
int a_int=0,a_double=0,a_float=0,a_char=0;

// Time complexity fonksiyonlar�
void dongu_bilgisi_olustur();
void time_complexity(int,int);
void degisken_version_bul(char *,char *,char *,char *,char *,char *,char *,char *);

// Fonksiyon i�indeki d�ng�lerin bilgisini tutuyor 
char dizi[50];

// T(n) fonksiyonlar�
void time();

// Fonksiyon varsa fonksiyonun ismini ve t�r�n� tutan de�i�kenler
char func_name[100];
char func_type[20];
		
int main() {
	dosyadan_oku();
	return 0;
}

void dosyadan_oku()
{
	FILE *dosya;
	dosya=fopen("kod.txt","r");
	if(dosya==NULL)
	{
		printf("Dosya acilamadi!\n");
		exit(1);
	}
	char satir[1000];
	int enb,kacinci;
	while(!feof(dosya))
	{
		fgets(satir,1000,dosya);
		printf("%s",satir);
	}
	printf("\n\n");
	printf("Dosyanin icerigi koddur.\n\n");
	space_complexity();
	dongu_bilgisi_olustur(&enb,&kacinci);
    time_complexity(enb,kacinci);
    time();
	fclose(dosya);
}

void space_complexity()
{
	FILE *dosya;
	dosya=fopen("kod.txt","r");
	if(dosya==NULL)
	{
		printf("Dosya acilamadi!\n");
		exit(1);
	}
	char satir[1000];
	char complexity[200];
	complexity[0]='\0';
	// Bir satirda ka� tane de�i�ken tan�mland��� bulunurken ka��nc� satir oldu�u bilgisi i�in   
	int sira=0;
	while(!feof(dosya))
	{
		fgets(satir,1000,dosya);
		sira++;
		// T�r�n ismi ge�iyorsa ife giriyor; main ve printf istisnas� kontrol�
		if(strstr(satir,"int")!=NULL && strstr(satir,"main")==NULL && strstr(satir,"printf")==NULL)
			yer_bilgisi_ekle(satir,sira,complexity);
		else if(strstr(satir,"float")!=NULL && strstr(satir,"main")==NULL)
			yer_bilgisi_ekle(satir,sira,complexity);
		else if(strstr(satir,"double")!=NULL && strstr(satir,"main")==NULL)
			yer_bilgisi_ekle(satir,sira,complexity);
		else if(strstr(satir,"char")!=NULL && strstr(satir,"main")==NULL)
			yer_bilgisi_ekle(satir,sira,complexity);
		else if(strstr(satir,"return")!=NULL)
			yer_bilgisi_ekle(satir,sira,complexity);
	}
	format_duzenle(complexity);					
}

void time_complexity(int adet,int sira)
{
	FILE *dosya;
    dosya=fopen("kod.txt","r");
    if(dosya==NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    // temp_satir: while i�inde ilerlerken while �n oldu�u sat�r� tutuyor
    // dizi: ka� tane n ka� tane log ifadesi oldu�unu tutuyor
    // degisken: while ve do while i�erisindeki de�i�kenin ismini tutuyor
    char satir[1000],temp_satir[1000],dizi[adet],degisken[10];
    // while i�erisinde d�ng�n�n nas�l de�i�ti�i aran�rken olas� durumlar�n tutulmas� i�in kullan�lan de�i�kenler
    char version1[20],version2[20],version3[20],version4[20],version5[20],version6[20];
    // index: diziye eklenecek de�i�kenin hangi indexte oldu�unu tutuyor
    // parantez: while ve do while k�s�mlar� i�in { adedini tutuyor
    int temp_adet=adet,index=0,str=0,parantez=0;
    fonksiyon_bilgisi(func_name,func_type);
    // Fonksiyon var
    int recursive=0;
    if(func_name[0]!='\0')
    {
    	// Fonksiyon recursive
    	if(recursive_control()==1)
    	{
    		recursive=1;
    		while(!feof(dosya))
			{
				fgets(satir,1000,dosya);
				if(strstr(satir,"return")!=NULL)
				{
					if(tekrar_adedi(satir,func_name)==1)
						printf("Time complexity: n\n");
					else if(tekrar_adedi(satir,func_name)==2 && strstr(satir,"+")!=NULL)
						printf("Time complexity: 2^n\n");
					else if(tekrar_adedi(satir,func_name)==2 && strstr(satir,"*")!=NULL)
						printf("Time complexity: n!\n");
				}
			}
		}
	}
	// Fonksiyon yok
    else
    {
    	// En b�y�k i� i�e d�ng�ye kadar ilerleniyor
	    while(sira>0)
	    {
	    	fgets(satir,100,dosya);
	    	if(strstr(satir,"for")!=NULL || strstr(satir,"do")!=NULL || (strstr(satir,"while")!=NULL && strstr(satir,";")==NULL))
	    		sira--;
		}
		while(!feof(dosya))
		{	
			if(temp_adet>0)
			{
				if(strstr(satir,"for")!=NULL)
				{
					temp_adet--;
					if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
				    {
				   		dizi[index]='n';
				    	index++;
					}
					else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
					{
				  		dizi[index]='l';
				    	index++;
					}
					fgets(satir,1000,dosya);
				}
				else if(strstr(satir,"while")!=NULL)
				{
					temp_adet--;
					degisken_version_bul(satir,degisken,version1,version2,version3,version4,version5,version6);
					if(temp_adet==0)
					{
						
						do{
							
							fgets(satir,1000,dosya);
							if(strstr(satir,version1)!=NULL || strstr(satir,version2)!=NULL || strstr(satir,version3)!=NULL || strstr(satir,version4)!=NULL ||
								strstr(satir,version5)!=NULL  || strstr(satir,version6)!=NULL || strstr(satir,"++")!=NULL ||  strstr(satir,"--")!=NULL)
							{
								
								if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
								{
						    		dizi[index]='n';
						    		index++;	
								}
								else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
								{
						    		dizi[index]='l';
						    		index++;
								}
							}
						}
						while(strstr(satir,"}")==NULL);
					}
					// while sonras�nda d�ng� var
					else
					{
						int i;
						for(i=0;satir[i]!='\0';i++)
							temp_satir[i]=satir[i];
						temp_satir[i]='\0';
						// whiledan sonraki sat�rda d�ng� kontrolu var m� bakmak i�in yeni s�ra okundu
						fgets(satir,1000,dosya);
						// Art�� d�ng�lerden �nce
						if(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL)
						{
							do{
								if(strstr(satir,version1)!=NULL || strstr(satir,version2)!=NULL || strstr(satir,version3)!=NULL || strstr(satir,version4)!=NULL ||
									strstr(satir,version5)!=NULL || strstr(satir,version6)!=NULL || strstr(satir,"++")!=NULL ||  strstr(satir,"--")!=NULL)
								{
									if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
									{
							   			dizi[index]='n';
							   			index++;
									}
									else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
									{
						    			dizi[index]='l';
										index++;
									}
								}
								fgets(satir,1000,dosya);
							}
							while(strstr(satir,"{")==NULL);
						}
						// Art�� d�ng�den sonra
						else if(strstr(satir,"for")!=NULL || strstr(satir,"while")!=NULL || strstr(satir,"do")!=NULL)
						{
							parantez++;
							while(parantez>0)
				       		{
				       			fgets(satir,1000,dosya);
				       			if(strstr(satir,"{")!=NULL)
				       				parantez++;
				       			else if(strstr(satir,"}")!=NULL)
				       				parantez--;
				       		}	
							do{
								fgets(satir,1000,dosya);
								if(strstr(satir,version1)!=NULL || strstr(satir,version2)!=NULL || strstr(satir,version3)!=NULL || strstr(satir,version4)!=NULL ||
									strstr(satir,version5)!=NULL || strstr(satir,version6)!=NULL || strstr(satir,"++")!=NULL ||  strstr(satir,"--")!=NULL)
								{
									if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
									{
							   			dizi[index]='n';
							   			index++;
									}
									else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
									{
						    			dizi[index]='l';
										index++;
									}
								}
							}
							while(strstr(satir,"}")==NULL);
							fseek(dosya,0,SEEK_SET);
							// Bu d�ng�den ��k�ld���nda s�radaki d�ng�n�n sat�r�nda bulunuluyor
							while(!feof(dosya))
							{
								fgets(satir,1000,dosya);
								if(strcmp(temp_satir,satir)==0)
								{
									do{
										fgets(satir,1000,dosya);
									}
									while(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL);
									break;
								}		
							}
						}	
					}
				}
				else if(strstr(satir,"do")!=NULL)
				{
					temp_adet--;
					// while sat�r�na kadar ilerlendi
					int i;
					for(i=0;satir[i]!='\0';i++)
						temp_satir[i]=satir[i];
					temp_satir[i]='\0';
					while(!feof(dosya))
					{
						fgets(satir,1000,dosya);
						if(strstr(satir,"while")!=NULL && strstr(satir,";")!=NULL)
							break;
					}
					degisken_version_bul(satir,degisken,version1,version2,version3,version4,version5,version6);
					// do while �n ba��na geri gelindi
					fseek(dosya,0,SEEK_SET);
					while(!feof(dosya))
					{
						fgets(satir,1000,dosya);
						if(strcmp(temp_satir,satir)==0)
							break;		
					}
					// Ba�ka d�ng� kalmad�ysa
					if(temp_adet==0)
					{
						do{
							fgets(satir,1000,dosya);
							if(strstr(satir,version1)!=NULL || strstr(satir,version2)!=NULL || strstr(satir,version3)!=NULL || strstr(satir,version4)!=NULL ||
								strstr(satir,version5)!=NULL  || strstr(satir,version6)!=NULL || strstr(satir,"++")!=NULL ||  strstr(satir,"--")!=NULL)
							{	
								if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
								{
									dizi[index]='n';
								    index++;	
								}
								else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
								{
									dizi[index]='l';
								    index++;
									}
								}
						}while(strstr(satir,"}")==NULL);
					}
					// Ba�ka d�ng� var
					else
					{
						int i;
						for(i=0;satir[i]!='\0';i++)
							temp_satir[i]=satir[i];
						temp_satir[i]='\0';
						// do whiledan sonraki sat�rda d�ng� kontrolu var m� bakmak i�in yeni s�ra okundu
						fgets(satir,1000,dosya);
						// Art�� d�ng�lerden �nce
						if(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL)
						{
							do{
								if(strstr(satir,version1)!=NULL || strstr(satir,version2)!=NULL || strstr(satir,version3)!=NULL || strstr(satir,version4)!=NULL ||
									strstr(satir,version5)!=NULL || strstr(satir,version6)!=NULL || strstr(satir,"++")!=NULL ||  strstr(satir,"--")!=NULL)
								{
									if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
									{
							   			dizi[index]='n';
							   			index++;
									}
									else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
									{
						    			dizi[index]='l';
										index++;
									}
								}
								fgets(satir,1000,dosya);
							}
							while(strstr(satir,"{")==NULL);
						}
						// Art�� d�ng�den sonra
						else if(strstr(satir,"for")!=NULL || strstr(satir,"while")!=NULL || strstr(satir,"do")!=NULL)
						{
							parantez++;
							while(parantez>0)
				       		{
				       			fgets(satir,1000,dosya);
				       			if(strstr(satir,"{")!=NULL)
				       				parantez++;
				       			else if(strstr(satir,"}")!=NULL)
				       				parantez--;
				       		}	
							do{
								fgets(satir,1000,dosya);
								if(strstr(satir,version1)!=NULL || strstr(satir,version2)!=NULL || strstr(satir,version3)!=NULL || strstr(satir,version4)!=NULL ||
									strstr(satir,version5)!=NULL || strstr(satir,version6)!=NULL || strstr(satir,"++")!=NULL ||  strstr(satir,"--")!=NULL)
								{
									if(strstr(satir,"+")!=NULL || strstr(satir,"-")!=NULL)
									{
							   			dizi[index]='n';
							   			index++;
									}
									else if(strstr(satir,"*")!=NULL || strstr(satir,"/")!=NULL)
									{
						    			dizi[index]='l';
										index++;
									}
								}
							}
							while(strstr(satir,"}")==NULL);
							fseek(dosya,0,SEEK_SET);
							// Bu d�ng�den ��k�ld���nda s�radaki d�ng�n�n sat�r�nda bulunuluyor
							while(!feof(dosya))
							{
								fgets(satir,1000,dosya);
								if(strcmp(temp_satir,satir)==0)
								{
									do{
										fgets(satir,1000,dosya);
									}
									while(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL);
									break;
								}		
							}
						}	
					}
				}
			}
			else
				break;
		}
	}
	if(recursive==0)
	{
		int j,n=0,l=0;
		for(j=0;j<adet;j++)
		{
			if(dizi[j]=='n')
				n++;
			else if(dizi[j]=='l')
				l++;
		}
		if(n==0 && l!=0)
			printf("Time complexity: logn^%d \n",l);
		else if(l==0 && n!=0)
			printf("Time complexity: n^%d \n",n);
		else if(n==0 && l==0)
			printf("Time complexity: 1");
		else
			printf("Time complexity: n^%d.logn^%d \n",n,l);
	}
	
}

void time()
{
	FILE *dosya;
	dosya=fopen("kod.txt","r");
	if(dosya==NULL)
	{
		printf("Dosya acilamadi!\n");
		exit(1);
	}
	char satir[1000],temp_satir[1000],temp_sabit[100];
	int sabit=0,dongu=0;
	char tn[1000],carpan[50],dongu_carpani[50];
	carpan[0]='\0';
	dongu_carpani[0]='\0';
	tn[0]='\0';
	while(!feof(dosya))
	{
		fgets(satir,1000,dosya);
		if(strstr(satir,"for")!=NULL || (strstr(satir,"while")!=NULL && strstr(satir,";")==NULL) || strstr(satir,"do")!=NULL)
			dongu++;
	}
	fseek(dosya,0,SEEK_SET);
	if(dongu==1)
	{
		do{
			fgets(satir,1000,dosya);
			if(strstr(satir,";")!=NULL && strstr(satir,"for")==NULL)
				sabit++;
		}
		while(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL);
		sprintf(tn,"%d",sabit);
		sprintf(carpan,"n");
		sprintf(dongu_carpani,"n+1");
		birlestir(tn,"+");
		birlestir(tn,dongu_carpani);	
		sabit=0;
		while(!feof(dosya))
			{
				fgets(satir,1000,dosya);
				if(strstr(satir,"}")!=NULL)
					break;
				else
					sabit++;
			}
			sprintf(temp_sabit,"+%d%s",sabit,carpan);
			birlestir(tn,temp_sabit);
			sabit=0;
			while(!feof(dosya))
			{
				fgets(satir,1000,dosya);
				if(strstr(satir,";")!=NULL)
					sabit++;
			}
			sprintf(temp_sabit,"+%d",sabit);
			birlestir(tn,temp_sabit);
			
			printf("T(n): %s ",tn);
	}
	else if(dongu==2)
	{
		do{
			fgets(satir,1000,dosya);
			if(strstr(satir,";")!=NULL && strstr(satir,"for")==NULL)
				sabit++;
		}
		while(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL);
		sprintf(tn,"%d",sabit);
		sprintf(carpan,"n");
		sprintf(dongu_carpani,"n+1");
		birlestir(tn,"+");
		birlestir(tn,dongu_carpani);	
		sabit=0;
		fgets(satir,1000,dosya);
		// ��lemler d�ng�den �nce
		if(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL)
		{
			do{
				fgets(satir,1000,dosya);
				if(strstr(satir,";")==NULL)
					sabit++;
			}
			while(strstr(satir,"for")==NULL && strstr(satir,"while")==NULL && strstr(satir,"do")==NULL);
			sprintf(temp_sabit,"+%d%s",sabit,carpan);
			birlestir(tn,temp_sabit);
		}
		// ��lemler d�ng�den sonra
		else if(strstr(satir,"for")!=NULL || strstr(satir,"while")!=NULL || strstr(satir,"do")!=NULL)
		{
			int i,parantez=0;
			for(i=0;satir[i]!='\0';i++)
				temp_satir[i]=satir[i];
			temp_satir[i]='\0';
			parantez++;
			while(parantez>0)
			{
				fgets(satir,1000,dosya);
				if(strstr(satir,"{")!=NULL)
					parantez++;
				else if(strstr(satir,"}")!=NULL)
					parantez--;
			}
			if(strstr(satir,"}")!=NULL)
				fgets(satir,1000,dosya);
			while(strstr(satir,"}")==NULL)
			{
				if(strstr(satir,";")!=NULL)
					sabit++;	
				fgets(satir,1000,dosya);
			}
			if(sabit!=0)
			{
				sprintf(temp_sabit,"+%d%s",sabit,carpan);
				birlestir(tn,temp_sabit);
				sabit=0;
			}
			fseek(dosya,0,SEEK_SET);
			// Bu d�ng�den ��k�ld���nda s�radaki d�ng�n�n sat�r�nda bulunuluyor
			while(!feof(dosya))
			{
				fgets(satir,1000,dosya);
				if(strcmp(temp_satir,satir)==0)
					break;			
			}
			sprintf(carpan,"n^2");
			sprintf(dongu_carpani,"n^2+2n+1");
			birlestir(tn,"+");
			birlestir(tn,dongu_carpani);	
			while(!feof(dosya))
			{
				fgets(satir,1000,dosya);
				if(strstr(satir,"}")!=NULL)
					break;
				else
					sabit++;
			}
			do{
				fgets(satir,1000,dosya);
			}while(strstr(satir,"}")==NULL);
			sprintf(temp_sabit,"+%d%s",sabit,carpan);
			birlestir(tn,temp_sabit);
			sabit=0;
			while(!feof(dosya))
			{
				fgets(satir,1000,dosya);
				
				if(strstr(satir,";")!=NULL)
					sabit++;
			}
			sprintf(temp_sabit,"+%d",sabit);
			birlestir(tn,temp_sabit);
			printf("T(n): %s ",tn);	
		}
	}
	else
		printf("T(n) hesaplanamadi.\n");				
}

int recursive_control()
{
	FILE *dosya;
    dosya=fopen("kod.txt","r");
    if(dosya==NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    char satir[1000];
    int durum=0;
    while(!feof(dosya))
    {
        fgets(satir,1000,dosya);
        // ; fonksiyonun kendisini almamas� i�in
        if(strstr(satir,func_name)!=NULL && strstr(satir,";")!=NULL)
        {
        	durum=1;
        	break;
		}
    }
    fclose(dosya);
    return durum;
}

void degisken_version_bul(char *satir,char *degisken,char *version1,char *version2,char *version3,char *version4,char *version5,char *version6)
{
	// Ko�ulunun i�indeki de�i�kenin bulunmas�
	int i,j=0;
	for(i=0;satir[i]!='(';i++);
	for(i=i+1;satir[i]!='>' && satir[i]!='<' && satir[i]!=' ';i++)
	{
		degisken[j]=satir[i];
		j++;
	}
	degisken[j]='\0';
	// degisken n 'e e�it ise 
	if(strcmp(degisken,"n")==0)
	{
		if(satir[i+1]=='=' || satir[i+1]==' ')
			i=i+2;
		else if(satir[i+2]==' ')
			i=i+3;
		else 
			i=i+1;
		j=0;
		for(i;satir[i]!=')';i++)
		{
			degisken[j]=satir[i];
			j++;
		}
		degisken[j]='\0';
	}
	sprintf(version1,"%s =",degisken);
	sprintf(version2,"%s=",degisken);
	sprintf(version3,"%s+=",degisken);
	sprintf(version4,"%s-=",degisken);
	sprintf(version5,"%s*=",degisken);
	sprintf(version6,"%s/=",degisken);	
}

void dongu_bilgisi_olustur(int *enb,int *kacinci)
{
	FILE *dosya;
    dosya=fopen("kod.txt","r");
    if(dosya==NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    char satir[1000];
    int parantez=0,i=0;
    while(!feof(dosya))
    {
        fgets(satir,1000,dosya);
        if(strstr(satir,"for")!=NULL || (strstr(satir,"while")!=NULL && strstr(satir,";")==NULL) || strstr(satir,"do")!=NULL)
        {
        	if(strstr(satir,"for")!=NULL)
        	{
        		parantez++;
        		dizi[i]='f';
        		i++;
			}
			else if(strstr(satir,"while")!=NULL && strstr(satir,";")==NULL)
        	{
        		parantez++;
        		dizi[i]='w';
        		i++;
        	}
        	else if(strstr(satir,"do")!=NULL)
        	{
	        	parantez++;
	        	dizi[i]='d';
	        	i++;
	    	}
        	while(parantez>0)
        	{
        		fgets(satir,1000,dosya);
        		if(strstr(satir,"{")!=NULL)
        			parantez++;
        		else if(strstr(satir,"}")!=NULL)
        			parantez--;
        		if(strstr(satir,"for")!=NULL)
		        {
		        	dizi[i]='f';
		        	i++;
				}
				else if(strstr(satir,"while")!=NULL && strstr(satir,";")==NULL)
		        {
		        	dizi[i]='w';
		        	i++;
				}
				else if(strstr(satir,"do")!=NULL)
		        {
		        	dizi[i]='d';
		        	i++;
				}
			}
			dizi[i]='/';
			i++;
		}
    }
    int j=0,temp=0,parca=0,sira,index=0;
    *enb=0;
    *kacinci=0;
    // En b�y�k say�da i� i�e d�ng�de ka� tane d�ng� oldu�u bulunuyor
    for(j;j<i;j++)
    {
    	if(dizi[j]!='/')
    		temp++;
		else
		{
			parca++;
			if(temp>*enb)
			{
				sira=parca;
				*enb=temp;
			}	
			temp=0;
		}
	}
	// enb: en fazla ka� ta� tane i� i�e d�ng� oldu�u, kacinci: bu d�ng�n�n ka��nc� d�ng� oldu�u
	j=0; 
	while(sira-1>0)
	{
		if(dizi[j]=='/')
			sira--;
		j++;
		index++;
	}
	j=index;
	while(j>=0)
	{
		if(dizi[j]!='/')
			*kacinci+=1;	
		j--;		
	}
}

void yer_bilgisi_ekle(char *satir,int sira,char *complexity)
{
	// Karma��kl�k hesab�ndaki say�lar� tutan de�i�kenler
	int sabit,n_us,n_katsayi;
	if(strstr(satir,"return")!=NULL)
	{
		int i,durum;
		// return son harfine kadar ilerlendi
		for(i=0;satir[i]!='n';i++);
		// return ifadesinden sonra ne geldi�i kontrol�
		for(i=i+2;satir[i]!=';';i++)
		{
			// Say�
			if(isdigit(satir[i]))
				durum=1;
			// Bo�luk istisnas�
			else if(satir[i]==' ')
				continue;	
			// Say� de�il	
			else
			{
				durum=0;
				break;
			}
		}
		// Say� de�il ise
		if(durum==0)
		{
			fonksiyon_bilgisi(func_name,func_type);
			// Recursive �a��rma varsa
			if(strstr(satir,func_name)!=NULL)
			{
				n_us=1;
				n_katsayi=1;
				char temp[20];
				sprintf(temp,"%dn^%d+",n_katsayi,n_us);
				birlestir(complexity,temp);
			}
			// Recursive �a��rma yoksa
			else
			{
				if(strstr(func_type,"int")!=NULL)
					a_int++;
				else if(strstr(func_type,"float")!=NULL)
					a_float++;
				else if(strstr(func_type,"double")!=NULL)
					a_double++;
				else if(strstr(func_type,"char")!=NULL)
					a_char++;
			}
		}
	}
	// Okunan satirda fonksiyon varsa
	else if(strstr(satir,"(")!=NULL)
	{
		// Fonksiyon parametreleri aras�nda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char kontrol[50];
			int i=0;
			for(i=0;satir[i]!='(';i++);
			// adet1 toplam [ say�s�n� tutuyor
			int adet1=parantez_say(satir);
			// adet2 anl�k bak�lan de�i�kendeki [ say�s�n� tutuyor
			int adet2;
			// DONUS kullan�lmas�n�n sebebi int dizi1[n][n], dizi2[n] gibi bir tan�mlama yap�ld���nda ilk dizinin i�lemleri bittikten sonra
			// ikinci dizi i�in ayn� i�lemlerin tekrarlanmas�n� sa�lamak
			DONUS: ;
			int j=0;
			// Fonksiyon parametreleri bulunup kontrol dizisine at�l�yor
			if(satir[i+1]!=')')
			{
				for(i=i+1;satir[i]!=',';i++)
				{
					kontrol[j]=satir[i];
					j++;
				}
				kontrol[j]='\0';
				adet2=tekrar_adedi(kontrol,"[");
			}
			if(strstr(kontrol,"[")!=NULL)
			{
				// Sadece bir eleman dizi ise
				if(adet1==adet2)
				{
					// T�m diziler bulundu ve hepsi ayn� t�r, hangi t�r oldu�u bulunup n_us ve n_katsayi de�erleri atan�yor
					// Bulunan sonu� complexity dizisine at�l�yor
					if(strstr(kontrol,"int")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=4;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					else if(strstr(kontrol,"float")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=4;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					else if(strstr(kontrol,"double")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=8;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					else if(strstr(kontrol,"char")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=1;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
				}
				// Birden fazla dizi var
				else
				{
					if(strstr(kontrol,"int")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=4;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					else if(strstr(kontrol,"float")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=4;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					else if(strstr(kontrol,"double")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=8;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					else if(strstr(kontrol,"char")!=NULL)
					{
						char temp[20];
						n_us=adet2;
						n_katsayi=1;
						sprintf(temp,"%dn^%d+",n_katsayi,n_us);
						birlestir(complexity,temp);
					}
					adet1=adet1-adet2;
					goto DONUS;
				}	
			}
			// S�radaki parametreye ilerle
			else
				goto DONUS;
		}
		// Parametrelerde dizi yok
		else
		{
			char kontrol[50];
			int i,j=0;
			// Parametrelerin bulunmas�
			for(i=0;satir[i]!='(';i++);
			for(i=i+1;satir[i]!=')';i++)
			{
				kontrol[j]=satir[i];
				j++;
			}
			kontrol[j]='\0';
			// Parantez i�indeki t�r adetleri say�lmas�
			a_int+=tekrar_adedi(kontrol,"int");
			a_float+=tekrar_adedi(kontrol,"float");
			a_double+=tekrar_adedi(kontrol,"double");
			a_char+=tekrar_adedi(kontrol,"char");
			// Adetlere g�re sabit de�i�ken de�eri hesaplama
			sabit=(a_int*4)+(a_double*8)+(a_float*4)+(a_char*1);
			// Bulunan de�erin stringe �evirilip �nceki de�erler ile birle�tirilmesi
			char temp[20];
			sprintf(temp,"%d+",sabit);
			birlestir(complexity,temp);
		}	
	}
	if(strstr(satir,"int")!=NULL)
	{
		// Sat�rda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=4;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Sat�rda dizi yoksa
		else
		{
			a_int=virgul_say(satir);
			sabit=4*a_int;
			char temp[20];
			sprintf(temp,"%d+",sabit);
			birlestir(complexity,temp);
		}
	}
	if(strstr(satir,"float")!=NULL)
	{
		// Sat�rda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=4;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Sat�rda dizi yoksa
		else
		{
			a_float=virgul_say(satir);
			sabit=4*a_float;
			char temp[20];
			sprintf(temp,"%d+",sabit);
			birlestir(complexity,temp);
		}
	}
	if(strstr(satir,"double")!=NULL)
	{
		// Sat�rda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=8;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Sat�rda dizi yoksa
		else
		{
			a_double=virgul_say(satir);
			sabit=8*a_double;
			char temp[20];
			sprintf(temp,"%d+",sabit);
			birlestir(complexity,temp);
		}
	}
	if(strstr(satir,"char")!=NULL)
	{
		// Sat�rda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=1;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Sat�rda dizi yoksa
		else
		{
			a_char=virgul_say(satir);
			sabit=1*a_char;
			char temp[20];
			sprintf(temp,"%d+",sabit);
			birlestir(complexity,temp);
		}
	}
}

void fonksiyon_bilgisi(char *func_name,char *func_type)
{
	func_name[0]='\0';
	func_type[0]='\0';
	FILE *dosya;
    dosya=fopen("kod.txt","r");
    if(dosya==NULL)
    {
        printf("Dosya acilamadi!\n");
        exit(1);
    }
    char satir[1000];
    while(!feof(dosya))
    {
        fgets(satir,1000,dosya);
        // Fonksiyon ad�n�n oldu�u satira gelince d�ng�den ��kacak
        // ; main i�inde ( kullan�lma ihtimali olan printf, scanf, fonksiyon �a��r�lmas� gibi durumlar�n kontrol� i�in
        if(strstr(satir,"(")!=NULL && strstr(satir,"main")==NULL && strstr(satir,";")==NULL)
        	break;
    }
    int i,j=0;
    // Fonksiyon t�r�n� bul
    for(i=0;satir[i]!=' ';i++)
		func_type[i]=satir[i];
	func_type[i]='\0';
    // Fonksiyon ismini bul
    for(i=i+1;satir[i]!=' ';i++)
    {
    	func_name[j]=satir[i];
    	j++;
	}
	func_name[j]='\0';
}

int parantez_say(char *satir)
{
	int i,count=0;
	for(i=0;satir[i]!='\n';i++)
	{
		if(satir[i]=='[')
		{
			count++;
		}
	}
	return count;
}

void birlestir(char *bas,char *son)
{
    int bas_n,son_n,i;
    for(i=0;bas[i]!='\0';i++);
    bas_n=i;
    for (i=0;son[i]!='\0';i++);
    son_n=i;
    for(i=0;i<son_n;i++)
        bas[i+bas_n]=son[i];
    bas[bas_n+son_n]='\0';
}

int tekrar_adedi(char satir[],char func_name[])
{
	int len1=strlen(satir);
	int len2=strlen(func_name);
	int i,j,temp,control,count=0;
	for(i=0;i<len1;i++)
    {
    	temp=i;
    	for(j=0;j<len2;j++)
    	{
        	if(satir[i]==func_name[j])
            i++;
    	}
      	control=i-temp;
      	if(control==len2)
        	count++;
      	i=temp;
   	}
	return count;
}

int virgul_say(char *satir)
{
	int i=0,count=0;
	for(i=0;satir[i]!='\n';i++)
	{
		if(satir[i]==',')
		{
			count++;
		}
	}
	return count+1;
}

void format_duzenle(char *complexity)
{
	char kontrol[10],temp_comp[50];
	temp_comp[0]='\0';
	int i=0,k,sabit=0,durum;
	DONUS: ;
	int j=0;
	if(complexity[i]!='\0')
	{
		for(i;complexity[i]!='+';i++)
		{	
			kontrol[j]=complexity[i];
			j++;
		}
		i++;
		kontrol[j]='\0';
		for(k=0;kontrol[k]!='\0';k++)
		{
			
			if(isdigit(kontrol[k]))				
				durum=1;
			else
			{
				durum=0;
				birlestir(temp_comp,kontrol);
				birlestir(temp_comp,"+");
				break;
			}
		}
		// Okunan de�er say�
		if(durum==1)
		{
			int temp;
			sscanf(kontrol,"%d",&temp);
			sabit+=temp;
		}
		goto DONUS;
	}
	char temp_sbt[10];
	sprintf(temp_sbt,"%d",sabit);
	birlestir(temp_comp,temp_sbt);
	printf("Space complexity: %s \n",temp_comp);
}
