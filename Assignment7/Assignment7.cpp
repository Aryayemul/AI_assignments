#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>

using namespace std;

// Function to apply forward chaining inference
set<string> applyForwardChaining(const vector<string>& initialFacts,
                                 const vector<pair<vector<string>, string>>& inferenceRules) {
    set<string> knownFacts(initialFacts.begin(), initialFacts.end());
    bool newFactFound = true;

    while (newFactFound) {
        newFactFound = false;

        for (const auto& rule : inferenceRules) {
            const vector<string>& prerequisites = rule.first;
            const string& outcome = rule.second;

            // Check if all prerequisites are met
            bool allMet = true;
            for (const string& condition : prerequisites) {
                if (knownFacts.find(condition) == knownFacts.end()) {
                    allMet = false;
                    break;
                }
            }

            // If all prerequisites met and outcome not yet known
            if (allMet && knownFacts.find(outcome) == knownFacts.end()) {
                knownFacts.insert(outcome);
                cout << "Derived new fact: " << outcome << endl;
                newFactFound = true;
            }
        }
    }

    return knownFacts;
}

int main() {
    // Initial facts
    vector<string> initialFacts = {"X", "Y"};

    // Inference rules (prerequisites, outcome)
    vector<pair<vector<string>, string>> inferenceRules = {
        {{"X", "Y"}, "Z"},
        {{"Z"}, "W"},
        {{"W"}, "V"}
    };

    cout << "Starting facts: ";
    for (const auto& fact : initialFacts)
        cout << fact << " ";
    cout << endl;

    // Apply forward chaining
    set<string> derivedFacts = applyForwardChaining(initialFacts, inferenceRules);

    cout << "Final derived facts: ";
    for (const auto& fact : derivedFacts)
        cout << fact << " ";
    cout << endl;

    return 0;
}
