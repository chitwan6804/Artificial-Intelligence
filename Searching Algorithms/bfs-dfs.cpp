#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// Function for BFS
void bfs(int** graph, int num_nodes, int start_node) {
    queue<int> q;
    int* visited = new int[num_nodes]();  

    cout << "BFS Order: " << start_node << " ";
    visited[start_node] = 1;
    q.push(start_node);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int j = 0; j < num_nodes; j++) {
            if (graph[node][j] == 1 && visited[j] == 0) {
                cout << j << " ";
                visited[j] = 1;
                q.push(j);
            }
        }
    }
    cout << endl;
    delete[] visited;
}

// Function for DFS
void dfs(int** graph, int num_nodes, int start_node) {
    stack<int> s;
    int* visited = new int[num_nodes]();  

    cout << "DFS Order: " << start_node << " ";
    visited[start_node] = 1;
    s.push(start_node);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        for (int j = 0; j < num_nodes; j++) {
            if (graph[node][j] == 1 && visited[j] == 0) {
                cout << j << " ";
                visited[j] = 1;
                s.push(node);  
                s.push(j);     
                break;         
            }
        }
    }
    cout << endl;
    delete[] visited;
}

int main() {
    int num_nodes;

    do {
        cout << "Enter the number of nodes (8-10): ";
        cin >> num_nodes;
    } while (num_nodes < 8 || num_nodes > 10);

    int** graph = new int*[num_nodes];
    for (int i = 0; i < num_nodes; i++) {
        graph[i] = new int[num_nodes];
    }

    cout << "Enter the adjacency matrix (" << num_nodes << "x" << num_nodes << "):" << endl;
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            cout<<"Value for ("<<i<<","<<j<<") : ";
            cin >> graph[i][j];
        }
    }

    cout<<"Matrix according to the user input:\n";
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            cout<< graph[i][j]<<" ";
        }
        cout<<endl;
    }

    int start_node;
    cout << "Enter the starting node (0-" << num_nodes - 1 << "): ";
    cin >> start_node;

    if (start_node < 0 || start_node >= num_nodes) {
        cout << "Invalid node! Please enter a node between 0 and " << num_nodes - 1 << "." << endl;
        return -1;
    }

    char option;
    cout << "Enter 'B' for BFS or 'D' for DFS: ";
    cin >> option;

    if (option == 'B' || option == 'b') {
        bfs(graph, num_nodes, start_node);
    } else if (option == 'D' || option == 'd') {
        dfs(graph, num_nodes, start_node);
    } else {
        cout << "Invalid option! Please enter 'B' for BFS or 'D' for DFS." << endl;
    }

    for (int i = 0; i < num_nodes; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}