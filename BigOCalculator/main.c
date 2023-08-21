#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Space complexity fonksiyonlarý
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

// Hangi deðiþkenden kaç tane olduðunu bulmak için kullanýlan deðiþkenler
int a_int=0,a_double=0,a_float=0,a_char=0;

// Time complexity fonksiyonlarý
void dongu_bilgisi_olustur();
void time_complexity(int,int);
void degisken_version_bul(char *,char *,char *,char *,char *,char *,char *,char *);

// Fonksiyon içindeki döngülerin bilgisini tutuyor 
char dizi[50];

// T(n) fonksiyonlarý
void time();

// Fonksiyon varsa fonksiyonun ismini ve türünü tutan deðiþkenler
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
	// Bir satirda kaç tane deðiþken tanýmlandýðý bulunurken kaçýncý satir olduðu bilgisi için   
	int sira=0;
	while(!feof(dosya))
	{
		fgets(satir,1000,dosya);
		sira++;
		// Türün ismi geçiyorsa ife giriyor; main ve printf istisnasý kontrolü
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
    // temp_satir: while içinde ilerlerken while ýn olduðu satýrý tutuyor
    // dizi: kaç tane n kaç tane log ifadesi olduðunu tutuyor
    // degisken: while ve do while içerisindeki deðiþkenin ismini tutuyor
    char satir[1000],temp_satir[1000],dizi[adet],degisken[10];
    // while içerisinde döngünün nasýl deðiþtiði aranýrken olasý durumlarýn tutulmasý için kullanýlan deðiþkenler
    char version1[20],version2[20],version3[20],version4[20],version5[20],version6[20];
    // index: diziye eklenecek deðiþkenin hangi indexte olduðunu tutuyor
    // parantez: while ve do while kýsýmlarý için { adedini tutuyor
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
    	// En büyük iç içe döngüye kadar ilerleniyor
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
					// while sonrasýnda döngü var
					else
					{
						int i;
						for(i=0;satir[i]!='\0';i++)
							temp_satir[i]=satir[i];
						temp_satir[i]='\0';
						// whiledan sonraki satýrda döngü kontrolu var mý bakmak için yeni sýra okundu
						fgets(satir,1000,dosya);
						// Artýþ döngülerden önce
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
						// Artýþ döngüden sonra
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
							// Bu döngüden çýkýldýðýnda sýradaki döngünün satýrýnda bulunuluyor
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
					// while satýrýna kadar ilerlendi
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
					// do while ýn baþýna geri gelindi
					fseek(dosya,0,SEEK_SET);
					while(!feof(dosya))
					{
						fgets(satir,1000,dosya);
						if(strcmp(temp_satir,satir)==0)
							break;		
					}
					// Baþka döngü kalmadýysa
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
					// Baþka döngü var
					else
					{
						int i;
						for(i=0;satir[i]!='\0';i++)
							temp_satir[i]=satir[i];
						temp_satir[i]='\0';
						// do whiledan sonraki satýrda döngü kontrolu var mý bakmak için yeni sýra okundu
						fgets(satir,1000,dosya);
						// Artýþ döngülerden önce
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
						// Artýþ döngüden sonra
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
							// Bu döngüden çýkýldýðýnda sýradaki döngünün satýrýnda bulunuluyor
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
		// Ýþlemler döngüden önce
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
		// Ýþlemler döngüden sonra
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
			// Bu döngüden çýkýldýðýnda sýradaki döngünün satýrýnda bulunuluyor
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
        // ; fonksiyonun kendisini almamasý için
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
	// Koþulunun içindeki deðiþkenin bulunmasý
	int i,j=0;
	for(i=0;satir[i]!='(';i++);
	for(i=i+1;satir[i]!='>' && satir[i]!='<' && satir[i]!=' ';i++)
	{
		degisken[j]=satir[i];
		j++;
	}
	degisken[j]='\0';
	// degisken n 'e eþit ise 
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
    // En büyük sayýda iç içe döngüde kaç tane döngü olduðu bulunuyor
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
	// enb: en fazla kaç taç tane iç içe döngü olduðu, kacinci: bu döngünün kaçýncý döngü olduðu
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
	// Karmaþýklýk hesabýndaki sayýlarý tutan deðiþkenler
	int sabit,n_us,n_katsayi;
	if(strstr(satir,"return")!=NULL)
	{
		int i,durum;
		// return son harfine kadar ilerlendi
		for(i=0;satir[i]!='n';i++);
		// return ifadesinden sonra ne geldiði kontrolü
		for(i=i+2;satir[i]!=';';i++)
		{
			// Sayý
			if(isdigit(satir[i]))
				durum=1;
			// Boþluk istisnasý
			else if(satir[i]==' ')
				continue;	
			// Sayý deðil	
			else
			{
				durum=0;
				break;
			}
		}
		// Sayý deðil ise
		if(durum==0)
		{
			fonksiyon_bilgisi(func_name,func_type);
			// Recursive çaðýrma varsa
			if(strstr(satir,func_name)!=NULL)
			{
				n_us=1;
				n_katsayi=1;
				char temp[20];
				sprintf(temp,"%dn^%d+",n_katsayi,n_us);
				birlestir(complexity,temp);
			}
			// Recursive çaðýrma yoksa
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
		// Fonksiyon parametreleri arasýnda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char kontrol[50];
			int i=0;
			for(i=0;satir[i]!='(';i++);
			// adet1 toplam [ sayýsýný tutuyor
			int adet1=parantez_say(satir);
			// adet2 anlýk bakýlan deðiþkendeki [ sayýsýný tutuyor
			int adet2;
			// DONUS kullanýlmasýnýn sebebi int dizi1[n][n], dizi2[n] gibi bir tanýmlama yapýldýðýnda ilk dizinin iþlemleri bittikten sonra
			// ikinci dizi için ayný iþlemlerin tekrarlanmasýný saðlamak
			DONUS: ;
			int j=0;
			// Fonksiyon parametreleri bulunup kontrol dizisine atýlýyor
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
					// Tüm diziler bulundu ve hepsi ayný tür, hangi tür olduðu bulunup n_us ve n_katsayi deðerleri atanýyor
					// Bulunan sonuç complexity dizisine atýlýyor
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
			// Sýradaki parametreye ilerle
			else
				goto DONUS;
		}
		// Parametrelerde dizi yok
		else
		{
			char kontrol[50];
			int i,j=0;
			// Parametrelerin bulunmasý
			for(i=0;satir[i]!='(';i++);
			for(i=i+1;satir[i]!=')';i++)
			{
				kontrol[j]=satir[i];
				j++;
			}
			kontrol[j]='\0';
			// Parantez içindeki tür adetleri sayýlmasý
			a_int+=tekrar_adedi(kontrol,"int");
			a_float+=tekrar_adedi(kontrol,"float");
			a_double+=tekrar_adedi(kontrol,"double");
			a_char+=tekrar_adedi(kontrol,"char");
			// Adetlere göre sabit deðiþken deðeri hesaplama
			sabit=(a_int*4)+(a_double*8)+(a_float*4)+(a_char*1);
			// Bulunan deðerin stringe çevirilip önceki deðerler ile birleþtirilmesi
			char temp[20];
			sprintf(temp,"%d+",sabit);
			birlestir(complexity,temp);
		}	
	}
	if(strstr(satir,"int")!=NULL)
	{
		// Satýrda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=4;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Satýrda dizi yoksa
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
		// Satýrda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=4;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Satýrda dizi yoksa
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
		// Satýrda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=8;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Satýrda dizi yoksa
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
		// Satýrda dizi varsa
		if(strstr(satir,"[")!=NULL)
		{
			char temp[20];
			n_us=parantez_say(satir);
			n_katsayi=1;
			sprintf(temp,"%dn^%d+",n_katsayi,n_us);
			birlestir(complexity,temp);
		}
		// Satýrda dizi yoksa
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
        // Fonksiyon adýnýn olduðu satira gelince döngüden çýkacak
        // ; main içinde ( kullanýlma ihtimali olan printf, scanf, fonksiyon çaðýrýlmasý gibi durumlarýn kontrolü için
        if(strstr(satir,"(")!=NULL && strstr(satir,"main")==NULL && strstr(satir,";")==NULL)
        	break;
    }
    int i,j=0;
    // Fonksiyon türünü bul
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
		// Okunan deðer sayý
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
