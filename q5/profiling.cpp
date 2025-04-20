#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> generateRandomInput(int size, int seed) {
    vector<int> arr(size);
    srand(seed);
    for (int i = 0; i < size; ++i) {
        arr[i] = (rand() % 100) - 25;
    }
    return arr;
}

int maxSubarraySumKadane(const std::vector<int>& arr) {

    int maxEndingHere = arr[0];
    int maxSoFar = arr[0];

    for (size_t i = 1; i < arr.size(); ++i) {
        maxEndingHere = std::max(arr[i], maxEndingHere + arr[i]);
        maxSoFar = std::max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}

int maxSubarraySumQuadratic(const std::vector<int>& arr) {

    int n = arr.size();
    int maxSum = arr[0];

    for (int i = 0; i < n; ++i) {

        int currentSum = 0;

        for (int j = i; j < n; ++j) {
            currentSum += arr[j];
            maxSum = std::max(maxSum, currentSum);
        }
    }

    return maxSum;
}

int maxSubarraySumCubic(const std::vector<int>& arr) {

    int n = arr.size();
    int maxSum = arr[0];

    for (int i = 0; i < n; ++i) {

        for (int j = i; j < n; ++j) {

            int currentSum = 0;

            for (int k = i; k <= j; ++k) {
                currentSum += arr[k];
            }
            
            maxSum = std::max(maxSum, currentSum);
        }
    }

    return maxSum;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Error: Expected 2 arguments - <seed> <input_size>\n";
        cerr << "Example: ./profiling 42 1000\n";
        return 1;
    }

    int seed = atoi(argv[1]);
    int size = atoi(argv[2]);

    if (size <= 0) {
        cerr << "Error: input_size must be a positive integer\n";
        cerr << "Example: ./profiling 123 100\n";
        return 1;
    }

    vector<int> arr = generateRandomInput(size, seed);

    cout << "Running Kadane's Algorithm (O(n))...\n";
    cout<< "Result:" << maxSubarraySumKadane(arr) << endl;

    cout << "Running Quadratic Algorithm (O(n^2))...\n";
    cout<< "Result:" << maxSubarraySumQuadratic(arr) << endl;

    cout << "Running Cubic Algorithm (O(n^3))...\n";
    cout<< "Result:" << maxSubarraySumCubic(arr) << endl;

    cout << "All algorithms executed successfully!\n";

    return 0;
}