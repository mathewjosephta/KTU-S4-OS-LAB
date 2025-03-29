#include <stdio.h>

int main() {
    int frames, pages, i, j, k, pageFaults = 0, front = 0;
    
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("Enter the number of page requests: ");
    scanf("%d", &pages);

    int pageString[pages], frame[frames];
    
    printf("Enter the page string: ");
    for (i = 0; i < pages; i++)
        scanf("%d", &pageString[i]);

    // Initialize frames with -1 (indicating empty)
    for (i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nPages\n");
    for (i = 0; i < pages; i++)
        printf("%d  ", pageString[i]);
    
    printf("\nPage Frames\n");

    for (i = 0; i < pages; i++) {
        int found = 0;

        // Check if page is already in frame
        for (j = 0; j < frames; j++) {
            if (frame[j] == pageString[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // Replace the oldest page
            frame[front] = pageString[i];
            front = (front + 1) % frames;
            pageFaults++;
        }

        // Print current frame status
        for (k = 0; k < frames; k++) {
            if (frame[k] != -1)
                printf("%d  ", frame[k]);
            else
                printf("-  "); // Empty frame
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (FIFO) = %d\n", pageFaults);
    return 0;
}
