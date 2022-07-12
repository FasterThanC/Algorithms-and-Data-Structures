// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
#include <iostream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <queue>
#include <map>
#include <list>
#include <sstream>
using namespace std;
#include <limits.h>

// Number of vertices in the graph
//#define V 9

const int maxName = 100;

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[], int nodeNumber)
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < nodeNumber; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], string names[], int nodeNumber)
{
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < nodeNumber; i++)
        cout << names[i] << " \t\t" << dist[i] << endl;
}

void drawTree(ofstream& file, int matrixSize, bool visitedNodes[], char nodes[], bool** releasedTree, int nodeInCheck, int& recursionDepth)
{


    for (int j = 0; j < matrixSize; j++)
    {
        if (releasedTree[j][nodeInCheck] && !visitedNodes[j])
        {
            cout << " ";
            file << "     ";
            for (int y = 0; y < recursionDepth + 1; ++y)
            {
                file << "-";
                cout << "-";
            }
            cout << nodes[j] << endl;
            file << nodes[j] << endl;
            visitedNodes[j] = 1;
            drawTree(file, matrixSize, visitedNodes, nodes, releasedTree, j, ++recursionDepth);
        }

    }
    --recursionDepth;


}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(ofstream& file, int graph[maxName][maxName], int src, string names[], int nodeNumber, int destinationCityIndex)
{
    int moment = 0;
    int dist[maxName]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[maxName]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < nodeNumber; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;
    int path[maxName];
    int pathIndex = 0;
    // Find shortest path for all vertices
    for (int count = 0; count < nodeNumber - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet, nodeNumber);
        file << "Momentas " << moment << endl;
        ++moment;
        file << "    Atidaryta: " << names[u] << endl;
        // Mark the picked vertex as processed
        sptSet[u] = true;
        path[pathIndex] = u;
        ++pathIndex;
        bool neighboor = false;
        bool first = false;
        bool wasThere = false;
        bool found = false;
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < nodeNumber; v++)
        {
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
            {
                if (!first)
                {
                    file << "    Uzdaryta: ";
                    first = true;
                    wasThere = true;
                }
                
                dist[v] = dist[u] + graph[u][v];
                file << names[v] << "(" << dist[v] << ") ";


            }
            if (graph[u][v] && !sptSet[v])
            {
                neighboor = true;
            }
            if (destinationCityIndex == v && dist[v] != INT_MAX)
            {
                
                found = true;
            }
        }
        if (!wasThere)
        {
            file << "    Uzdarytu virsuniu nera.";
        }
        if (!found)
        {
            file << endl << "    Trumpiausias kelias nerastas." << endl;
            file << endl;
        }
        else
        {
            file << endl << "    Rastas kelias i miesta " << names[destinationCityIndex] << " kaina " << dist[destinationCityIndex] << " Eur." << endl;
            file << endl;
        }
        if (!neighboor)
        {
            --pathIndex;
        }
                
    }

    if (dist[destinationCityIndex] != INT_MAX)
    {
        file << endl << "TRECIA DALIS. Rezultatai" << endl << endl;
        file << "  1. Pigiausias kelias: ";
        cout << endl << "Pigiausias kelias: ";

        for (int i = 0; i < pathIndex; ++i)
        {
            file << names[path[i]] << ", ";
            cout << names[path[i]] << ", ";
        }
        file << names[destinationCityIndex] << ".";
        cout << names[destinationCityIndex] << ".";
        file << endl;
        cout << endl;
        file << "  2. Keliones kaina i miesta " << names[destinationCityIndex] << " yra " << dist[destinationCityIndex] << " Eur.";
        cout << "Keliones kaina i miesta " << names[destinationCityIndex] << " yra " << dist[destinationCityIndex] << " Eur.";
    }
    else
    {
        file << endl << "TRECIA DALIS. Rezultatai" << endl << endl;
        file << "  1. Kelio i miesta " << names[destinationCityIndex] << " nera" << endl;
        cout << endl << "Kelio i miesta " << names[destinationCityIndex] << " nera" << endl;
    }
}



