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

        Vector operator*=(double c){ //Handles multiplication of a vector by a scalar c
            
            //Multiples each value in components by c
            for (double& component : components){
                component *= c;
            }
            
            //Recomputes magnitude and generates new vector string
            this->vector_string = generateVectorString();
            this->magnitude = computeMagnitude();

            return *this;

        }

        Vector operator*(double c){

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

        double operator*(Vector& v){ //Handles dot product multiplication

            //PLEASE NOTE -> THIS FUNCTION PERFORMS DOT PRODUCT MULTIPLICATION ONLY
            //FOR CROSS PRODUCT MULTIPLICATION, SEE [ CHANGE THIS WHEN I MAKE THAT FUNCTION ]

            //Exception handling for vectors in different r
            if (v_dim != v.v_dim){
                std::cerr << "Cannot multiply two vectors of different dimensions.";
            }

            double sum = 0;
            
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

        double getAngleBetweenVectors(Vector& v){ //Returns the angle between two angles

            if (v_dim != v.v_dim){
                std::cerr << "Cannot get angle between two vectors of different dimensions.\n";
            }

            int dot_product = *this * v;

            //Uses formula for angle between vectors and returns result
            double angle = acos(dot_product / (magnitude * v.magnitude));
            angle *= (180 / M_PI); //Converts radians to degrees

            return angle;

        }

        Vector getVectorProjection(Vector b){ //Returns the vector projection of another vector b onto this vector

            //NOTE -> THIS REPRESENTS THE EQUATION Proj(_a)b = ((a * b) / |a|^2) * a
            //And the vector which this function is called on is a

            double dotProduct = *this * b;
            double multiplier = dotProduct / pow(magnitude, 2); //Computes a * b / |a|^2
            
            //Multiplies the scalar (multiplier) by this vector and stores it as a new vector to be returned
            Vector new_vector = *this * multiplier;

            return new_vector;

        }

        double getScalarProjection(Vector b){ //Returns the scalar projection of another vector b onto this vector

            //Sets up a temp vector to get its magnitude
            Vector temp_vector = getVectorProjection(b);
            //This works because the scalar projection is the signed magnitude of the vector projection

            return temp_vector.magnitude;

        }

        std::vector<double> getDirectionAngles(){ //Returns the direction angles of a given vector

            //This function will return the direction vectors alpha, beta, gamma in the following form:
            //A std::vector with index 0 -> alpha | index 1 -> beta | index 2 -> gamma

            //Note that this method will only work for angles in R3 or R2
            if (v_dim > 3){
                std::cerr << "Cannot compute direction angles for vectors with R > 3.";
            }

            std::vector<double> direction_angles;

            for (double component : components){
                double cos_of_angle = component / magnitude; //Computes the cos of the angle (a_n / |a|)
                direction_angles.push_back(acos(cos_of_angle)); //Adds the arccos of that angle to the vector to be returned
            }

            return direction_angles;

        }

        Vector crossProduct(Vector b){ //Returns the cross product of this vector with a vector b

            //Cross product is only defined for vectors in R3
            if (v_dim != 3 || b.v_dim != 3){
                std::cerr << "Both vectors must be in R3 to compute cross product.";
            }

            std::vector<double> new_vector_comps = { //Sets up vector components using cross product formula
                components[1] * b.components[2] - components[2] * b.components[1],
                components[2] * b.components[0] - components[0] * b.components[2],
                components[0] * b.components[1] - components[1] * b.components[0]
            };

            //Sets up and returns the new vector
            Vector new_vector(3, new_vector_comps);

            return new_vector;

        }

};


int main(){

    //Test stuff
    std::vector<double> vector_comps = {1, 3, 4};
    Vector* v = new Vector(3, vector_comps);
    std::vector<double> vector2_comps = {2, 7, -5};
    Vector* w = new Vector(3, vector2_comps);
    Vector z = v->crossProduct(*w);




    return 0;
}