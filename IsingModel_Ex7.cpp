#include <iostream>
#include <math.h>
#define ISINGSIZE 16

class IsingParticle{
    private:
        int spin; // +1 is spin up, -1 is spin down
    public:
        IsingParticle(){spin  = +1;} //constructor. Sets spin in up position
        void flipSpin(){spin *= -1;} // flips the spin
        int const spinValue(){return spin;}; // returns the spin value
};

class IsingSystem{
    private:
        IsingParticle particles[ISINGSIZE][ISINGSIZE];
        int current_column;
        int current_row;
        int left_column;
        int right_column;
        int up_row;
        int down_row;
        void find_neighbours();
    public:
        IsingSystem();          // Function name starts with caps, is constructor
        void choose();          // choose a particle in the lattice
        void perturb();         // spin-flip for the chosen particle
        void print();           // prints the current lattice configuration
        double localEnergy();   // Interaction energy for the chosen particle
        double totalEnergy();   // total energy for the lattice
        double magnetisation(); // magnetisation of the system
};
IsingSystem::IsingSystem () { //Ex 2i Code
    current_column =0;  current_row =0;
    left_column =0;     right_column =0;
    up_row =0;          down_row =0;
    srand (time(NULL)); //No need for this in individual function calls
}

void IsingSystem::choose(){ //Ex 2ii Code
    current_column = rand() % ISINGSIZE;
    current_row = rand() % ISINGSIZE;
    std::cout << "Current Chosen Particle: (" << current_column << "," << current_row << ")" << std::endl ;
}

void IsingSystem::perturb(){ //Ex 3 Code
    std::cout <<"Before perturb: " << particles[current_column][current_row].spinValue();
    particles[current_column][current_row].flipSpin();
    std::cout <<" ------> After perturb: " << particles[current_column][current_row].spinValue() << std::endl ;
}

void IsingSystem::print(){ //Ex 4 Code
    int n, m;
    
    for(m=0;m<ISINGSIZE;m++){
        for(n=0;n<ISINGSIZE;n++){
            std::cout << particles[m][n].spinValue();
        }
        std::cout << std::endl ;
    }
}
    
void IsingSystem::find_neighbours(){ //Ex 5 Code
    left_column = (current_column == 0) ?  ISINGSIZE-1 : current_column-1;
    right_column  = (current_column == ISINGSIZE-1) ?  0 : current_column+1;
    up_row  = (current_row == 0) ?  ISINGSIZE-1 : current_row-1;
    down_row  = (current_row == ISINGSIZE-1) ?  0 : current_row+1;
    //std::cout << "Neighbours - left, right, up down: " << left_column <<", "<< right_column <<", "<< up_row <<", "<< down_row << std::endl;
}

double IsingSystem::localEnergy(){ //Ex 5 Code
    int J = 0, current_spin = particles[current_column][current_row].spinValue();
    find_neighbours();
    
    J += (particles[left_column][current_row].spinValue() == current_spin) ? -1 : 1;
    J += (particles[right_column][current_row].spinValue() == current_spin) ? -1 : 1;
    J += (particles[current_column][up_row].spinValue() == current_spin) ? -1 : 1;
    J += (particles[current_column][down_row].spinValue() == current_spin) ? -1 : 1;
    //std::cout << J << std::endl;
    return J;
    
}

double IsingSystem::magnetisation(){ //Ex 6 Code
    int i,j;
    float m,sum = 0;
    
    for(i=0;i<ISINGSIZE;i++){
        for(j=0;j<ISINGSIZE;j++){
            sum += particles[i][j].spinValue();
        }
    }
    return m = sum/(ISINGSIZE*ISINGSIZE);
}

double IsingSystem::totalEnergy(){ //Ex 7 Code
    int i,j;
    double t = 0;
    
    for(i=0;i<ISINGSIZE;i++){
        current_column = i;
        for(j=0;j<ISINGSIZE;j++){
            current_row = j;
            t += localEnergy();
        }
    }
    return t;
}
int main(){
    IsingParticle P; //Single particle
    IsingSystem Model; //System of ISINGSIZE^2 particles
    int i; // Simple iterator
    

    std::cout << "-----Ex 2i Output-----" <<std::endl;
    std::cout << "The spin of your particle is " << P.spinValue() << std::endl ;
    P.flipSpin();
    std::cout << "The spin of your particle is " << P.spinValue() << std::endl ;
    std::cout << std::endl;
    
    std::cout << "-----Ex 6 and 7 initial-----" <<std::endl;
    std::cout << "Magnetisation of initial conditions: " << Model.magnetisation() << std::endl;
    std::cout << "Total Energy of initial conditions: " << Model.totalEnergy() << std::endl;
    std::cout << std::endl;
    
    std::cout << "-----Ex 2ii Output-----" <<std::endl;
    Model.choose();Model.choose();Model.choose();Model.choose();
    std::cout << std::endl;
    
    std::cout << "-----Ex 3 Output-----" <<std::endl;
    Model.perturb();
    std::cout << std::endl;
    
    std::cout << "-----Ex 4 Output-----" <<std::endl;
    Model.print();
    for(i=0;i<4;i++){Model.choose();Model.perturb();};
    Model.print();
    std::cout << std::endl;
    
    std::cout << "-----Ex 5 Output-----" <<std::endl;
    Model.choose(); Model.localEnergy(); Model.perturb(); Model.localEnergy();
    std::cout << std::endl; //Change in energy --> localEnergy = localEnergy * -1
    
    std::cout << "-----Ex 6 and 7 final-----" <<std::endl;
    std::cout << "Magnetisation of final conditions: " << Model.magnetisation() << std::endl;
    std::cout << "Total Energy of final conditions: " << Model.totalEnergy() << std::endl;
    std::cout << std::endl;
    
    system("Pause");
    return 0;
}
