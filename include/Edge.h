#ifndef EDGE_H
#define EDGE_H


class Edge
{
    public:
        Edge();
        virtual ~Edge();
        Edge(int id, int numPort, int idEdge, int portEdge) :
            this.id(id), this.numPort(numPort), this.idEdge(this.idEdge), this.portEdge;

        int id;
        int numPort;
        int idAggr;
        int portAggr;
        int idNode;
        int portNode;


};

#endif // EDGE_H
