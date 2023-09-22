//Library Import
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 4000
#define clean system("cls")
#define enter printf("Tekan Enter untuk kembali ke menu!\n")

//Functiton declaration
int login();
/*Fungsi untuk mengeprint halaman login dan akan mereturn int hasilLogin 
yang merupakan hasil pembandingan dua buah string*/

void menu();
/*Fungsi untuk mengeprint halaman menu*/

void write();
/*Fungsi untuk menambahkan diary*/

int cekTanggal(int periksaTanggal, int periksaBulan, int periksaTahun);
/*Fungsi untuk mengecek apakah tanggal sesuai dengan tanggal pada kalender*/

int cekBulan(int periksaBulan);
/*Fungsi untuk mengecek apakah bulan sesuai dengan tanggal pada kalender*/

void bulan();
/*Fungsi untuk mengeprint bulan dalam kata */

void read();
/*Fungsi untuk membaca diary yang sudah ditulis*/

void delete();
/*Fungsi untuk mendelet diary yang ingin dihapus*/

//Global Variabel
char inputPass[10];
char buffer[4065];
int jumlahData = 0;
int pilihan;

//Struct
typedef struct data{
    int tanggal;
    int bulan;
    int tahun;
    char judul[50];
    char isi[SIZE];
}data[500];

//File Processing
FILE *fp, *temp_fp;

//Program Code
int main(){
    
    //Mendapatkan nilai dari int hasilLogin 
    int awal = login();

    //Jika hasilLogin = 0 (password yang dimasukkan benar)
    if (awal == 0)
    {
        //Menjalankan program minimal 1x
        do{
            start:     //label nama untuk jumping statement.

            //Menjalankan fungsi menu
            menu();
            scanf("%d", &pilihan);
            getchar();

            //Menuju menu yang diinput
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
                    /*Mendelet dataDiary.txt dan merename 
                    temp_file.txt menjadi dataDiary.txt*/
                    remove("dataDiary.txt");
                    rename("temp_file.txt", "dataDiary.txt");
                    break;

                case 4:
                    printf("Sampai jumpa lagi :)\n");
                    break; 

                //Jika input != 4
                default:

                    konfirmasi:     //label nama untuk jumping statement.
                    printf("Input salah\n");
                    printf("Ketik 1 untuk kembali ke menu\n");
                    printf("Ketik 2 untuk keluar dari aplikasi\n");
                    printf("Pilihan anda:\n>> ");
                    scanf("%d", &pilihan);
                
                    //Jika ingin kembali ke menu
                    if(pilihan == 1){
                        goto start;     //Jumping statement
                    }

                    //Jika ingin mengakhiri program
                    else if (pilihan == 2){
                        pilihan = 4;
                        printf("Sampai jumpa lagi :)\n");
                    }

                    else{
                        printf("Error! \n");
                        goto konfirmasi;     //Jumping statement
                    }
                    break;
            } 
        }while(pilihan != 4); //Dilakukan selama pilihan != 4
    }

    //Jika hasilLogin != 0 (password yang dimasukkan salah)
    else{
        printf("Error! Silahkan Restart Program!\n");
    }
    
    return 0;
}

//login
int login(){
    clean;
    printf("=================================\n");
    printf("|\tMy Personal Diary\t|\n");
    printf("=================================\n");
    printf("LOGIN PAGE\n");
    printf("Input Password : ");
	scanf("%s", &inputPass);
    getchar();
    
    //Melakukan compare string
    int hasilLogin = strcmp(inputPass,"kelompok1");
    return hasilLogin;
}

//Menu
void menu(){
    clean;
    printf("=================================\n");
    printf("|\tMy Personal Diary\t|\n");
    printf("=================================\n");
    printf("Menu yang tersedia: \n");
    printf("1. Menulis buku harian baru\n");
    printf("2. Membaca buku harian yang tersedia\n");
    printf("3. Menghapus buku harian yang tersedia\n");
    printf("4. Exit\n");
    printf("Pilihan anda:\n>> ");
}

//write
void write(){
    clean;
    fp = fopen("dataDiary.txt", "a");
    data akun;
    printf("Program kami dapat menampung 4000 character dan 500 judul diary\n\n");

    //input tanggal 
    ubahTanggal:     //label nama untuk jumping statement.
    printf("Tanggal diary (dd/mm/yyyy) : ");
    scanf("%d/%d/%d", &akun[jumlahData].tanggal, &akun[jumlahData].bulan, &akun[jumlahData].tahun);
    getchar();
    int test = cekTanggal(akun[jumlahData].tanggal,akun[jumlahData].bulan,akun[jumlahData].tahun);
    int test1 = cekBulan(akun[jumlahData].bulan);

    if (test != 1 || test1 != 1)
    {
        printf("Masukkan tanggal dengan benar!\n");
        goto ubahTanggal;
    }
    
    //input judul diary
    printf("Judul\t\t\t   : ");
    scanf("%[^\n]", akun[jumlahData].judul);
    getchar();
    
    //input isi dalam 1 paragraf, selesai sampai enter.
    printf("\nIsi : \n");
    scanf("%[^\n]", akun[jumlahData].isi);
    getchar();
    
    //melakukan append ke file dataDiary.txt
    fprintf(fp, "%d/%d/%d,%s,%s\n", 
        akun[jumlahData].tanggal, 
        akun[jumlahData].bulan, 
        akun[jumlahData].tahun,  
        akun[jumlahData].judul, 
        akun[jumlahData].isi);

    jumlahData++;

    fclose(fp);
}

