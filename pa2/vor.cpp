/**
 * @file vor.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
//included within  "vor.h" for template instantiation


#include <deque>
#include "dotColorPicker.h"
#include "solidColorPicker.h"
#include "fadeColorPicker.h"
#include "vor.h"
#include "deque.h"
#include "animation.h"
#include <queue>

/* vorDotDFS given as an example for PA2 */
animation filler::vorDotDFS(PNG& img, double density, int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid,dotSize);
    return vor<Stack>(img, density, a, frameFreq);
}

animation filler::vorSolidDFS(PNG& img, double density, int frameFreq)
{
    solidColorPicker a;
    return vor<Stack>(img, density, a, frameFreq);

}

animation filler::vorFadeDFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    fadeColorPicker a(fadeFactor);
    return vor<Stack>(img, density, a, frameFreq);

}

/* vorDotBFS given as an example for PA2 */
animation filler::vorDotBFS(PNG& img, double density, int dotGrid,int dotSize, int frameFreq)
{
    dotColorPicker a(dotGrid, dotSize);
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorSolidBFS(PNG& img, double density, int frameFreq)
{
    solidColorPicker a;
    return vor<Queue>(img, density, a, frameFreq);
}

animation filler::vorFadeBFS(PNG& img, double density, double fadeFactor, int frameFreq)
{
    fadeColorPicker a(fadeFactor);
    return vor<Queue>(img, density, a, frameFreq);
}


template <template <class T> class OrderingStructure>
animation filler::vor(PNG& img, double density, colorPicker& fillColor, int frameFreq)
{

    /**
     * @todo You need to implement this function!
     *
     * This is a general description of a space filling algorithm, where 
     * the space is partitioned into a set of regions each color of which
     * is determined by the color of a point 
     * chosen from an original image. We call those original points
     * "centers." (See pictures in the specification.)
     *
     * The algorithm requires ordering structures used to orchestrate
     * the sequence of points filled. This structure type info is passed to the 
     * fill algorithm via its template parameter. For a breadth-first fill,
     * we use Queues, and for a depth-first fill, we use Stacks. Function
     * vorDotDFS provides an example call to function vor.
     * 
     * The algorithm includes the following steps:
     * 1) you will first select a random set
     * of coordinates (and their colors) to use as centers from which to
     * begin the fill. (this function is in file vor_given.cpp -- for 
     * testing purposes, you'll use regularly spaced points, rather than 
     * random.)
     * 2) Initialize a structure to use to maintain a collection of 
     * ordering structures
     *
     * 3) Initialize the fill: For each center c, in round-robin order,
     *     do the following:
     *     a)  add the center to the its ordering structure. (every center 
     *         its own!
     *     b)  mark the location of that center as processed (the way you 
     *         do this is up to you!)
     *     c)  we have a choice to actually set the color of the pixel in 
     *         the fill when we add or when we remove. In our test cases, 
     *         we assume that you will change a color when a point is 
     *         added to a structure. (this is mostly relevant for checking 
     *         the animations.)
     *
     * 5) Complete the fill: Until all ordering structures (OS) are empty, 
     *    do the following for each OS, in a round robin order, indexing
     *    the iterations by k (an integer distance from the center):
     *    
     *      For each point less than or equal to distance k from its center:
     *      a)Remove the  point p from the ordering structure, and then...
     *
     *        i.    add p's unprocessed neighbors to the ordering structure if 
     *              they are within the appropriate distance from the center. We 
     *              describe this more carefully below. We call these the "valid"
     *              neighbors.
     *        ii.    use the colorPicker to set the new color of the valid neighbors.
     *        iii.    mark the valid neighbors as processed.
     *        iv.    as each neighbor is processed, if it is an appropriate 
     *              frame, send the current PNG to the
     *              animation (as described below).
    *
     *      b) When implementing your breadth-first and depth-first fills, 
     *            you will need to explore neighboring pixels in some order.
     *
     *        For this assignment, each pixel p has *up to* 8 neighbors, consisting of 
     *        the 8 pixels who share an edge with p. (We leave it to
     *        you to describe those 8 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y), 
     *        DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)**
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        TWO IMPORTANT NOTES: 
     *        1) *UP* here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction. 
     *        2) not all of the 8 neighbors will be processed at every iteration of the
     *        while loop. You must assure that all vertices distance k or less
     *        from the center are processed (colored and put on the queue) before
     *        ANY whose distance is *greater than* k. k is a non-negative integer. 
     *        Finally, distance is the standard Euclidean distance  (computed 
     *        using the Pythagorean theorem). It is this requirement that assures
     *        that the fill grows outward from the center in the shape of a circle,
     *        rather than a diamond or a square. 
     *
     *      c) For every g pixels filled, **starting at the gth pixel**, you
     *        must add a frame to the animation, where g = frameFreq. // increment g after each pixel increment use mod
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *      d) Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */



    /* Your code here. As a point of reference, we used three different helper
     * functions to complete this code. You may add as many as you wish, since
     * we will be grading vor.h. File "vor_given.cpp also includes the function
     * used to generate the original set of centers.
     */
    PNG vorImg = PNG(img.width(), img.height());
    unsigned int imgWidth = img.width();
    unsigned int imgHeight = img.height();

    // initialize counter for g
    int g = 0;
    cout << "frame frequency: " << frameFreq << endl;
    cout << "image width: " << imgWidth << endl;
    cout << "image height: " << imgHeight << endl;

    // initialize animation class
    animation anim;

    // sample random centers from image
    vector<center> centers = filler::randSample(img, density);

    // structure to use to maintain a collection of ordering structures
    std::queue<OrderingStructure<point>> OrderingStructs;

    // initialize integer vector to keep track of processed vs. unprocessed points
    // 0 = unprocessed, 1 = processed
    unsigned int isProcessedSize = imgWidth * imgHeight;
    std::vector<int> isProcessed(isProcessedSize);
    for (unsigned int i = 0; i < isProcessedSize; i++) {
        isProcessed[i] = 0;
    }

    // initialize ordering structure for each center
    for (auto & center : centers) {
        // create point out of center
        point centerPoint = point(center);
        // initialize ordering structure
        OrderingStructure<point> points;
        // add the point with center to the ordering structure
        if (isProcessed[getIndex(centerPoint, imgWidth)] == 0) {
            points.add(centerPoint);
            cout << "center x, center y: " << center.x << " ," << center.y << endl;
            // enqueue to ordering vector
            OrderingStructs.push(points);
//        cout << "size of ordering struct: " << OrderingStructs.size() << endl;
            // mark location of center as processed
            isProcessed[getIndex(centerPoint, imgWidth)] = 1;

            // change color of point p in new image
            HSLAPixel *pixel = vorImg.getPixel(centerPoint.x, centerPoint.y);
            *pixel = fillColor(centerPoint);
            // increment g
            g++;
            if (g % frameFreq == 0) {
                anim.addFrame(vorImg);
            }
        }
    }


    // initialize k
    int k = 0;
    // continue iterating until collection of OS is empty
    while (!OrderingStructs.empty()) {
        // do a round robin of all ordering structures
        int size = OrderingStructs.size();
        cout << "current size of collection of OS: " << size << endl;
        for (int i = 0; i < size; i++) {
            // get an OS from collection
            OrderingStructure<point> activeOS = OrderingStructs.front();
            OrderingStructs.pop();
//            cout << "popped active OS, new size of collection of OS " << OrderingStructs.size() << endl;

            if (!activeOS.isEmpty()) {
                cout << "active OS is not empty" << endl;
                // keep iterating through ordering structure
                k = activeOS.peek().level;
                while(!activeOS.isEmpty() && activeOS.peek().level == k) {
                    point curr = activeOS.remove();
//                    cout << "level of current point: " << activeOS.peek().level << endl;
                    // create vector to temporarily store all neighboring points
                    vector<point> neighborPoints;
                    // UP (-y)
                    point n1 = point(curr.x, curr.y - 1, curr.c, k+1);
                    // UPLEFT (-x, -y)
                    point n2 = point(curr.x - 1, curr.y - 1, curr.c, k+1);
                    // LEFT (-x)
                    point n3 = point(curr.x - 1, curr.y, curr.c, k+1);
                    // LEFTDOWN (-x, +y)
                    point n4 = point(curr.x - 1, curr.y + 1, curr.c, k+1);
                    // DOWN (+y)
                    point n5 = point(curr.x, curr.y + 1, curr.c, k+1);
                    // DOWNRIGHT (+x, +y)
                    point n6 = point(curr.x + 1, curr.y + 1, curr.c, k+1);
                    // RIGHT (+x)
                    point n7 = point(curr.x + 1, curr.y, curr.c, k+1);
                    // RIGHTUP (+x, -y)
                    point n8 = point(curr.x + 1, curr.y - 1, curr.c, k+1);
                    neighborPoints.push_back(n1);
                    neighborPoints.push_back(n2);
                    neighborPoints.push_back(n3);
                    neighborPoints.push_back(n4);
                    neighborPoints.push_back(n5);
                    neighborPoints.push_back(n6);
                    neighborPoints.push_back(n7);
                    neighborPoints.push_back(n8);
                    for (int j = 0; j < 8; j++) {
//                        cout << "curr point x, y: " << neighborPoints[j].x << " , " << neighborPoints[j].y << endl;
                        if (isProcessable(neighborPoints[j], curr, imgWidth, imgHeight, k) &&
                            isProcessed[getIndex(neighborPoints[j], imgWidth)] == 0) {
//                            cout << "neighbor point is valid!" << endl;
//                            cout << "marking as processed, filling color and adding to OS..." << endl;
                            activeOS.add(neighborPoints[j]);
                            // mark location of center as processed
                            isProcessed[getIndex(neighborPoints[j], imgWidth)] = 1;
                            HSLAPixel * pixel = vorImg.getPixel(neighborPoints[j].x, neighborPoints[j].y);
                            * pixel = fillColor(neighborPoints[j]);
                            // increment g
                            g++;
                            if (g % frameFreq == 0) {
                                cout << "adding new frame to animation... frame number " << g/frameFreq << endl;
                                anim.addFrame(vorImg);
                            }
                        }
                    }
                }
                // put points to back of collection of ordering structure
                if (!activeOS.isEmpty()){
                    OrderingStructs.push(activeOS);
                }
            }
        }
        // increment k
        k++;
        cout << "new k value: " << k << endl;
    }
    cout << "sending final frame to animation..." << endl;
    // send final frame to animation
    anim.addFrame(vorImg);

    return anim;
}

bool filler::isProcessable(point neighbour, point current, unsigned int imgWidth, unsigned int imgHeight, int k) {
    double dist = sqrt(pow((neighbour.x - current.c.x), 2) + pow((neighbour.y - current.c.y), 2));
//    cout << "distance of neighbor to center: " << dist << endl;
    bool isValid = neighbour.x >= 0 && neighbour.y >= 0 && neighbour.x < imgWidth && neighbour.y < imgHeight && dist <= k + 1; // TODO: test inequality signs
//    cout << "is processable: " << isValid << endl;
    return isValid;
}

int filler::getIndex(point point, unsigned int imgWidth) {
    return point.y * imgWidth + point.x;
}
