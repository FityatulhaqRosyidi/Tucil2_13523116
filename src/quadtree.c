#include "quadtree.h"
#include "utils.h"

QuadTree* createNode(int x, int y, int width, int height, unsigned char* image, int channels, int absWidth) {
    QuadTree* newNode = (QuadTree*)malloc(sizeof(QuadTree));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Gagal mengalokasikan memori");
        exit(1);
    }

    newNode->x = x;
    newNode->y = y;
    newNode->width = width;
    newNode->height = height;
    newNode->isLeaf = true;

    // inisiasi array color mean
    newNode->colorMean[0] = calculate_mean(image, x, y, width, height, channels, 0, absWidth);
    newNode->colorMean[1] = calculate_mean(image, x, y, width, height, channels, 1, absWidth);
    newNode->colorMean[2] = calculate_mean(image, x, y, width, height, channels, 2, absWidth);


    // Inisialisasi children ke NULL
    for (int i = 0; i < 4; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void connect(QuadTree* parent, QuadTree* child, int index) {
    if (parent == NULL) {
        fprintf(stderr, "Error: Node induk tidak boleh NULL.\n");
        return;
    }
    if (index < 0 || index >= 4) {
        fprintf(stderr, "Error: Indeks anak harus antara 0 dan 3.\n");
        return;
    }

    parent->children[index] = child;

    parent->isLeaf = false;
}

void freeQuadTree(QuadTree* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        freeQuadTree(root->children[i]);
    }

    free(root);
}

int getTreeDepth(QuadTree* root) {
    if (root == NULL) {
        return 0; // Kedalaman dari tree kosong adalah 0
    }

    int maxDepth = 0;
    for (int i = 0; i < 4; i++) {
        int childDepth = getTreeDepth(root->children[i]);
        if (childDepth > maxDepth) {
            maxDepth = childDepth;
        }
    }

    return 1 + maxDepth; // Menambahkan 1 untuk menghitung level saat ini
}

int getNodeCount(QuadTree* root) {
    if (root == NULL) {
        return 0; // Jika node kosong, jumlah simpul adalah 0
    }

    int count = 1; // Hitung node saat ini
    for (int i = 0; i < 4; i++) {
        count += getNodeCount(root->children[i]); // Tambahkan jumlah node dari subtree
    }

    return count;
}
