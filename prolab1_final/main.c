#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

struct NOKTALAR
{
    double *x,*y,*z;
    int *r,*g,*b;

}*str_nokta_bilgileri;

char *dosyalar[100];
char *dosya_adlari[100];
int i=0;
int gecici_dosya_sayisi=0;
int dosya_sayisi=0;
int rgb_kontrol=1,ascii_kontrol=1,nokta_sayisi=0;
int gercek_nokta_sayisi=0;
int dosya_hata[100];
int noktaSayilari[100];
int dataTipleri[100];
int rgbTipleri[100];
double toplamUzakliklar[100];
double ortalamaUzakliklar[100];
int uzaklikHesaplandi=0;
int k=0;//STRUCT DEGISKENI (DOSYA SAYISI KADAR)
float xyz;
int rgb;
int f=0,g=0,h=0,r=0,t=0,y=0,u=0;
char *dosya_output_adlari[100];
FILE *output_dosya;
char *noktaHatalariniTut[100];
char *baslikHatalariniTut[100];
char *noktaEslesmeHatalariniTut[100];
int sonNoktaHatasi[100];
int sonBaslikHatasi[100];
int sonNoktaEslesmeHatasi[100];

void output_olustur()
{
    output_dosya = fopen("output.nkt","w");
    fprintf(output_dosya,"SECIM 1\n");

    for(int x=0; x<dosya_sayisi; x++)
        if(sonBaslikHatasi[x]==1)
        {
            fprintf(output_dosya,"\n%s\n", baslikHatalariniTut[x]);
        }

    fprintf(output_dosya,"\n");

    for(int x=0; x<dosya_sayisi; x++)
        if(sonNoktaHatasi[x]==1)
        {
            fprintf(output_dosya,"\n%s\n", noktaHatalariniTut[x]);
        }

    fprintf(output_dosya,"\n");

    for(int x=0; x<dosya_sayisi; x++)
        if(sonNoktaEslesmeHatasi[x]==1)
        {
            fprintf(output_dosya,"%s\n", noktaEslesmeHatalariniTut[x]);
        }

    fclose(output_dosya);
}

void kup_hesapla()
{
    int yazdirmaKontrol=0;
    double minx=101, miny=101, minz=101, maxx=0, maxy=0, maxz=0, maxuzunluk;

    for(int s=0; s<dosya_sayisi; s++)
    {
        minx=10100;
        miny=10100;
        minz=10100;
        maxx=0;
        maxy=0;
        maxz=0;
        if(dosya_hata[s]==0)
        {
            for(i=0; i<noktaSayilari[s]; i++)
            {
                if(str_nokta_bilgileri[s].x[i]<minx)
                {
                    minx=str_nokta_bilgileri[s].x[i];
                }
                if(str_nokta_bilgileri[s].y[i]<miny)
                {
                    miny=str_nokta_bilgileri[s].y[i];
                }
                if(str_nokta_bilgileri[s].z[i]<minz)
                {
                    minz=str_nokta_bilgileri[s].z[i];
                }

                if(str_nokta_bilgileri[s].x[i]>maxx)
                {
                    maxx=str_nokta_bilgileri[s].x[i];
                }
                if(str_nokta_bilgileri[s].y[i]>maxy)
                {
                    maxy=str_nokta_bilgileri[s].y[i];
                }
                if(str_nokta_bilgileri[s].z[i]>maxz)
                {
                    maxz=str_nokta_bilgileri[s].z[i];
                }
            }

            maxuzunluk=maxx-minx;
            if( (maxy-miny) > maxuzunluk )
            {
                maxuzunluk= maxy-miny;
            }
            if( (maxz-minz) > maxuzunluk )
            {
                maxuzunluk= maxz-minz;
            }

            printf("\n\n%s dosyasinin min kose degerleri (x y z): %f - %f - %f\nmaxuzunluk: %f\n", dosya_adlari[s],minx, miny, minz, maxuzunluk);

            printf("\nA kosesi x y z degerleri: %f %f %f", minx+maxuzunluk, miny, minz );
            printf("\nB kosesi x y z degerleri: %f %f %f", minx, miny, minz );
            printf("\nC kosesi x y z degerleri: %f %f %f", minx, miny+maxuzunluk, minz );
            printf("\nD kosesi x y z degerleri: %f %f %f", minx+maxuzunluk, miny+maxuzunluk, minz );
            printf("\nE kosesi x y z degerleri: %f %f %f", minx+maxuzunluk, miny, minz+maxuzunluk );
            printf("\nF kosesi x y z degerleri: %f %f %f", minx, miny, minz+maxuzunluk );
            printf("\nG kosesi x y z degerleri: %f %f %f", minx, miny+maxuzunluk, minz+maxuzunluk );
            printf("\nH kosesi x y z degerleri: %f %f %f", minx+maxuzunluk, miny+maxuzunluk, minz+maxuzunluk );

            output_dosya = fopen("output.nkt","a+");

            if(yazdirmaKontrol==0)
            {
                fprintf(output_dosya,"\nSECIM 3\n\n");
                yazdirmaKontrol++;
            }

            fprintf(output_dosya, "%s\n", dosya_adlari[s]);

            fprintf(output_dosya,"%f %f %f\n", minx+maxuzunluk, miny, minz );
            fprintf(output_dosya,"%f %f %f\n", minx, miny, minz );
            fprintf(output_dosya,"%f %f %f\n", minx, miny+maxuzunluk, minz );
            fprintf(output_dosya,"%f %f %f\n", minx+maxuzunluk, miny+maxuzunluk, minz );
            fprintf(output_dosya,"%f %f %f\n", minx+maxuzunluk, miny, minz+maxuzunluk );
            fprintf(output_dosya,"%f %f %f\n", minx, miny, minz+maxuzunluk );
            fprintf(output_dosya,"%f %f %f\n", minx, miny+maxuzunluk, minz+maxuzunluk );
            fprintf(output_dosya,"%f %f %f\n\n", minx+maxuzunluk, miny+maxuzunluk, minz+maxuzunluk );

            fclose(output_dosya);
        }
    }
}

