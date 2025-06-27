# DeadlockDetectorSim

## Overview
This repository contains a C++ program designed to simulate and manage resource allocation among multiple processes in a system, identifying potential deadlocks. It is developed for the ENCS3390 Operating System Concepts course and helps in understanding resource allocation, request handling, and deadlock detection.

## Repository Contents
- `main.cpp`: The main C++ source file that includes the logic for reading input files, processing data, and detecting deadlocks.
- `Allocation.csv`: Sample CSV file representing the NxM allocation matrix for processes and resources.
- `Request.csv`: Sample CSV file representing the NxM request matrix for processes and resources.
- `Available.csv`: Sample CSV file representing the M available vector of resources.
- `ENCS3390_project3.docx`: The project description document outlining the task requirements and specifications.

## Features
- Reads and processes input from CSV files to construct the current state of resource allocation and requests.
- Validates the consistency of the dimensions across input files.
- Detects deadlock scenarios in the system based on the current allocation, request, and availability of resources.
- Outputs either a list of deadlocked processes or a possible sequence of process executions that avoids deadlock.

## How It Works
The program operates by simulating a system's resource allocation state through matrices and vectors:
1. **Load Data**: Parses `Allocation.csv`, `Request.csv`, and `Available.csv` to build internal representations of the system state.
2. **Check Consistency**: Ensures that the data across different files matches in dimensions and is logically coherent.
3. **Deadlock Detection**: Applies deadlock detection algorithms to determine if the system is in a deadlock state.
4. **Output Results**: Depending on the state of the system, it either lists the processes involved in a deadlock or suggests a safe sequence of executions.

## Contribution
This project is an educational tool intended for students to learn and demonstrate understanding in managing system resources and deadlock detection. Contributions should focus on improving the efficiency of the algorithms and enhancing the readability of the output.
