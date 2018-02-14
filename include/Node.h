#ifndef NODE_H
#define NODE_H


class Node
{
    public:
        Node();
        virtual ~Node();
        Node(int id, int numPort, int idEdge, int portEdge) :
            this.id(id), this.numPort(numPort), this.idEdge(this.idEdge), this.portEdge;

        int id;
        int numPort;
        int idEdge;
        int portEdge;

};

#endif // NODE_H
