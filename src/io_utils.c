#include "io_utils.h"

void showBanner() {
    printf("=================================================\n");
    printf("|                TUCIL 2 STIMA                  |\n");
    printf("|             QUADTREE COMPRESION               |\n");
    printf("=================================================\n");
    printf("                by : yayatsigma                  \n");
    printf("\n\n");
}

void getInputPath(char* alamat) {
    // Meminta get untuk alamat dengan validasi
    while (1) {
        printf("Masukkan alamat absolut file input \n>> ");
        if (fgets(alamat, 256, stdin) != NULL) {
            // Menghapus newline jika ada
            alamat[strcspn(alamat, "\n")] = '\0';
            if (strlen(alamat) > 0) {
                break; // Jika alamat tidak kosong, keluar dari loop
            } else {
                printf("Error: Alamat tidak boleh kosong.\n");
            }
        } else {
            printf("Error: Gagal membaca alamat.\n");
        }
    }
}

void getOutputPath(char* alamat) {
    // Meminta get untuk alamat dengan validasi
    while (1) {
        printf("Masukkan alamat absolut file output \n>> ");
        if (fgets(alamat, 256, stdin) != NULL) {
            // Menghapus newline jika ada
            alamat[strcspn(alamat, "\n")] = '\0';
            if (strlen(alamat) > 0) {
                break; // Jika alamat tidak kosong, keluar dari loop
            } else {
                printf("Error: Alamat tidak boleh kosong.\n");
            }
        } else {
            printf("Error: Gagal membaca alamat.\n");
        }
    }
}


void getMethod(int* metode) {
    int status;
    printf("===============================\n");
    printf("Error Measurement Methods:\n");
    printf("1. Variance\n");
    printf("2. Mean Absolute Deviation (MAD)\n");
    printf("3. Max Pixel Different\n");
    printf("4. Entropy\n");
    printf("===============================\n");
    while (1) {
        printf("Masukkan metode (1 - 4) \n>> ");
        status = scanf("%d", metode);
        if (status == 1 && *metode > 0 && *metode < 5) {
            break; // Jika get valid, keluar dari loop
        } else {
            printf("Error: metode harus berupa integer antara 1 - 4.\n");
            while (getchar() != '\n'); // Membersihkan buffer get
        }
    }
}

void getThreshold(int* threshold) {
    int status;
    while (1) {
        printf("Masukkan threshold (integer) \n>> ");
        status = scanf("%d", threshold);
        if (status == 1) {
            break; // Jika get valid, keluar dari loop
        } else {
            printf("Error: threshold harus berupa integer.\n");
            while (getchar() != '\n'); // Membersihkan buffer get
        }
    }
}

void getMinimumBlockSize(int* minimumBlockSize) {
    int status;
    while (1) {
        printf("Masukkan Ukuran blok minimum (integer) \n>> ");
        status = scanf("%d", minimumBlockSize);
        if (status == 1) {
            break; // Jika get valid, keluar dari loop
        } else {
            printf("Error: get harus berupa integer.\n");
            while (getchar() != '\n'); // Membersihkan buffer get
        }
    }
}

// void getCompressionTarget(double* target) {
//     int status;
//     while (1) {
//         printf("Masukkan Target persentase kompresi (integer) \n>> ");
//         status = scanf("%lf", target);
//         if (status == 1) {
//             break; // Jika get valid, keluar dari loop
//         } else {
//             printf("Error: get harus berupa double.\n");
//             while (getchar() != '\n'); // Membersihkan buffer get
//         }
//     }
// }