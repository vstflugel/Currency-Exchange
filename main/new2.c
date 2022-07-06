#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.c"

// Define the maximum number of vertices in the graph
#define N 6
#define MAX 6
#define INFINITY 100000
#define AVAILABLE 1;
#define NOTAVAILABLE 0;

/////////////////////////////////////////
////////////////////////////////////////
///////////////////////////////////////
//Struct part of the code

int arr_banks[MAX] = {0};

int num = 0;

typedef struct Graph
{
    char name[5]; //name of bank
    // An array of pointers to Node to represent an adjacency list
    struct Node *head[N];
    int refer[N];
} bank;

// Data structure to store adjacency list nodes of the graph
typedef struct Node
{
    char curr[4]; //3 letter name of currency
    int dest, weight;
    struct Node *next;
} currency;

// Data structure to store a graph edge
typedef struct Edge
{
    int src, dest, weight;
} conversion;

struct stTable
{
    int *pKnown;
    float *pdistance_to_source;
    int *pPrevious_vertex;
};

// Function to create an adjacency list from specified edges
bank *createGraph(char name_of_bank[], int array[], int V)
{
    unsigned i;

    // allocate storage for the graph data structure
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

    strcpy(graph->name, name_of_bank);

    // initialize head pointer for all vertices
    for (i = 0; i < N; i++)
    {
        graph->head[i] = NULL;
        graph->refer[i] = NOTAVAILABLE;
    }

    for (i = 0; i < V; i++)
    {
        graph->refer[array[i]] = AVAILABLE;
    }

    num++;
    return graph;
}

int find_min(long long int A[], int n)
{
    long long int min = A[0];
    int index = 0;
    for (int i = 1; i < n; i++)
    {
        if (min > A[i])
        {
            min = A[i];
            index = i;
        }
    }
    return index;
}
/////////////////////////////////////////////////
///////////////////////////////////////////
////////////////////////////////////////

// Function to print adjacency list representation of a graph
void printGraph(struct Graph *graph, char names[][4])
{
    int i;
    printf("%s\n", graph->name);
    for (i = 0; i < N; i++)
    {
        // print current vertex and all its neighbors
        struct Node *ptr = graph->head[i];
        while (ptr != NULL)
        {
            printf("%s —> %s (%d)\t", names[i], names[ptr->dest], ptr->weight);
            ptr = ptr->next;
        }

        printf("\n");
    }
}


bool search(struct Node *head, int x)
{

    struct Node *current = head; // Initialize current

    while (current != NULL)

    {

        if (current->dest == x)

            return true;

        current = current->next;
    }

    return false;
}

void AddConversion(struct Node **head_ref, int dest, int weight)
{
    bool check = search(*head_ref, dest);
    if (check)
    {
        printf("Error: The conversion already exists\n");
    }
    else
    {
        /* 1. allocate node */
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

        /* 2. put in the data  */
        new_node->dest = dest;
        new_node->weight = weight;
        /* 3. Make next of new node as head */
        new_node->next = (*head_ref);

        /* 4. move the head to point to the new node */
        (*head_ref) = new_node;
    }
}
void AddCurrency(int c, bank *G)
{
    G->refer[c] = AVAILABLE;
}

////////////////////////////////////////
//////////////////////////////////////////
//Sir's old deletion codes from linked list

void deleteList(struct Node **head_ref)
{
    /* deref head_ref to get the real head */
    struct Node *current = *head_ref;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
      in the caller. */
    *head_ref = NULL;
}

void deleteNode(struct Node **head_ref, int key)
{
    // Store head node
    struct Node *temp = *head_ref, *prev;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->dest == key)
    {
        *head_ref = temp->next; // Changed head
        free(temp);             // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->dest != key)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL)
        return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp); // Free memory
}

//////////////////////////////////////////
/////////////////////////////////////////
///////////////////////////////////////

//The currency deletion and conversion deletion have been implemented, please do test it out and debug
//The implementation of the additon of currency and conversion should be equally easy

void DeleteBank(bank *G)
{
    for (int i = 0; i < N; i++)
    {
        deleteList(&G->head[i]);
    }
    free(G);
}

void deleteCurrency(bank *B, int key) //deleting an entire currency
{
    for (int i = 0; i < N; i++)
    {
        deleteNode(&B->head[i], key);
    }
    deleteList(&B->head[key]);
}

void deleteConversion(bank *B, int source, int destination) //deleting a conversion/edge
{
    deleteNode(&B->head[source], destination);
}

struct stTable *Djistra(bank *G, int from, int to)
{
    struct stTable *myTable;
    int i, j;
    PQueue Q;
    int u, v, x;
    struct Node *temp;
    double cost;

    myTable = (struct stTable *)malloc(sizeof(struct stTable));
    if (myTable == NULL)
    {
        exit(0);
    }
    myTable->pKnown = (int *)malloc(N * sizeof(int));
    myTable->pdistance_to_source = (float *)malloc(N * sizeof(float));
    myTable->pPrevious_vertex = (int *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++)
    {
        myTable->pKnown[i] = 0;
        myTable->pdistance_to_source[i] = INFINITY;
        myTable->pPrevious_vertex[i] = -1;
    }

    myTable->pdistance_to_source[from] = 0;

    Q = CreateEmptyPriorityQueue(N);
    for (i = 0; i < N; i++)
        newnode(Q, i, myTable->pdistance_to_source[i]);

    while (!IsPQueueEmpty(Q))
    {
        u = ExtractMin(Q);

        myTable->pKnown[u] = 1;
        temp = G->head[u];
        while (temp != NULL)
        {
            v = temp->dest;
            if ((!myTable->pKnown[v]) && (myTable->pdistance_to_source[v] > temp->weight + myTable->pdistance_to_source[u]))
            {
                myTable->pdistance_to_source[v] = (temp->weight) + myTable->pdistance_to_source[u];
                myTable->pPrevious_vertex[v] = u;
                DecreaseKey(Q, v, myTable->pdistance_to_source[v]);
            }
            temp = temp->next;
        }
    }

    // cost=myTable->pdistance_to_source[to];

    return myTable;
}

void printpath(struct stTable *T, int from, int to, char names[][4])
{
    int x = to;
    while (x != from)
    {
        printf("%s<--", names[x]);
        x = T->pPrevious_vertex[x];
    }
    printf("%s\n", names[from]);
}

long long int bestpath(bank *arr[], int from, int to, int delete[], char names[][4])
{
    long long int A[MAX];
    for (int i = 0; i < num; i++)
    {
        if (delete[i] == 1)
            A[i] = (Djistra(arr[i], from, to))->pdistance_to_source[to];
        else
            A[i] = INFINITY;
    }
    int x = find_min(A, num);
    if (num != 0 && A[x] < INFINITY)
    {
        printf("Bank_name:%s Cost:%lld\n", arr[x]->name, A[x]);
        printf("path: ");
        printpath(Djistra(arr[x], from, to), from, to, names);
    }
    else
        printf("NOT POSSIBLE\n");
}
