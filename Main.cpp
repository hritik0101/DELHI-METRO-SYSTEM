#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Map for station names with corresponding numeric IDs
unordered_map<int, string> mp;
unordered_map<string, int> ms;

       
class Graph_M {
public:
    class Vertex {
    public:
        std::unordered_map<int, pair<int,int>> nbrs; // Neighbors and their edge weights
    };

    // Static map to store vertices, with integer keys
    static std::unordered_map<int, Vertex> vtces;

    // Method to check if a vertex exists
    bool containsVertex(int vname) const 
    {
        return vtces.find(vname) != vtces.end();
    }

    // Method to add a vertex to the graph
    void addVertex(int vname) 
    {
        Vertex vtx;
        vtces[vname] = vtx; // Add the vertex to the static map
    }
    
    // Method to remove a vertex from the graph
    void removeVertex(int vname) 
    {
        // Check if the vertex exists
        if (vtces.find(vname) == vtces.end()) {
            std::cout << "Vertex " << vname << " does not exist.\n";
            return;
        }

        // Get the vertex to be removed
        Vertex& vtx = vtces[vname];

        // Get all its neighbors
        std::vector<int> keys;
        for (const auto& pair : vtx.nbrs) {
            keys.push_back(pair.first); // Collect neighbor keys
        }

        // Remove the vertex from each neighbor's adjacency list
        for (int key : keys) {
            vtces[key].nbrs.erase(vname);
        }

        // Remove the vertex from the graph
        vtces.erase(vname);
    }

