#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Assumption of everything measured in cm

double MAX_DISTANCE_ERROR = 1; // Margin of error for distance
double MAX_ANGLE_ERROR = 1;    // Margin of error for robot angle in Degrees

// Top left grid coordinates
double TOP_LEFT_X = 0;
double TOP_LEFT_Y = 10;

// Bottom right grid coordinates
double BOTTOM_RIGHT_X = 10;
double BOTTOM_RIGHT_Y = 0;

// Centre of grid coordinates
double CENTRE_X = abs(TOP_LEFT_X - BOTTOM_RIGHT_X)/2; 
double CENTRE_Y = abs(TOP_LEFT_Y - BOTTOM_RIGHT_Y)/2; 

static double calculateDistance(double startX, double startY, double destX, double destY) {
    sqrt(pow(destX - startX, 2) + pow(destY - startY, 2));
}

static double calculateAngle(double startX, double startY, double destX, double destY) {

    // Create vectors from the centre for both positions
    double startLine [2] = {(startX - CENTRE_X), (startY - CENTRE_Y)};
    double destLine [2] = {(destX - CENTRE_X), (destY - CENTRE_Y)};

    cout << "vector 1 : " << startLine[0] << ", " << startLine[1] << endl;
    cout << "vector 2 : " << destLine[0] << ", " << destLine[1] << endl;

    // Calculate the inner angle between them
    double pq = (startLine[0] * destLine[0]) + (startLine[1] * destLine[1]);
    double magPQ = sqrt(pow(startLine[0], 2) + pow(startLine[1], 2)) * sqrt(pow(destLine[0], 2) + pow(destLine[1], 2));   
    double pqDivMag = pq/magPQ;

    cout << pq << endl;
    cout << magPQ << endl;
    cout << pqDivMag << endl;
    cout << (pqDivMag == 1) << endl;
    cout << acos(pqDivMag) << endl;

    if (magPQ == 0) return -1; // Error for divide by 0

    double angle = acos(pq/magPQ);

    return angle/M_PI * 180;
}

static void move(double startX, double startY, double destX, double destY, double index)
{ // we will pass 0 as the initial index
    if (index < sizeof(arrayOfPots_X)) {
        
    // Calculate the distance between the positions
    double distance = calculateDistance(startX, startY, destX, destY);
    // Calculate the angle between them
    double angle = calculateAngle(startX, startY, destX, destY);
    // array that contains X coordinates of pots
    double arrayOfPots_X[];
    // array that contains Y coordinates of pots
    double arrayOfPots_Y[];
    
    
        if (distance < MAX_DISTANCE_ERROR) {
        cout << "At location" << endl;
        index++;
        } else {
            turn(angle); // turn at given angle
            moveForward(); // move forward
        }
        move(currentX, currentY, arrayOfPots_X[index], arrayOfPots_Y[index], index); // there needs to be a function to obtain current X and current Y
    }
}


/*static void movement(double startX, double startY, double destX, double destY, double reqAngle) {
    
    // Calculate the distance between the positions
    double distance = calculateDistance(startX, startY, destX, destY);

    //Calculate the angle between them
    double angle = getAngle(startX, startY, destX, destY);
    
    while (distance > MAX_DISATNCE_ERROR || angle > MAX_ANGLE_ERROR) {

        if (distance > MAX_DISTANCE_ERROR) {
            move();
        } else if (angle > MAX_ANGLE_ERROR) {
            turn();
        }
    }
}*/

int main() {
    cout << "angle is " << calculateAngle(5, 0, 0, 5) << endl;
    cout << "angle is " << calculateAngle(5, 5, 5, 5) << endl;
    cout << "angle is " << calculateAngle(0, 0, 0, 0) << endl;
    cout << "angle is " << calculateAngle(-2, 0, -1, 5) << endl;
}
