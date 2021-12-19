#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define swap(t, x, y) {t z = x; x = y; y = z; }


typedef struct{
    int kode;
    char nama[10];
    char jenis[10];
    int stok;
} barang;

int partition(barang *, int, int);
void quick(barang *, int, int);

void create();
void display();
void add();
void total();
void update();
void delete();
void search();
void sort();


int main(){
    int pilih1;
    do{
        system("cls");
        printf("\n=================================");
        printf("\nSISTEM PENDATAAN BARANG DAGANGAN");
        printf("\n=================================");
        printf("\n1. BUAT BARU");
        printf("\n2. TAMPILKAN DATA");
        printf("\n3. TAMBAH DATA");
        printf("\n4. PERBARUI DATA (MASIH DALAM PROSES PERBAIKAN)");
        printf("\n5. HAPUS DATA");
        printf("\n6. CARI DATA");
        printf("\n7. URUTKAN DATA");
        printf("\n0. KELUAR");
        printf("\n=================================\n");
        printf("MASUKKAN PILIHAN ANDA: "); scanf("%d", &pilih1);

        switch (pilih1){
            case 1:
                create();
            break;
            case 2:
                display();
            break;
            case 3:
                add();
            break;
            case 4:
                update();
            break;
            case 5:
                delete();
            break;
            case 6:
                search();
            break;
            case 7:
                sort();
            break;

        } 
    }while(pilih1 != 0);
}

int partition(barang *b, int index_awal, int index_akhir){
    barang b1 = b[index_akhir]; //pivot
    int i = index_awal - 1, j;
    for(j = index_awal; j<index_akhir; j++){
        if(b[j].stok <= b1.stok){
            i++;
            swap(barang ,b[i], b[j]);
        }
    }
    i++;
    swap(barang, b[i], b[index_akhir]);
    return i;
}

void quick(barang *b, int index_awal, int index_akhir){
    if(index_awal < index_akhir){
        int p = partition(b, index_awal, index_akhir);
        quick(b, index_awal, p - 1);
        quick(b, p + 1, index_akhir);
    }
}

void create(){
    barang *b;
    FILE *fp;
    int n, i;
    system("cls");
    printf("Berapa barang yang dimasukkan: "); 
    scanf("%d", &n);
    
    b = (barang*)calloc(n, sizeof(barang));
    fp = fopen("barang.txt", "w");

    system("cls");
    for(i=0; i<n; i++){
        printf("\n=============================================\n");
        printf("MASUKKAN DATA BARANG KE-%d", i + 1);
        printf("\n=============================================\n");
        printf("Masukkan id: ");
        scanf("%d", &b[i]);
        fflush(stdin);
        printf("Masukkan nama: ");
        scanf("%[^\n]s", &b[i].nama);
        fflush(stdin);
        printf("Masukkan jenis: ");
        scanf("%[^\n]s", &b[i].jenis);
        printf("Masukkan jumlah: ");
        scanf("%d", &b[i].stok);
        fwrite(&b[i], sizeof(barang), 1, fp);
    }
    system("cls");
    printf("\n=============================================\n");
    printf("DATA BERHASIL DIBUAT");
    printf("\n=============================================\n");
    system("PAUSE");
    fclose(fp);
}

void total(){
    barang b1;
    FILE *fp;
    fp = fopen("barang.txt", "r");
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp)/sizeof(barang);
    printf("\nJUMLAH DATA = %d", n);
    fclose(fp);
}

void display(){
    system("cls");
    barang b1;
    FILE *fp;
    fp = fopen("barang.txt", "r");

    printf("\n=============================================\n");
    printf("Kode |Nama_Barang  Jenis_Barang  Jumlah_stok");
    printf("\n=============================================");
    while(fread(&b1, sizeof(barang), 1, fp)){
        printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
    }
    fclose(fp);
    printf("\n=============================================");
    total();
    printf("\n=============================================\n");
    system("PAUSE");

}

void add(){
    barang *b;
    FILE *fp;
    int n, i;
    system("cls");
    printf("Berapa barang yang ditambah: "); 
    scanf("%d", &n);
    
    b = (barang*)calloc(n, sizeof(barang));
    fp = fopen("barang.txt", "a");

    system("cls");

    for(i=0; i<n; i++){
        printf("\n=============================================\n");
        printf("MASUKKAN DATA BARANG KE-%d", i + 1);
        printf("\n=============================================\n");
        printf("Masukkan id: ");
        scanf("%d", &b[i]);
        fflush(stdin);
        printf("Masukkan nama: ");
        scanf("%[^\n]s", &b[i].nama);
        fflush(stdin);
        printf("Masukkan jenis: ");
        scanf("%[^\n]s", &b[i].jenis);
        printf("Masukkan jumlah: ");
        scanf("%d", &b[i].stok);
        fwrite(&b[i], sizeof(barang), 1, fp);
    }
    fclose(fp);
    system("cls");
    printf("\n=============================================\n");
    printf("DATA BERHASIL DITAMBAHKAN");
    printf("\n=============================================\n");
    system("PAUSE");
}