//Cek Tangal
int cekTanggal(int periksaTanggal, int periksaBulan, int periksaTahun){
    int tanggalOk = 0; // salah

    //jika tanggal yang di input melebihi tanggal yang ada di kalender asli
    if ((periksaTanggal > 31) && (periksaBulan == 1 || periksaBulan == 3 || periksaBulan == 5 || periksaBulan == 7 || periksaBulan == 8 || periksaBulan == 10 || periksaBulan == 12)){
        return tanggalOk;
    }
    else if ((periksaTanggal > 30) && (periksaBulan == 4 || periksaBulan == 6 || periksaBulan == 9 || periksaBulan == 11)){
        return tanggalOk;
    }
    else if(periksaBulan == 2)
    {
        if ( periksaTanggal == 29 && periksaTahun %4 == 0){
            tanggalOk = 1; // benar
            return tanggalOk;   
        }
        else if (periksaTanggal > 28){
             return tanggalOk;
        }    
    }
    else{
        tanggalOk = 1;
        return tanggalOk;   
    }   
}

//Cek Bulan
int cekBulan(int periksaBulan){
    int tanggalOk = 1;

    //jika bulan yang di input melebihi bulan yang ada di kalender asli
    if ( periksaBulan <= 12 )
    {
        return tanggalOk;
    }
    else
    {
        tanggalOk = 0;
        return tanggalOk;   
    }   
}

//print bulan
void bulan(int bulanBaru){
    /*Melakukan pengecekkan pada bulan dan melakukan 
    output sesuai bulan yang diinput dalam kata*/
    if (bulanBaru == 1){
        printf(" Januari ");
    } 
    else if (bulanBaru == 2){
        printf(" Februari ");
    } 
    else if (bulanBaru == 3){
        printf(" Maret ");
    }
    else if (bulanBaru == 4){
        printf(" April ");
    } 
    else if (bulanBaru == 5){
        printf(" Mei ");
    }
    else if (bulanBaru == 6){
        printf(" Juni ");
    }
    else if (bulanBaru == 7){
        printf(" Juli ");
    }
    else if (bulanBaru == 8){
        printf(" Agustus ");
    }    
    else if (bulanBaru == 9){
        printf(" September ");
    }
    else if (bulanBaru == 10){
        printf(" Oktober ");
    }
    else if (bulanBaru == 11){
        printf(" November ");
    }
    else if (bulanBaru == 12){
        printf(" Desember ");
    }
}

//read
void read(){
    fp = fopen("dataDiary.txt", "r");
    data akun;
    int pilih;
    jumlahData = 0;

    /*Membaca dan memasukkan seluruh isi dataDiary.txt 
    sampai end of file menuju struct data akun*/
    while (!feof(fp)){
        fscanf(fp, "%d/%d/%d,%[^,],%[^\n]\n", 
        &akun[jumlahData].tanggal, 
        &akun[jumlahData].bulan, 
        &akun[jumlahData].tahun, 
        akun[jumlahData].judul, 
        akun[jumlahData].isi);

        printf("%d. ", jumlahData+1);
        printf("%s\n", akun[jumlahData].judul);
        jumlahData++;
    }

    // Membaca diary jika user memilih read
    if (pilihan == 2)
    {
        printf("Data mana yang ingin dibaca?\n>> ");

        //Input diary yang ingin dibaca
        scanf("%d", &pilih);
        getchar();
        clean;
        pilih -=1;
        //Print Tanggal
        printf("%d",akun[pilih].tanggal);
        
        //Print Bulan (menjalankan fungsi tanggal)
        tanggal(akun[pilih].bulan);

        //Print Tahun
        printf("%d\n",akun[pilih].tahun);
      
        //Print judul diary
        printf("\t\t\t%s\n\n", akun[pilih].judul);

        //Print isi diary
        printf("%s\n\n", akun[pilih].isi);
        enter;
        getchar();
    }
    fclose(fp);
} 

//delete
void delete(){
    int hapusBaris, baca = 1, baris = 1;
    fp = fopen("dataDiary.txt", "r");
    temp_fp = fopen("temp_file.txt", "w");
    printf("Pilih data yang ingin dihapus:\n>> ");

    //Input baris yang ingin dihapus
    scanf("%d", &hapusBaris);
    getchar();
    
    //dilakukan selama nilai dari int baca != 0
    while (baca){
		//Mengambil 1 baris pada fp, lalu menyimpannya di dalam variabel buffer
    	fgets(buffer, SIZE, fp);

		//Jika sudah berada di akhir baris file
    	if(feof(fp)){
        	baca = 0;   
    	}

		//Jika baris yang yang sedang diambil tidak sama dengan baris yang mau dihapus
	    else if(baris != hapusBaris){
        	fputs(buffer, temp_fp);
		}
		baris++;
    }
    printf("\nData berhasil dihapus!\n");
    enter;
    getchar();
    fclose(fp);
    fclose(temp_fp);
}