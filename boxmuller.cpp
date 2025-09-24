#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

// Define a constant for PI
const double PI = 3.14159265358979323846;

void generateGaussianSamples(const std::string &filename, int num_samples)
{
    // Modern C++ random number generation
    // 1. Seed the random number engine
    std::mt19937 engine(time(0) + (int)filename[0]); // Seed differently for X and Y

    // 2. Create a distribution for uniform random numbers in (0, 1]
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // 3. Open the output file
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Generate samples in pairs using the Box-Muller transform
    for (int i = 0; i < num_samples / 2; ++i)
    {
        double u1 = dist(engine);
        double u2 = dist(engine);

        // Box-Muller transform
        double z1 = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
        double z2 = sqrt(-2.0 * log(u1)) * sin(2.0 * PI * u2);

        outFile << z1 << std::endl;
        outFile << z2 << std::endl;
    }

    outFile.close();
    std::cout << "Generated " << num_samples << " samples in " << filename << std::endl;
}

int main()
{
    int num_samples = 1000000; 

    generateGaussianSamples("X_samples.txt", num_samples);
    generateGaussianSamples("Y_samples.txt", num_samples);

    return 0;
}