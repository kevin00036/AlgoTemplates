#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

/////////////////class definition////////////////////

class Graph
{
    public:
        class Vertex;
        class Edges;

        Graph();
        explicit Graph(int);
        Graph(int, int);
        Graph(const Graph&);
        ~Graph();
        Vertex operator[](int);
        void addEdge(int, int);
        void reset();
        void reverse();
        void DFS(int, bool);
        void BFS(int, bool);

        int nVertices_;

    private:
        Vertex* vertices_;
        Edges* edges_;
        
};

class Graph::Vertex
{
    public:
        Vertex();
        Vertex(int);
        void reset();
        void visit();
        void leave(int);
        int getLabel() const;
        bool isVisited() const;
        bool isLeaved() const;
        int getLeaveTime() const;

    private:
        int label_;
        bool isVisited_;
        bool isLeaved_;
        int leaveTime_;
};

class Graph::Edges
{
    public:
        Edges();
        explicit Edges(int);
        explicit Edges(int, int);
        ~Edges();
        void set(int);
        void set(int, int);
        void add(int, int);
        int getDegree(int, int);
        bool isConnected(int, int);
        int get(int, int);
        void reverse();

    private:
        class Edge;

        void adjust();

        bool sorted_;
        int nVertices_;
        int nEdges_;
        int maxEdges_;
        int* edgeCount_;
        int* edgeSum_;
        Edge* edges_;
};

class Graph::Edges::Edge
{
    public:
        Edge();
        Edge(int, int);
        void set(int, int);
        int getFrom();
        int getTo();

        static bool compare(const Edge&, const Edge&);
        static void reverse();
        static int from_;
        static int to_;

    private:
        int nodes_[2];
};

////////////////////////Practice////////////////////////////

Graph::Vertex::Vertex()
{
    reset();
}

Graph::Vertex::Vertex(int label)
{
    label_ = label;
    reset();
}

void Graph::Vertex::reset()
{
    isVisited_ = false;
    isLeaved_ = false;
}

void Graph::Vertex::visit()
{
    isVisited_ = true;
}

void Graph::Vertex::leave(int leaveTime)
{
    isLeaved_ = true;
    leaveTime_ = leaveTime;
}

int Graph::Vertex::getLabel() const
{
    return label_;
}

bool Graph::Vertex::isVisited() const
{
    return isVisited_;
}

bool Graph::Vertex::isLeaved() const
{
    return isLeaved_;
}

int Graph::Vertex::getLeaveTime() const
{
    return leaveTime_;
}

int Graph::Edges::Edge::from_ = 0;
int Graph::Edges::Edge::to_ = 1;

Graph::Edges::Edge::Edge()
{
}

Graph::Edges::Edge::Edge(int from, int to)
{
    nodes_[Edge::from_] = from;
    nodes_[Edge::to_] = to;
}

void Graph::Edges::Edge::set(int from, int to)
{
    nodes_[Edge::from_] = from;
    nodes_[Edge::to_] = to;
}

int Graph::Edges::Edge::getFrom()
{
    return nodes_[Edge::from_];
}

int Graph::Edges::Edge::getTo()
{
    return nodes_[Edge::to_];
}

bool Graph::Edges::Edge::compare(const Edge& a, const Edge& b)
{
    if (a.nodes_[Edge::from_] != b.nodes_[Edge::from_])
        return a.nodes_[Edge::from_] < b.nodes_[Edge::from_];
    else
        return a.nodes_[Edge::to_] < b.nodes_[Edge::to_];
}

void Graph::Edges::Edge::reverse()
{
    Edge::from_ ^= 1;
    Edge::to_ ^= 1;
}

Graph::Edges::Edges()
{
}

Graph::Edges::Edges(int nVertices)
{
    nVertices_ = nVertices;
    maxEdges_ = nVertices_ * nVertices_;
    edgeCount_ = new int[2 * nVertices_];
    edgeSum_ = new int[nVertices_ + 1];
    edges_ = new Edge[maxEdges_];
    fill(edgeCount_, edgeCount_ + nVertices_, 0);
    edgeSum_[0] = 0;
    nEdges_ = 0;
}

Graph::Edges::Edges(int nVertices, int maxEdges)
{
    nVertices_ = nVertices;
    maxEdges_ = maxEdges;
    edgeCount_ = new int[2 * nVertices_];
    edgeSum_ = new int[nVertices_ + 1];
    edges_ = new Edge[maxEdges_];
    fill(edgeCount_, edgeCount_ + nVertices_, 0);
    edgeSum_[0] = 0;
    nEdges_ = 0;
}

Graph::Edges::~Edges()
{
    delete [] edgeCount_;
    delete [] edgeSum_;
    delete [] edges_;
}

void Graph::Edges::set(int nVertices)
{
    if (edgeCount_)
        delete [] edgeCount_;
    if (edgeSum_)
        delete [] edgeSum_;
    if (edges_)
        delete [] edges_;
    nVertices_ = nVertices;
    maxEdges_ = nVertices_ * nVertices_;
    edgeCount_ = new int[2 * nVertices_];
    edgeSum_ = new int[nVertices_ + 1];
    edges_ = new Edge[maxEdges_];
    fill(edgeCount_, edgeCount_ + nVertices_, 0);
    edgeSum_[0] = 0;
    nEdges_ = 0;
}

