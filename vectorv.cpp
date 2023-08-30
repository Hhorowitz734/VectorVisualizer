#include <iostream>
#include <unistd.h> 
#include <cstdlib>
#include <ctime>
#include <cmath>

class Vector{ //Base vector class represents a vector in R2
    public:

        //Positions of the vector in raylib
        double x_pos;
        double y_pos;

        //Components of the vector
        double x_comp;
        double y_comp;

        //Magnitude of the vector
        double magnitude;

        //Constructor
        Vector(double xcomponent, double ycomponent){

            //Sets the components of the vector
            x_comp = xcomponent;
            y_comp = ycomponent;

            //Calculates the magnitude of the vector
            magnitude = sqrt(pow(x_comp, 2) + pow(y_comp, 3));

            std::cout << "Vector created: <" + std::to_string(x_comp).substr(0, 3) + ", " + std::to_string(y_comp).substr(0, 3) + ">\n";

        }
};


int main(){

    Vector* v = new Vector(1, 2);

    return 0;
}