void update(){
    barang b1;
    FILE *fp, *fp1;
    int kode, found=0;
    fp = fopen("barang.txt", "r");
    fp1 = fopen("sementara.txt", "w");

    printf("Masukkan id yang ingin diupdate: ");
    scanf("%d", &kode);

    while(fread(&b1, sizeof(barang), 1, fp)){
        
        if(b1.kode == kode){
            found=1;
            fflush(stdin);
            printf("Masukkan nama baru: ");
            scanf("%[^\n]s", &b1.nama);
            fflush(stdin);
            printf("Masukkan jenis baru: ");
            scanf("%[^\n]s", &b1.kode);
            printf("Masukkan jumlah baru: ");
            scanf("%d", &b1.stok);

        }
        fwrite(&b1, sizeof(barang), 1, fp1);
        
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("sementara.txt", "r");
        fp = fopen("barang.txt", "w");

        while(fread(&b1, sizeof(barang), 1, fp1)){
            fwrite(&b1, sizeof(barang), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
    } else{
        printf("\nData tidak ditemukan");
    }
    fclose(fp); 
}

void delete(){
    barang b1;
    FILE *fp, *fp1;
    int kode, found=0;
    fp = fopen("barang.txt", "r");
    fp1 = fopen("temporary.txt", "w");
    display();

    printf("\n=============================================\n");
    printf("Masukkan id yang ingin dihapus: ");
    printf("\n=============================================");
    scanf("%d", &kode);

    while(fread(&b1, sizeof(barang), 1, fp)){
        
        if(b1.kode == kode){
            found=1;
        } else{
            fwrite(&b1, sizeof(barang), 1, fp1);
        }
        
        
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1 = fopen("temporary.txt", "r");
        fp = fopen("barang.txt", "w");

        while(fread(&b1, sizeof(barang), 1, fp1)){
            fwrite(&b1, sizeof(barang), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
    } else{
        printf("\nData tidak ditemukan");
    }
    fclose(fp);

    system("cls");
    printf("\n=============================================\n");
    printf("DATA BERHASIL DIHAPUS");
    printf("\n=============================================\n");
    system("PAUSE");
}

void search(){
    barang b1;
    FILE *fp;
    int kode, found=0, pilih2;
    char nama[10], jenis[10];
    fp = fopen("barang.txt", "r");
    system("cls");
    printf("CARI BERDASARKAN: ");
    printf("\n==================");
    printf("\n1. KODE BARANG");
    printf("\n2. NAMA BARANG");
    printf("\n3. JENIS BARANG");
    printf("\n4. JUMLAH STOK");
    printf("\n==================");
    printf("\nMASUKKAN PILIHAN ANDA: "); scanf("%d", &pilih2);
    printf("==================\n");

    system("cls");

    switch (pilih2)
    {
    case 1:
        printf("Masukkan kode barang yang akan dicari: ");
        scanf("%d", &kode);

        while (fread(&b1, sizeof(barang), 1, fp))
        {
            if (b1.kode == kode)
            {
            found = 1;
            printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
            }
        
        }
    break;
    
    case 2:
        printf("Masukkan nama barang yang akan dicari: ");
        scanf("%s", &nama);
        fflush(stdin);
        while (fread(&b1, sizeof(barang), 1, fp))
        {
            if ((strcmp (b1.nama, nama)) == 0){
            found = 1;
            printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
            }
        
        }
    break;

    case 3:
        printf("Masukkan jenis barang yang akan dicari: ");
        scanf("%s", &jenis);
        while (fread(&b1, sizeof(barang), 1, fp))
        {
            if ((strcmp (b1.jenis, jenis)) == 0){
            found = 1;
            printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
            }
        
        }
    break;
    
    case 4:
        int pilih3, stok;
        system("cls");
        printf("====================");
        printf("\nPILIH MODE PENCARIAN");
        printf("\n====================");
        printf("\n1. LEBIH DARI NILAI");
        printf("\n2. SAMA DENGAN NILAI");
        printf("\n3. KURANG DARI NILAI");
        printf("\n====================");
        printf("\nMASUKKAN PILIHAN: "); scanf("%d", &pilih3);
        printf("====================\n");

        switch (pilih3)
        {
        case 1:
            printf("Masukkan jumlah barang: ");
            scanf("%d", &stok);

            while (fread(&b1, sizeof(barang), 1, fp)){
                if (b1.stok >= stok){
                    found = 1;
                    printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
                }
        
            }     
            break;

            case 2:
            printf("Masukkan jumlah barang: ");
            scanf("%d", &stok);

            while (fread(&b1, sizeof(barang), 1, fp)){
                if (b1.stok == stok){
                    found = 1;
                    printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
                }
        
            }     
            break;
        
        case 3:
            printf("Masukkan jumlah barang: ");
            scanf("%d", &stok);

            while (fread(&b1, sizeof(barang), 1, fp)){
                if (b1.stok <= stok){
                    found = 1;
                    printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
                }
        
            }     
            break;
        }
    }
    /*
    printf("Masukkan kode barang yang akan dicari: ");
    scanf("%d", &kode);

    while (fread(&b1, sizeof(barang), 1, fp))
    {
        if (b1.kode == kode)
        {
            found = 1;
            printf("\n%-5d|%-15s%-15s%-5d", b1.kode, b1.nama, b1.jenis, b1.stok);
        }
        
    }
    */
    if(!found){
        system("cls");
        printf("\nData tidak ditemukan");
    }
    fclose(fp);
    printf("\n\n");
    system("PAUSE");
}

void sort(){
    barang *b, b1;
    FILE *fp;
    int i;

    fp = fopen("barang.txt", "r");
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp)/sizeof(barang);
    b = (barang*)calloc(n, sizeof(barang));

    rewind(fp);
    for (i = 0; i < n; i++){
        fread(&b[i], sizeof(barang), 1, fp);
    }

    quick(b, 0, n);

    for (i = 0; i < n; i++){
        printf("\n%-5d|%-15s%-15s%-5d", b[i].kode, b[i].nama, b[i].jenis, b[i].stok);
    }
    
    fclose(fp);
    printf("\n");
    system("PAUSE");
}

