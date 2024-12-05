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
        std::unordered_map<int, pair<int,int>> nbrs; 
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
        vtces[vname] = vtx; 
    }
    
    // Method to remove a vertex from the graph
    void removeVertex(int vname) 
    {
        if (vtces.find(vname) == vtces.end()) {
            std::cout << "Vertex " << vname << " does not exist.\n";
            return;
        }

        Vertex& vtx = vtces[vname];

        std::vector<int> keys;
        for (const auto& pair : vtx.nbrs) {
            keys.push_back(pair.first); 
        }

        for (int key : keys) {
            vtces[key].nbrs.erase(vname);
        }

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

        vtces[vname1].nbrs.erase(vname2);
        vtces[vname2].nbrs.erase(vname1);
    }

    int numEdges() const {
        int count = 0;

        for (const auto& pair : vtces) {
            const Vertex& vtx = pair.second;
            count += vtx.nbrs.size();
        }

        return count / 2;
    }

    // Method to check if an edge exists between two vertices
    bool containsEdge(int vname1, int vname2) const {
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end()) {
            return false;
        }

        const Vertex& vtx1 = vtces.at(vname1);
        if (vtx1.nbrs.find(vname2) == vtx1.nbrs.end()) {
            return false;
        }

        return true;
    }

    // Method to check if there's a path from vname1 to vname2
    bool hasPath(int vname1, int vname2, std::unordered_map<int, bool>& processed) {
        if (containsEdge(vname1, vname2)) {
            return true;
        }

        processed[vname1] = true;

        const Vertex& vtx = vtces[vname1];
        for (const auto& nbr : vtx.nbrs) {
            int nbrVertex = nbr.first;

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
        std::unordered_map<int, int> dist;
        std::unordered_map<int, int> parent;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq; 

        for (auto& vertex : vtces) {
            dist[vertex.first] = INT_MAX;
            parent[vertex.first] = -1;
        }

        dist[source] = 0;
        pq.push({0, source});

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
        std::unordered_map<int, int> time;  
        std::unordered_map<int, int> parent; 
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        for (auto& vertex : vtces) {
            time[vertex.first] = INT_MAX;
            parent[vertex.first] = -1;
        }

        time[source] = 0;
        pq.push({0, source});

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

    void bfsMinStations(int source, int destination) 
    {
        std::unordered_map<int, int> distance;  
        std::unordered_map<int, int> intermediateStations;  
        std::unordered_map<int, int> parent; 
        std::queue<int> q; 

        for (auto& vertex : vtces) {
            distance[vertex.first] = -1; 
            intermediateStations[vertex.first] = -1; 
            parent[vertex.first] = -1; 
        }

        distance[source] = 0;
        intermediateStations[source] = 0;  
        q.push(source);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == destination) {
                break;
            }

            for (auto& nbr : vtces[u].nbrs) {
                int v = nbr.first;

                if (distance[v] == -1) {
                    distance[v] = distance[u] + 1; 
                    intermediateStations[v] = intermediateStations[u] + 1; 
                    parent[v] = u; 
                    q.push(v);
                }
            }
        }

        if (distance[destination] == -1) {
            std::cout << "No path found from " << mp[source] << " to " << mp[destination] << ".\n";
        } else {
            std::cout<<"\n";
            std::cout << "Minimum number of intermediate stations between " << mp[source] << " and " << mp[destination] << " is: " 
                      << intermediateStations[destination] << "\n";

            std::cout << "Path: ";
            std::stack<int> path;  
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
            addVertex(i);  
        }

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
             
            str += "\t\t\t";  

            str += std::to_string(weight);

            str += "       \t";

            str += std::to_string(time);
            
            str += "       \n";  
        }

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
        cin>>input;
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
