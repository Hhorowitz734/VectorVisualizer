#include <iostream>
#include <unistd.h> 
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

class Vector{ //Base vector class represents a vector 

    private:

        std::string generateVectorString(){ //Takes in components and generates a vector string

            vector_string = "Vector: <";

            for (int i = 0; i < components.size(); i++){ // Loops over and adds each component to the string

                vector_string += std::to_string(components[i]).substr(0, 5);

                if (i < components.size() - 1){
                    vector_string += ", ";
                }

            }
            
            vector_string += ">\n";

            return vector_string;
        }

        double computeMagnitude(){ //Computes the magnitude of the vector

            double sum_roots = 0;

            for (double component : components) {
                sum_roots += pow(component, 2);
            }

            magnitude = sqrt(sum_roots);

            return magnitude;
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

            //Calculates the magnitude and generates the vector string
            this->magnitude = computeMagnitude();
            this->vector_string = generateVectorString();

            std::cout << vector_string;
        }

        Vector operator*=(int c){ //Handles multiplication of a vector by a scalar c
            
            //Multiples each value in components by c
            for (double& component : components){
                component *= c;
            }
            
            //Recomputes magnitude and generates new vector string
            this->vector_string = generateVectorString();
            this->magnitude = computeMagnitude();

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

            //PLEASE NOTE -> THIS FUNCTION PERFORMS DOT PRODUCT MULTIPLICATION ONLY
            //FOR CROSS PRODUCT MULTIPLICATION, SEE [ CHANGE THIS WHEN I MAKE THAT FUNCTION ]

            //Exception handling for vectors in different r
            if (v_dim != v.v_dim){
                std::cerr << "Cannot multiply two vectors of different dimensions.";
            }

            int sum = 0;
            
            //Multiplies values of components and adds them to sum (to compute dot product)
            for (int i = 0; i < v_dim; i++){
                sum += (components[i] * v.components[i]);
            }

            return sum;
        }

        Vector operator+(Vector& v){

            if (v_dim != v.v_dim){
                std::cerr << "Cannot add two vectors of different dimensions.";
            }

            //Sets up the new vector
            int new_vector_dims = v_dim;
            std::vector<double> new_vector_components;

            //Adds the components of the two vector
            for (int i = 0; i < v_dim; i++){
                new_vector_components.push_back(components[i] + v.components[i]);
            }

            Vector new_vector(new_vector_dims, new_vector_components);

            return new_vector;

        }

        Vector operator-(Vector& v){
            
            if (v_dim != v.v_dim){
                std::cerr << "Cannot subtract two vectors of different dimensions.";
            }

            //Sets up the new vector
            int new_vector_dims = v_dim;
            std::vector<double> new_vector_components;

            //Adds the components of the two vector
            for (int i = 0; i < v_dim; i++){
                new_vector_components.push_back(components[i] - v.components[i]);
            }

            Vector new_vector(new_vector_dims, new_vector_components);

            return new_vector;

        }

        void setPosition(std::vector<double> position){ //Sets the vector position on the plane

            if (position.size() != v_dim){
                std::cerr << "Position vector must have length equal to vector dimension.";
                return;
            }

            this->position = position;
        }

        Vector getUnitVector(){ //Returns the unit vector of the vector

            //Sets up the new vector
            int new_vector_dims = v_dim;
            std::vector<double> new_vector_components;
            
            //Creates a new vector where the components are divided by the magnitude
            for (double component : components){
                new_vector_components.push_back(component / magnitude);
            }

            Vector new_vector(new_vector_dims, new_vector_components);

            //Sets position to same as curent vetor
            if (position.size() == v_dim){
                new_vector.setPosition(position);
            }

            return new_vector;

        }

        double getAngleBetweenVectors(Vector v){ //Returns the angle between two angles

            if (v_dim != v.v_dim){
                std::cerr << "Cannot get angle between two vectors of different dimensions.\n";
            }

            int dot_product = *this * v;

            //Uses formula for angle between vectors and returns result
            double angle = acos(dot_product / (magnitude * v.magnitude));
            angle *= (180 / M_PI); //Converts radians to degrees

            return angle;

        }

};


int main(){

    //Test stuff
    std::vector<double> vector_comps = {6, 2, 3};
    Vector* v = new Vector(3, vector_comps);
    std::vector<double> vector2_comps = {6, 2, 4};
    Vector* w = new Vector(3, vector2_comps);
    std::cout << v->getAngleBetweenVectors(*w);


    delete v;

    return 0;
}