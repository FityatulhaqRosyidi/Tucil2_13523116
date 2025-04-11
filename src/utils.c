#include "utils.h"
#include "stb_image.h"


int calculate_mean(unsigned char* image, int x, int y, int width, int height, int channels, int idx, int absWidth) {
    assert(image != NULL);

    long long sum = 0;
    int pixelCount = 0;

    for (int j = 0; j < height ; ++j) { 
        for (int i = 0; i < width; ++i) {
            int index = ((y + j) * absWidth + (x + i)) * channels;
            sum = sum + image[index + idx];
            pixelCount ++;
        }
    }

    return (sum / pixelCount);
}

double calculate_variance(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth) {
    //jumlah variansi semua channel
    int sum = 0;

    //jumlah variansi per satuan channel
    int oneChannelSum = 0;

    //banyak pixel dalam satu blok
    int N = width * height;

    for (int c = 0; c < channels; c++) {
        // hitung variansi masing2 channel
        
        for (int j = 0; j < height ; ++j) { 
            for (int i = 0; i < width; ++i) {
                int index = ((y + j) * absWidth + (x + i)) * channels;
                int colorValue = (int)image[index + c];
                oneChannelSum += pow(colorValue - colorMean[c], 2);
            }
        }
        // disini variansi per warna sudah ketemu
        sum += (oneChannelSum / N);
        // reset
        oneChannelSum = 0;
    }
    return (double)sum / 3.0;

}

double calculate_MAD(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth) {
    //jumlah variansi semua channel
    int sum = 0;

    //jumlah variansi per satuan channel
    int oneChannelSum = 0;

    //banyak pixel dalam satu blok
    int N = width * height;

    for (int c = 0; c < channels; c++) {
        // hitung variansi masing2 channel
        
        for (int j = 0; j < height ; ++j) { 
            for (int i = 0; i < width; ++i) {
                int index = ((y + j) * absWidth + (x + i)) * channels;
                int colorValue = (int)image[index + c];
                oneChannelSum += abs(colorValue - colorMean[c]);
            }
        }
        // disini variansi per warna sudah ketemu
        sum += (oneChannelSum / N);
        // reset
        oneChannelSum = 0;
    }
    return (double)sum / 3.0;
}

double calculate_MPD(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth) {
    int difference = 0;
    int oneChannelDifference = 0;
    int maxPixel, minPixel;

    for (int c = 0; c < channels; c++) {
        maxPixel = (int)image[(y * absWidth + x) * channels + c];
        minPixel = (int)image[(y * absWidth + x) * channels + c];
        for (int j = 0; j < height ; ++j) { 
            for (int i = 0; i < width; ++i) {
                int index = ((y + j) * absWidth + (x + i)) * channels;
                int colorValue = (int)image[index + c];

                if (colorValue > maxPixel) {
                    maxPixel = colorValue;
                }
                if (colorValue < minPixel) {
                    minPixel = colorValue;
                }
            }
        }
        oneChannelDifference = maxPixel - minPixel;
        // disini variansi per warna sudah ketemu
        difference += oneChannelDifference;
        // reset
        oneChannelDifference = 0;
    }
    return (double)difference / 3.0;
}

double calculate_Entropy(unsigned char* image, int x, int y, int width, int height, int channels, int* colorMean, int absWidth) {

    double entropyR, entropyG, entropyB, entropyTotal;
    int frequenceTableR[256] = {0};
    int frequenceTableG[256] = {0};
    int frequenceTableB[256] = {0};
    double probabilityR, probabilityG, probabilityB;
    int count, N;

    N = width * height;


    // looping pertama untuk mengisi tabel frekuensi
    for (int j = 0; j < height ; ++j) { 
        for (int i = 0; i < width; ++i) {
            int index = ((y + j) * absWidth + (x + i)) * channels;
            int colorValueR = (int)image[index];
            int colorValueG = (int)image[index + 1];
            int colorValueB = (int)image[index + 2];

            frequenceTableR[colorValueR]++;
            frequenceTableG[colorValueG]++;
            frequenceTableB[colorValueB]++;
        }
    }
    
    // looping kedua untuk menghitung entropi
    count = 0;
    entropyR = 0;
    entropyG = 0;
    entropyB = 0;

    for (int j = 0; j < height ; ++j) { 
        for (int i = 0; i < width; ++i) {
            int index = ((y + j) * absWidth + (x + i)) * channels;
            int colorValueR = (int)image[index];
            int colorValueG = (int)image[index + 1];
            int colorValueB = (int)image[index + 2];

            probabilityR = (double)frequenceTableR[count] / N;
            probabilityG = (double)frequenceTableG[count] / N;
            probabilityB = (double)frequenceTableB[count] / N;

            entropyR += probabilityR * (log(probabilityR) / log(2.0));
            entropyG += probabilityG * (log(probabilityG) / log(2.0));
            entropyB += probabilityB * (log(probabilityB) / log(2.0));

            count++;
        }
    }
    entropyTotal = (-1) * (entropyR + entropyG + entropyB);
    
    return entropyTotal / 3.0;
}

