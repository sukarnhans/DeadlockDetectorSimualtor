#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

vector<vector<int>> readCSV1(const string& filename, int* resourceCount) {
    vector<vector<int>> matrix;
    ifstream file(filename);
    string line, value;

    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        stringstream ss(line);
        vector<int> row;

        getline(ss, value, ','); // Skip the process/resource identifier
        while (getline(ss, value, ',')) {
            row.push_back(stoi(value));
        }
        if (matrix.empty()) {
            *resourceCount = row.size(); // Set the number of resources
        }
        matrix.push_back(row);
    }
    file.close();
    return matrix;
}

vector<int> readCSV2(const string& filename, int* resourceCount) {
    vector<int> vec;
    ifstream file(filename);
    string value;

    getline(file, value); // Skip the resource identifier line

    while (getline(file, value, ',')) {
        vec.push_back(stoi(value));
    }
    file.close();

    *resourceCount = vec.size();
    return vec;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void printVector(const vector<int>& vec) {
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

void deadlockDetection(vector<vector<int>> allocationMatrix, vector<vector<int>> requestMatrix, vector<int> availableVector) {
    int n = allocationMatrix.size(); // processes
    int m = availableVector.size(); //resources
    vector<int> work = availableVector;
    vector<bool> finish(n, false);
    vector<int> sequence; // safe sequence

    //Initialize Finish vector based on Allocation matrix
    for (int i = 0; i < n; i++) {
        bool allResourcesFinished = true;
        for (int j = 0; j < m; j++) {
            if (allocationMatrix[i][j] != 0) {
                allResourcesFinished = false;
                break;
            }
        }
        finish[i] = allResourcesFinished;
    }

    bool found;
    do {
        found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++) {
                    if (work[j] < requestMatrix[i][j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocationMatrix[i][j];
                    }
                    finish[i] = true;
                    sequence.push_back(i); //Add to the safe sequence
                    found = true;
                    break;
                }
            }
        }
    } while (found);

    //Check for deadlock
    bool deadlock = false;
    for (bool state : finish) {
        if (!state) {
            deadlock = true;
            break;
        }
    }

    //Print the output based on whether there is a deadlock or not
    if (deadlock) {
        cout << "The system is in a deadlock state.\nDeadlocked processes: <";
        bool first = true;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                if (!first) {
                    cout << ", ";
                }
                cout << "P" << i + 1;
                first = false;
            }
        }
        cout << ">" << endl;
    } else {
        cout << "The system is not in a deadlock state.\nPossible process execution sequence without deadlock: <";
        for (int i = 0; i < sequence.size(); i++) {
            if (i > 0) {
                cout << ", ";
            }
            cout << "P" << sequence[i] + 1;
        }
        cout << ">" << endl;
    }
}


int main() {
    int allocationResources = 0, requestResources = 0, availableResources = 0;

    vector<vector<int>> allocationMatrix = readCSV1("Allocation.csv", &allocationResources);
    vector<vector<int>> requestMatrix = readCSV1("Request.csv", &requestResources);
    vector<int> availableVector = readCSV2("Available.csv", &availableResources);

    cout << "Allocation Matrix (" << allocationResources << " resources):" << endl;
    printMatrix(allocationMatrix);

    cout << "\nRequest Matrix (" << requestResources << " resources):" << endl;
    printMatrix(requestMatrix);

    cout << "\nAvailable Vector (" << availableResources << " resources):" << endl;
    printVector(availableVector);

    bool areConsistent = (allocationResources == requestResources && allocationResources == availableResources && requestResources == availableResources);

    if (areConsistent == true) {
        cout << "\n\nGiven Dimensions are Consistent!" << endl << endl;
        deadlockDetection(allocationMatrix, requestMatrix, availableVector);
    } else {
        cout << "\n\nGiven Dimensions are Inconsistent!" << endl << endl;
    }

    return 0;
}