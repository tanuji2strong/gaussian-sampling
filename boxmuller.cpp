#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

const double PI = 3.14159265358979323846;

int main() {
    srand(time(NULL));
    const int num_samples = 100000;
    float fx[500] = {0.0f};
    float fy[500] = {0.0f};

    std::cout << "Generating " << num_samples << " samples and building histogram...\n";

    for (int i = 0; i < num_samples / 2; ++i) {
        double u1 = ((double)rand() + 1.0) / (RAND_MAX + 1.0); 
        double u2 = ((double)rand() + 1.0) / (RAND_MAX + 1.0);

        double r = std::sqrt(-2.0 * std::log(u1));
        double theta = 2.0 * PI * u2;
        double z1 = r * std::cos(theta);
        double z2 = r * std::sin(theta);

        int k1 = (int)((z1 + 5.0) * 50.0); 
        int k2 = (int)((z2 + 5.0) * 50.0);

        if (k1 >= 0 && k1 < 500) fx[k1]++;
        if (k2 >= 0 && k2 < 500) fy[k2]++;
    }

    std::ofstream outFileX("histogram_X.txt");
    std::ofstream outFileY("histogram_Y.txt");
    if (!outFileX || !outFileY) {
        std::cerr << "Failed to open output files.\n";
        return 1;
    }

    for (int i = 0; i < 500; ++i) {
        double bin_center_value = (double(i) / 50.0) - 5.0;
        outFileX << bin_center_value << "\t" << fx[i] << "\n";
        outFileY << bin_center_value << "\t" << fy[i] << "\n";
    }

    outFileX.close();
    outFileY.close();
    std::cout << "Wrote histogram_X.txt and histogram_Y.txt\n";
    return 0;
}
