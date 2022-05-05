# include <string.h> 
# include <stdio.h>
#include <time.h> 
#include <sys/time.h> 
# define SIZE 1000
int araDegistir( char *, char *,char *,int);

int max (int a, int b) { return (a > b)? a: b; }

void badCharH( char *str, int size,	int badchar[SIZE]) 
{ 
	int i; 

	for (i = 0; i < SIZE; i++) 
		badchar[i] = -1; 

	for (i = 0; i < size; i++) 
		badchar[(int) str[i]] = i;
} 

int araDegistir( char *txt, char *aranan,char *degistir,int caseSense) 
{ 
	int m = strlen(aranan); 
	int n = strlen(txt); 
	int k = strlen(degistir);
	int boyut,i;
	int adr[20],adri=0,adresSay=0;//Bulunan kelimeye göre kaç adet olduðu adr dizisinde tutulur adri ve adresSay deðiþkenlerinde adres sayýsý tutulur.
	for (i = 0; i < 20; i++) adr[i] = -1; 
	if(k-m==0) boyut=0;//deðiþtirilecek metin aranan metin ayný boyda
	if(k-m>0) boyut=1;//deðiþtirilecek metin aranan metinden uzun
	if(k-m<0) boyut=-1;//deðiþtirilecek metin aranan metinden kýsa
	int sayac=0;
	int badchar[SIZE]; 
	badCharH(aranan, m, badchar); 

	int cnt = 0;
	if (caseSense==1){  						
	while(cnt <= (n - m)) 														
	{ 
		int j = m-1; 																
		while(j >= 0 && aranan[j] == txt[cnt+j]) 								
			j--; 																
		if (j < 0) 
		{ 
		//	printf("\n uzaklik = %d", cnt);
			adr[adri]=cnt;
			adri++;
			adresSay++;
			if(cnt+m<n) {
				cnt+=m-badchar[txt[cnt+m-1]];			
			}
			else 		cnt+=1;
		} 
		else
			cnt += max(1, j - badchar[txt[cnt+j]]); 
	}
	}
		if (caseSense==2){  						
	while(cnt <= (n - m)) 														
	{ 
		int j = m-1; 																
		while(j >= 0 && (txt[cnt+j]<91)? aranan[j] == txt[cnt+j]+32: aranan[j] == txt[cnt+j]) 		//aranan[j] == txt[cnt+j] || 						
			//printf("\n %c \n",txt[cnt+j]);
			j--; 																
		if (j < 0) 
		{ 
			//printf("\n uzaklik = %d", cnt);
			adr[adri]=cnt;
			adri++;
			adresSay++;
			if(cnt+m<n) {
				cnt+=m-badchar[txt[cnt+m-1]];			
			}
			else 		cnt+=1;
		} 
		else
			cnt += max(1, j - badchar[txt[cnt+j]]); 
	}
	}
	//Yukarýda Boyer Moore algoritmasý ile aranan kelimenin adresleri adr[20] dizisinde tutulur.
	//Þimdi aþaðýda mevcut adreslerde ki ifadeleri deðiþtireceðiz.
	////////////////////
	if(boyut==0){
		adri=0;
		while(adr[adri]!=-1){				
			for(i=0;i<k;i++) txt[adr[adri]+i]=degistir[i];		
			adri++;
		}
	}
	else if(boyut==1){//deðiþtirilecek metin aranan metinden uzun
		int fark=k-m;
		adri=0;
		int i=0,j,a;
		int t;
		i=0;
		while(adr[adri]!=-1){
			//adr[adri]-=1;
			adr[adri]+=(i);
			for(j=0;j<fark;j++)
			{
				t=n;						
				
				while(t!=adr[adri])//döngü n=t eleman sayýsýndan geriye doðru uzaklýk adresine kadar döner.
				{
					txt[t+1]=txt[t];
					//txt[t]='x';	
					t--;					
				}
				i++;
				n++;	
			}
			for(a=0;a<k;a++){
				txt[adr[adri]+a]=degistir[a];
			}				
			adri++;
		}	
	}
	else if(boyut==-1){//deðiþtirilecek metin aranan metinden kýsa
		int fark=m-k;
		int t,j,tt,a;
		int say=adresSay-1;//Bulunan adres sayýsý
		while(say!=-1){
			for(a=0;a<k;a++){
				txt[adr[say]+a]=degistir[a];
			}		
			//t=adr[say]+fark+1;
			t=adr[say]+m-1;
			tt=t;
			for(j=0;j<fark;j++){				
				while(t!=n){				
					txt[t]=txt[t+1];						
					t++;
				}
				t=tt-(j+1);
				n--;
			}
			say--;
		}
	}
	return adresSay;
} 
int main() 
{ 
	char metin[SIZE];
	char aranan[50],degistir[50];
	int caseSense,n=0,i=0,bulunan;

	printf("Aranacak kelimeyi giriniz: ");
	gets(aranan);
	printf("\nYerine yazilacak olan ifadeyi giriniz: ");
	gets(degistir);
	printf("\nCase sensitive durumunu giriniz->ON:1 OFF:2 \n");//caseSense 1 ise sadece yazýlaný kabul eder.(Büyükse büyük,küçükse küçük)
	scanf("%d",&caseSense);//caseSense 2 ise büyük küçük kabul eder.
	FILE *fp; 
  	fp=fopen("metin.txt","r"); 
  	int c;	  
    while((c = fgetc(fp)) != EOF) {
        if (c != NULL) {
            metin[n]=c;
			n++;			
		}			
    }  	
  	fclose(fp);
  	for(i=1;i<=5;i++) metin[n+i]=' ';n+=6;
	printf("Dosyadan Okunan Metin:");
  	i=0;
  	while(i!=n){
	  printf("%c",metin[i]);
	  i++;
	} 
	time_t start,end;
	time (&start);
	//clock_t start, end;
	//start=clock();
	bulunan=araDegistir(metin, aranan ,degistir,caseSense); 
	time (&end);
	//end=clock();
	i=0;
	n = strlen(metin);
	printf("\nYeni Metin:");
	while(i!=n){
	  printf("%c",metin[i]);
	  i++;
	}
	printf("\nBulunan ve degistirilen ifade sayisi:%d",bulunan);
	printf ("\nIslem suresi: %.5lf", difftime (end,start));
	//printf ("\nIslem suresi: %.8lf", end-start);
	fp = fopen("metin.txt","w");
	fputs(metin, fp);
	//printf("\nYeni metin dosyaya yazildi.");
	fclose(fp);
	return 0; 
} 

