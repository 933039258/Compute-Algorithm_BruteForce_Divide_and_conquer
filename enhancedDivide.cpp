#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct coord
{
    int x, y;
};

struct record
{
    int x, y;
    float d;
};

float minList[1000000][5];
int minCounter = 0;


//This function is used to calculate the distance between two point
float distance(struct coord a, struct coord b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void mergeTogether(coord arry[], int l, int m, int r, int coor)
{
    int k = 0;
    int num1 = m - l + 1;
    int num2 = r - m;

    //Create temp list
    coord *tl, *tr;
    tl = new coord[num1];
    tr = new coord[num2];

    for(int i = 0; i < num1; i++)
    {
        tl[i].x = arry[l + i].x;
        tl[i].y = arry[l + i].y;
    }
    for(int j = 0; j < num2; j++)
    {
        tr[j].x = arry[m + 1 + j].x;
        tr[j].y = arry[m + 1 + j].y;
    }

    //Start merge back
    int i = 0;
    int j = 0;
    k = l;
    while(i < num1 && j < num2)
    {
        if(coor == 0)
        {
            if(tl[i].x <= tr[j].x)
            {
                arry[k].x = tl[i].x;
                arry[k].y = tl[i].y;
                i++;
            }
            else
            {
                arry[k].x = tr[j].x;
                arry[k].y = tr[j].y;
                j++;
            }
            k++;
        }
        else if(coor == 1)
        {
            if(tl[i].y <= tr[j].y)
            {
                arry[k].x = tl[i].x;
                arry[k].y = tl[i].y;
                i++;
            }
            else
            {
                arry[k].x = tr[j].x;
                arry[k].y = tr[j].y;
                j++;
            }
            k++;
        }  
    }

    while(i < num1)
    {
        arry[k].x = tl[i].x;
        arry[k].y = tl[i].y;
        i++;
        k++;
    }
    while(j < num2)
    {
        arry[k].x = tr[j].x;
        arry[k].y = tr[j].y;
        j++;
        k++;
    }
    free(tl);
    free(tr);
}

void mergeSort(coord arry[], int l, int r, int coor)
{
    if(l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arry, l, m, coor);
        mergeSort(arry, m+1, r, coor);
        mergeTogether(arry, l, m, r, coor);
    }
}

//This function is the Brute Force method to find the closest pair of point
float bruteForce(coord list[], int num)
{
    float min = 99999.99;
    int pos1, pos2;

    for(int i = 0; i < num; i++)
    {
        for(int j = 0; j < num; j++)
        {
            if(distance(list[i], list[j]) < min && distance(list[i], list[j]) > 0)
            {
                min = distance(list[i], list[j]);
                //Store the record
                minList[minCounter][0] = min;
                minList[minCounter][1] = list[i].x;
                minList[minCounter][2] = list[i].y;
                minList[minCounter][3] = list[j].x;
                minList[minCounter][4] = list[j].y;
                minCounter++;
            }
        }
    }
    return min;
}

//This function is used when created the list that contain point from M+-d
float innerMinDistance(coord * list, int num, float d)
{
    float min = d;
    for(int i = 0; i < num; i ++)
    {
        for(int j = 0; j < num; j++)
        {
            //Only compare those pair that y smaller than d
            if(abs(list[i].y-list[j].y) < d)
            {
                //Now find the closest pair inside the given list
                if(distance(list[i], list[j]) < min && distance(list[i], list[j]) > 0)
                {
                    min = distance(list[i], list[j]);
                    
                    //Store the record
                    minList[minCounter][0] = min;
                    minList[minCounter][1] = list[i].x;
                    minList[minCounter][2] = list[i].y;
                    minList[minCounter][3] = list[j].x;
                    minList[minCounter][4] = list[j].y;
                    minCounter++;
                }
            }
        }
    }
    return min;
}

