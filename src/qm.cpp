#include "../include/qm.hpp"
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std; // Added to remove std:: prefix


QuineMcCluskey::QuineMcCluskey(int num_vars) : num_vars(num_vars) {}

// Convert an integer to its binary string representation
string QuineMcCluskey::to_binary(int num) {
    string bin;
    for (int i = num_vars - 1; i >= 0; --i) {
        bin += (num & (1 << i)) ? '1' : '0';
    }
    return bin;
}

// Calculate Hamming distance between two binary strings
int QuineMcCluskey::hamming_distance(const string& a, const string& b) {
    int dist = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) dist++;
    }
    return dist;
}

// Combine two binary strings differing by one bit, replacing the differing bit with '-'
string QuineMcCluskey::combine(const string& a, const string& b) {
    string res = a;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) res[i] = '-';
    }
    return res;
}

// Find all prime implicants using the Quine-McCluskey method
vector<Term> QuineMcCluskey::find_prime_implicants(const vector<int>& minterms) {
    // Initialize with each minterm as a term
    vector<Term> current;
    for (int m : minterms) {
        current.emplace_back(to_binary(m), set<int>{m});
    }

    vector<Term> next, prime_implicants;
    bool combined;

    // Iteratively combine terms differing by one bit
    do {
        combined = false;
        next.clear();
        vector<bool> used(current.size(), false);

        for (size_t i = 0; i < current.size(); ++i) {
            for (size_t j = i + 1; j < current.size(); ++j) {
                if (hamming_distance(current[i].binary, current[j].binary) == 1) {
                    combined = true;
                    string new_bin = combine(current[i].binary, current[j].binary);
                    set<int> merged = current[i].minterms;
                    merged.insert(current[j].minterms.begin(), current[j].minterms.end());
                    Term new_term(new_bin, merged);
                    if (find(next.begin(), next.end(), new_term) == next.end()) {
                        next.push_back(new_term);
                    }
                    used[i] = used[j] = true;
                }
            }
        }

        // Add unused terms to prime implicants
        for (size_t i = 0; i < current.size(); ++i) {
            if (!used[i] && find(prime_implicants.begin(), prime_implicants.end(), current[i]) == prime_implicants.end()) {
                prime_implicants.push_back(current[i]);
            }
        }

        current = next;
    } while (combined);

    return prime_implicants;
}

// Identify essential prime implicants (those covering minterms not covered by others)
vector<Term> QuineMcCluskey::find_essential_prime_implicants(const vector<Term>& primes, const vector<int>& minterms) {
    vector<Term> result;
    for (int m : minterms) {
        int count = 0;
        Term essential;
        for (const auto& t : primes) {
            if (t.minterms.count(m)) {
                count++;
                essential = t;
            }
        }
        if (count == 1) {
            if (find(result.begin(), result.end(), essential) == result.end()) {
                result.push_back(essential);
            }
        }
    }
    return result;
}

// Minimize the Boolean function by selecting essential and additional prime implicants
vector<string> QuineMcCluskey::minimize(const vector<int>& minterms) {
    // Step 1: Find all prime implicants
    vector<Term> primes = find_prime_implicants(minterms);

    // Step 2: Find essential prime implicants
    vector<Term> essentials = find_essential_prime_implicants(primes, minterms);

    // Step 3: Determine minterms covered by essentials
    set<int> covered;
    for (const auto& e : essentials) {
        covered.insert(e.minterms.begin(), e.minterms.end());
    }

    // Step 4: Identify remaining uncovered minterms
    set<int> remaining;
    for (int m : minterms) {
        if (covered.find(m) == covered.end()) {
            remaining.insert(m);
        }
    }

    // Step 5: Prepare result with essential prime implicants
    vector<string> result;
    for (const auto& e : essentials) {
        result.push_back(e.binary);
    }

    // Step 6: If there are remaining minterms, select additional prime implicants
    if (!remaining.empty()) {
        // Find candidate prime implicants that cover at least one remaining minterm
        vector<Term> candidates;
        for (const auto& p : primes) {
            for (int m : p.minterms) {
                if (remaining.count(m)) {
                    candidates.push_back(p);
                    break;
                }
            }
        }

        // Greedily select prime implicants to cover all remaining minterms
        while (!remaining.empty()) {
            Term best;
            int max_cover = 0;
            for (const auto& c : candidates) {
                int cover = 0;
                for (int m : c.minterms) {
                    if (remaining.count(m)) {
                        cover++;
                    }
                }
                if (cover > max_cover) {
                    max_cover = cover;
                    best = c;
                }
            }
            if (max_cover == 0) {
                throw runtime_error("Cannot cover all minterms");
            }
            result.push_back(best.binary);
            for (int m : best.minterms) {
                remaining.erase(m);
            }
            auto it = find(candidates.begin(), candidates.end(), best);
            if (it != candidates.end()) {
                candidates.erase(it);
            }
        }
    }

    return result;
}

// Term equality operator for comparing binary strings and minterm sets
bool Term::operator==(const Term& other) const {
    return binary == other.binary && minterms == other.minterms;
}