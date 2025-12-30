/*Develop a C program to simulate the following contiguous memory allocation Techniques*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

// Simple display function with fragment and unused blocks
void display(int blockSizes[], int blockCount, int processSizes[], int processCount, int allocation[], int fragment[]) {
    printf("\nProcess No.\tProcess Size\tBlock No.\tFragment\n");
    for (int i = 0; i < processCount; i++) {
        printf(" %d\t\t%d\t\t", i + 1, processSizes[i]);
        if (allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, fragment[i]);
        else
            printf("Not Allocated\t-\n");
    }
    
    // Show unused blocks
    printf("\nUnused Blocks:\n");
    int unused = 0;
    for (int i = 0; i < blockCount; i++) {
        int used = 0;
        for (int j = 0; j < processCount; j++) {
            if (allocation[j] == i) {
                used = 1;
                break;
            }
        }
        if (!used) {
            printf("Block %d: %d\n", i + 1, blockSizes[i]);
            unused++;
        }
    }
    if (unused == 0)
        printf("No unused blocks\n");
}

// First Fit Algorithm
void firstFit(int blockSizes[], int blockCount, int processSizes[], int processCount) {
    int allocation[MAX_PROCESSES];
    int fragment[MAX_PROCESSES];
    int occupied[MAX_BLOCKS] = {0};

    for (int i = 0; i < processCount; i++) {
        allocation[i] = -1;
        for (int j = 0; j < blockCount; j++) {
            if (!occupied[j] && blockSizes[j] >= processSizes[i]) {
                allocation[i] = j;
                fragment[i] = blockSizes[j] - processSizes[i];
                occupied[j] = 1;
                break;
            }
        }
    }
    printf("\n--- First Fit ---");
    display(blockSizes, blockCount, processSizes, processCount, allocation, fragment);
}

// Best Fit Algorithm
void bestFit(int blockSizes[], int blockCount, int processSizes[], int processCount) {
    int allocation[MAX_PROCESSES];
    int fragment[MAX_PROCESSES];
    int occupied[MAX_BLOCKS] = {0};

    for (int i = 0; i < processCount; i++) {
        allocation[i] = -1;
        int bestIdx = -1;
        for (int j = 0; j < blockCount; j++) {
            if (!occupied[j] && blockSizes[j] >= processSizes[i]) {
                if (bestIdx == -1 || blockSizes[j] < blockSizes[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            fragment[i] = blockSizes[bestIdx] - processSizes[i];
            occupied[bestIdx] = 1;
        }
    }
    printf("\n--- Best Fit ---");
    display(blockSizes, blockCount, processSizes, processCount, allocation, fragment);
}

// Worst Fit Algorithm
void worstFit(int blockSizes[], int blockCount, int processSizes[], int processCount) {
    int allocation[MAX_PROCESSES];
    int fragment[MAX_PROCESSES];
    int occupied[MAX_BLOCKS] = {0};

    for (int i = 0; i < processCount; i++) {
        allocation[i] = -1;
        int worstIdx = -1;
        for (int j = 0; j < blockCount; j++) {
            if (!occupied[j] && blockSizes[j] >= processSizes[i]) {
                if (worstIdx == -1 || blockSizes[j] > blockSizes[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            fragment[i] = blockSizes[worstIdx] - processSizes[i];
            occupied[worstIdx] = 1;
        }
    }
    printf("\n--- Worst Fit ---");
    display(blockSizes, blockCount, processSizes, processCount, allocation, fragment);
}

// Main function
int main() {
    int blockSizes[MAX_BLOCKS], processSizes[MAX_PROCESSES];
    int blockCount, processCount;

    // Input memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &blockCount);
    printf("Enter size of each memory block:\n");
    for (int i = 0; i < blockCount; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSizes[i]);
    }

    // Input processes
    printf("\nEnter number of processes: ");
    scanf("%d", &processCount);
    printf("Enter size of each process:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSizes[i]);
    }

    // Execute all three strategies
    firstFit(blockSizes, blockCount, processSizes, processCount);
    bestFit(blockSizes, blockCount, processSizes, processCount);
    worstFit(blockSizes, blockCount, processSizes, processCount);

    return 0;
}


/*
Sample Output:


Enter number of memory blocks: 5
Enter size of each memory block:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 300
Block 5: 600

Enter number of processes: 4
Enter size of each process:
Process 1: 212
Process 2: 417
Process 3: 112
Process 4: 426

--- First Fit ---
Process No.     Process Size   Block No.       Fragment
 1              212            2               288
 2              417            5               183
 3              112            3               88
 4              426            Not Allocated   -

Unused Blocks:
Block 1: 100
Block 4: 300

--- Best Fit ---
Process No.     Process Size   Block No.       Fragment
 1              212            4               88
 2              417            2               83
 3              112            3               88
 4              426            5               174

Unused Blocks:
Block 1: 100

--- Worst Fit ---
Process No.     Process Size   Block No.       Fragment
 1              212            5               388
 2              417            2               83
 3              112            4               188
 4              426            Not Allocated   -

Unused Blocks:
Block 1: 100
Block 3: 200
 */