    // Method to add an edge (for testing)
    void addEdge(int vname1, int vname2, int value, int time) 
    {
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end()) 
        {
            cout<<"ENTER VALID STATION NUMBERS!!";
            return;
        }
        else if(vtces[vname1].nbrs.find(vname2) != vtces[vname1].nbrs.end())
        {
            cout<<"A PATH ALREADY EXISTS!!";
            return;
        }
        vtces[vname1].nbrs[vname2].first = value;
        vtces[vname2].nbrs[vname1].first = value;
        vtces[vname1].nbrs[vname2].second = time;
        vtces[vname2].nbrs[vname1].second = time;
    }

    // Method to remove an edge between two vertices
    void removeEdge(int vname1, int vname2) {
        // Check if the vertices exist and the edge is present
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end())
        {
            cout<<"ENTER VALID STATION NUMBERS!!";
            return;
        }
        else if(vtces[vname1].nbrs.find(vname2) == vtces[vname1].nbrs.end())
        {
            cout<<"A PATH DOES NOT EXISTS!!";
            return;
        }

        // Remove the edge in both directions (undirected graph)
        vtces[vname1].nbrs.erase(vname2);
        vtces[vname2].nbrs.erase(vname1);
    }

    // Method to calculate the number of edges in the graph
    int numEdges() const {
        int count = 0;

        // Iterate over all vertices
        for (const auto& pair : vtces) {
            const Vertex& vtx = pair.second;
            count += vtx.nbrs.size(); // Add the number of neighbors
        }

        // Divide by 2 because the graph is undirected
        return count / 2;
    }

    // Method to check if an edge exists between two vertices
    bool containsEdge(int vname1, int vname2) const {
        // Check if both vertices exist
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end()) {
            return false;
        }

        // Check if vname1 has vname2 as a neighbor
        const Vertex& vtx1 = vtces.at(vname1); // Use at for const safety
        if (vtx1.nbrs.find(vname2) == vtx1.nbrs.end()) {
            return false;
        }

        return true;
    }

    // Method to check if there's a path from vname1 to vname2
    bool hasPath(int vname1, int vname2, std::unordered_map<int, bool>& processed) {
        // Check if there's a direct edge between vname1 and vname2
        if (containsEdge(vname1, vname2)) {
            return true;
        }

        // Mark the vertex as processed
        processed[vname1] = true;

        // Get the neighbors of vname1
        const Vertex& vtx = vtces[vname1];
        for (const auto& nbr : vtx.nbrs) {
            int nbrVertex = nbr.first;

            // If the neighbor is not processed, recursively check if there's a path
            if (processed.find(nbrVertex) == processed.end()) {
                if (hasPath(nbrVertex, vname2, processed)) {
                    return true;
                }
            }
        }

        return false;
    }


    // Dijkstra's Algorithm to find the shortest path from source to destination
    void dijkstra(int source, int destination) {
        // Initialize the distance map and priority queue
        std::unordered_map<int, int> dist;  // Distance from source
        std::unordered_map<int, int> parent; // To keep track of the path
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq; // Min-heap

        // Initialize all distances to infinity and the parent to -1
        for (auto& vertex : vtces) {
            dist[vertex.first] = INT_MAX;
            parent[vertex.first] = -1;
        }

        // Set the distance of the source to 0 and push it into the priority queue
        dist[source] = 0;
        pq.push({0, source});

        // Process vertices using the priority queue
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == destination) break;

            for (const auto& nbr : vtces[u].nbrs) {
                int v = nbr.first;
                int weight = nbr.second.first;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Backtrack to find the shortest path
        if (dist[destination] == INT_MAX) {
            std::cout << "No path found.\n";
        } else {
            std::vector<int> path;
            for (int v = destination; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());

            for (int i = 0; i < path.size(); i++) {
                std::cout << mp[path[i]];
                if (i != path.size() - 1) std::cout << " -> ";
            }
            std::cout << "\nTotal distance: " << dist[destination] << " kms\n";
        }
    }
    void dijkstra2(int source, int destination) {
        // Initialize the time map and priority queue
        std::unordered_map<int, int> time;  // time from source
        std::unordered_map<int, int> parent; // To keep track of the path
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq; // Min-heap

        // Initialize all time to infinity and the parent to -1
        for (auto& vertex : vtces) {
            time[vertex.first] = INT_MAX;
            parent[vertex.first] = -1;
        }

        // Set the time of the source to 0 and push it into the priority queue
        time[source] = 0;
        pq.push({0, source});

        // Process vertices using the priority queue
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (u == destination) break;

            for (const auto& nbr : vtces[u].nbrs) {
                int v = nbr.first;
                int weight = nbr.second.second;

                if (time[u] + weight < time[v]) {
                    time[v] = time[u] + weight;
                    parent[v] = u;
                    pq.push({time[v], v});
                }
            }
        }

        // Backtrack to find the shortest path
        if (time[destination] == INT_MAX) {
            std::cout << "No path found.\n";
        } else {
            std::vector<int> path;
            for (int v = destination; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());

            for (int i = 0; i < path.size(); i++) {
                std::cout << mp[path[i]];
                if (i != path.size() - 1) std::cout << " -> ";
            }
            std::cout << "\nTotal Time: " << time[destination] << " minutes\n";
        }
    }

    // BFS to find the minimum number of intermediate stations (edges) from source to destination
    void bfsMinStations(int source, int destination) 
    {
        std::unordered_map<int, int> distance;  // Stores the minimum number of edges
        std::unordered_map<int, int> intermediateStations;  // Stores number of intermediate stations
        std::unordered_map<int, int> parent;  // To reconstruct the path
        std::queue<int> q;  // Queue for BFS

        // Initialize all vertices as unvisited
        for (auto& vertex : vtces) {
            distance[vertex.first] = -1;  // -1 means unvisited
            intermediateStations[vertex.first] = -1;  // -1 means uninitialized
            parent[vertex.first] = -1;  // No parent initially
        }

        // Start BFS from the source vertex
        distance[source] = 0;
        intermediateStations[source] = 0;  // No intermediate stations for the source itself
        q.push(source);

        // BFS loop
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // If we reach the destination, stop BFS
            if (u == destination) {
                break;
            }

            // Traverse neighbors of the current vertex
            for (auto& nbr : vtces[u].nbrs) {
                int v = nbr.first;

                // If the neighbor is unvisited
                if (distance[v] == -1) {
                    distance[v] = distance[u] + 1;  // Increment the distance
                    intermediateStations[v] = intermediateStations[u] + 1;  // Update intermediate station count
                    parent[v] = u;  // Set parent for path reconstruction
                    q.push(v);
                }
            }
        }

        // Output the result
        if (distance[destination] == -1) {
            std::cout << "No path found from " << mp[source] << " to " << mp[destination] << ".\n";
        } else {
            std::cout<<"\n";
            std::cout << "Minimum number of intermediate stations between " << mp[source] << " and " << mp[destination] << " is: " 
                      << intermediateStations[destination] << "\n";

            // Reconstruct and display the path
            std::cout << "Path: ";
            std::stack<int> path;  // Stack to reverse the path as we are backtracking
            int current = destination;
            while (current != -1) {
                path.push(current);
                current = parent[current];
            }

            // Print the path
            while (!path.empty()) 
            {
                std::cout << mp[path.top()];
                if(path.size()!=1)
                std::cout << "--> ";
                path.pop();
            }
            std::cout << std::endl;
        }
    }


    // Function to create the metro map
    void Create_Metro_Map() {
        

        // Adding vertices to the graph (first 10 stations)
        for (int i = 0; i < 10; ++i) {
            addVertex(i);  // Add vertex using numeric ID
        }

        // Adding edges (connections between stations) with weights
        addEdge(0, 1, 8, 12);    // Noida Sector 62~B <-> Botanical Garden~B (distance: 8 km, time: 12 min)
        addEdge(1, 2, 10, 15);   // Botanical Garden~B <-> Yamuna Bank~B (distance: 10 km, time: 15 min)
        addEdge(2, 4, 8, 10);    // Yamuna Bank~B <-> Vaishali~B (distance: 8 km, time: 10 min)
        addEdge(2, 3, 6, 8);     // Yamuna Bank~B <-> Rajiv Chowk~BY (distance: 6 km, time: 8 min)
        addEdge(3, 5, 9, 14);    // Rajiv Chowk~BY <-> Moti Nagar~B (distance: 9 km, time: 14 min)
        addEdge(5, 6, 7, 11);    // Moti Nagar~B <-> Janak Puri West~BO (distance: 7 km, time: 11 min)
        addEdge(6, 7, 6, 9);     // Janak Puri West~BO <-> Dwarka Sector 21~B (distance: 6 km, time: 9 min)
        addEdge(8, 9, 15, 20);   // Huda City Center~Y <-> Saket~Y (distance: 15 km, time: 20 min)
        addEdge(0, 5, 20, 30);   // Noida Sector 62~B <-> Moti Nagar~B (distance: 20 km, time: 30 min)
        addEdge(1, 4, 12, 18);   // Botanical Garden~B <-> Vaishali~B (distance: 12 km, time: 18 min)
        addEdge(3, 8, 18, 25);   // Rajiv Chowk~BY <-> Huda City Center~Y (distance: 18 km, time: 25 min)
        addEdge(2, 7, 14, 22);   // Yamuna Bank~B <-> Dwarka Sector 21~B (distance: 14 km, time: 22 min)
        addEdge(7, 8, 9, 12);    // Dwarka Sector 21~B <-> Huda City Center~Y (distance: 9 km, time: 12 min)
        addEdge(6, 8, 25, 35);   // Janak Puri West~BO <-> Huda City Center~Y (distance: 25 km, time: 35 min)

    }


    // Method to display all stations (vertices) with numbers
    void display_Stations() const {
        std::cout << "\n*\n";

        int i = 1;
        vector<pair<ll,string>> vec;
        for (const auto& pair : vtces) 
        {
            vec.push_back({pair.first+1,mp[pair.first]});
            // std::cout << pair.first << ". " << mp[pair.first] << "\n";  // Display the station number and name (vertex id)
            // i++;
        }
        sort(vec.begin(),vec.end());
        for(auto k:vec)
        {
            std::cout << k.first << ". " << k.second << "\n";
        }

        std::cout << "\n*\n";
    }



    // Method to display the graph (Delhi Metro Map)
