#include <iostream>
#include <unistd.h> 
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

class Vector{ //Base vector class represents a vector 
    public:

        //Represents the dimension the vector is in
        int v_dim;

        //Positions of the vector in raylib
        double x_pos;
        double y_pos;

        //Components of the vector
        std::vector<double> components;

        //Magnitude of the vector
        double magnitude;

        //Constructor
        Vector(int num_components, std::vector<double> comps){

            if (num_components != comps.size() || num_components <= 0){ //Added this to avoid errors of user not knowing that dim their vector is in
                throw std::invalid_argument("Number of components must be positive and equal to num_components");
            }

            v_dim = num_components;

            //Sets the components of the vector
            this->components = comps;

            //Calculates the magnitude of the vector and displays it
            double sum_roots;
            std::string vector_string = "Vector: <";
            for (int i = 0; i < components.size(); i++){

                sum_roots += pow(components[i], 2); //Adds square of term for magnitude calculation

                //Handles stuff for the vector string
                vector_string += std::to_string(components[i]).substr(0, 3);
                if (i < components.size() - 1){
                    vector_string += ", ";
                }
            }
            magnitude = sqrt(sum_roots);
            vector_string += ">\n";
            std::cout << vector_string;
        }

        

};


int main(){

    //Test stuff
    std::vector<double> vector_comps = {1, 2};
    Vector* v = new Vector(2, vector_comps);

    return 0;
}