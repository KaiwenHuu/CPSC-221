#include "block.h"

/**
 * Returns the width of the block.
 */
int Block::width() const{
    const int width = data.size();
    return width;
}

/**
 * Returns the height of the block.
 */
int Block::height() const{
    const int height = data[0].size();
    return height;
}

/**
 * Default Block constructor.
 */
Block::Block() {/* nothing */}

/**
 * Useful Block constructor.
 * Makes a block from the rectangle of width by height pixels in im
 * whose upper-left corner is at position (x,y).
 */
Block::Block(PNG & im, int x, int y, int width, int height) {
    // initialize data size
    data.resize(width, vector<HSLAPixel>(height));

    // iterate from 0 to width for x and 0 to height for y
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            data[i][j] = *im.getPixel(i + x, j + y);
        }
    }
}

/**
 * Draws the block at position (x,y) in the image im
 */
void Block::render(PNG & im, int x, int y) const {
    // fetch width and height of block
    int height = this->height();
    int width = this->width();

    // iterate over each pixel inside block
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            *im.getPixel(i + x, j + y) = data[i][j];
        }
    }
}

/**
 * Changes the saturation of every pixel in the block to 0,
 * which removes the color, leaving grey.
 */
void Block::greyscale() {
    // fetch width and height of block
    int height = this->height();
    int width = this->width();

    // iterate over each pixel inside block
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            data[i][j].s = 0;
        }
    }
}
