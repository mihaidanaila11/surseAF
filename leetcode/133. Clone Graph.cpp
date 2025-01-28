#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<int,bool> vis;
        unordered_map<int, Node*> nodes;

        Node* newNode = dfs(node, vis, nodes);

        cout << "adrese: " << node << " " << newNode << "\n"; 
        cout << "adrese: " << node->neighbors[0] << " " << newNode->neighbors[0]; 
        return newNode;
    }

private:
    Node* dfs(Node* node, unordered_map<int, bool>& vis, unordered_map<int, Node*>& nodes){
        

        if(node == nullptr){
            return nullptr;
        }

        vector<Node*> vecini = node->neighbors;

        vis[node->val] = true;

        Node* newNode = new Node(node->val);
        nodes[node->val] = newNode;


        for(auto vecin : vecini){
            if(!vis[vecin->val]){
                // nu exista => creez
                Node* newVecin = dfs(vecin, vis, nodes);
                newNode->neighbors.push_back(newVecin);
                newVecin->neighbors.push_back(newNode);
            }
            else{
                newNode->neighbors.push_back(nodes[vecin->val]);
                vecin->neighbors.push_back(newNode);
            }
            

        }

        return newNode;
    }
};

int main(){

     vector<Node*> nodes(5);  // Alocăm 5 (0..4) pentru ușurința indexării

    for (int i = 1; i <= 4; ++i) {
        nodes[i] = new Node(i);
    }

    // Lista de adiacență
    vector<vector<int>> adjacencyList = {
        {},           // Index 0 - ignorat
        {2, 4},       // Nodul 1
        {1, 3},       // Nodul 2
        {2, 4},       // Nodul 3
        {1, 3}        // Nodul 4
    };

    for (int i = 1; i <= 4; ++i) {
        for (int neighbor : adjacencyList[i]) {
            nodes[i]->neighbors.push_back(nodes[neighbor]);
        }
    }
    
    Solution s;
    s.cloneGraph(nodes[1]);

    return 0;
}