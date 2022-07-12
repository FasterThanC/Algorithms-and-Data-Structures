/*	
Aerouostas (ADT: prioritetinė eilė, ilgas sveikas skaičius).
Aerouostas turi 1 pakilimo/nusileidimo taką, besileidžiantys lėktuvai turi prioritetą, t.y.
jei takas laisvas, tai pirmiausia priimamas besileidžiantis lėktuvas,
bet jei kažkuris lėktuvas pradėjo pakilimą, tai visi kiti, tame tarpe ir norintys nusileisti, lėktuvai turi laukti;
lėktuvas, norintis nusileisti, negali laukti labai ilgai, nes jam baigsis degalai.

Tikslas: patyrinėti prie kokio apkrovimo aerouostui pakanka vieno tako.

Pradiniai duomenys:
nusileidimo laikas (trukmė),
pakilimo laikas (trukmė),
laikas, kurį norintis leistis lėktuvas, dar gali išbūti ore,
lėktuvo panorusio kilti/leistis einamuoju momentu tikimybė

(galima realizacija: generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą),
besileidžiantys ir kylantys lėktuvai pasirodo su vienoda tikimybe.

Rezultatai: nukritęs lėktuvas (modeliavimas iš karto baigiamas),
maksimalus ir vidutinis norinčio nusileisti lėktuvo laukimo laikas,
maksimalus ir vidutinis norinčio pakilti lėktuvo laukimo laikas.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "BigInt.h"
#include "priorityqueue.h"
using namespace std;

void calculate_average(Queue queue, size_t * takeoff_average, size_t* takeoff_max_time, size_t * land_average, size_t* land_max_time);
Plane create_plane(int time);

int step_time(Queue queue);
double random_d();

int main(int argc, char* argv[])
{
    int steps = 0; //in minutes
    srand(time(NULL));
    ofstream file("protokolas.txt");
    ifstream input("duom.txt");

    // SET PARAMETERS
    srand(0);

    system("cls");
    cout << "Vadim Ceremisinov, 4 grupe 1 pogrupis, 3 uzdavinis 4 variantas." << endl;
    cout << "Uzduotis - Aerouostas (ADT: prioritetine eile, ilgas sveikas skaicius)."<< endl;
    cout << "Programos tikslas patyrineti prie kokio apkrovimo aerouostui pakanka vieno tako." << endl << endl;
    cout << "Pradiniai duomenys:" << endl;

    file << "PIRMA DALIS. Duomenys" << endl;
    file << "  1) Vadim Ceremisinov, 4 grupe 1 pogrupis, 3 uzdavinis 4 variantas." << endl;
    file << "  2) Uzduotis - Aerouostas (ADT: prioritetine eile, ilgas sveikas skaicius)."<< endl;
    file << "  3) Programos tikslas patyrineti prie kokio apkrovimo aerouostui pakanka vieno tako." << endl;

    // READ INPUT FILE
    if(!input)
    {
        cout << "Duomenu failo neimanoma atidaryti" << endl;
        cout << "Uzdaroma programa..." << endl;
        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1) Programa sekmingai nebaige darbo" << endl;
        exit(0);
    }

    int takeoff_time;
    int land_time;
    int stay_in_air_time;
    double probability;

    string tmp;

    input >> land_time;
    getline(input, tmp);
    input >> takeoff_time;
    getline(input, tmp);
    input >> stay_in_air_time;
    getline(input, tmp);
    input >> probability;
    probability /= 100;
    getline(input, tmp);
    input >> steps;
    getline(input, tmp);

    input.close();

    cout << "Nusileidimo laikas: " << land_time << " min." << endl;
    file << "  4) Nusileidimo laikas: " << land_time << " min." << endl;

    cout << "Pakilimo laikas: " << takeoff_time << " min." << endl;
    file << "  5) Pakilimo laikas: " << takeoff_time << " min." << endl;

    cout << "Norincio leistis lektuvo laikas, kuri dar gali isbuti ore: " << stay_in_air_time << " min." << endl;
    file << "  6) Norincio leistis lektuvo laikas, kuri dar gali isbuti ore: " << stay_in_air_time << " min." << endl;

    cout << "Lektuvo panorusio kilti/leistis einamuoju momentu tikimybe: " << probability*100 << "%." << endl;
    file << "  7) Lektuvo panorusio kilti/leistis einamuoju momentu tikimybe: " << probability*100 << "%." << endl;

    cout << "Is viso trukme: " << steps << " min (" << ((double) steps / (double) (24*60)) << " diena)." << endl;
    file << "  8) Is viso trukme: " << steps << " min (" << ((double) steps / (double) (24*60)) << " diena)." << endl;

    size_t takeoff_plane_count = 0;
    size_t land_plane_count = 0;

    size_t takeoff_total_time = 0;
    size_t land_total_time = 0;

    size_t max_land_wait_time = 0;
    size_t max_takeoff_wait_time = 0;

    Queue planes = CreateQueue();


    // SIMULATION
    // ONE LOOP = ONE TIME STEP

    file << endl << "ANTRA DALIS. Vykdymas" << endl;
    int plane_crashed = 0;
    int timeleft = 0;
    int count = 1;
    for(int i = 0; i < steps; i++)
    {
        count = 1;
        file << "  T = " << i << endl;

        // PROCESS PLANE QUEUE ALLOW PLANE TO LAND/TAKEOOF WHEN timeleft <= 0

        if(timeleft <= 0)
        {
            Data d = Peek(planes);
            if(d.priority != -1)
            {
                if(d.priority == 0)
                {
                    timeleft = land_time;
                    land_total_time += d.value.wait_time;
                    land_plane_count++;
                    if(max_land_wait_time < d.value.wait_time)
                        max_land_wait_time = d.value.wait_time;
                    file << "   " << count << ") Laukiantis lektuvas pradejo leistis po " << d.value.wait_time << " min laukimo." << endl;
                    count++;
                }
                else
                {
                    timeleft = takeoff_time;
                    takeoff_total_time += d.value.wait_time;
                    takeoff_plane_count++;
                    if(max_takeoff_wait_time < d.value.wait_time)
                        max_takeoff_wait_time = d.value.wait_time;
                    file << "   " << count << ") Laukiantis lektuvas pradejo kilti po " << d.value.wait_time << " min laukimo." << endl;
                    count++;

                }
                Pop(&planes);
            }
        }
        else
        {
            Data d = Peek(planes);
            if(d.priority != -1)
            {
                file << "   " << count << ") Pirmas laukiantis eileje lektuvas dar gali likti ore " << d.value.remaining_time << " min." << endl;
                count++;
            }
        }


        // GENERATE NEW PLANE ACCORDING TO THE PROBABILITY
        if(random_d() < probability)
        {
            Data b;
            Plane new_plane = create_plane(stay_in_air_time);
            b.value = new_plane;
            b.priority = new_plane.type;
            Enqueue(&planes, b, new_plane.type);
            if(b.priority == 0)
            {
                file << "   " << count << ") Laukia pakilimo naujas lektuvas. Gali buti ore " << b.value.remaining_time << " min." << endl;
            }
            else
            {
                file << "   " << count << ") Laukia nusileidimo naujas lektuvas." << endl;
            }
            count++;
        }

        // STEP THROUGH TIME AND CHECK IF A PLANE CRASHED
        plane_crashed = step_time(planes);
        if(plane_crashed == 1)
        {
            file << "   " << count << ") Suduzo lektuvas." << endl;
            break;
        }

        file << endl;

        timeleft--;
    }

    size_t land_avg = 0;
    size_t takeoff_avg = 0;

    if(land_plane_count != 0)
    {
        land_avg = land_total_time / land_plane_count;
    }

    if(takeoff_plane_count != 0)
    {
        takeoff_avg = takeoff_total_time / takeoff_plane_count;
    }

    calculate_average(planes, &takeoff_avg, &max_takeoff_wait_time, &land_avg, &max_land_wait_time);

    if(plane_crashed == 1)
    {
        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1) Lektuvas suduzo." << endl;
        file << "  2) Vidutinis leidimosi laikas: " << land_avg << " min." << endl;
        file << "  3) Is viso leidosi laiko: " << max_land_wait_time << " min." << endl;
        file << "  4) Vidutinis kilimo laikas: " << takeoff_avg << " min." << endl;
        file << "  5) Is viso kilo laiko: " << max_takeoff_wait_time << " min." << endl;

        cout << endl << "Rezultatai:" << endl;
        cout << "Lektuvas suduzo." << endl;
        cout << "Vidutinis leidimosi laikas: " << land_avg << " min." << endl;
        cout << "Is viso leidosi laiko: " << max_land_wait_time << " min." << endl;
        cout << "Vidutinis kilimo laikas: " << takeoff_avg << " min." << endl;
        cout << "Is viso kilo laiko: " << max_takeoff_wait_time << " min." << endl;
    }
    else
    {
        file << endl << "TRECIA DALIS. Rezultatai" << endl;
        file << "  1) Lektuvas nesuduzo" << endl;
        file << "  2) Vidutinis leidimosi laikas: " << land_avg << " min." << endl;
        file << "  3) Is viso leidosi laiko: " << max_land_wait_time << " min." << endl;
        file << "  4) Vidutinis kilimo laikas: " << takeoff_avg << " min." << endl;
        file << "  5) Is viso kilo laiko: " << max_takeoff_wait_time << " min." << endl;

        cout << endl << "Rezultatai:" << endl;
        cout << "Lektuvas nesuduzo." << endl;
        cout << "Vidutinis leidimosi laikas: " << land_avg << " min." << endl;
        cout << "Is viso leidosi laiko: " << max_land_wait_time << " min." << endl;
        cout << "Vidutinis kilimo laikas: " << takeoff_avg << " min." << endl;
        cout << "Is viso kilo laiko: " << max_takeoff_wait_time << " min." << endl;
    }

    return 0;
}

double random_d()
{
    return (double)rand() / (double)RAND_MAX;
}

void calculate_average(Queue queue, size_t * takeoff_average, size_t* takeoff_max_time, size_t * land_average, size_t* land_max_time)
{
    struct Node *current = queue.headNode;
    struct Node *headNode = queue.headNode;

    size_t max = 0;
    size_t avg = 0;
    size_t total = 0;
    size_t count = 0;

    size_t max1 = 0;
    size_t avg1 = 0;
    size_t total1 = 0;
    size_t count1 = 0;

    if(current == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        if(current->value.value.type == 1)
        {
            total += current->value.value.wait_time;
            count++;
            if(max < current->value.value.wait_time)
                max = current->value.value.wait_time;
        }

        if(current->value.value.type == 0)
        {
            total1 += current->value.value.wait_time;
            count1++;
            if(max1 < current->value.value.wait_time)
                max1 = current->value.value.wait_time;
        }

        current = current -> nextNode;
    }

    if(*takeoff_max_time < max)
        *takeoff_max_time = max;

    if(*land_max_time < max1)
        *land_max_time = max1;

    if(count != 0)
    {
        avg = total / count;
        *takeoff_average = (avg + *takeoff_average) / 2;
    }
    if(count1 != 0)
    {
        avg1 = total1 / count1;
        *land_average = (avg1 + *land_average) / 2;
    }
}

Plane create_plane(int time)
{
    Plane plane;
    plane.remaining_time = time;
    plane.type = rand() % 2;
    plane.wait_time = 0;
    return plane;
}

int step_time(Queue queue)
{
    struct Node *current = queue.headNode;
    struct Node *headNode = queue.headNode;

    if(headNode == NULL)
    {
        return 0;
    }

    while (current != NULL)
    {
        current->value.value.remaining_time--;
        current->value.value.wait_time += 1;

        if(current->value.value.remaining_time <= 0 && current->value.value.type == 0)
        {
            return 1;
        }

        current = current -> nextNode;
    }

    return 0;
}