long getFileSize(const char* filePath) {
    FILE* file = fopen(filePath, "rb"); // Membuka file dalam mode baca biner
    if (file == NULL) {
        fprintf(stderr, "Error: Tidak dapat membuka file %s\n", filePath);
        return -1;
    }

    // Memindahkan pointer file ke akhir
    fseek(file, 0, SEEK_END);

    // Mendapatkan ukuran file
    long fileSize = ftell(file);

    // Menutup file
    fclose(file);

    return fileSize;
}

void DAC(int minimumBlockSize, QuadTree* root, unsigned char* image, unsigned char* newImage, int channels, int threshold, int absWidth, int method) {
    // attributes
    int x = root->x;
    int y = root->y;
    int height = root->height;
    int width = root->width;
    int rootPixelSize = root->width * root->height; // ukuran blok pada root
    double variance;

    // Error Measurement Method
    if (method == 1) { // variance normal
        variance = calculate_variance(image, x, y, width, height, channels, root->colorMean, absWidth);  // nilai variansi
    } else if (method == 2) { // Mean Absolute Value
        variance = calculate_MAD(image, x, y, width, height, channels, root->colorMean, absWidth);  // nilai variansi
    } else if (method == 3) { // Max Pixel Difference
        variance = calculate_MPD(image, x, y, width, height, channels, root->colorMean, absWidth);  // nilai variansi
        printf("%d\n", channels);
    } else if (method == 4) {
        variance = calculate_Entropy(image, x, y, width, height, channels, root->colorMean, absWidth);  // nilai variansi
    }

    // basis 
    if (rootPixelSize < minimumBlockSize || variance < threshold) {
        // generate image
        for (int j = 0 ; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                int index = ((y + j) * absWidth + (x + i)) * channels;
                newImage[index] = (unsigned char) (root->colorMean[0]);
                newImage[index + 1] = (unsigned char) (root->colorMean[1]);
                newImage[index + 2] = (unsigned char) (root->colorMean[2]);
            }
        }
        // debug
        // printf("Write at block <%d, %d> | pixel size : %d | colorMean : <%d %d %d> \n", x, y, rootPixelSize, root->colorMean[0], root->colorMean[1], root->colorMean[2]);
    } else { // rekurens
        
        QuadTree* firstChild = createNode(x, y, (width + 1)/2, (height + 1)/2, image, channels, absWidth);
        QuadTree* secondChild = createNode(x + (width + 1)/2, y, width/2, (height + 1)/2, image, channels, absWidth);
        QuadTree* thirdChild = createNode(x, y + (height + 1)/2, (width + 1)/2, height/2, image, channels, absWidth);
        QuadTree* fourthChild = createNode(x + (width + 1)/2, y + (height + 1)/2, width/2, height/2, image, channels, absWidth);

        connect(root, firstChild, 0);
        connect(root, secondChild, 1);
        connect(root, thirdChild, 2);
        connect(root, fourthChild, 3);

        DAC(minimumBlockSize, firstChild, image, newImage, channels, threshold, absWidth, method);
        DAC(minimumBlockSize, secondChild, image, newImage, channels, threshold, absWidth, method);
        DAC(minimumBlockSize, thirdChild, image, newImage, channels, threshold, absWidth, method);
        DAC(minimumBlockSize, fourthChild, image, newImage, channels, threshold, absWidth, method);
    }
}


