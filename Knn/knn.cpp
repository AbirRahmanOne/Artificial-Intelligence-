#include<bits/stdc++.h>

using namespace std ;

#define FOR(i,x,y) for(int i=x ; i<(y) ; i++)
const int N = 200010 ;
const int inf = 1e9 ;

/** Variable and data structure **/
int n,m, k ;
double val ;
string str ;

vector<double> table[N] ;
vector<double> dev , mean ;

struct node
{
    int id,cls ;
    double dis ;

    node(double dis_this , int id_this , int cls_this )
    {
        dis = dis_this ;
        id = id_this ;
        cls = cls_this ;
    }

    bool operator < (const node oth ) const
    {
        return dis <oth.dis + 1e-6 ;
    }
};


double Euclidean_distance(double x1, double y1 , double x2, double y2)
{
    double res = ( (x2-x1) * (x2 - x1)) - ( (y2-y1) * (y2-y1) ) ;

    return  sqrt(res) ;
}

double std_fun(double v ,double mean , double deviation )
{
    return (v -mean) / deviation ;
}



int main(int argc, char *argv[] )
{
    ifstream input1 (argv[1] , ios:: in ) ;
    stringstream key(argv[4]) ;
    key>>k ;

    /** Read input for file **/
    while(!input1.eof())
    {
        getline(input1,str) ;
        if(!str.size())
        {
            break ;
        }

        stringstream ss(str) ;
        int inital = 0 ;
        while(ss>>val)
        {
            table[n].push_back(val) ;

            if(n == 0 )
            {
                mean.push_back(val) ;
                m++ ;
            }
            else
            {
                mean[inital] += val ;
                inital++ ;
            }
        }

        n++ ;
    }

    input1.end ;

    /** average **/
    FOR(i,0,m-1)
    {
        mean[i]/= n ;
    }

    /** std **/
    FOR(i,0,m-1)
    {
        double sum = 0;
        FOR(j,0,n)
        {
            sum += ((double)table[j][i]- mean[i]) * ((double)table[j][i]- mean[i])  ;
        }

        double res = sum/n ;
        res = sqrt(res) ;
        dev.push_back(res) ;

    }

    /** Normalizing The Data **/

    FOR(i,0,n)
    {
        FOR(j,0,m-1)
        {
            table[i][j] = std_fun(table[i][j],mean[j] , dev[j] ) ;
        }
    }

    double total_Accuracy = 0.0 ;

    ifstream input2 (argv[2] , ios:: in ) ;
    int t_t=0 ;


    while(!input2.eof())
    {
        getline(input2,str) ;
        if(!str.size())
        {
            break ;
        }
        stringstream ss(str) ;
        vector<double> testData ;

        int inital =0 ;

        while(ss >> val)
        {
            if(inital == m-1)
            {
                testData.push_back(val) ;
            }
            else
            {
                // normalizing
                testData.push_back( (val - mean[inital]) / dev[inital] ) ;
            }
            inital++ ;
        }



    vector<node> myData ;

    FOR(i,0,n)
    {
        double dist = 0 ;

        FOR(j,0,m)
        {
            if(j==m-1)
            {
                //class
                myData.push_back(node(sqrt(dist),i,(int)table[i][j])) ;
            }
            else
            {
                dist+= ( (testData[j] - table[i][j]) * (testData[j] - table[i][j])) ;
            }
        }
    }

    sort(myData.begin() , myData.end()) ;
    map<int,int> Map ;
    map<int,int> :: iterator it ;

    int mx =0 , total =0 , pre_class =0 , Ture_class = (int)testData[m-1] ;
    double accuracy = 0;

    FOR(i,0,k)
    {
        Map[myData[i].cls] ++ ;
        mx = max(mx,Map[myData[i].cls] ) ;
    }

    for( it=Map.begin(); it!= Map.end() ; ++it)
    {
        int a = it->first ;
        int b = it->second ;

        if(b == mx)
        {
            total++ ;
            if(!pre_class)
            {
                pre_class = a ;
            }
        }
    }


    if(total>1)
    {
        if(pre_class == Ture_class )
        {
            accuracy = 1.000/total ;
        }
    }
    else
    {
        if(pre_class == Ture_class)
        {
            accuracy = 1.0000 ;
        }
    }


    printf("ID=%5d, predicted=%3d, true=%3d, nn=%5d, distance=%7.2lf, accuracy=%4.2lf\n", t_t , pre_class, Ture_class, myData[0].id , myData[0].dis, accuracy) ;
    t_t++ ;
    total_Accuracy += accuracy;

    }

    printf("classification accuracy=%6.4lf\n", total_Accuracy / t_t );
    input2.end ;


    return 0 ;
}