void display_Map() const 
{
    std::cout << "\t                Delhi Metro Map\n";
    std::cout << "\t              ------------------\n";
    std::cout << "       ----------------------------------------------------\n";
    std::cout << "FROM---------------------TO-------------------------------------FARE-------TIME\n";
    
    // Loop through each vertex
    for (const auto& pair : vtces) {
        const int& key = pair.first;
        const Vertex& vtx = pair.second;

        std::string str = mp[key] + " =>\n";  // Start the string with the vertex name

        // Loop through all neighbors
        for (const auto& nbr : vtx.nbrs) {
            std::string nbr_str = mp[nbr.first];  // Neighbor name (vertex id)
            int weight = nbr.second.first;  // Edge weight (fare)
            int time  = nbr.second.second;  // Travel time

            // Format the output with necessary spacing
            str += "            \t         " + nbr_str;
            
            // Adjust spacing after the neighbor's name (assuming names are ~15 characters long)
            str += "\t\t\t";  // Adding a tab if name is shorter than 15 chars

            // Ensure fare (weight) is properly aligned
            str += std::to_string(weight);

            // Add space between fare and time
            str += "       \t";

            // Add the time information, also aligned for clarity
            str += std::to_string(time);
            
            // New line for the next entry
            str += "       \n";  
        }

        // Print the final formatted string for each vertex
        std::cout << str;
    }

    std::cout << "           ------------------------------------\n";
    std::cout << "---------------------------------------------------------------------\n";
}

};




// Define the static member
std::unordered_map<int, Graph_M::Vertex> Graph_M::vtces;



