# JohnsonRule
 
# Two-Stage Production Scheduling Using Johnson's Rule

## Overview
This project implements a simple greedy method to optimally solve the two-stage production (flow) scheduling problem using Johnson's Rule. Johnson's Rule is a classic algorithm for minimizing the time span of jobs across two stages in a production flow. It sorts jobs based on their processing times to determine an optimal sequence for execution.

## Features
- **Dynamic Memory Allocation:** Ensures flexibility to handle various input jobs.
- **Quicksort Algorithm:** Efficiently sorts jobs based on their minimum processing times.
- **Makespan Calculation:** Computes the total completion time of jobs while detecting idle gaps in the process.
- **Input File Support:** Reads input for wash times and dry times from a user-specified file.
- **Error Handling:** Handles file input errors and memory allocation failures gracefully.

## How It Works
1. **Input:** 
   - The program accepts wash times and dry times for `n` jobs via an input file.
2. **Greedy Selection:**
   - Each job is assigned a priority based on the minimum of its wash and dry times.
   - Jobs are sorted in ascending order of priority using a quicksort algorithm.
3. **Optimal Scheduling:**
   - Jobs are divided into two sequences:
     - Jobs with lower wash times are scheduled earlier.
     - Jobs with lower dry times are scheduled later.
   - This ensures the minimal makespan according to Johnson's Rule.
4. **Output:**
   - Displays the start times for washing and drying, identifies idle gaps, and calculates the makespan.

## File Format
The input file must follow this structure:
- The first line contains the number of jobs (`n`).
- The subsequent lines contain two integers per job: wash time and dry time.
