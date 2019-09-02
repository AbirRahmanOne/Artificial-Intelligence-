#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include <map>
#include<stack>


using namespace std ;

const int N = 100020 ;
const int inf = 9999999 ;


typedef pair<int,int> pii ;
vector<pii> graph[N] ;
int cost[N] ;
int path[N]  ;

map<string,int> Hash ;
map<int,string> Hash2 ;

int n ;
void Dijkstra(int source )
{
    //memset(cost,inf ,sizeof(cost)) ;

    priority_queue<pii, vector<pii>, greater<pii> > Q;

    cost[source] = 0 ;
    Q.push({cost[source],source}) ;

    while(!Q.empty() )
    {
        pii top = Q.top() ;
        Q.pop() ;

        int c = top.first ;
        int u = top.second ;

        for(int i = 0 ; i<graph[u].size() ; i++)
        {
            pii next = graph[u][i] ;

            int cx = next.second ;
            int v = next.first ;

            if(cost[v] > cost[u] + cx )
            {
                cost[v] = cost[u]+cx ;
                path[v] = u ;
                Q.push({cost[v],v}) ;

            }
        }
    }

}

void reset() {
    for ( int i = 0; i<= n; i++ ) {
        cost[ i ] = inf;
    }
}

int main(int argc, char *argv[])
{

    freopen(argv[1],"r",stdin) ;

    string from , to ;
    int km ;

    int id  = 0;
    while(true)
    {

        cin >> from;
        if(from == "END") break;

        cin>>to;
        cin>>km ;

        if(Hash[from] == 0)
        {
            Hash[from] = ++id ;
            Hash2[id] = from ;


        }
        if(Hash[to] == 0 )
        {
            Hash[to] = ++id ;
            Hash2[id] = to ;
        }

        graph[ Hash[from]].push_back( {Hash[to],km}) ;
        graph[ Hash[to]].push_back( {Hash[from],km}) ;


    }
    //cin>>from >>to ;

    n = Hash.size() ; // node size


    string src , des ;
    //cin >> src >> des;
    src = argv[2] ;
    des = argv[3];
        //cout << src << " " << des << endl;
    int s = Hash[src] ;
    int d = Hash[des] ;
    //cout<<s <<" " <<d <<endl ;
    reset() ;

    Dijkstra(s) ;
    //cout<<cost[d] <<endl ;
    if(cost[d] == inf )
    {
        cout<<"distance: infinity" <<endl ;
        cout<<"route:" <<endl ;
        cout<<"none" <<endl ;
    }
    else
    {
        cout<<"Distance: " <<cost[d] <<"km" <<endl ;
        cout<<"route:" <<endl ;

        stack<int> S;
        S.push(d);
        while(path[d]!=s)
        {
            if(d==s)
                break;

            d=path[d];
            S.push(d);
        }
        S.push(s);
        int p=S.top();
        S.pop();

        while(!S.empty())
        {
            cout<<Hash2[p]<<" to "<<Hash2[S.top()]<<", "<<cost[S.top()]-cost[p]<<" km"<<endl;
            p=S.top();
            S.pop();
        }
    }

    return 0 ;
}
