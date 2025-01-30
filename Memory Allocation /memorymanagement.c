#include<stdio.h>

// First Fit Allocation
void firstfit(int p_size[], int n, int m_size[], int m) {
    printf("\t\tFIRST FIT \n");
    int i, j, flag;
    for(i = 0; i < n; i++) {
        flag = 0;
        for(j = 0; j < m; j++) {
            if(m_size[j] >= p_size[i]) {
                printf("%d ALLOCATED IN %d MEMORY BLOCK", p_size[i], m_size[j]);
                m_size[j] = m_size[j] - p_size[i];
                printf(" => %d SPACE REMAINING \n", m_size[j]);
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            printf("%d CANNOT BE ALLOCATED \n", p_size[i]);
        }
    }
}

// Worst Fit Allocation
void worstfit(int p_size[], int n, int m_size[], int m) {
    printf("\t\tWORST FIT \n");
    int i, j, max, loc;
    for(i = 0; i < n; i++) {
        max = m_size[0];
        loc = 0;
        for(j = 0; j < m; j++) {
            if(m_size[j] > max) {
                max = m_size[j];
                loc = j;
            }
        }
        if(max >= p_size[i]) {
            printf("%d ALLOCATED IN %d MEMORY BLOCK", p_size[i], m_size[loc]);
            m_size[loc] = m_size[loc] - p_size[i];
            printf(" => %d SPACE REMAINING \n", m_size[loc]);
        } else {
            printf("%d CANNOT BE ALLOCATED \n", p_size[i]);
        }
    }
}

// Best Fit Allocation
void bestfit(int p_size[], int n, int m_size[], int m) {
    printf("\t\tBEST FIT \n");
    int i, j, loc;
    for(i = 0; i < n; i++) {
        loc = -1;
        for(j = 0; j < m; j++) {
            if(m_size[j] >= p_size[i]) {
                if(loc == -1) {
                    loc = j;
                } else if(m_size[loc] > m_size[j]) {
                    loc = j;
                }
            }
        }
        if(loc != -1) {
            printf("%d ALLOCATED IN %d MEMORY BLOCK", p_size[i], m_size[loc]);
            m_size[loc] = m_size[loc] - p_size[i];
            printf(" => %d SPACE REMAINING \n", m_size[loc]);
        } else {
            printf("%d CANNOT BE ALLOCATED \n", p_size[i]);
        }
    }
}

// Main function
void main() {
    int i, p_size[100], m_size[100], n, m;
    
    // Input: Number of processes and their sizes
    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);
    printf("ENTER THE ARRAY OF PROCESS SIZES: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &p_size[i]);
    }
    
    // Input: Number of memory blocks and their sizes
    printf("ENTER THE NUMBER OF MEMORY BLOCKS: ");
    scanf("%d", &m);
    printf("ENTER THE ARRAY OF MEMORY BLOCK SIZES: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &m_size[i]);
    }
    
    // Call the allocation functions
    firstfit(p_size, n, m_size, m);
    bestfit(p_size, n, m_size, m);
    worstfit(p_size, n, m_size, m);
}
