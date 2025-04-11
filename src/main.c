#include <stdio.h>
#include <string.h>
#include <time.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"
#include "utils.h"
#include "quadtree.h"
#include "io_utils.h"

int main() {

    int minimumBlockSize, threshold, method, treeDepth, nodeCount, width, height, channels;
    double executionTime ,sizeBefore, sizeAfter, compressionPercentage;
    clock_t start, end;
    char ip[256];
    char op[256];

    showBanner();
    getInputPath(ip);
    const char* inputPath = ip;
    const char* outputPath = op;
    getOutputPath(op);
    getMethod(&method);
    getThreshold(&threshold);
    getMinimumBlockSize(&minimumBlockSize);
    
    
    unsigned char* image = stbi_load(inputPath, &width, &height, &channels, 0);
    if (image == NULL) {
        fprintf(stderr, "Error: Gagal memuat gambar %s\n", inputPath);
        return 1;
    }


    unsigned char* newImage = (unsigned char*)malloc(channels * width * height);
    if (image == NULL) {
        fprintf(stderr, "Error: Gagal mengalokasikan memori untuk gambar.\n");
        exit(1);
    }

    // Root Tree
    QuadTree* root = createNode(0, 0, width, height, image, channels, width);

    // Divide and Conquer Algorithm
    start = clock();
    DAC(minimumBlockSize, root, image, newImage, channels, threshold, width, method);
    end = clock();


    // tulis gambar ke file
    int success = stbi_write_jpg(outputPath, width, height, channels, newImage, 50);

    // outputs
    executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    sizeBefore = (double) getFileSize(inputPath) / 1024.0;
    sizeAfter = (double)getFileSize(outputPath) / 1024.0;
    compressionPercentage = (1 - (sizeAfter/sizeBefore)) * 100;
    treeDepth = getTreeDepth(root);
    nodeCount = getNodeCount(root);

    printf("Waktu Eksekusi : %.2f sec\n", executionTime);
    printf("size before : %.2f KB\n", sizeBefore);
    printf("size after : %.2f KB\n", sizeAfter);
    printf("compression percentage : %.2f%% \n", compressionPercentage);
    printf("Tree Depth : %d\n", treeDepth);
    printf("Tree node count : %d\n", nodeCount);

    if (success) {
        printf("Gambar berhasil disimpan di %s\n", outputPath);
    } else {
        fprintf(stderr, "Error: Gagal menyimpan gambar.\n");
    }

    // Bebaskan memori setelah selesai
    stbi_image_free(image);
    free(newImage);
    freeQuadTree(root);

    return 0;
}

