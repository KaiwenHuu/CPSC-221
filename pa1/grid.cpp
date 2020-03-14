#include "grid.h"
#include "grid_given.cpp"

// PA1 functions


/**
 * Destroys the current Grid. This function should ensure that
 * memory does not leak on destruction of a grid.
 */
Grid::~Grid(){ /*your code here*/
    clear();
}

/**
 * Rotate row r (row 0 is the first) by count positions.
 * If row r is ABCDE (left to right) in grid g then row r
 * in grid g should be DEABC after the call g.rotateR(r, 2).
 * Rotate headOfCol_ if necessary.
 */
void Grid::rotateR(int r, int count) {
    r = r % headOfRow_.size();
    int shift = count; // number of shifts is count mod size of column-size

    for (int i = 0; i < shift; i++) {
        headOfRow_[r] = headOfRow_[r]->left;
    }

    Node* curr = headOfRow_.at(r); // sets a pointer curr that points to the same Node as p
    Node* u = curr->up;
    Node* d = curr->down;

    for (int column = 0; column < headOfCol_.size(); column++) { // runs a for-loop column times where column is width

        for (int i = 0; i < shift; i++) {
            curr->up = curr->up->right;
            curr->down = curr->down->right;
            u = curr->left;
            d = curr->left;

        }

        if (r == 0) {
            headOfCol_[column] = headOfCol_[column]->left;                
        }

        curr = curr->right; // goes to the next grids in the row
        u = u->right;
        d = d->right;
    }

}

/**
 * Rotate column c (column 0 is the first) by count positions.
 * If column c is ABCDE (top to bottom) in grid g then column c
 * in grid g should be DEABC after the call g.rotateC(c, 2).
 * Rotate headOfRow_ if necessary.
 */
void Grid::rotateC(int c, int count) { /* your code here */
    c = c % headOfCol_.size();
    int shift = count % headOfRow_.size(); // number of shifts is count mod size of row-size
    Node* p = headOfCol_.at(c); // pointer p points to the first Node in column c

    for (int i = 0; i < shift; i++) {
        p = p->down;
    }

    headOfCol_[c] = p; // what does this do?

    Node* curr = headOfCol_.at(c); // sets a pointer curr that points to the same Node as p
    Node* l = curr->left;
    Node* r = curr->right;

    for (int row = 0; row < headOfRow_.size(); row++) { // runs a for-loop row times where row is height

        for (int i = 0; i < shift; i++) {
            curr->left = curr->left->down;
            curr->right = curr->right->down;
            l->down->right = curr;
            r->down->left = curr;
        }

        if (c == 0) {
            headOfRow_[row] = headOfRow_[row]->left;
        }

        curr = curr->down; // goes to the next grids in the column
        l = l->down;
        r = r->down;
    }

}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Grid class. Clears headOfRow_ and headOfCol_ vectors.
 * Sets bwidth_, bheight_ to zero.
 * After clear() the grid represents an empty grid.
 */
void Grid::clear() {

    for (int i = 0; i < numRows(); i++) {
        Node* curr = headOfRow_[i];

        for (int j = 0; j < numCols(); j++) {
            Node* p = curr->right;
            delete curr;
            curr = p;
        }
    }

    bwidth_ = 0;
    bheight_ = 0;

    headOfRow_.clear();
    headOfCol_.clear();

}

/**
 * Makes the current Grid a copy of the "other" Grid.
 * The dimensions should be the same.  The Nodes should
 * contain the same blocks, but the Nodes should be newly
 * allocated. This function is used in both the copy
 * constructor and the assignment operator for Grids.
 */
void Grid::copy(Grid const& other) {
    clear();
    bwidth_ = other.bwidth_;		// width of all Node blocks
    bheight_ = other.bheight_;	// height of all Node blocks

    int nRows = other.numRows();
    int nCols = other.numCols();

    // Set up a temporary two-dimesional vector of ptrs to Nodes containing
    // the correct sub-blocks of the image.
    vector < vector < Node * > > A;
    for( int j=0; j<nRows; j++ ) {
        vector < Node * > temp;
        Node* node = other.headOfRow_[j];
        for( int i=0; i<nCols; i++ ) {
            Node *p = new Node(node->block);
            temp.push_back(p);
            node = node->right;
        }
        A.push_back(temp);
    }
    // Set up the pointer structure between Nodes
    for( int j=0; j<nRows; j++ ) {
        for( int i=0; i<nCols; i++ ) {
            Node *p = A[j][i];
            p->up    = A[(j==0) ? nRows-1 : j-1] [i];
            p->down  = A[(j==nRows-1) ? 0 : j+1][i];
            p->left  = A[j] [(i==0) ? nCols-1 : i-1];
            p->right = A[j] [(i==nCols-1) ? 0 : i+1];
        }
    }
    for( int j=0; j<nRows; j++ ) {
        headOfRow_.push_back(A[j][0]);
    }
    for( int i=0; i<nCols; i++ ) {
        headOfCol_.push_back(A[0][i]);
    }
}