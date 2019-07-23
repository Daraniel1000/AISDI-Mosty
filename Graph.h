//Autor: Maciej Kapuściński
#ifndef AISDI_GRAPH_H
#define AISDI_GRAPH_H
#include<vector>
#include<stdexcept>
#include<iostream>
using namespace std;

class Graph
{
private:
    class vertex
    {
    public:
        int vnum;
        vector<size_t> edges;
        vertex& operator=(const vertex& other)
        {
            edges = other.edges;
            vnum = other.vnum;
            return *this;
        }
        void add(const size_t v)
        {
            edges.push_back(v);
        }
        void erase(const size_t i)
        {
            edges.erase(edges.begin() + i);
        }
    };
    vector<vertex> vertexList;
    vector<bool> visited;
    Graph();
    void dfs(const size_t v)
    {
        if(visited[v]) return;
        visited[v] = true;
        for(size_t a: vertexList[v].edges)
            dfs(a);
    }

    int DFSap(size_t v, size_t vf, size_t *D, size_t &dv, vector<bool> &isArt)
    {
        size_t Low,temp;
        bool test;
        D[v] = Low = dv++;
        test = false;
        for(size_t p: vertexList[v].edges)
        {
            if(p != vf)               // nie może być ojcem v
            {
                if(!D[p])               // nie był odwiedzony
                {
                    temp = DFSap(p, v, D, dv, isArt);    // rekurencyjnie odwiedzamy go
                    if(temp < Low) Low = temp;
                    if(temp >= D[v]) test = true; // Test na punkt artykulacji
                }
                else if(D[p] < Low) Low = D[p];
            }
        }
        if(test)
            isArt[v] = true;
        return Low;                // Wynik
    }

public:
    Graph(const size_t n)
    {
        vertexList.resize(n, vertex{});
        for(size_t a=0; a<n; ++a)
            vertexList[a].vnum = a;
        /*for(int a=0; a<n; ++a)
        {
            vertexList.push_back(new vertex());
        }
        vertexList.shrink_to_fit();*/
    }

    Graph(const Graph &other): Graph(other.vertexList.size())
    {
        for(size_t a=0; a<vertexList.size(); ++a)
            vertexList[a] = other.vertexList[a];
    }

    Graph& operator=(const Graph& other)
    {
        vertexList.resize(other.vertexList.size(), vertex{});
        for(size_t a=0; a<vertexList.size(); ++a)
            vertexList[a] = other.vertexList[a];
        return *this;
    }

    bool operator==(const Graph& other) const
    {
        if(vertexList.size() != other.vertexList.size()) return false;
        for(size_t a=0; a<vertexList.size(); ++a)
        {
            if(vertexList[a].edges != other.vertexList[a].edges) return false;
        }
        return true;
    }

    vertex& operator[](const size_t n)
    {
      return vertexList[n];
    }

    void print() const
    {
        for(size_t a=0; a<vertexList.size(); ++a)
        {
            cout<<a<<": ";
            for(auto i: vertexList[a].edges)
                cout<<i<<" ";
            cout<<endl;
        }
    }

    size_t size() const
    {
        return vertexList.size();
    }

    void addEdge(const size_t v1, const size_t v2)
    {
        if(max(v1,v2) >= vertexList.size()) throw out_of_range("Trying to add edge to nonexistent vertex");
        vertexList[v1].add(v2);
        vertexList[v2].add(v1);
    }

    Graph removeVertex(const size_t v)
    {
        Graph temp(*this);
        size_t i;
        for(auto a: temp[v].edges)
        {
            i=0;
            while(temp[a].edges[i++] != v);
            temp[a].erase(--i);
        }
        temp.vertexList[v].vnum = -1;
        while(temp.vertexList.back().vnum == -1) temp.vertexList.pop_back();
        return temp;
    }

    bool isGraphConnected(const size_t n=0)
    {
        visited.clear();
        visited.resize(vertexList.size(), 0);
        dfs(n);
        for(size_t a=0; a<visited.size(); ++a)
            if(!visited[a] && vertexList[a].vnum>=0) return false;
        return true;
    }

    bool isVertexConnected(const size_t n) const
    {
        return !vertexList[n].edges.empty();
    }

    vector<bool> getArtPoints(const size_t n=0)
    {
        vector<bool> isArt(vertexList.size(), false);
        visited.clear();
        visited.resize(vertexList.size(), 0);
        size_t dv, nc;
        size_t *D = new size_t[vertexList.size()];
        for(size_t i=0; i<vertexList.size(); ++i)
            D[i] = 0;
        /*for(size_t v=0; v<vertexList.size(); ++v)
        {
            if(!D[v])
            {*/
                dv   = 2;
                nc   = 0;
                D[n] = 1;
                for(size_t i: vertexList[n].edges)
                {
                    if(!D[i])
                    {
                        nc++;
                        DFSap(i, n, D, dv, isArt);
                    }
                }

                if(nc > 1)
                {
                    isArt[n] = true;
                }
           /* }
        }*/
        delete[] D;
        return isArt;
    }

};

#endif // AISDI_GRAPH_H