void kure_hesapla()
{
    int yazdirmaKontrol=0;
    int sayac=0;
    double kure_x,kure_y,kure_z;
    double yaricap;
    double noktanin_merkeze_uzakligi=0;
    int kure_icindeki_nokta_sayisi=0;

    int max_nokta_sayisi=0;
    for(int s=0; s<dosya_sayisi; s++)
    {
        if(noktaSayilari[s]>max_nokta_sayisi)
        {
            max_nokta_sayisi=noktaSayilari[s];
        }
    }
    int kure_icindeki_nokta_indisleri[max_nokta_sayisi];
    int kure_dongu_degiskeni=0;

    printf("\nKurenin x degerini girin...");
    scanf("%lf",&kure_x);
    printf("Kurenin y degerini girin...");
    scanf("%lf",&kure_y);
    printf("Kurenin z degerini girin...");
    scanf("%lf",&kure_z);
    printf("Kurenin yaricapini girin...");
    scanf("%lf",&yaricap);

    for(int s=0; s<dosya_sayisi; s++)
    {
        sayac=0;
        kure_icindeki_nokta_sayisi=0;
        if(dosya_hata[s]==0)
        {
            printf("\n%s dosyasi icin belirtilen kurenin icinde kalan noktalar:\n",dosya_adlari[s]);
            for(i=0; i<noktaSayilari[s]; i++)
            {
                noktanin_merkeze_uzakligi = sqrt( pow( (str_nokta_bilgileri[s].x[i] - kure_x ), 2 ) +

                                                  pow( (str_nokta_bilgileri[s].y[i] - kure_y ), 2 ) +

                                                  pow( (str_nokta_bilgileri[s].z[i] - kure_z ), 2 ) );

                if(noktanin_merkeze_uzakligi<=yaricap)
                {
                    printf("%d. nokta > x: %f, y: %f, z: %f\n",kure_icindeki_nokta_sayisi+1,str_nokta_bilgileri[s].x[i],str_nokta_bilgileri[s].y[i],str_nokta_bilgileri[s].z[i]);
                    kure_icindeki_nokta_indisleri[kure_dongu_degiskeni]=i;
                    kure_icindeki_nokta_sayisi++;
                }
            }
            printf("\nKure icinde bulunan nokta sayisi: %d\n\n",kure_icindeki_nokta_sayisi);

            output_dosya = fopen("output.nkt","a+");

            if(yazdirmaKontrol==0)
            {
                fprintf(output_dosya,"\nSECIM 4\n\n");
                yazdirmaKontrol++;
            }

            fprintf(output_dosya, "%s\n", dosya_adlari[s]);

            fprintf(output_dosya,"cx=%lf\n",kure_x);
            fprintf(output_dosya,"cy=%lf\n",kure_y);
            fprintf(output_dosya,"cz=%lf\n",kure_z);
            fprintf(output_dosya,"cr=%lf\n",yaricap);

            if(rgbTipleri[s]==0)
            {
                fprintf(output_dosya,"ALANLAR x y z\n");
            }
            else if(rgbTipleri[s]==1)
            {
                fprintf(output_dosya,"ALANLAR x y z r g b\n");
            }

            fprintf(output_dosya,"NOKTALAR %d\n",noktaSayilari[s]);

            if(dataTipleri[s]==0)
            {
                fprintf(output_dosya,"DATA binary\n");
            }
            else if(dataTipleri[s]==1)
            {
                fprintf(output_dosya,"DATA ascii\n");
            }

            if(rgbTipleri[s]==0)
            {
                for(int a=0; a<noktaSayilari[s]; a++)
                {
                    for(int b=0; b<kure_icindeki_nokta_sayisi; b++)
                    {
                        if(kure_icindeki_nokta_indisleri[b]==a)
                        {
                            fprintf(output_dosya,"%f %f %f\n",str_nokta_bilgileri[s].x[b],str_nokta_bilgileri[s].y[b],str_nokta_bilgileri[s].z[b]);
                            sayac++;
                        }
                    }
                }
                fprintf(output_dosya,"Kure icindeki nokta sayisi: %d\n",sayac);
            }
            else if(rgbTipleri[s]==1)
            {
                for(int a=0; a<noktaSayilari[s]; a++)
                {
                    for(int b=0; b<kure_icindeki_nokta_sayisi; b++)
                    {
                        if(kure_icindeki_nokta_indisleri[b]==a)
                        {
                            fprintf(output_dosya,"%f %f %f %d %d %d\n", str_nokta_bilgileri[s].x[b],str_nokta_bilgileri[s].y[b],str_nokta_bilgileri[s].z[b],
                                    str_nokta_bilgileri[s].r[b],str_nokta_bilgileri[s].g[b],str_nokta_bilgileri[s].b[b]);
                            sayac++;
                        }
                    }
                }
                fprintf(output_dosya,"Kure icindeki nokta sayisi: %d\n",sayac);
            }
            fprintf(output_dosya,"\n");
            fclose(output_dosya);
        }
    }
}

