// #include <iostream>
// #include <queue>
// #include <vector>
// using namespace std;
//
// void beam_search(int** graph, int num_nodes, int start_node, int beam_width) {
//     queue<int> q;
//     vector<int> visited(num_nodes, 0);  
//    
//     visited[start_node] = 1;
//     q.push(start_node);
//     cout << "Beam Search Order with width " << beam_width << ": " << start_node << " ";
//  
//     while (!q.empty()) {
//         int level_size = q.size();  
//         int count = 0;  
//        
//         for (int i = 0; i < level_size; i++) {
//             int node = q.front();
//             q.pop();
//           
//             for (int j = 0; j < num_nodes; j++) {
//                 if (graph[node][j] == 1 && !visited[j]) {
//                     cout << j << " ";
//                     visited[j] = 1;
//                     q.push(j);
//                     count++;
//                   
//                     if (count >= beam_width) break;
//                 }
//             }
//             if (count >= beam_width) break;
//         }
//     }
//     cout << endl;
// }

// int main() {
//     int num_nodes;
//
//     cout << "Enter the number of nodes: ";
//     cin >> num_nodes;
//
//     int** graph = new int*[num_nodes];
//     for (int i = 0; i < num_nodes; i++) {
//         graph[i] = new int[num_nodes];
//     }
//
//     cout << "Enter the adjacency matrix (" << num_nodes << "x" << num_nodes << "):" << endl;
//     for (int i = 0; i < num_nodes; i++) {
//         for (int j = 0; j < num_nodes; j++) {
//             cin >> graph[i][j];
//         }
//     }
//
//     int start_node;
//     cout << "Enter the starting node (0-" << num_nodes - 1 << "): ";
//     cin >> start_node;
//
//     if (start_node < 0 || start_node >= num_nodes) {
//         cout << "Invalid node! Please enter a node between 0 and " << num_nodes - 1 << "." << endl;
//         return -1;
//     }
//
//     for (int beam_width = 1; beam_width <= 3; beam_width++) {
//         beam_search(graph, num_nodes, start_node, beam_width);
//     }
//
//     for (int i = 0; i < num_nodes; i++) {
//         delete[] graph[i];
//     }
//     delete[] graph;
//
//     return 0;
// }

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void beam_search(int** graph, int num_nodes, int start_node, int beam_width) {
    queue<int> q;
    vector<int> visited(num_nodes, 0);  
    
    visited[start_node] = 1;
    q.push(start_node);
    cout << "Beam Search Order with width " << beam_width << ": " << start_node << " ";
    
    while (!q.empty()) {
        int level_size = q.size();  

        queue<int> next_level;

        for (int i = 0; i < level_size; i++) {
            int node = q.front();
            q.pop();
            
            int neighbor_count = 0;
            for (int j = 0; j < num_nodes; j++) {
                if (graph[node][j] == 1 && !visited[j]) {
                    if (neighbor_count < beam_width) {
                        cout << j << " ";
                        visited[j] = 1;
                        next_level.push(j);
                        neighbor_count++;
                    } else {
                        break; 
                    }
                }
            }
        }

        while (!next_level.empty()) {
            q.push(next_level.front());
            next_level.pop();
        }
    }
    cout << endl;
}

int main() {
    const int num_nodes = 12;
    
    int graph_12[12][12] = {
        {0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}
};

    int** graph = new int*[num_nodes];
    for (int i = 0; i < num_nodes; i++) {
        graph[i] = new int[num_nodes];
        for (int j = 0; j < num_nodes; j++) {
            graph[i][j] = graph_12[i][j];
        }
    }

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            cout<< graph[i][j]<<" ";
        }
        cout<<endl;
    }

    int start_node = 0;  

    for (int beam_width = 1; beam_width <= 3; beam_width++) {
        beam_search(graph, num_nodes, start_node, beam_width);
    }

    for (int i = 0; i < num_nodes; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}
