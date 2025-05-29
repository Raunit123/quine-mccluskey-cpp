#include "../include/qm.hpp"
#include<vector>
#include<iostream>
#include<sstream>

using namespace std;


int main() {
    cout << "Enter the number of variables: ";
    int num_vars;
    cin >> num_vars;
    cin.ignore(); // Ignore the newline character after the number input

    // Prompt user for the minterms
    cout << "Enter the minterms separated by spaces: ";
    string line;
    getline(cin, line); // Read the entire line of minterms
    stringstream ss(line);
    vector<int> minterms;
    int minterm;
    while (ss >> minterm) {
        minterms.push_back(minterm); // Extract each minterm and add to vector
    }

    // Validate the minterms
    int max_minterm = (1 << num_vars) - 1; // Maximum possible minterm value
    for (int m : minterms) {
        if (m < 0 || m > max_minterm) {
            cerr << "Error: Minterm " << m << " is out of range for " << num_vars << " variables.\n";
            return 1;
        }
    }

    // Perform minimization using the QuineMcCluskey class
    QuineMcCluskey qm(num_vars);
    try {
        vector<string> result = qm.minimize(minterms);
        cout << "Minimized Boolean function consists of " << result.size() << " terms:\n";
        for (const auto& term : result) {
            cout << term << "\n"; // Print each minimized term
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}