void ortalama_hesapla()
{
    int yazdirmaKontrol=0;
    if(uzaklikHesaplandi==1)
    {
        for(int s=0; s<dosya_sayisi; s++)
        {
            if(dosya_hata[s]==0)
            {
                printf("\n%s dosyasindaki noktalarin uzakliklarinin ortalamasi: %f\n",dosya_adlari[s],ortalamaUzakliklar[s]);

                output_dosya = fopen("output.nkt","a+");


                if(yazdirmaKontrol==0)
                {
                    fprintf(output_dosya,"\nSECIM 5\n");
                    yazdirmaKontrol++;
                }

                fprintf(output_dosya, "\n%s\n", dosya_adlari[s]);

                fprintf(output_dosya,"%f\n",ortalamaUzakliklar[s]);

                fclose(output_dosya);
            }
        }
    }
    else
    {
        double uzaklik, enKucukUzaklik=10000.0, enBuyukUzaklik=0.0, uzaklikSayisi=0.0;

        for(int s=0; s<dosya_sayisi; s++)
        {
            if(dosya_hata[s]==0)
            {
                uzaklikSayisi=0.0;
                enKucukUzaklik=1000.0;
                enBuyukUzaklik=0.0;
                toplamUzakliklar[s]=0.0;
                for(int i=0; i<noktaSayilari[s]-1; i++)
                {
                    for(int j=i+1; j<noktaSayilari[s]; j++)
                    {
                        uzaklik=sqrt( pow( (str_nokta_bilgileri[s].x[i] - str_nokta_bilgileri[s].x[j] ), 2 ) +

                                      pow( (str_nokta_bilgileri[s].y[i] - str_nokta_bilgileri[s].y[j] ), 2 ) +

                                      pow( (str_nokta_bilgileri[s].z[i] - str_nokta_bilgileri[s].z[j] ), 2 ) );

                        if(uzaklik<enKucukUzaklik)
                        {
                            enKucukUzaklik=uzaklik;
                        }
                        if(uzaklik>enBuyukUzaklik)
                        {
                            enBuyukUzaklik=uzaklik;
                        }
                        toplamUzakliklar[s]+=uzaklik;
                        uzaklikSayisi+=1.0;
                    }
                }
                ortalamaUzakliklar[s]=toplamUzakliklar[s]/uzaklikSayisi;
                printf("\n%s dosyasindaki noktalarin uzakliklarinin ortalamasi: %f\n",dosya_adlari[s],ortalamaUzakliklar[s]);

                output_dosya = fopen("output.nkt","a+");

                if(yazdirmaKontrol==0)
                {
                    fprintf(output_dosya,"\nSECIM 5\n");
                    yazdirmaKontrol++;
                }

                fprintf(output_dosya, "%s\n", dosya_adlari[s]);

                fprintf(output_dosya,"%f\n",ortalamaUzakliklar[s]);

                fclose(output_dosya);
            }
        }
    }
}

