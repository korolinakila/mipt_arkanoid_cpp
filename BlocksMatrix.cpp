#include "Block.h"
#include "BlocksMatrix.h"
#include "Graph_lib/Graph.h"

#define field_width 800
#define field_height 400

BlocksMatrix::BlocksMatrix(int matrixHeight, int matrixWidth) :
        matrixWidth(matrixWidth), matrixHeight(matrixHeight),
        blockWidth(field_width / matrixWidth), blockHeight(field_height / matrixHeight)
        {

    field.resize(matrixWidth);

    for (int i = 0; i < matrixWidth; i++) {
        field[i].resize(matrixHeight);
    }

}
bool BlocksMatrix::allBlocksDestroyed() const {
    for (const auto& row : field)
        for (Block* b : row)
            if (b) return false;
    return true;
}

void BlocksMatrix::generate() {
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++) {
            field[i][j] = new Block(Graph_lib::Point(j*blockWidth, i*blockHeight), blockWidth, blockHeight, 5);  // 5 = hp
        }
    }
}

void BlocksMatrix::generate(std::vector<std::vector<int>> generate_matrix) {
    for (int i = 0; i < matrixWidth; i++) {
        for (int j = 0; j < matrixHeight; j++) {
            if (generate_matrix[i][j]) {
            field[i][j] = new Block(Graph_lib::Point(j*blockWidth, i*blockHeight), blockWidth, blockHeight, 5);  // 5 = hp
            }
        }
    }
}

int BlocksMatrix::getMatrixHeight() const {
    return matrixHeight;
}

int BlocksMatrix::getMatrixWidth() const {
    return matrixWidth;
}

int BlocksMatrix::getBlockHeight() const {
    return blockHeight;
}

int BlocksMatrix::getBlockWidth() const {
    return blockWidth;
}

Block* BlocksMatrix::get_block(int x, int y) const {
    if (x >= 0 && x < matrixWidth && y >= 0 && y < matrixHeight) {
        return field[x][y];
    }
    return nullptr;
}

void BlocksMatrix::del_block(int x, int y) {
    field[x][y] = nullptr;
}
