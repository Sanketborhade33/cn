#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 10
#define INFINITY INT_MAX

// Structure to hold the distance vector for each node
typedef struct {
    int distance[MAX_NODES];
    int nextHop[MAX_NODES];
} Node;

// Function to initialize the nodes
void initializeNodes(Node nodes[], int numNodes, int cost[MAX_NODES][MAX_NODES]) {
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (cost[i][j] != INFINITY) {
                nodes[i].distance[j] = cost[i][j];
                nodes[i].nextHop[j] = j;
            } else {
                nodes[i].distance[j] = INFINITY;
                nodes[i].nextHop[j] = -1;
            }
        }
        nodes[i].distance[i] = 0; // Distance to self is zero
    }
}

// Function to update distances based on received vectors
void updateDistances(Node nodes[], int numNodes) {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                for (int k = 0; k < numNodes; k++) {
                    if (nodes[i].distance[j] > nodes[i].distance[k] + nodes[k].distance[j]) {
                        nodes[i].distance[j] = nodes[i].distance[k] + nodes[k].distance[j];
                        nodes[i].nextHop[j] = nodes[k].nextHop[j];
                        updated = 1;
                    }
                }
            }
        }
    } while (updated);
}

// Function to print the routing table
void printRoutingTable(Node nodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        printf("Routing table for Node %d:\n", i);
        for (int j = 0; j < numNodes; j++) {
            if (nodes[i].distance[j] < INFINITY) {
                printf("  To Node %d: Distance = %d, Next Hop = %d\n", j, nodes[i].distance[j], nodes[i].nextHop[j]);
            } else {
                printf("  To Node %d: Distance = INFINITY\n", j);
            }
        }
        printf("\n");
    }
}

int main() {
    int numNodes = 4;
    // Cost matrix
    int cost[MAX_NODES][MAX_NODES] = {
        {0, 1, 4, INFINITY},
        {1, 0, 2, 5},
        {4, 2, 0, 1},
        {INFINITY, 5, 1, 0}
    };

    Node nodes[MAX_NODES];
    initializeNodes(nodes, numNodes, cost);
    updateDistances(nodes, numNodes);
    printRoutingTable(nodes, numNodes);

    return 0;
}