int main() 
{
     // Adding first 10 stations and assigning numeric IDs
    mp[0] = "Noida Sector 62~B ";
    mp[1] = "Botanical Garden~B";
    mp[2] = "Yamuna Bank~B     ";
    mp[3] = "Rajiv Chowk~BY    ";
    mp[4] = "Vaishali~B        ";
    mp[5] = "Moti Nagar~B      ";
    mp[6] = "Janak Puri West~BO";
    mp[7] = "Dwarka Sector 21~B";
    mp[8] = "Huda City Center~Y";
    mp[9] = "Saket~Y           ";


    Graph_M g;
    g.Create_Metro_Map();
    
    cout << "\n\t\t\t*WELCOME TO THE METRO APP\n";
    
    while(true) {
        cout << "\t\t\t\t~LIST OF ACTIONS~\n\n";
        cout << "1. LIST ALL THE STATIONS IN THE MAP\n";
        cout << "2. SHOW THE METRO MAP\n";
        cout << "3. GET SHORTEST DISTANCE PATH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "4. GET MINIMUM CHANGE PATH TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "5. GET SHORTEST PATH (TIME WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
        cout << "6. ADMINISTRATOR ACCESS\n";
        cout << "7. EXIT THE MENU\n";
        cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7) : ";
        
        string input;
        // getline(cin, input);  // Get the whole line including spaces
        cin>>input;
        // Check if the input is exactly 1 character long and that character is a digit
        if (!(input.length() == 1 && isdigit(input[0]))) 
        {
            cout<<"\n";
            cout << "                          !!PLEASE ENTER VALID INPUT!! \n\n";
        }
        int choice = input[0] - '0';
        cout << "\n*\n";
        if(choice==7)
        {
            exit(0);
            break;
        }
        else if(choice == 1)
        {
            g.display_Stations();
        }
        else if(choice == 2)
        {
            g.display_Map();
        }
        else if(choice == 3)
        {
            g.display_Stations();
            cout<<"ENTER SOURCE STATION NUMBER-->";
            ll x;
            cin>>x;
            cout<<"ENTER DESTINATION STATION NUMBER-->";
            ll y;
            cin>>y;
            g.dijkstra(x-1,y-1);
        }
        else if(choice == 4)
        {
            g.display_Stations();
            cout<<"ENTER SOURCE STATION NUMBER-->";
            ll x;
            cin>>x;
            cout<<"ENTER DESTINATION STATION NUMBER-->";
            ll y;
            cin>>y;
            g.bfsMinStations(x-1,y-1);
        }
        else if(choice == 5)
        {
            g.display_Stations();
            cout<<"ENTER SOURCE STATION NUMBER-->";
            ll x;
            cin>>x;
            cout<<"ENTER DESTINATION STATION NUMBER-->";
            ll y;
            cin>>y;
            g.dijkstra2(x-1,y-1);
        }
        else if(choice == 6)
        {
            cout<<"ENTER MANSTER KEY (12345):";
            string s;
            // getline(cin, s);
            cin>>s;
            if(s=="12345")
            {
                cout<<"\n";
                cout << "                          !!WELCONE ADMINISTRATOR!! \n\n";
                while(true)
                {
                    cout << "\t\t\t\t~LIST OF ACTIONS~\n\n";
                    cout << "1. ADD ANOTHER STATION\n";
                    cout << "2. REMOVE ANY STATION\n";
                    cout << "3. ADD ANOTHER PATH\n";
                    cout << "4. REMOVE A PATH\n";
                    cout << "5. EXIT";
                    cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 5) : ";
                    string str;
                    cin>>str;
                    ll num = str[0] - '0';
                    if(num==1)
                    {
                        cout << "ENTER STATION NAME :";
                        string s1;
                        cin>>s1;
                        g.addVertex(mp.size());
                        while(s1.size()<18)
                        {
                            s1+=" ";
                        }
                        mp[mp.size()] = s1;
                    }
                    else if(num==2)
                    {
                        g.display_Stations();
                        cout<<"ENTER YOUR CHOICE(NUMBER) FROM THE ABOVE LIST : ";
                        int x;
                        cin>>x;
                        g.removeVertex(x-1);
                        cout<<"\nSTATION "<<mp[x-1]<<" WAS REMOVED.";
                    }
                    else if(num==3)
                    {
                        g.display_Stations();
                        cout<<"ENTER FIRST STATION NUMBER-->";
                        ll x;
                        cin>>x;
                        cout<<"ENTER SECOND STATION NUMBER-->";
                        ll y;
                        cin>>y;
                        cout<<"ENTER DISTANCE BETWEEN THEM-->";
                        ll z;
                        cin>>z;
                        cout<<"ENTER TIME-->";
                        ll w;
                        cin>>w;
                        g.addEdge(x-1,y-1,z,w);

                    }
                    else if(num==4)
                    {
                        g.display_Stations();
                        cout<<"ENTER FIRST STATION NUMBER-->";
                        ll x;
                        cin>>x;
                        cout<<"ENTER SECOND STATION NUMBER-->";
                        ll y;
                        cin>>y;
                        g.removeEdge(x-1,y-1);
                    }
                    else break;
                }
            }
            else 
            {
                cout<<"\n";
                cout << "                           !!INCORRECT MASTER KEY!! \n\n";
            }
        }
    }
    return 0;
}
