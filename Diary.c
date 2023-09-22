//Library Import
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Functiton
int login();
void write();
void read();
void delete();
void change();

//Global Variabel
char inputUser[10];
char inputPass[10];
char dummy[10000];
char user[10];
char pass[10];

typedef struct data
{
    char tanggal[9];
    char jam[6];
    char judul[50];
    char isi[1500];
}data[500];

char lanjut;
int pilihan;
int i;
int z = 0;

FILE *fp, *temp_fp, *passwd, *temp_passwd;

//Program Code
int main(){
    passwd = fopen("pass.txt", "r");
    fscanf(passwd, "%[^,],%[^\n]",user,pass);
    int awal = login();
    fclose(passwd);
    if (awal == 0)
    {
        while(pilihan != 5){
            start:
            system("cls");
            printf("=================================\n");
            printf("|\tMy Personal Diary\t|\n");
            printf("=================================\n\n\n");
            printf("Menu yang tersedia: \n");
            printf("1. Menulis buku harian baru\n");
            printf("2. Membaca buku harian yang tersedia\n");
            printf("3. Menghapus buku harian yang tersedia\n");
            printf("4. Ganti Username dan ganti Password\n");
            printf("5. Exit\n");
            printf("Pilihan anda:  ");
            scanf("%d", &pilihan);
            getchar();
            switch (pilihan)
            {
                case 1:
                    write();
                    break;
                case 2:
                    read();
                    break;
                case 3:
                    read();               
                    delete();
                    remove("dataDiary.txt");
                    rename("temp_file.txt", "dataDiary.txt");
                    break;
                case 4:
                    change();
                    remove("pass.txt");
                    rename("temp_pass.txt", "pass.txt");
                    break;
                case 5:
                    printf("Sampai jumpa lagi :)\n");
                    break;                
                default:
                    printf("Input salah\n");
                    printf("Input 1 untuk kembali ke menu\n");
                    printf("input 2 untuk keluar dari aplikasi\n");
                    printf("Pilihan anda:  ");
                    scanf("%d", &pilihan);
                    if(pilihan == 1){
                        goto start;
                    }else{
                        printf("Sampai jumpa lagi :)\n");
                    }
                    break;
            } 
        }
    }
    else{
        printf("Error! Silahkan Restart Program!\n");
    }
    
    return 0;
}

//login
int login(){
    system("cls");
    printf("LOGIN PAGE\n");
    printf("Username : ");
	scanf("%s", &inputUser);
    getchar();  
    printf("Password : ");
	scanf("%s", &inputPass);

    int hasilLogin = strcmp(inputUser,user) + strcmp(inputPass,pass);

    return hasilLogin;
}

//write
void write(){
    system("cls");
    fp = fopen("dataDiary.txt", "a");
    data akun;

    printf("Tanggal diary (ddmmyyyy) :");
    scanf("%[^\n]", akun[z].tanggal);
    getchar();
    fprintf(fp, "%s,", akun[z].tanggal);

    printf("Jam (hh:mm) :  ");
    scanf("%s", akun[z].jam);
    getchar();
    fprintf(fp, "%s,", akun[z].jam);

    printf("Judul: ");
    scanf("%[^\n]", akun[z].judul);
    getchar();
    fprintf(fp, "%s,", akun[z].judul);
    
    printf("Program kami dapat menampung --- kata\n");
    printf("Isi: \n");
    scanf("%[^\n]", akun[z].isi);
    getchar();
    fprintf(fp, "%s#", akun[z].isi);
    
    do{
        printf("Lanjut? y/n\n>>");
        scanf("%c", &lanjut);
        getchar();
        if (lanjut == 'y'){
            scanf("%[^\n]", akun[z].isi);
            getchar();
            fprintf(fp, "%s#", akun[z].isi);
        }
        
        else if (lanjut == 'n'){
            fprintf(fp, "\n");        
            break;
        }
    }while(lanjut == 'y');
    
    z++;
    fclose(fp);
}

