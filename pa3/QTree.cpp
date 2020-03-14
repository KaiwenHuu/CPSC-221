/**
 *
 * Balanced Quad Tree (pa3)
 *
 * This file will be used for grading.
 *
 */

#include "QTree.h"

// Return the biggest power of 2 less than or equal to n
int biggestPow2(int n) {
  if( n < 1 ) return 0;
  int v = 1;
  while( v <= n ) v <<= 1;
  return v >> 1;
}

QTree::Node::Node(PNG & im, pair<int,int> ul, int sz, Node *par)
  :upLeft(ul),size(sz),parent(par),nw(NULL),ne(NULL),sw(NULL),se(NULL)
{
  var = varAndAvg(im,ul,size,avg);
}

QTree::~QTree(){
  clear();
}

QTree::QTree(const QTree & other) {
  copy(other);
}


QTree & QTree::operator=(const QTree & rhs){
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}


QTree::QTree(PNG & imIn, int leafB, RGBAPixel frameC, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(true), frameColor(frameC)
{

  /* YOUR CODE HERE */
  im = imIn;
  constructorHelper();
}


QTree::QTree(PNG & imIn, int leafB, bool bal)
  : leafBound(leafB), balanced(bal), drawFrame(false)
{
  
  /* YOUR CODE HERE */
  im = imIn;
  constructorHelper();
}

void QTree::constructorHelper() {
  int height = im.height();
  // cout << "image's height is: " << height << endl;
  int width = im.width();
  // cout << "image's width is: " << width << endl;
  int side = min(height, width);
  // cout << "image's side is: " << side << endl;
  side = biggestPow2(side);
  // cout << "image's side is now the lowest power of 2: " << side << endl;
  im.resize(side, side);

  root = new Node(im, make_pair(0, 0), side, NULL);

  q.push(root); numLeaf = 1;

  while (numLeaf < leafBound && leafBound < height * width) {
    // cout << "there are " << numLeaf << "leaves" << endl;
    Node* top = q.top();
    // cout << "is this a leaf? " << isLeaf(top) << endl;
    // cout << "top's variance is: " << top->var << endl;
    // cout << "number of leaf and size of q before q.pop(): " << numLeaf << ", "<< q.size() << endl;
    q.pop();
    // cout << "number of leaf and size of q after q.pop(): " << numLeaf << ", " << q.size() << endl; 
    if (isLeaf(top)){
      split(top);
    }
    // cout << "number of leaf and size of q after split: " << numLeaf << ", " << q.size() << endl; 
  }
}


bool QTree::isLeaf( Node *t ) {
  
  /* YOUR CODE HERE */
  if (t->ne == NULL && t->nw == NULL && t->sw == NULL && t->se == NULL) {
    return true;
  }

  else {
    return false;
  }
}
  
void QTree::split( Node *t ) {
  
  /* YOUR CODE HERE */

  // FOR BALANCED QTREES-------------------------------------------------
  // A split might cause one or two nbrs of the parent of t to split
  // to maintain balance.  Note that these two nbrs exist (unless they're
  // not in the image region) because the current set of leaves are
  // balanced.
  // if( t is a NW (or NE or SW or SE) child ) then we need to check that
  // the North and West (or North and East or South and West or
  // South and East) nbrs of t->parent have children. If they don't
  // we need to split them.
  
  numLeaf = numLeaf - 1;
  
  int size = t->size / 2; // size of the 4 squares

  // create pairs for NW, NE, SW, SE
  pair<int, int> pairNW = t->upLeft;
  pair<int, int> pairNE = make_pair(t->upLeft.first + size, t->upLeft.second);
  pair<int, int> pairSW = make_pair(t->upLeft.first, t->upLeft.second + size);
  pair<int, int> pairSE = make_pair(t->upLeft.first + size, t->upLeft.second + size);

  t->nw = new Node(im, pairNW, size, t); // create Node for NW
  // cout << "subNW node has upLeft: " << t->nw->upLeft.first << ", " << t->nw->upLeft.second << t->nw->var << endl;
  t->ne = new Node(im, pairNE, size, t); // create Node for SE
  // cout << "subNE node has upLeft: " << t->ne->upLeft.first << ", " << t->ne->upLeft.second << t->ne->var << endl;
  t->sw = new Node(im, pairSW, size, t); // create Node for SW
  // cout << "subSW node has upLeft: " << t->sw->upLeft.first << ", " << t->sw->upLeft.second << t->sw->var << endl;
  t->se = new Node(im, pairSE, size, t); // create Node for SE
  // cout << "subSE node has upLeft: " << t->se->upLeft.first << ", " << t->se->upLeft.second << t->se->var << endl;

  q.push(t->nw);
  q.push(t->ne);
  q.push(t->sw);
  q.push(t->se);
  // cout << "variances: " << t->nw->var << ", " << t->ne->var << ", " << t->sw->var << ", " << t->se->var << ", " << endl;

  numLeaf = numLeaf + 4;

  // TODO: re-split nodes if tree is not balanced 

  if (balanced && t != root) {
        if (t->parent->nw == t) {
            Node *north = NNbr(t->parent);
            if (north != NULL && isLeaf(north))
                split(north);
            Node *west = WNbr(t->parent);
            if (west != NULL && isLeaf(west))
                split(west);
        } else if (t->parent->ne == t) {
            Node *north = NNbr(t->parent);
            if (north != NULL && isLeaf(north))
                split(north);
            Node *east = ENbr(t->parent);
            if (east != NULL && isLeaf(east))
                split(east);
        } else if (t->parent->sw == t) {
            Node *south = SNbr(t->parent);
            if (south != NULL && isLeaf(south))
                split(south);
            Node *west = WNbr(t->parent);
            if (west != NULL && isLeaf(west))
                split(west);
        } else if (t->parent->se == t) {
            Node *south = SNbr(t->parent);
            if (south != NULL && isLeaf(south))
                split(south);
            Node *east = ENbr(t->parent);
            if (east != NULL &&isLeaf(east))
                split(east);
        }
    }
}


/* NNbr(t)
 * return the same-sized quad tree node that is north of Node t.
 * return NULL if this node is not in the QTree.
 */
//int countNNbr = 0;
QTree::Node * QTree::NNbr(Node *t) {

  /* YOUR CODE HERE */
  if (t->parent == NULL) {
    return NULL;
  }

  if (t->parent->se == t) {
    return t->parent->ne;
  }

  if (t->parent->sw == t) {
    return t->parent->nw;
  }

  if (t->parent->ne == t) {
    Node *curr = NNbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->se;
  }

  if (t->parent->nw == t) {
    Node *curr = NNbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->sw;
  }  
  /*
  if (t->upLeft.second == t->parent->upLeft.second) { // if t is a northern subnode
    countNNbr = countNNbr + 1;
    NNbr(t->parent);
  }

  else {
    Node* curr = t->parent;
    if (t->upLeft.first == t->parent->upLeft.first) { // if t is sw
      for (int i = 0; i < countNNbr; i++) {
        curr = curr->nw;
      }
      return curr->se;
    }
    if (t->upLeft.first == t->parent->upLeft.first + t->size) { // if t is se
      for (int i = 0; i < countNNbr; i++) {
        curr = curr->ne;
      }
      return curr->sw;
    }
  }*/
  
}

/* SNbr(t)
 * return the same-sized quad tree node that is south of Node t.
 * return NULL if this node is not in the QTree.
 */
//int countSNbr = 0;
QTree::Node * QTree::SNbr(Node *t) {

  /* YOUR CODE HERE */
  if (t->parent == NULL) {
    return NULL;
  }

  if (t->parent->ne == t) {
    return t->parent->se;
  }

  if (t->parent->nw == t) {
    return t->parent->sw;
  }

  if (t->parent->se == t) {
    Node *curr = SNbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->ne;
  }

  if (t->parent->sw == t) {
    Node *curr = SNbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->nw;
  }
  /*if (t->parent == NULL) {
    return NULL;
  }

  if (t->upLeft.second == t->parent->upLeft.second + t->size) { // if t is a southern subnode
    countSNbr = countSNbr + 1;
    SNbr(t->parent);
  }

  else {
    Node* curr = t->parent;
    if (t->upLeft.first == t->parent->upLeft.first) { // if t is nw
      for (int i = 0; i < countSNbr; i++) {
        curr = curr->sw;
      }
      return curr->ne;
    }
    if (t->upLeft.first == t->parent->upLeft.first + t->size) { // if t is ne
      for (int i = 0; i < countSNbr; i++) {
        curr = curr->se;
      }
      return curr->nw;
    }
  }*/
  
}

/* ENbr(t)
 * return the same-sized quad tree node that is east of Node t.
 * return NULL if this node is not in the QTree.
 */
//int countENbr = 0;
QTree::Node * QTree::ENbr(Node *t) {

  /* YOUR CODE HERE */

  if (t->parent == NULL) {
    return NULL;
  }

  if (t->parent->sw == t) {
    return t->parent->se;
  }

  if (t->parent->nw == t) {
    return t->parent->ne;
  }

  if (t->parent->ne == t) {
    Node *curr = ENbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->nw;
  }

  if (t->parent->se == t) {
    Node *curr = ENbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->sw;
  }
  /*if (t->parent == NULL) {
    return NULL;
  }

  if (t->upLeft.first == t->parent->upLeft.first + t->size) { // if t is a eastern subnode
    countENbr = countENbr + 1;
    ENbr(t->parent);
  }

  else {
    Node* curr = t->parent;
    if (t->upLeft.first == t->parent->upLeft.first) { // if t is sw
      for (int i = 0; i < countSNbr; i++) {
        curr = curr->se;
      }
      return curr->nw;
    }
    if (t->upLeft.first == t->parent->upLeft.first + t->size) { // if t is nw
      for (int i = 0; i < countSNbr; i++) {
        curr = curr->ne;
      }
      return curr->sw;
    }
  }*/
  
}

/* WNbr(t)
 * return the same-sized quad tree node that is west of Node t.
 * return NULL if this node is not in the QTree.
 */
//int countWNbr = 0;
QTree::Node * QTree::WNbr(Node *t) {

  /* YOUR CODE HERE */
  if (t->parent == NULL) {
    return NULL;
  }

  if (t->parent->se == t) {
    return t->parent->sw;
  }

  if (t->parent->ne == t) {
    return t->parent->nw;
  }

  if (t->parent->nw == t) {
    Node *curr = WNbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->ne;
  }

  if (t->parent->sw == t) {
    Node *curr = WNbr(t->parent);
    if (curr == NULL) {
      return NULL;
    }
    return curr->se;
  }
  /*if (t->parent == NULL) {
    return NULL;
  }

  if (t->upLeft.first == t->parent->upLeft.first) { // if t is a western subnode
    countWNbr = countWNbr + 1;
    WNbr(t->parent);
  }

  else {
    Node* curr = t->parent;
    if (t->upLeft.first == t->parent->upLeft.first) { // if t is ne
      for (int i = 0; i < countSNbr; i++) {
        curr = curr->nw;
      }
      return curr->se;
    }
    if (t->upLeft.first == t->parent->upLeft.first + t->size) { // if t is se
      for (int i = 0; i < countSNbr; i++) {
        curr = curr->sw;
      }
      return curr->ne;
    }
  }*/
  
}

bool QTree::write(string const & fileName){

  /* YOUR CODE HERE */
  writeHelp(root);
  // include the following line to write the image to file.

  return(im.writeToFile(fileName));
}

void QTree::writeHelp(Node* curr) {
  if (isLeaf(curr)) {
    int x = curr->upLeft.first; int y = curr->upLeft.second;
    RGBAPixel average = curr->avg;
    for (int i = 0; i < curr->size; i++) {
      for (int j = 0; j < curr->size; j++) {
        if (drawFrame && (i == 0 || j == 0 || i == curr->size - 1 || j == curr->size - 1)) {
          *im.getPixel(i + x, j + y) = frameColor;
        }
        else {
          *im.getPixel(i + x, j + y) = average;
        }
      }
    }
  }

  else {
    writeHelp(curr->nw); writeHelp(curr->ne); writeHelp(curr->sw); writeHelp(curr->se);
  }
  
}


void QTree::clear() {

  /* YOUR CODE HERE */
  clearHelp(root);
  root = NULL;
}

void QTree::clearHelp(Node* t) {
  if (isLeaf(t)){
    delete t;
    return;
  }
  else {
    clearHelp(t->nw);
    clearHelp(t->ne);
    clearHelp(t->sw);
    clearHelp(t->se);
    delete t;
  }
}


void QTree::copy(const QTree & orig) {

  /* YOUR CODE HERE */

  // copy orig to itself (possibly by traversing orig?)
  im = orig.im;
  numLeaf = orig.numLeaf;
  leafBound = orig.leafBound;
  balanced = orig.balanced;
  drawFrame = orig.drawFrame;
  frameColor = orig.frameColor;

  root = new Node(im, orig.root->upLeft, orig.root->size, NULL);

  copyHelper(orig.root, root);
}

void QTree::copyHelper(Node* curr, Node* curr2) {

  if (!isLeaf(curr)) {
    curr2->nw = new Node(im, curr->nw->upLeft, curr->nw->size, curr);
    curr2->nw->avg = curr->nw->avg;
    copyHelper(curr->nw, curr2->nw);
    curr2->ne = new Node(im, curr->ne->upLeft, curr->ne->size, curr);
    curr2->ne->avg = curr->ne->avg;
    copyHelper(curr->ne, curr2->ne);
    curr2->sw = new Node(im, curr->sw->upLeft, curr->sw->size, curr);
    curr2->sw->avg = curr->sw->avg;
    copyHelper(curr->sw, curr2->sw);
    curr2->se = new Node(im, curr->se->upLeft, curr->se->size, curr);
    curr2->se->avg = curr->se->avg;
    copyHelper(curr->se, curr2->se);
  }
}