void enyakin_ve_enuzak_noktalar()
{
    int yazdirmaKontrol=0;
    double uzaklik, enKucukUzaklik=100000.0, enBuyukUzaklik=0.0, uzaklikSayisi=0.0;
    int indiski=0, indiskj=0, indisbi=0, indisbj=0;

    for(int s=0; s<dosya_sayisi; s++)
    {
        if(dosya_hata[s]==0)
        {
            uzaklikSayisi=0.0;
            enKucukUzaklik=1000000.0;
            enBuyukUzaklik=0.0;
            toplamUzakliklar[s]=0.0;
            for(int i=0; i<noktaSayilari[s]-1; i++)
            {
                for(int j=i+1; j<noktaSayilari[s]; j++)
                {
                    uzaklik=sqrt( pow( (str_nokta_bilgileri[s].x[i] - str_nokta_bilgileri[s].x[j] ), 2 ) +

                                  pow( (str_nokta_bilgileri[s].y[i] - str_nokta_bilgileri[s].y[j] ), 2 ) +

                                  pow( (str_nokta_bilgileri[s].z[i] - str_nokta_bilgileri[s].z[j] ), 2 ) );
                    if(uzaklik<enKucukUzaklik)
                    {
                        enKucukUzaklik=uzaklik;
                        indiski=i, indiskj=j;
                    }
                    if(uzaklik>enBuyukUzaklik)
                    {
                        enBuyukUzaklik=uzaklik;
                        indisbi=i, indisbj=j;
                    }
                    toplamUzakliklar[s]+=uzaklik;
                    uzaklikSayisi+=1.0;
                }
            }
            ortalamaUzakliklar[s]=toplamUzakliklar[s]/uzaklikSayisi;
            uzaklikHesaplandi=1;

            printf("\n%s dosyasinin en yakin ve en uzak noktalari\n",dosya_adlari[s]);

            printf("NOKTANIN DEGERLERI EN YAKIN: %f %f %f\n",str_nokta_bilgileri[s].x[indiski],str_nokta_bilgileri[s].y[indiski],str_nokta_bilgileri[s].z[indiski]);
            printf("NOKTANIN DEGERLERI EN YAKIN: %f %f %f\n\n",str_nokta_bilgileri[s].x[indiskj],str_nokta_bilgileri[s].y[indiskj],str_nokta_bilgileri[s].z[indiskj]);

            printf("NOKTANIN DEGERLERI EN UZAK: %f %f %f\n",str_nokta_bilgileri[s].x[indisbi],str_nokta_bilgileri[s].y[indisbi],str_nokta_bilgileri[s].z[indisbi]);
            printf("NOKTANIN DEGERLERI EN UZAK: %f %f %f\n\n",str_nokta_bilgileri[s].x[indisbj],str_nokta_bilgileri[s].y[indisbj],str_nokta_bilgileri[s].z[indisbj]);

            output_dosya = fopen("output.nkt","a+");

            if(yazdirmaKontrol==0)
            {
                fprintf(output_dosya,"\nSECIM 2\n");
                yazdirmaKontrol++;
            }

            fprintf(output_dosya,"\n%s\n",dosya_adlari[s]);

            if(rgbTipleri[s]==0)
            {
                fprintf(output_dosya,"%f %f %f\n",str_nokta_bilgileri[s].x[indiski],str_nokta_bilgileri[s].y[indiski],str_nokta_bilgileri[s].z[indiski]);
                fprintf(output_dosya,"%f %f %f\n",str_nokta_bilgileri[s].x[indiskj],str_nokta_bilgileri[s].y[indiskj],str_nokta_bilgileri[s].z[indiskj]);

                fprintf(output_dosya,"%f %f %f\n",str_nokta_bilgileri[s].x[indisbi],str_nokta_bilgileri[s].y[indisbi],str_nokta_bilgileri[s].z[indisbi]);
                fprintf(output_dosya,"%f %f %f\n",str_nokta_bilgileri[s].x[indisbj],str_nokta_bilgileri[s].y[indisbj],str_nokta_bilgileri[s].z[indisbj]);
            }
            else if(rgbTipleri[s]==1)
            {
                fprintf(output_dosya,"%f %f %f %d %d %d\n", str_nokta_bilgileri[s].x[indiski],str_nokta_bilgileri[s].y[indiski],str_nokta_bilgileri[s].z[indiski],
                        str_nokta_bilgileri[s].r[indiski],str_nokta_bilgileri[s].g[indiski],str_nokta_bilgileri[s].b[indiski]);

                fprintf(output_dosya,"%f %f %f %d %d %d\n", str_nokta_bilgileri[s].x[indiskj],str_nokta_bilgileri[s].y[indiskj],str_nokta_bilgileri[s].z[indiskj],
                        str_nokta_bilgileri[s].r[indiskj],str_nokta_bilgileri[s].g[indiskj],str_nokta_bilgileri[s].b[indiskj]);

                fprintf(output_dosya,"%f %f %f %d %d %d\n", str_nokta_bilgileri[s].x[indisbi],str_nokta_bilgileri[s].y[indisbi],str_nokta_bilgileri[s].z[indisbi],
                        str_nokta_bilgileri[s].r[indisbi],str_nokta_bilgileri[s].g[indisbi],str_nokta_bilgileri[s].b[indisbi]);

                fprintf(output_dosya,"%f %f %f %d %d %d\n", str_nokta_bilgileri[s].x[indisbj],str_nokta_bilgileri[s].y[indisbj],str_nokta_bilgileri[s].z[indisbj],
                        str_nokta_bilgileri[s].r[indisbj],str_nokta_bilgileri[s].g[indisbj],str_nokta_bilgileri[s].b[indisbj]);
            }
            fclose(output_dosya);
        }
    }
}

int nokta_bilgi_kontrolu(char satirTutucu[],int satir)
{
    int x=0;
    int bosluk_sayisi=0, nokta_hatasi=0;
    for(x=0; satirTutucu[x]!='\0'; x++)
    {
        if(satirTutucu[x]==' ')
        {
            bosluk_sayisi++;
        }
    }
    satir++;

    if(rgb_kontrol==0)
    {
        if(bosluk_sayisi<2)
        {
            printf("\n%d. noktanin x y z degerleri eksik verilmistir!",satir);
            nokta_hatasi=1;
            sprintf(noktaHatalariniTut[k]+strlen(noktaHatalariniTut[k]),"\n%d. noktanin x y z degerleri eksik verilmistir!",satir);

        }
        else if(bosluk_sayisi>2)
        {
            printf("\n%d noktasi ekstra bilgiye sahiptir!",satir);
            nokta_hatasi=1;
            sprintf(noktaHatalariniTut[k]+strlen(noktaHatalariniTut[k]),"\n%d. noktasi ekstra bilgiye sahiptir!",satir);
        }
    }

    else if(rgb_kontrol==1)
    {

        if(bosluk_sayisi<2)
        {
            printf("\n%d. noktanin x y z ve r g b degerleri eksik verilmistir!",satir);
            nokta_hatasi=1;
            sprintf(noktaHatalariniTut[k]+strlen(noktaHatalariniTut[k]),"\n%d. noktanin x y z ve r g b degerleri eksik verilmistir!",satir);

        }
        else if(bosluk_sayisi<5)
        {
            printf("\n%d. noktanin r g b degerleri eksik verilmistir!",satir);
            nokta_hatasi=1;
            sprintf(noktaHatalariniTut[k]+strlen(noktaHatalariniTut[k]),"\n%d. noktanin r g b degerleri eksik verilmistir!",satir);


        }
        else if(bosluk_sayisi>5)
        {
            printf("\n%d noktasi ekstra bilgiye sahiptir!",satir);
            nokta_hatasi=1;
            sprintf(noktaHatalariniTut[k]+strlen(noktaHatalariniTut[k]),"\n%d. noktasi ekstra bilgiye sahiptir!",satir);

        }
    }
    if(nokta_hatasi==1)
    {
        noktaHatalariniTut[k] = realloc(noktaHatalariniTut[k], strlen(noktaHatalariniTut[k])+60);
    }
    return nokta_hatasi;
}