//read
void read(){
    fp = fopen("dataDiary.txt", "r");
    data akun;
    int zz=0;
    int pilih;
    while (!feof(fp)){
        fscanf(fp,"%[^,],%[^,],%[^,],%[^\n]\n", akun[zz].tanggal, akun[zz].jam, akun[zz].judul, akun[zz].isi);
        printf("%d. %s, %s, %s\n", zz+1,akun[zz].tanggal, akun[zz].jam, akun[zz].judul);
        zz++;
    }
    
    if (pilihan == 2)
    {
        printf("Data mana yang ingin dibaca?: ");
        scanf("%d", &pilih);
        getchar();
        system("cls");
        char tanggalbaru[10];
        strcpy(tanggalbaru, akun[pilih-1].tanggal);

        printf("%c%c",tanggalbaru[0],tanggalbaru[1]);

        if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='1'){
            printf(" Januari ");
        } 
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='2'){
            printf(" Februari ");
        } 
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='3'){
            printf(" Maret ");
        }
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='4'){
            printf(" April ");
        } 
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='5'){
            printf(" Mei ");
        }
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='6'){
            printf(" Juni ");
        }
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='7'){
            printf(" Juli ");
        }
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='8'){
            printf(" Agustus ");
        }    
        else if (tanggalbaru[2]=='0'&&tanggalbaru[3]=='9'){
            printf(" September ");
        }
        else if (tanggalbaru[2]=='1'&&tanggalbaru[3]=='0'){
            printf(" Oktober ");
        }
        else if (tanggalbaru[2]=='1'&&tanggalbaru[3]=='1'){
            printf(" November ");
        }
        else if (tanggalbaru[2]=='1'&&tanggalbaru[3]=='2'){
            printf(" Desember ");
        }

        printf("%c%c%c%c\n",tanggalbaru[4],tanggalbaru[5],tanggalbaru[6],tanggalbaru[7]);

        int panjang = strlen(akun[pilih-1].isi);
        for (int xcv = 0; xcv < panjang; xcv++)
        {
            if (akun[pilih-1].isi[xcv]=='#')
            {
                akun[pilih-1].isi[xcv]='\n';
            }
        }

        printf("%s\n", akun[pilih-1].jam);
        printf("\t\t\t%s\n\n", akun[pilih-1].judul);
        printf("%s", akun[pilih-1].isi);
        
        getchar();
    }
    fclose(fp);
} 

//delete
void delete(){
    int hapusBaris;
    int baca = 1;
	int baris = 1;
    fp = fopen("dataDiary.txt", "r");
    temp_fp = fopen("temp_file.txt", "w");
    printf("Pilih data yang ingin dihapus: ");
    scanf("%d", &hapusBaris);
    getchar();
    
    while (baca){
		//Mengambil 1 baris pada fp, lalu menyimpannya di dalam variabel dummy
    	fgets(dummy, 500000, fp);

		//Jika sudah berada di akhir baris file
    	if(feof(fp)){
        	baca = 0;   
    	}

		//Jika baris yang yang sedang diambil tidak sama dengan baris yang mau dihapus
	    else if(baris != hapusBaris){
        	fputs(dummy, temp_fp);
		}
		baris++;
    }
    fclose(fp);
    fclose(temp_fp);
}

void change(){
    system("cls");

    passwd = fopen("pass.txt", "a");
    temp_passwd = fopen("temp_pass.txt", "w");

    fscanf(passwd, "%[^,],%[^\n]",user,pass);

    printf("Masukkan username baru : ");
    scanf("%s", user);
    getchar();

    printf("Masukkan password baru : ");
    scanf("%s", pass);
    getchar();

    fprintf(temp_passwd,"%s,%s",user,pass);

    fclose(passwd);
    fclose(temp_passwd);
    
    printf("Username dan Password anda berhasil dirubah!\n");
    getchar();
}