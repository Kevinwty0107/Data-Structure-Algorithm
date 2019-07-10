#include <fstream>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

static int collipse;

typedef struct
{
    char student_ID[20];
    char student_name[10];
}DicElement;

typedef struct
{
//    int valid;
    int m;
    DicElement * element;
}HashDictionary;

typedef HashDictionary * pHashDictionary;

pHashDictionary createEmptyDictionary(int m)
{
    int i;
    pHashDictionary phd;
    phd = (pHashDictionary)malloc(sizeof(HashDictionary));
    if (phd != NULL)
    {
        phd->element = (DicElement *)malloc(sizeof(DicElement) * m);
        if (phd->element)
        {
            for (i = 0; i < m; i++)
            {
                strcpy(phd->element[i].student_ID, "0");
                strcpy(phd->element[i].student_name, "0");
            }
            phd->m = m;
            return (phd);
        }
        else free(phd);
    }
    cout<<"Out of space!"<<endl;
    return NULL;
}

int h(char * key)
{
    return (((int)key[0] * (int)key[1] - (int)key[2] * 99) * ((int)key[0] * (int)key[1] - (int)key[2] * 99 + 987) % 1000);
}

int linearSearch(pHashDictionary student, char * key, int *position)
{
    int d, inc;
    d = h(key);
    for (inc = 0; inc < student->m; inc++)
    {
        if ((string)student->element[d].student_name == (string)key)
        {
            * position = d;
            collipse++;
            return 1;
        }
        else if ((string)student->element[d].student_name == "0")
        {
            * position = d;
            return 0;
        }
        d = (d + 1) % student->m;
    }
    * position = -1;
    return 0;
}

int linearInsert(pHashDictionary student, DicElement ele)
{
    int position;
    if (linearSearch(student, ele.student_name, &position) == 1)
        cout<<"Element found."<<endl;
    else if (position != -1)
        student->element[position] = ele;
    else return 0;
    return 1;
}

int linearDelete(pHashDictionary student, char * key)
{
    int position;
    if (linearSearch(student, key, &position) == 1)
    {
        cout<<"Deletion completed."<<endl;
        strcpy(student->element[position].student_ID, "0");
        strcpy(student->element[position].student_name, "0");
        return 1;
    }
    cout<<"Failed to find this student."<<endl;
    return 0;
}

void input_file(ifstream &in, pHashDictionary student)
{
    DicElement temp;
    strcpy(temp.student_ID, "0");
    strcpy(temp.student_name, "0");
    int d, sum = 0;
    string line;

    if (in)
        while (getline (in, line))
        {
            sum++;
            char name[10] = {"0"}, id[20] = {"0"};
            int i = 0;
            while (line[i] != ' ')
                i++;
            int j = i + 2;
            while (line[j] != ' ')
                j++;
            line.copy(id, j - i - 2, i + 2);
            while (line[j] == ' ')
                j++;
            int k = j;
            while (line[k] != ' ')
                k++;
            line.copy(name, k - j, j);

            d = h(name);
            strcpy(temp.student_ID, id);
            strcpy(temp.student_name, name);
            linearInsert(student, temp);
        }
    else
        cout<<"No such file."<< endl;
    return;
}

void output_Dic(pHashDictionary student)
{
    for (int i = 0; i < student->m; i++)
        if ((string)student->element[i].student_ID != "0")
            cout<<student->element[i].student_ID<<" "<<student->element[i].student_name<<endl;
}

int main()
{
    collipse = 0;

    int position;
    pHashDictionary student;
    char Find_name[10];

    cout<<"Input the name you want to find: ";
    cin>>Find_name;
    student = createEmptyDictionary(1000);
    ifstream in("list.txt");
    input_file(in, student);
    if(linearSearch(student, Find_name, &position))
        cout<<student->element[position].student_name<<"'s student ID is: "<<student->element[position].student_ID<<endl;

    DicElement freshman;
    cout<<"\nInput the freshman's student ID and his/her name: ";
    cin>>freshman.student_ID>>freshman.student_name;
    if(linearInsert(student, freshman))
        cout<<"Insertion completed."<<endl;

    char Delete_name[10];
    cout<<"\nInput the name you want to eliminate: ";
    cin>>Delete_name;
    linearDelete(student, Delete_name);
    cout<<"\nThe ultimate student list is: "<<endl;
    output_Dic(student);

    cout<<"\nThe number of collision is: "<<collipse<<endl;
}