void binary_deger_oku(FILE *dosya)
{
    if(rgb_kontrol==0)
    {
        f=0,g=0,h=0,r=0,t=0,y=0,u=0;
        while(1)
        {
            size_t sayi;
            sayi=fread(&xyz,sizeof(float),1,dosya);
            if(sayi<1)
            {
                break;
            }

            if(f%3==0)
            {
                str_nokta_bilgileri[k].x[g]=xyz;
                g++;
                str_nokta_bilgileri[k].x=realloc(str_nokta_bilgileri[k].x,(g+1)*sizeof(double));
            }
            if(f%3==1)
            {
                str_nokta_bilgileri[k].y[h]=xyz;
                h++;
                str_nokta_bilgileri[k].y=realloc(str_nokta_bilgileri[k].y,(h+1)*sizeof(double));
            }
            if(f%3==2)
            {
                str_nokta_bilgileri[k].z[r]=xyz;
                r++;
                str_nokta_bilgileri[k].z=realloc(str_nokta_bilgileri[k].z,(r+1)*sizeof(double));
            }
            f++;
        }

        noktaSayilari[k]=f/3;
        if(noktaSayilari[k]!=nokta_sayisi)
        {
            printf("%s dosyasindaki nokta sayisi gecerli degildir.\n",dosya_adlari[k]);
            sprintf(noktaEslesmeHatalariniTut[k]+strlen(noktaEslesmeHatalariniTut[k])," dosyasindaki nokta sayisi gecerli degildir.");
            noktaEslesmeHatalariniTut[k] = realloc(noktaEslesmeHatalariniTut[k], strlen(noktaEslesmeHatalariniTut[k])+100);
            sonNoktaEslesmeHatasi[k]=1;
            dosya_hata[k]=1;
        }
        else
        {
            printf("%s dosyasi basariyla okundu.\n",dosya_adlari[k]);
        }
    }

    else if(rgb_kontrol==1)
    {
        f=0,g=0,h=0,r=0,t=0,y=0,u=0;
        while(1)
        {
            size_t sayi;
            if(f%6 < 3)
            {
                sayi=fread(&xyz,sizeof(float),1,dosya);
                if(sayi<1)
                {
                    break;
                }

                if(f%3==0)
                {
                    str_nokta_bilgileri[k].x[g]=xyz;
                    g++;
                    str_nokta_bilgileri[k].x=realloc(str_nokta_bilgileri[k].x,(g+1)*sizeof(double));
                }
                if(f%3==1)
                {
                    str_nokta_bilgileri[k].y[h]=xyz;
                    h++;
                    str_nokta_bilgileri[k].y=realloc(str_nokta_bilgileri[k].y,(h+1)*sizeof(double));
                }
                if(f%3==2)
                {
                    str_nokta_bilgileri[k].z[r]=xyz;
                    r++;
                    str_nokta_bilgileri[k].z=realloc(str_nokta_bilgileri[k].z,(r+1)*sizeof(double));
                }
            }
            else
            {
                sayi=fread(&rgb,sizeof(float),1,dosya);
                if(sayi<1)
                {
                    break;
                }

                if(f%3==0)
                {
                    str_nokta_bilgileri[k].r[t]=rgb;
                    t++;
                    str_nokta_bilgileri[k].r=realloc(str_nokta_bilgileri[k].r,(t+1)*sizeof(int));
                }
                if(f%3==1)
                {
                    str_nokta_bilgileri[k].g[y]=rgb;
                    y++;
                    str_nokta_bilgileri[k].g=realloc(str_nokta_bilgileri[k].g,(y+1)*sizeof(int));
                }
                if(f%3==2)
                {
                    str_nokta_bilgileri[k].b[u]=rgb;
                    u++;
                    str_nokta_bilgileri[k].b=realloc(str_nokta_bilgileri[k].b,(u+1)*sizeof(int));
                }
            }
            f++;
        }
        noktaSayilari[k]=f/6;
        if(noktaSayilari[k]!=nokta_sayisi)
        {
            printf("%s dosyasindaki nokta sayisi gecerli degildir.\n",dosya_adlari[k]);
            sprintf(noktaEslesmeHatalariniTut[k]+strlen(noktaEslesmeHatalariniTut[k])," dosyasindaki nokta sayisi gecerli degildir.");
            noktaEslesmeHatalariniTut[k] = realloc(noktaEslesmeHatalariniTut[k], strlen(noktaEslesmeHatalariniTut[k])+100);
            sonNoktaEslesmeHatasi[k]=1;
            dosya_hata[k]=1;
        }
        else
        {
            printf("%s dosyasi basariyla okundu.\n",dosya_adlari[k]);
        }
    }
    k++;
}