//This function is the main used function
float closestFunc(coord * listx, coord * listy, int num)
{
    //This is the base case
    if(num <= 3)
    {
        return bruteForce(listx, num);
    }

    int mid = num/2;                //Find the mid position
    coord midP = listx[mid];        //Find the mid point

    coord pleft[mid+1];             //Create array to store the y list
    coord pright[num-mid-1];
    int left = 0, right = 0;

    //cout << "Here 1?" << endl;

    //Separate the list in sorted y array into two part, but keep the y sorted
    //cout << "Here CCP?" << endl;
    for(int i = 0; i < num; i++)
    {
        //cout << "i is: " << i << endl;
        //cout << "Data is: " << listx[i].x << endl;
        if(listy[i].x < midP.x)
        {
            //cout << "Here CCL?" << endl;
            pleft[left] = listy[i];
            left++;
        }
        else
        {
            //cout << "Here CCR?" << endl;
            pright[right] = listy[i];
            right++;
        }  
    }

    float dl = closestFunc(listx, pleft, mid);        //Recur left
    float dr = closestFunc(listx + mid, pright, num-mid);      //Recur right

    //free(pleft);
    //free(pright);

    float  d;
    if(dl < dr)
    {
        d = dl;
    }
    else
    {
        d = dr;
    }

    //Select the point in the strip
    coord innerList[num];
    int j = 0;
    for(int i = 0; i < num; i++)
    {
        if(abs(listy[i].x-midP.x) < d)
        {
            innerList[j] = listy[i];
            j++;
        }
    }

    //Compare the point in the strip, should be O(n)
    float dInner = innerMinDistance(innerList, j, d);

    if(dInner < d)
    {
        return dInner;
    }
    else
    {
        return d;
    }
}

int main(int argc, char *argv[])
{

    //Do the basic command checking
    if (argc > 2)
    {
        cout << "Wrong number of argument!" << endl;
        return 0;
    }

    //Start read in the file
    ifstream inFile;
    inFile.open(argv[1], ios::in);

    //Read the line number
    string eachLine;
    int line_num = 0;
    while(getline(inFile, eachLine))
    {
        //cout << eachLine << endl;
        line_num++;
    }
    inFile.close();

    /*****Test: Print the line number*****
    //cout << line_num<< endl;
    */

    //Create the coordinate array
    coord list[line_num];

    //Re-open the file since buffer is cleared
    inFile.open(argv[1], ios::in);

    //Start convert the line to number
    string currentNum;
    line_num = 0;       //Re-use the line number counter
    while(getline(inFile, eachLine))
    {
        int spacePos;
        for(int i = 0; i < eachLine.length(); i++)
        {
            if(eachLine[i] == ' ')
            {
                spacePos = i;
            }
        }
        currentNum = eachLine.substr(0, spacePos);      //Get first number
        list[line_num].x = stoi(currentNum);
        currentNum = eachLine.substr(spacePos+1, eachLine.length()-spacePos);   //Get second number
        list[line_num].y = stoi(currentNum);
        line_num++;
    }

    /*****Test: Print the list*****
    cout << "== Start print the list?" << endl;
    for(int i = 0; i < line_num; i++)
    {
        cout << list[i][0] << ' ' << list[i][1] << endl;
    }
    cout << "== Print over." << endl;
    */

    //Start sort list based on x coordinate
    coord * list_x = new coord[line_num];       //Create the x array
    coord * list_y = new coord[line_num];       //Create the y array
    int indexCurrentByx = line_num-1;
    int indexCurrentByy = line_num-1;
    for(int i = 0; i < line_num; i++)         //Copying old list to current
    {
        list_x[i] = list[i];
        list_y[i] = list[i];
    }

    mergeSort(list_x, 0, line_num-1, 0);
    mergeSort(list_y, 0, line_num-1, 1);

    //cout << "Here?" << endl;
    /*****Test: Print the list*****
    cout << "== Start print the list?" << endl;
    for(int i = 0; i < line_num; i++)
    {
        cout << "This is list x: " << list_x[i].x << endl;
        //cout << "This is list y: " << list_y[i].y << endl;
        //cout << "Line number is: " << line_num << endl;
    }
    cout << "== Print over." << endl;
    */
    
    


    //Start the algorithm

    //Get runtime before start
    auto start = high_resolution_clock::now();

    //cout << "== Call the function." << endl;
    float result = closestFunc(list_x, list_y, line_num);
    //cout << "== Called the function." << endl;

    //Get time after finish
    auto stop = high_resolution_clock::now();

    //Find the point:
    ofstream outP("output_enhanceddnc.txt");
    outP << result << endl;
    for(int i = 0; i < minCounter; i++)
    {
        if(minList[i][0] == result)
        {
            //cout << "== TOuch!" << endl;
            outP << minList[i][1] << " ";
            outP << minList[i][2] << " ";
            outP << minList[i][3] << " ";
            outP << minList[i][4] << endl;
        }
    }

    //Get duration:
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "== Runtime is: " << duration.count() << endl;
    cout << "== Final result is: " << result << endl;

    return 0;
}