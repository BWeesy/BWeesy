#include <iostream>
#include <math.h>
#include <time.h>
#define ISINGSIZE 16
#define ITERATIONS 100

class IsingParticle{
    private:
        int spin; // +1 is spin up, -1 is spin down
    public:
        IsingParticle(){spin = +1;} //constructor. Sets spin in up position
        void flipSpin(){if(spin == +1) spin = -1; else spin = +1;}// flips the spin
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
        IsingSystem(); // Function name starts with caps, is constructor
        void choose(); // choose a particle in the lattice
        void perturb(); // spin-flip for the chosen particle
        void print(); // prints the lattice configuration
        int localEnergy(); // Interaction energy for the chosen particle
        double totalEnergy(); // total energy for the lattice
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
}

void IsingSystem::perturb(){ //Ex 3 Code
    particles[current_column][current_row].flipSpin();
}

void IsingSystem::print(){ //Ex 4 Code
    int n, m;
    
    for(m=0;m<ISINGSIZE;m++){
        for(n=0;n<ISINGSIZE;n++){
            std::cout << particles[m][n].spinValue();
        }
        std::cout << std::endl;
    }
}
    
void IsingSystem::find_neighbours(){ //Ex 5 Code
    left_column = (current_column == 0) ?  ISINGSIZE-1 : current_column-1;
    right_column  = (current_column == ISINGSIZE-1) ?  0 : current_column+1;
    up_row  = (current_row == 0) ?  ISINGSIZE-1 : current_row-1;
    down_row  = (current_row == ISINGSIZE-1) ?  0 : current_row+1;
}

int IsingSystem::localEnergy(){ //Ex 5 Code
    int J = 0, current_spin = particles[current_column][current_row].spinValue();
    find_neighbours();
    
    J += (particles[left_column][current_row].spinValue() == current_spin) ? -1 : 1;
    J += (particles[right_column][current_row].spinValue() == current_spin) ? -1 : 1;
    J += (particles[current_column][up_row].spinValue() == current_spin) ? -1 : 1;
    J += (particles[current_column][down_row].spinValue() == current_spin) ? -1 : 1;
    
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
    IsingSystem Model;
    int i, energyBefore = 0, energyAfter =0, energyChange = 0;
    double r,T = 100;
    std::cout << std::endl << Model.magnetisation() <<" "<< Model.totalEnergy() << std::endl;
    for(i=0;i<ITERATIONS;i++){
        Model.choose();
        energyBefore = Model.localEnergy();
        Model.perturb();
        energyAfter = Model.localEnergy();
        Model.perturb();
        energyChange = energyAfter - energyBefore;
        r = (double) rand()/RAND_MAX;
        if (r < exp(-energyChange/T)) Model.perturb();
        
    }
    std::cout << std::endl << Model.magnetisation() <<" "<< Model.totalEnergy() << std::endl;
    
    system("Pause");
    return 0;
}