int ascii_deger_oku(FILE *dosya)
{
    char satirTutucu[100];
    int satir=0;
    int nokta_bilgi_hatasi=0;
    int overallhata=0;
    sonNoktaHatasi[k]=0;

    if(rgb_kontrol==0)
    {

        while( (fgets(satirTutucu,100,dosya))!=NULL )
        {
            char sayi1[20], sayi2[20], sayi3[20];
            sscanf(satirTutucu,"%s %s %s",sayi1,sayi2,sayi3);

            str_nokta_bilgileri[k].x[satir]=atof(sayi1);
            str_nokta_bilgileri[k].y[satir]=atof(sayi2);
            str_nokta_bilgileri[k].z[satir]=atof(sayi3);

            nokta_bilgi_hatasi=nokta_bilgi_kontrolu(satirTutucu,satir);
            if(nokta_bilgi_hatasi==1)
            {
                overallhata=1;
                sonNoktaHatasi[k]=1;
            }

            satir++;
            gercek_nokta_sayisi = satir;

            str_nokta_bilgileri[k].x=realloc(str_nokta_bilgileri[k].x,(satir+1)*sizeof(double));
            str_nokta_bilgileri[k].y=realloc(str_nokta_bilgileri[k].y,(satir+1)*sizeof(double));
            str_nokta_bilgileri[k].z=realloc(str_nokta_bilgileri[k].z,(satir+1)*sizeof(double));
        }
    }

    else if(rgb_kontrol==1)
    {
        while( (fgets(satirTutucu,100,dosya))!=NULL )
        {
            char sayi1[20], sayi2[20], sayi3[20], renk1[20], renk2[20], renk3[20];
            sscanf(satirTutucu,"%s %s %s %s %s %s",sayi1,sayi2,sayi3,renk1,renk2,renk3);

            str_nokta_bilgileri[k].x[satir]=atof(sayi1);
            str_nokta_bilgileri[k].y[satir]=atof(sayi2);
            str_nokta_bilgileri[k].z[satir]=atof(sayi3);
            str_nokta_bilgileri[k].r[satir]=atoi(renk1);
            str_nokta_bilgileri[k].g[satir]=atoi(renk2);
            str_nokta_bilgileri[k].b[satir]=atoi(renk3);

            nokta_bilgi_hatasi=nokta_bilgi_kontrolu(satirTutucu,satir);
            if(nokta_bilgi_hatasi==1)
            {
                overallhata=1;
                sonNoktaHatasi[k]=1;
            }

            satir++;
            gercek_nokta_sayisi = satir;

            str_nokta_bilgileri[k].x=realloc(str_nokta_bilgileri[k].x,(satir+1)*sizeof(double));
            str_nokta_bilgileri[k].y=realloc(str_nokta_bilgileri[k].y,(satir+1)*sizeof(double));
            str_nokta_bilgileri[k].z=realloc(str_nokta_bilgileri[k].z,(satir+1)*sizeof(double));
            str_nokta_bilgileri[k].r=realloc(str_nokta_bilgileri[k].r,(satir+1)*sizeof(int));
            str_nokta_bilgileri[k].g=realloc(str_nokta_bilgileri[k].g,(satir+1)*sizeof(int));
            str_nokta_bilgileri[k].b=realloc(str_nokta_bilgileri[k].b,(satir+1)*sizeof(int));
        }
    }

    if(overallhata==1)
    {
        printf("\n%s dosyasindaki nokta bilgileri hatali verilmistir.\n",dosya_adlari[k]);
    }
    if(gercek_nokta_sayisi!=nokta_sayisi)
    {
        printf("\n\n%s dosyasindaki nokta sayisi gecerli degildir.\n",dosya_adlari[k]);
        sprintf(noktaEslesmeHatalariniTut[k]+strlen(noktaEslesmeHatalariniTut[k])," dosyasindaki nokta sayisi gecerli degildir.");
        noktaEslesmeHatalariniTut[k] = realloc(noktaEslesmeHatalariniTut[k], strlen(noktaEslesmeHatalariniTut[k])+100);
        sonNoktaEslesmeHatasi[k]=1;
        overallhata=1;
    }
    if(overallhata==0 && dosya_hata[k]==0)
    {
        printf("%s dosyasi basariyla okundu.\n",dosya_adlari[k]);
        noktaSayilari[k]=gercek_nokta_sayisi;
    }

    k++;
    return overallhata;
}

