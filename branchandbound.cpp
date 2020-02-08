#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

//constants in the memory

std::vector<bool> visited; 
int32_t final_res = INT_MAX; 
int32_t min_o = INT_MAX; 
int32_t first_1 = INT_MAX;
int32_t second_2 = INT_MAX;
  
////////////////////////////////////////////////////////////////////////////////////////////////////
int32_t firstMin(std::vector<std::vector <int>> &graph, int i) 
{ 
    for (int k = 0; k < graph.size(); ++k)
    {
        int32_t curr = graph[i][k];
        
        if ((curr < min)&&(curr != 0)) 
        {
            min_o = graph[i][k];
        }
    }
    return min_o; 
} 
int32_t secondMin(std::vector<std::vector <int>> &graph, int i) 
{  
    for (int j = 0; j <  graph.size(); ++j) 
    { 
        if (graph[i][j] < first_1 && graph[i][j] != 0) 
        { 
            first_1 = graph[i][j]; 
            second_2 = first_1; 
        } 
        else if (graph[i][j] <= second_2 && graph[i][j] != 0)
        {
            second_2 = graph[i][j]; 
        }
    } 
    return second_2; 
} 
////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void bb(std::vector<std::vector <int>> &graph, std::vector<int> curr_path, int curr_weight, int deeping, int curr_bound) 
{ 

    if (deeping == graph.size()) 
    { 
        if (graph[curr_path[deeping-1]][curr_path[0]] != 0) 
        { 
            int curr_res = curr_weight + graph[curr_path[deeping-1]][curr_path[0]]; 
            if (curr_res < final_res) 
            { 
                final_res = curr_res; 
            } 
        } 
        return; 
    } 

    for (int i = 0; i < graph.size(); ++i) 
    { 
        if (graph[curr_path[deeping-1]][i] != 0 && visited[i] == false) 
        { 
            int temp = curr_bound; 
            curr_weight += graph[curr_path[deeping-1]][i]; 
            if (deeping == 1) 
              curr_bound -= ((firstMin(graph, curr_path[deeping-1]) + firstMin(graph, i))/2); 
            else
              curr_bound -= ((secondMin(graph, curr_path[deeping-1]) + firstMin(graph, i))/2); 
            if (curr_bound + curr_weight < final_res) 
            { 
                curr_path[deeping] = i; 
                visited[i] = true; 
                bb(graph, curr_path, curr_weight, deeping+1, curr_bound); 
            } 
            curr_weight -= graph[curr_path[deeping-1]][i]; 
            curr_bound = temp;
            visited[i] = false;
        } 
    } 
} 
  
 
void TSP_branch_bound(std::vector<std::vector <int>> &graph) 
{ 
    int curr_bound = 0;
    std::vector<int> curr_path (graph.size(), -1);

    if(graph.size() == 1) 
    {
        final_res = 0;
        return;
    }
    
    if(graph.size() == 2) 
    {
        if(graph[0][1] != 0)
        {
            final_res = graph[0][1]*2;
        }
        return;
    }
    
    for(int i; i < graph.size(); ++i)
    {
        visited.push_back(false);
    }

    visited[0] = true;
    
    for (int i = 0; i < graph.size(); ++i)
    {
        if((firstMin(graph, i) == INT_MAX)||(secondMin(graph, i) == INT_MAX))
        {
            return;
        }
        curr_bound += (firstMin(graph, i) + secondMin(graph, i));  
    }
                       
    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2;  
    bb(graph,curr_path, 0, 1, curr_bound); 
} 


void Creategraph(int vertices, std::vector<std::vector <int>> &graph)
{
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            std::cin >> graph[i][j];
        }
    }
}

int main() 
{ 

    int vertices;

    std::cin >> vertices;
    
    std::vector<std::vector <int>> graph (vertices, std::vector<int> (vertices));
    
    Creategraph(vertices, graph);
  
    TSP_branch_bound(graph);

    if (final_res == INT_MAX)
    {
        std::cout << -1;
    }

    else
    {
        std::cout << final_res;
    }
    
    return 0; 
} 