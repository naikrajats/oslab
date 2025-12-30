/* 
Develop a C program to simulate page replacement algorithms:  
a) FIFO   b) LRU 
*/

#include <stdio.h>

#define MAX_FRAMES 5
#define MAX_PAGES 20

// Function to display current frames
void displayFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }
    printf("\n");
}

// FIFO Page Replacement Algorithm
void fifo(int pages[], int n, int frames[], int f) {
    printf("\n=== FIFO Page Replacement ===\n");
    
    int pageFaults = 0;
    int front = 0; // Points to the oldest page
    
    // Initialize frames as empty
    for (int i = 0; i < f; i++)
        frames[i] = -1;
    
    for (int i = 0; i < n; i++) {
        printf("\nPage %d: ", pages[i]);
        
        // Check if page already in frames
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            // Page fault - replace using FIFO
            frames[front] = pages[i];
            front = (front + 1) % f;
            pageFaults++;
            printf("Page Fault -> ");
        } else {
            printf("Page Hit   -> ");
        }
        displayFrames(frames, f);
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

// LRU Page Replacement Algorithm
void lru(int pages[], int n, int frames[], int f) {
    printf("\n=== LRU Page Replacement ===\n");
    
    int pageFaults = 0;
    int time[MAX_FRAMES] = {0}; // Track when each page was last used
    int timeCounter = 0;
    
    // Initialize frames as empty
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = -1;
    }
    
    for (int i = 0; i < n; i++) {
        printf("\nPage %d: ", pages[i]);
        
        // Check if page already in frames
        int found = 0;
        int foundIndex = -1;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                foundIndex = j;
                break;
            }
        }
        
        if (found) {
            // Update time for this page (most recently used)
            time[foundIndex] = ++timeCounter;
            printf("Page Hit   -> ");
        } else {
            // Page fault - find LRU page
            int lruIndex = 0;
            int minTime = time[0];
            
            for (int j = 1; j < f; j++) {
                if (time[j] < minTime) {
                    minTime = time[j];
                    lruIndex = j;
                }
            }
            
            // Replace LRU page
            frames[lruIndex] = pages[i];
            time[lruIndex] = ++timeCounter;
            pageFaults++;
            printf("Page Fault -> ");
        }
        displayFrames(frames, f);
    }
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int n, f;
    
    // Input page reference string
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);
    
    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d: ", i + 1);
        scanf("%d", &pages[i]);
    }
    
    // Input number of frames
    printf("\nEnter number of frames (max %d): ", MAX_FRAMES);
    scanf("%d", &f);
    
    // Validate number of frames
    if (f > MAX_FRAMES) {
        printf("Error: Maximum frames allowed is %d\n", MAX_FRAMES);
        return 1;
    }
    
    // Run both algorithms
    fifo(pages, n, frames, f);
    lru(pages, n, frames, f);
    
    return 0;
}


/*
Sample Output
Enter number of pages in reference string: 12
Enter page reference string:
Page 1: 1
Page 2: 2
Page 3: 3
Page 4: 4
Page 5: 1
Page 6: 2
Page 7: 5
Page 8: 1
Page 9: 2
Page 10: 3
Page 11: 4
Page 12: 5

Enter number of frames (max 5): 3

=== FIFO Page Replacement ===

Page 1: Page Fault ->  1  -  - 
Page 2: Page Fault ->  1  2  - 
Page 3: Page Fault ->  1  2  3 
Page 4: Page Fault ->  4  2  3 
Page 1: Page Fault ->  4  1  3 
Page 2: Page Fault ->  4  1  2 
Page 5: Page Fault ->  5  1  2 
Page 1: Page Hit   ->  5  1  2 
Page 2: Page Hit   ->  5  1  2 
Page 3: Page Fault ->  5  3  2 
Page 4: Page Fault ->  5  3  4 
Page 5: Page Hit   ->  5  3  4 

Total Page Faults: 9

=== LRU Page Replacement ===

Page 1: Page Fault ->  1  -  - 
Page 2: Page Fault ->  1  2  - 
Page 3: Page Fault ->  1  2  3 
Page 4: Page Fault ->  1  2  4 
Page 1: Page Hit   ->  1  2  4 
Page 2: Page Hit   ->  1  2  4 
Page 5: Page Fault ->  1  2  5 
Page 1: Page Hit   ->  1  2  5 
Page 2: Page Hit   ->  1  2  5 
Page 3: Page Fault ->  3  2  5 
Page 4: Page Fault ->  3  4  5 
Page 5: Page Hit   ->  3  4  5 

Total Page Faults: 7


*/