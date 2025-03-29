#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cfloat>

using namespace std;

void read_distribution(const char *filename, double distribution[26])
{
    ifstream fin("distribution.txt");
    int x, i=0;
    while(!fin.eof())
    {
        fin>>x;
        distribution[i++]=x;
    }
    fin.close();
}



void compute_histogram(const char *text, double histogram[26])
{

    // histogram = frequency of each element/nr of elements

    int count[26]={0}, nrElements = 0;
    char current_char;

    for (int i=0; i<strlen(text); i++)
    {
        current_char = text[i];
        if (current_char>='A' && current_char<='Z')
            current_char = tolower(text[i]);
        count[current_char - 'a']++;
        nrElements++;
    }

    /*for (int i=0; i<26; i++)
    {
        if (nrElements>0)
            histogram[i]=(double)count[i]/nrElements;
        else
            histogram[i]=0.0;
    }*/

    for (int i=0; i<26; i++)
        histogram[i]=count[i];
}



double chi_squared_distance(const double hist1[26], const double hist2[26])
{

    // hist1 = the text to be cracked
    // hist2 = english letters histogram

    double chi_squared = 0;
    int number_of_letters = 0, expected_number;
    double next;

    for (int i=0; i<26; i++)
        number_of_letters += hist1[i];

    for (int i='a'; i<='z'; i++)
    {
        expected_number = number_of_letters * hist2[i];
        next = (double)(expected_number - hist1[i]) / hist1[i];
        chi_squared += next;
    }

    return chi_squared;
}



double euclidean_distance(const double hist1[26], const double hist2[26])
{
    double sum = 0;
    int number_of_letters = 0, expected_number;
    double next;

    for (int i=0; i<26; i++)
        number_of_letters += hist1[i];

    for (int i='a'; i<='z'; i++)
    {
        expected_number = number_of_letters * hist2[i];
        next = (double)(expected_number - hist1[i]);
        sum += next;
    }

    return sqrt(sum);
}



double cosine_distance(const double hist1[26], const double hist2[26])
{
    double sum = 0;   // numerator
    double sum1=0, sum2=0;

    double numerator, denominator;

    double cosine_calculus;

    int number_of_letters = 0, expected_number;
    double next, next1, next2;

    for (int i=0; i<26; i++)
        number_of_letters += hist1[i];

    for (int i='a'; i<='z'; i++)
    {
        expected_number = number_of_letters * hist2[i];
        next = (double)(expected_number * hist1[i]);
        sum += next;

        next1 = (double)(expected_number * expected_number);
        next2 = (double)(hist2[i] * hist2[i]);
    }

    numerator = sum;
    denominator = sqrt(sum1*sum2);

    cosine_calculus = 1 - (numerator / denominator);

    return cosine_calculus;
}



void break_caesar_cipher(const char* text, int top_shifts[], double top_distance[], double (*distance_function)(const double*, const double*))
{
    const double englishHistogram[] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1};
    double histogram[26]={0};
    double histogram_to_go[26]={0};
    double distance;
    double first, second, third;

    vector<int> first_shift, second_shift, third_shift;

    first = second = third = DBL_MAX;

    compute_histogram(text, histogram);

    vector<int> sequence;
    for (int i=0; i<26; i++)
        sequence.push_back(histogram[i]);

    for (int shift = 0; shift < 26; ++shift)
    {
        vector<int> shiftedSequence = sequence;
        std::rotate(shiftedSequence.begin(), shiftedSequence.begin() + shift, shiftedSequence.end());

        for (int i=0; i<26; i++)
            histogram_to_go[i] = shiftedSequence[i];

        distance = distance_function(histogram_to_go, englishHistogram);

        if (distance < first)
        {
            first = second = third = distance;
            first_shift = second_shift = third_shift = shiftedSequence;
        }
        else
            if (distance < second && distance != first)
            {
                second = third = distance;
                second_shift = third_shift = shiftedSequence;
            }
            else
                if (distance < third && distance != second)
                {
                    third = distance;
                    third_shift = shiftedSequence;
                }
    }

    top_distance[0] = first;  top_distance[1] = second;  top_distance[2] = third;
    for (int i=0; i<26; i++)
        top_shifts[i] = first_shift[i];
    for (int i=26; i<52; i++)
        top_shifts[i] = second_shift[i];
    for (int i=52; i<104; i++)
        top_shifts[i] = third_shift[i];

}



void showMenu()
{
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"MENU:";

    cout<<"Type 1 for read_distribution\n";
    cout<<"Type 2 fro compute_histogram\n";
    cout<<"Type 3 for chi_squared_distance\n";
    cout<<"Type 4 for euclidean_distance\n";
    cout<<"Type 5 for cosine_distance\n";
    cout<<"Type 6 for break_caesar_cipher\n";

    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"Type your choice!\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout<<"Type -1 to exit!";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

}



int main()
{
    int top_shifts[104];
    double top_distance[2];
    double Distribution[26];
    char text[] = "abcdefvhhhgchvv";

    int choice;

    while (choice != -1)
    {
        showMenu();
        cin>>choice;
        switch(choice)
        {
            case 1:
                read_distribution("distribution.txt", Distribution);
                break;
            case 2:
                compute_histogram(text, Distribution);
                break;
            case 3:
                break_caesar_cipher(text, top_shifts, top_distance, chi_squared_distance);
                break;
            case 4:
                break_caesar_cipher(text, top_shifts, top_distance, euclidean_distance);
                break;
            case 5:
                break_caesar_cipher(text, top_shifts, top_distance, cosine_distance);
                break;
            case 6:
                break_caesar_cipher(text, top_shifts, top_distance, chi_squared_distance);
                break;
            case -1:
                cout<<"Exiting...\n";
                break;
            default:
                cout<<"Wrong choice!\n";
        }
        cout<<endl;
    }

    return 0;
}