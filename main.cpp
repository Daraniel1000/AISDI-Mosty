#include<iostream>
#include<vector>
#include<list>
#include"Graph.h"
using namespace std;

int main()
{
    //################WCZYTYWANIE#####################
    unsigned int v1,v2;
    cin>>v1;//>>v2;
    if(v1 < 4) return 0;
    Graph graph(v1);
    while(!cin.eof())
    //for(auto a=v2; a>0; --a)
    {
        cin>>v1>>v2;
        graph.addEdge(v1,v2);
    }
    if(graph[v1].edges.back() == graph[v1].edges[graph[v1].edges.size()-2])
    {
        //cout<<"duplication encountered"<<endl;
        graph[v1].edges.pop_back();
        graph[v2].edges.pop_back();
    }
    if(!graph.isGraphConnected())
    {
        cout<<"Graf nie jest spójny: niezgodność z założeniem"<<endl;
        return 0;
    }
    //graph.print();
    //##########wwwwwwKONIEC WCZYTYWANIA##############
    //##########WYSZUKIWANIE MOSTÓW ROZLEGŁYCH########
    vector<bool> artp = graph.getArtPoints(), artnew, odw(graph.size(), false);
    list<size_t> single;
    Graph temp(0);
    for(size_t a=0; a<graph.size(); ++a)
    {
        odw[a] = true;
        if(artp[a])
        {
            single.clear();
            for(size_t b: graph[a].edges)
            {
                if(graph[b].edges.size() == 1) single.push_back(b);
                else
                {
                    if(odw[b] == true) continue;
                    else cout<<a<<" "<<b<<endl;
                }
            }
            if(single.size() > 1)
            {
                for(size_t b: single)
                {
                    if(odw[b] == true) continue;
                    cout<<a<<" "<<b<<endl;
                }
            }
            else
            {
                if(!odw[single.front()])
                {
                    temp = graph.removeVertex(single.front()).removeVertex(a);
                    v1 = (single.front() == graph[a].edges[0])? graph[a].edges[1]: graph[a].edges[0];
                    if(!temp.isGraphConnected(v1))
                        cout<<a<<" "<<single.front()<<endl;
                }
            }
        }
        else
        {
            temp = graph.removeVertex(a);
            artnew = temp.getArtPoints(graph[a].edges[0]);
            for(size_t b: graph[a].edges)
            {
                if(odw[b] == true) continue;
                if(artnew[b] == true)
                    cout<<a<<" "<<b<<endl;
            }
        }
    }
}
