#include <iostream>
#include <unistd.h> 
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

class Vector{ //Base vector class represents a vector 

    private:

        std::string generateVectorString(std::vector<double> comps){ //Takes in components and generates a vector string

            vector_string = "Vector: <";

            for (int i = 0; i < comps.size(); i++){ // Loops over and adds each component to the string

                vector_string += std::to_string(comps[i]).substr(0, 5);

                if (i < comps.size() - 1){
                    vector_string += ", ";
                }

            }
            
            vector_string += ">\n";

            return vector_string;
        }

    public:

        //Position of our vector in raylib -> NOTE THIS IS NOT THE ACTUAL POSITION OF A VECTOR ON A PLANE
        double x_position;
        double y_position;
        std::vector<double> position;

        //Represents the dimension the vector is in
        int v_dim;

        //Components of the vector
        std::vector<double> components;

        //Magnitude of the vector
        double magnitude;

        //String for the vector display
        std::string vector_string = "Vector: <";

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
            for (int i = 0; i < components.size(); i++){

                sum_roots += pow(components[i], 2); //Adds square of term for magnitude calculation

                //Handles stuff for the vector string
                vector_string += std::to_string(components[i]).substr(0, 5);
                if (i < components.size() - 1){
                    vector_string += ", ";
                }
            }
            magnitude = sqrt(sum_roots);
            vector_string += ">\n";
            std::cout << vector_string;
        }

        Vector operator*=(int c){ //Handles multiplication of a vector by a scalar c
            
            //Multiples each value in components by c
            for (double& component : components){
                component *= c;
            }

            this->vector_string = generateVectorString(components);

            return *this;

        }

        Vector operator*(int c){

            //Initializes info for constructor of new vector
            int new_vector_dims = v_dim;
            std::vector<double> new_vector_components;
            
            //Multiples each component in current vector by c
            for (double component : components){
                new_vector_components.push_back(component * c);
            }

            Vector new_vector(new_vector_dims, new_vector_components);

            if (position.size() == v_dim){ //Sets same position as current vector if the position is set
                new_vector.setPosition(position);
            }

            return new_vector;
        }

        int operator*(Vector& v){ //Handles dot product multiplication

            //Exception handling for vectors in different r
            if (v_dim != v.v_dim){
                std::cerr << "Cannot multiply two vectors of different dimensions.";
            }

            int sum = 0;
            
            for (int i = 0; i < v_dim; i++){
                sum += (components[i] * v.components[i]);
            }

            return sum;
        }


        void setPosition(std::vector<double> position){ //Sets the vector position on the plane

            if (position.size() != v_dim){
                std::cerr << "Position vector must have length equal to vector dimension.";
                return;
            }

            this->position = position;
        }

};


int main(){

    //Test stuff
    std::vector<double> vector_comps = {1, 2};
    Vector* v = new Vector(2, vector_comps);
    Vector* u = new Vector(2, vector_comps);
    std::cout << *u * *v << '\n';


    delete v;
    delete u;

    return 0;
}