int baslik_hata_kontrolu (FILE *dosya)
{
    char satir_okuyucu[150];
    char c;
    int i=0, satir, karsilastirma_degiskeni, baslik_hatasi=0;
    for(satir=0; satir<5; satir++)
    {
        while ((c=fgetc(dosya))!=EOF)
        {
            if(c!='\n')
            {
                satir_okuyucu[i]=c;
                i++;
            }
            else if(c=='\n')
            {
                satir_okuyucu[i]='\0';
                i=0;
                break;
            }
        }
        switch(satir)
        {
        case 0:
            karsilastirma_degiskeni=strcmp(satir_okuyucu,"# Noktalar dosya format");
            if(karsilastirma_degiskeni==0)
            {
                printf("\n->Aciklama satiri kontrolu basarili");
            }
            else
            {
                printf("\n->Aciklama satiri hatali verilmistir");
                strcpy(baslikHatalariniTut[k]+strlen(baslikHatalariniTut[k]),"\n->Aciklama satiri hatali verilmistir");
				baslikHatalariniTut[k] = realloc(baslikHatalariniTut[k], strlen(baslikHatalariniTut[k])+100);
                baslik_hatasi=1;
            }
            break;
        case 1:
            karsilastirma_degiskeni=strcmp(satir_okuyucu,"VERSION 1");
            if(karsilastirma_degiskeni==0)
            {
                printf("\n->Versiyon no kontrolu basarili");
            }
            else
            {
                printf("\n->Versiyon no hatali verilmistir");
                strcpy(baslikHatalariniTut[k]+strlen(baslikHatalariniTut[k]),"\n->Versiyon no hatali verilmistir");
				baslikHatalariniTut[k] = realloc(baslikHatalariniTut[k], strlen(baslikHatalariniTut[k])+100);
                baslik_hatasi=1;
            }
            break;
        case 2:
            karsilastirma_degiskeni=strcmp(satir_okuyucu,"ALANLAR x y z");
            if(karsilastirma_degiskeni==0)
            {
                printf("\n->Alanlar kontrolu basarili, kontrol edilen x y z");
                rgb_kontrol=0;
                break;
            }
            if(karsilastirma_degiskeni!=0)
            {
                karsilastirma_degiskeni=strcmp(satir_okuyucu,"ALANLAR x y z r g b");
                if(karsilastirma_degiskeni==0)
                {
                    printf("\n->Alanlar kontrolu basarili, kontrol edilen x y z r g b");
                    rgb_kontrol=1;
                }
                else
                {
                    printf("\n->Alanlar bilgisi hatali verilmistir");
                    strcpy(baslikHatalariniTut[k]+strlen(baslikHatalariniTut[k]),"\n->Alanlar bilgisi hatali verilmistir");
					baslikHatalariniTut[k] = realloc(baslikHatalariniTut[k], strlen(baslikHatalariniTut[k])+100);
                    baslik_hatasi=1;
                    rgb_kontrol=1;
                }
            }
            break;
        case 3:
            nokta_sayisi=atoi(&satir_okuyucu[8]);
            char satir_tutucu[30]="NOKTALAR ";
            sprintf((satir_tutucu+9), "%d", nokta_sayisi);
            karsilastirma_degiskeni=strcmp(satir_okuyucu,satir_tutucu);
            if(karsilastirma_degiskeni==0)
            {
                printf("\n->Nokta aciklamasi kontrolu basarili, belirtilen nokta sayisi:%d",nokta_sayisi);
            }
            else
            {
                printf("\n->Nokta aciklamasi hatali verilmistir");
                strcpy(baslikHatalariniTut[k]+strlen(baslikHatalariniTut[k]),"\n->Nokta aciklamasi hatali verilmistir");
				baslikHatalariniTut[k] = realloc(baslikHatalariniTut[k], strlen(baslikHatalariniTut[k])+100);
                baslik_hatasi=1;
            }
            break;
        case 4:
            karsilastirma_degiskeni=strcmp(satir_okuyucu,"DATA ascii");
            if(karsilastirma_degiskeni==0)
            {
                printf("\n->Dosya ascii olarak okunacaktir");
                ascii_kontrol=1;
                break;
            }
            if(karsilastirma_degiskeni!=0)
            {
                karsilastirma_degiskeni=strcmp(satir_okuyucu,"DATA binary");
                if(karsilastirma_degiskeni==0)
                {
                    printf("\n->Dosya binary olarak okunacaktir");
                    ascii_kontrol=0;
                }
                else
                {
                    printf("\n->DATA bilgisi hatali verilmistir");
                    strcpy(baslikHatalariniTut[k]+strlen(baslikHatalariniTut[k]),"\n->DATA bilgisi hatali verilmistir");
					baslikHatalariniTut[k] = realloc(baslikHatalariniTut[k], strlen(baslikHatalariniTut[k])+100);
                    baslik_hatasi=1;
                }
            }
            break;
        }
    }
    sonBaslikHatasi[k]=baslik_hatasi;
    return baslik_hatasi;
}

void dosyalari_oku_ve_kontrol_et()
{
    int hata=0;
    for(i=0; i<dosya_sayisi; i++)
    {
        hata=0;
        FILE *dosya=fopen(dosya_adlari[i],"r");
        if(dosya==NULL)
        {
            printf("HATA: %s dosyasi acilamadi!\n",dosya_adlari[i]);
        }
        else
        {
            printf("\n\n\n^^^^^ %s isimli dosyanin baslik kontrolleri ^^^^^\n", dosya_adlari[i]);

            int karsilastirma_degiskeni = baslik_hata_kontrolu(dosya);

            if(karsilastirma_degiskeni==1)
            {
                printf("\n\n!!! %s dosyasinin baslik bilgileri hatali !!!\n\n",dosya_adlari[i]);
                dosya_hata[i]=karsilastirma_degiskeni;
                rgbTipleri[i]=rgb_kontrol;
                dataTipleri[i]=ascii_kontrol;

                switch(ascii_kontrol)
                {
                case 0:
                    binary_deger_oku(dosya);
                    break;
                case 1:
                    ascii_deger_oku(dosya);
                    break;
                }
            }
            else if(karsilastirma_degiskeni==0)
            {
                printf("\n\n%s dosyasinin baslik bilgileri basarili,\nnokta bilgileri kontrol edilip okumaya karar verilecek...\n\n", dosya_adlari[i]);

                rgbTipleri[i]=rgb_kontrol;
                dataTipleri[i]=ascii_kontrol;

                switch(ascii_kontrol)
                {
                case 0:
                    binary_deger_oku(dosya);
                    break;
                case 1:
                    hata=ascii_deger_oku(dosya);
                    dosya_hata[i]=hata;
                    break;
                }
            }
        }
        fclose(dosya);
    }
    output_olustur();
}

