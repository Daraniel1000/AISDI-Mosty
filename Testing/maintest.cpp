#include<iostream>
#include<stdexcept>
#include"../Graph.h"
#define NRTESTS 7
using namespace std;

int main()
{
    int n=0;
    Graph *a = new Graph(2);
    Graph b(0);
    a->addEdge(1,0);
    if(a->isGraphConnected()) ++n;
    //cout<<n<<endl;
    try
    {
        a->addEdge(1,2);
    }
    catch(out_of_range)
    {
        ++n;
    }
    //cout<<n<<endl;
    *a = a->removeVertex(1);
    if(a->isGraphConnected()) ++n;
    //cout<<n<<endl;
    delete a;
    a=new Graph(5);
    a->addEdge(1,0);
    a->addEdge(1,2);
    a->addEdge(2,3);
    a->addEdge(3,0);
    if(!a->isGraphConnected())++n;
    //cout<<n<<endl;
    b = a->removeVertex(4);
    if(b.isGraphConnected())++n;
    //cout<<n<<endl;
    Graph c(b);
    if(b==c && b==a->removeVertex(4)) ++n;
    delete a;
    a = new Graph(3);
    a->addEdge(0,1);
    a->addEdge(2,1);
    if (a->getArtPoints()[1] && !(a->getArtPoints()[0] && a->getArtPoints()[2])) ++n;

    cout<<"Poprawnie wykonało się "<<n<<" testów z "<<NRTESTS<<endl;
}