// driver program to test above function
int main()
{

    int realNameIndex;
    string startingCity;
    int startingCityIndex;
    string destinationCity;
    int destinationCityIndex;
    string names[maxName];
    ofstream file("protokolas.txt");
    string fileName;

    string traveler;
    
    system("cls");
    cout << "Klaidas Sinkevicius, 4 grupe, 2 pogrupis, 4 uzdavinis, 4 variantas" << endl;
    cout << "Programos tikslas rasti pigiausia keliones is vieno duoto miesto i kita duota miesta marsruta ir jo kaina" << endl;
    cout << "(Grafo realizacija pridnziama kaimynystes sarasais)" << endl << endl;


    file << "PIRMA DALIS. Duomenys" << endl << endl;
    file << "  1. Klaidas Sinkevicius, 4 grupe, 2 pogrupis, 4 uzdavinis, 4 variantas" << endl;
    file << "  2. Programos tikslas rasti pigiausia keliones is vieno duoto miesto i kita duota miesta marsruta ir jo kaina" << endl;
    file << "     (Grafo realizacija pridnziama kaimynystes sarasais)" << endl;




    cout << "Iveskite duomenu failo pavadinima: ";
    cin >> fileName;

    ifstream data(fileName);
    if (!data)
    {
        cout << "Failo " << fileName << " neimanoma atidaryti" << endl;
        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1. Programa sekmingai nebaige darbo" << endl;
        cout << "Uzdaroma programa..." << endl;
        exit(0);
    }

    string tmp;
    int nodeNumber;
    data >> nodeNumber;
    cout << endl << "Virsuniu skaicius: " << nodeNumber << endl;
    file << "  3. Virsuniu skaicius: " << nodeNumber << endl;
    getline(data, tmp);

    
    cout << "Pradiniai duomenys:" << endl;
    
    int graph[maxName][maxName]{0};
    data >> startingCity;
    cout << "Pradzios miestas: " << startingCity << endl;
    file << "  4. Pradzios miestas: " << startingCity << endl;
    getline(data, tmp);

    data >> destinationCity;
    cout << "Keliones tikslas: " << destinationCity << endl;
    file << "  5. Keliones tikslas: " << destinationCity << endl;
    getline(data, tmp);

    data >> traveler;
    cout << "Vaziuojantis zmogus: " << traveler << endl;
    file << "  6. Vaziuojantis zmogus: " << traveler << endl;
    getline(data, tmp);
    getline(data, tmp);
    getline(data, tmp);

    string tempNames[maxName];
    int namesIndex = 0;
    int priceIndex = 0;
    int price[maxName]{0};
    int ownerIndex = 0;
    string owner[maxName];
    int index = -1;
    char symbols[maxName];
    do
    {
        do
        {
            ++index;
            data >> symbols[index];
        } while (symbols[index] != '-');
        symbols[index] = '\0';
        tempNames[namesIndex] = symbols;
        ++namesIndex;
        data.get(symbols[index]);
        for (int i = 0; i < index; ++i)
        {
            symbols[i] = 0;
        }
        index = -1;

        do
        {
            ++index;
            data >> symbols[index];
        } while (symbols[index] != '-');
        symbols[index] = '\0';
        tempNames[namesIndex] = symbols;
        ++namesIndex;
        data.get(symbols[index]);
        for (int i = 0; i < index; ++i)
        {
            symbols[i] = 0;
        }
        index = 0;

        data >> price[priceIndex];
        ++priceIndex;
        data >> symbols[index];
        while (symbols[index] != '-')
        {
            data >> symbols[index];
            ++index;
        }
        data.get(symbols[index]);
        for (int i = 0; i < index; ++i)
        {
            symbols[i] = 0;
        }
        index = -1;

        do
        {
            ++index;
            data.get(symbols[index]);
        } while (symbols[index] != '\n');
        symbols[index] = '\0';
        owner[ownerIndex] = symbols;
        ++ownerIndex;

        for (int i = 0; i < index; ++i)
        {
            symbols[i] = 0;
        }
        index = -1;

        ++index;
        data.get(symbols[index]);

    } while (symbols[index] != '\n');

    realNameIndex = 0;
    bool nameInAList = false;
    int previousNumber = 0;
    int secondaryIndex = 0;
    for (int i = 0; i < namesIndex; ++i)
    {
        int j = 0;
        for (; j < realNameIndex; ++j)
        {
            if (tempNames[i] == names[j])
            {
                nameInAList = true;
                break;
            }
        }
        if (i % 2 == 0)
        {
            previousNumber = j;
        }
        if (!nameInAList)
        {
            names[realNameIndex] = tempNames[i];
            if (names[realNameIndex] == startingCity)
            {
                startingCityIndex = realNameIndex;
            }
            if (names[realNameIndex] == destinationCity)
            {
                destinationCityIndex = realNameIndex;
            }
            ++realNameIndex;
        }

        if (i % 2 == 1)
        {
            if (owner[secondaryIndex] == traveler)
            {
                price[secondaryIndex] = price[secondaryIndex] / 2;
            }
            
            graph[previousNumber][j] = price[secondaryIndex];
            graph[j][previousNumber] = price[secondaryIndex];
            ++secondaryIndex;
        }
        nameInAList = false;
    }
    getline(data, tmp);
    stringstream buffer;
    buffer << data.rdbuf();
    cout << endl << buffer.str() << endl;
    file << endl << buffer.str() << endl;

    file << endl << "ANTRA DALIS. Vykdymas" << endl << endl;

    dijkstra(file, graph, startingCityIndex, names, nodeNumber, destinationCityIndex);



    return 0;
}