void her_dosya_icin_bellek_ayir()
{
    str_nokta_bilgileri=malloc(dosya_sayisi*sizeof(struct NOKTALAR));

    for(i=0; i<dosya_sayisi; i++)
    {
        str_nokta_bilgileri[i].x=malloc(sizeof(double));
        str_nokta_bilgileri[i].y=malloc(sizeof(double));
        str_nokta_bilgileri[i].z=malloc(sizeof(double));
        str_nokta_bilgileri[i].r=malloc(sizeof(int));
        str_nokta_bilgileri[i].g=malloc(sizeof(int));
        str_nokta_bilgileri[i].b=malloc(sizeof(int));
    }
}

void nkt_dosyalarini_al()
{
    struct dirent *dosya_adi;
    DIR *klasor = opendir(".");

    if (klasor == NULL)
    {
        printf("HATA: Klasor acilamadi!\n");
        exit(1);
    }

    while ((dosya_adi = readdir(klasor)) != NULL)
    {
        dosyalar[i] = malloc(strlen(dosya_adi->d_name)+1);
        strcpy(dosyalar[i], dosya_adi->d_name);
        i++;
        gecici_dosya_sayisi++;
    }

    int son_elemanin_indexi;
    for(i=0; i<gecici_dosya_sayisi; i++)
    {

        son_elemanin_indexi =  strlen(dosyalar[i])-1;
        if( dosyalar[i][son_elemanin_indexi]  =='t' &&
                dosyalar[i][son_elemanin_indexi-1]=='k' &&
                dosyalar[i][son_elemanin_indexi-2]=='n' &&
                dosyalar[i][son_elemanin_indexi-3]=='.' &&
                strstr(dosyalar[i],"output")==NULL        )
        {
            dosya_adlari[dosya_sayisi] = malloc(strlen(dosyalar[i])+1);
            strcpy(dosya_adlari[dosya_sayisi], dosyalar[i]);
            dosya_sayisi++;
        }
    }
    closedir(klasor);
    for(i=0; i<dosya_sayisi; i++)
    {
        noktaHatalariniTut[i] = malloc(100);
        baslikHatalariniTut[i] = malloc(100);
        noktaEslesmeHatalariniTut[i] = malloc(100);
        printf("%d. indis %s\n",i, dosya_adlari[i]);
        strcpy(noktaHatalariniTut[i],dosya_adlari[i]);
        strcpy(baslikHatalariniTut[i],dosya_adlari[i]);
        strcpy(noktaEslesmeHatalariniTut[i],dosya_adlari[i]);
    }
}

void menuyu_goster()
{
    int secim;
    int islem1kontrol=0;
    do
    {
        printf("\n-------------------------------------------");
        printf("\n\n* * * * * * * *  M E N U  * * * * * * * *\n\n");
        printf("1 > Dosya Kontrolu\n");
        printf("2 > En Yakin & En Uzak Noktalar\n");
        printf("3 > En Kucuk Kup\n");
        printf("4 > Kure Icerisindeki Noktalar\n");
        printf("5 > Noktalar Arasi Uzakliklari Ortalamasi\n");
        printf("6 > Cikis\n\n");
        printf("Yapmak istediginiz islemi seciniz...\n");
        printf("-------------------------------------------\n");

        scanf("%d",&secim);
        fflush(stdin);

        switch(secim)
        {
        case 1:
            if(islem1kontrol==1)
            {
                printf("Dosyalar zaten kontrol edildi! Farkli bir islem yapmayi deneyin...\n");
                break;
            }
            printf("##### Dosyalari oku ve kontrol et #####\n");
            dosyalari_oku_ve_kontrol_et();
            islem1kontrol=1;
            break;
        case 2:
            if(islem1kontrol==0)
            {
                printf("Dosyalar kontrol edilmedi! Lutfen ilk olarak 1. islemi calistiriniz...");
                break;
            }
            printf("##### En yakin ve en uzak noktalar #####\n");
            enyakin_ve_enuzak_noktalar();
            break;
        case 3:
            if(islem1kontrol==0)
            {
                printf("Dosyalar kontrol edilmedi! Lutfen ilk olarak 1. islemi calistiriniz...");
                break;
            }
            printf("##### Kup testi #####\n");
            kup_hesapla();
            break;
        case 4:
            if(islem1kontrol==0)
            {
                printf("Dosyalar kontrol edilmedi! Lutfen ilk olarak 1. islemi calistiriniz...");
                break;
            }
            printf("##### Kure testi #####\n");
            kure_hesapla();
            break;
        case 5:
            if(islem1kontrol==0)
            {
                printf("Dosyalar kontrol edilmedi! Lutfen ilk olarak 1. islemi calistiriniz...");
                break;
            }
            printf("##### Nokta uzakliklari ortalamasi #####\n");
            ortalama_hesapla();
            break;
        case 6:
            printf("Cikis yapiliyor\n");
            exit(1);
            break;
        default:
            printf("Gecersiz secim!\n");
            break;
        }
    }
    while(secim!=6);
}

int main()
{
    nkt_dosyalarini_al();
    her_dosya_icin_bellek_ayir();
    menuyu_goster();
    return 0;
}