void Graph::Edges::set(int nVertices, int maxEdges)
{
    if (edgeCount_)
        delete [] edgeCount_;
    if (edgeSum_)
        delete [] edgeSum_;
    if (edges_)
        delete [] edges_;
    nVertices_ = nVertices;
    maxEdges_ = maxEdges;
    edgeCount_ = new int[2 * nVertices_];
    edgeSum_ = new int[nVertices_ + 1];
    edges_ = new Edge[maxEdges_];
    fill(edgeCount_, edgeCount_ + nVertices_, 0);
    edgeSum_[0] = 0;
    nEdges_ = 0;
}

void Graph::Edges::add(int from, int to)
{
    if (nEdges_ < maxEdges_) {
        sorted_ = false;
        edges_[nEdges_].set(from, to);
        edgeCount_[Edge::from_ * nVertices_ + from]++;
        edgeCount_[Edge::to_ * nVertices_ + to]++;
        nEdges_++;
    }
}

int Graph::Edges::getDegree(int vertex, int flag = 1)
{
    if (1 == flag)
        return edgeCount_[Edge::from_ * nVertices_ + vertex];
    else if (-1 == flag)
        return edgeCount_[Edge::to_ * nVertices_ + vertex];
    else
        return edgeCount_[nVertices_ + vertex] + edgeCount_[vertex];
}

void Graph::Edges::adjust()
{
    if (!sorted_) {
        sort(edges_, edges_ + nEdges_, Edge::compare);
        for (int i = 1; i <= nVertices_; i++) {
            edgeSum_[i] = edgeSum_[i - 1] + getDegree(i - 1);
            cout << edgeSum_[i] << ' ';
        }
        cout << endl;
        sorted_ = true;
    }
}

bool Graph::Edges::isConnected(int from, int to)
{
    adjust();
    bool isconnected = false;
    if (from < nVertices_ && to < nVertices_) {
        int binaryleft(edgeSum_[from]);
        int binaryright(edgeSum_[from + 1]);
        while (binaryleft != binaryright) {
            int middle = (binaryleft + binaryright) >> 1;
            if (edges_[middle].getTo() == to) {
                isconnected = true;
                break;
            }
            else if (edges_[middle].getTo() > to) {
                binaryright = middle;
            }
            else {
                binaryleft = middle + 1;
            }
        }
    }
    return isconnected;
}

int Graph::Edges::get(int from, int index)
{
    adjust();
    if (from < nVertices_ && index + edgeSum_[from] < edgeSum_[from + 1])
        return edges_[edgeSum_[from] + index].getTo();
    else
        return -1;
}

void Graph::Edges::reverse()
{
    Edge::reverse();
    adjust();
}

Graph::Graph()
{
}

Graph::Graph(int nVertices)
{
    nVertices_ = nVertices;
    vertices_ = new Vertex[nVertices_];
    edges_ = new Edges(nVertices);
}

Graph::Graph(int nVertices, int maxEdges)
{
    nVertices_ = nVertices;
    vertices_ = new Vertex[nVertices_];
    edges_ = new Edges(nVertices, maxEdges);
}

Graph::Graph(const Graph& graph)
{
    
}

Graph::~Graph()
{
    if (vertices_)
        delete [] vertices_;
    if (edges_)
        delete edges_;
}

Graph::Vertex Graph::operator[](int index)
{
    if (index < nVertices_)
        return vertices_[index];
}

void Graph::addEdge(int from, int to)
{
    edges_->add(from, to);
}

void Graph::reset()
{
    for (int i = 0; i < nVertices_; i++)
        vertices_[i].reset();
}

void Graph::reverse()
{
    edges_->reverse();
}

void Graph::DFS(int start, bool flag = false)
{
    if (start < nVertices_) {
        //stack<int> st;
        int* st = new int[nVertices_ * nVertices_];
        //st.push(start);
        st[0] = start;
        int length = 1;
        int now;
        int leaveTime = 0;
        while (length > 0) {
        //while (!st.empty()) {
            now = st[length - 1];
            //now = st.top();
            if (!flag) {
                length--;
                //st.pop();
            }
            if (vertices_[now].isVisited()) {
                if (!vertices_[now].isLeaved()) {
                    vertices_[now].leave(leaveTime);
                    leaveTime++;
                }
                length--;
                //st.pop();
            }
            else {
                vertices_[now].visit();
                int next = 0;
                int child = edges_->get(now, next);
                while (child != -1) {
                    if (!vertices_[child].isVisited()) {
                        st[length] = child;
                        length++;
                        //st.push(child);
                    }
                    next++;
                    child = edges_->get(now, next);
                }
            }
        }
        delete [] st;
    }
}

void Graph::BFS(int start, bool flag = false)
{
    if (start < nVertices_) {
        //queue<int> qu;
        int* qu = new int[nVertices_ * nVertices_];
        //qu.push(start);
        int head = 1;
        int tail = 0;
        int now;
        int leaveTime = 0;
        while (head != tail) {
        //while (!qu.empty()) {
            now = qu[tail];
            //now = qu.back();
            if (!flag) {
                tail++;
                //qu.pop();
            }
            if (vertices_[now].isVisited()) {
                if (!vertices_[now].isLeaved()) {
                    vertices_[now].leave(leaveTime);
                    leaveTime++;
                }
                tail++;
                //qu.pop();
            }
            else {
                vertices_[now].visit();
                int next = 0;
                int child = edges_->get(now, next);
                while (child != -1) {
                    if (!vertices_[child].isVisited()) {
                        //qu.push(child);
                        qu[head] = child;
                        head++;
                    }
                    next++;
                    child = edges_->get(now, next);
                }
            }
        }
        delete [] qu;
    }
}

#endif
