#ifndef QM_HPP
#define QM_HPP

#include <string>
#include <vector>
#include <set>

using namespace std;

// Represents a term in the Quine-McCluskey algorithm
struct Term {
    string binary;        // Binary representation (e.g., "10-1")
    set<int> minterms;    // Set of minterms this term covers

    // Default constructor
    Term() : binary(""), minterms() {}

    // Parameterized constructor with explicit std::move
    Term(string b, set<int> m) : binary(std::move(b)), minterms(std::move(m)) {}

    bool operator==(const Term& other) const;
};

class QuineMcCluskey {
public:
    // Constructor: Initialize with number of variables
    explicit QuineMcCluskey(int num_vars);

    // Minimize the Boolean function given a list of minterms
    vector<string> minimize(const vector<int>& minterms);

private:
    int num_vars;  // Number of variables in the Boolean function

    // Convert an integer to its binary string representation
    string to_binary(int num);

    // Calculate Hamming distance between two binary strings
    int hamming_distance(const string& a, const string& b);

    // Combine two binary strings differing by one bit
    string combine(const string& a, const string& b);

    // Find all prime implicants
    vector<Term> find_prime_implicants(const vector<int>& minterms);

    // Identify essential prime implicants
    vector<Term> find_essential_prime_implicants(const vector<Term>& primes, const vector<int>& minterms);
};

#endif