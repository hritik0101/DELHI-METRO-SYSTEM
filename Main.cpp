#include <bits/stdc++.h>
using namespace std;
using ll = long long;


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
            cout<<"ENTER MANSTER KEY :";
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