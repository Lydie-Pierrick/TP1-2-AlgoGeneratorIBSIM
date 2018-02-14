#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    int k;
    cout << "Enter a positive even k : ";
    cin >> k;

    // make sure k is valid
    if(k < 0 || k % 2 == 1){
        cout << "Invalid integer !" << endl;
        return 1;
    }

    ofstream file;
    // Open and link to the file
    file.open("fattree.topo");

    int nNodesPerPod = (k/2)*(k/2);
    int nNodesPerSwitch = k /2;
    int nPortsPerHost = 1;
    int nCores = (k/2)*(k/2);
    int nHosts = k * k;
    int counterNodes = 0;

    // A number that we are not sure about
    int nThird = 1;

    // Generate the file header
    file << "#fat tree topology file." << endl;
    file << "#Value of k = " << k << endl;
    file << "#Total number of hosts = " << nHosts << endl;
    file << "#Number of hosts under each switch = " << nNodesPerSwitch << endl;
    file << "####################################################" << endl << endl;

    // Print each node
    // Each pod
    for(int iPods = 0; iPods < k; iPods ++){
        // Half switches
        for(int iSwitch = k/2; iSwitch < k; iSwitch ++){
            // Each node of the switch
            for(int iNode = 0; iNode < nNodesPerSwitch; iNode ++){
                file << "Hca\t1\t\"Node(" << counterNodes << ")\"" << endl;
                file << "[" << nPortsPerHost << "] \"Edge(" << iPods << " " << iSwitch << " " << nThird << ")\"[" << iSwitch << "]" << endl << endl;
                counterNodes ++;
            }
        }
    }

    // Each pod
    for(int iPods = 0; iPods < k; iPods ++){
        counterNodes = 0;
        // Print each Edge switch
        int iSwitch = 0;
        while(iSwitch < nNodesPerSwitch){
            file << "Switch\t" << k << "\t\"Edge(" << iPods << " " << iSwitch << " " << nThird << ")\"" << endl;
            int iPort = 1;
            // For the first three ports : all for switch Aggr
            while(iPort <= nNodesPerSwitch){
                file << "[" << iPort << "] \"Aggr(" << iPods << " " << iSwitch + nNodesPerSwitch << " " << nThird << ")\"[" << iSwitch + 1 << "]" << endl;
                iPort ++;
                iSwitch ++;
            }

            // For the last three ports : all for nodes
            while(iPort > nNodesPerSwitch && iPort <= k){
                file << "[" << iPort << "] \"Node(" << counterNodes << ")\"[" << nPortsPerHost << "]" << endl;
                iPort ++;
                counterNodes ++;
            }

            file << endl;
        }
    }

    // Print each Aggr switch
    for(int iPods = 0; iPods < k; iPods ++){
        int iSwitch = nNodesPerSwitch;
        while(iSwitch < k){
            file << "Switch\t" << k << "\t\"Aggr(" << iPods << " " << iSwitch << " " << nThird << ")\"" << endl;
            int iPort = 1;
            // For the first three ports : all for switch Core
            while(iPort <= nNodesPerSwitch){
                file << "[" << iPort << "] \"Core(" << nCores << " " << iSwitch + 1 << " " << iPort << ")\"[" << iSwitch + 1 << "]" << endl;
                iPort ++;
            }

            // For the last three ports : all for switch Edge
            while(iPort > nNodesPerSwitch && iPort <= k){
                file << "[" << iPort << "] \"Edge(" << iPods << " " << iSwitch - nNodesPerSwitch << " " << nThird << ")\"[" << iSwitch + 1 << "]" << endl;
                iPort ++;
                iSwitch ++;
            }
            file << endl;
        }
    }

    // Core (iCore_n1, iCore_n2, iCore_n3)
    int iCore_n1 = nCores;
    int iCore_n2 = 1;
    int iCore_n3 = 1;
    // Print each Core switch
    for(int iCore = 0; iCore < nCores; iCore ++){

        if(iCore_n3 <= nNodesPerSwitch){
            file << "Switch\t" << k << "\t\"Core(" << iCore_n1 << " " << iCore_n2 << " " << iCore_n3 << ")\"" << endl;
            for(int iPort = 1; iPort <= k; iPort ++){
                file << "[" << iPort<< "] \"Aggr(" << iPort - 1 << " " << iCore_n2 - 1 << " " << nThird << ")\"[" << iCore_n3 - 1 << "]" << endl;
            }
            iCore_n3 ++;

            if(iCore_n3 > nNodesPerSwitch){
                iCore_n3 = 1;
                iCore_n2 ++;
            }
        }
        file << endl;
    }

    file.close();

    cout << "Successfully output into the file \"fattree.topo\" ! " << endl;
    return 0;
}
