#include <stdio.h>
#include <unistd.h>		/* find current location */
#include <stdlib.h>     /* srand, rand */
#include <string.h>     /* strcat */
#include <math.h>		/* math calc */

#define INPUT_FILE_NAME "input.txt"
#define NUMCITY 4   	//Random city no - in case of using andom geneation 'OR' MAX No of input City
#define LANDSIZE 100	//Max value during random value generation
#define square(A) ((A) * (A))

typedef int Loc[2];

void Input(Loc cities[]);									//Take input from file of Loc
void generate(Loc cities[]);								//generate random city
void display_cities(Loc cities[]);							//display all the citys
float distance(Loc city1,Loc city2);						//Find Distance between 2 city
void copy_Route(Loc citiesDest[], Loc citiesSource[]);		//Copy Routeed cities
void copy_City(Loc dest, Loc source);						//Copy one city to another
void swap_cities(Loc city1, Loc city2);					//Swap 2 city
void permutations(Loc cities[], int numCities);				//Put all elements in pivot - before starting a new itaration
void scramble(Loc cities[], Loc *pivot, int numCities);	//Generate all combination by brute force approach
void target_function(Loc cities[]);						//Get final smallest value by comparison
float Route_length(Loc cities[]);							//Get total Route length
void form(Loc cities[]);

float shortestRouteLength;
Loc shortestRoute[NUMCITY];
int total_no_of_input=NUMCITY;

int main()
{

	Loc cities[NUMCITY];

	//Input(cities);
	printf("Hello!\n\n");
	//generate(cities);
	form(cities);
	printf("The cities are:\n");
	display_cities(cities);
	//printf("Total No of Input = %d\n",total_no_of_input);



	shortestRouteLength = Route_length(cities);		//Generate initial value - not final
	copy_Route(shortestRoute, cities);
	printf("Generating permutations:\n");
	scramble(cities, cities, total_no_of_input);
	printf("The shortest route is:\n");
	display_cities(shortestRoute);
	printf("Length is: %f\n", shortestRouteLength);
	//float dist=distance(cities[0],cities[1])+distance(cities[1]+cities[2]);
//	printf("\nTotal distance=%f",dist);


	//Time calculation End
	//t = clock() - t;
  	//printf ("It took %f second(s).\n",((float)t)/CLOCKS_PER_SEC);
	////////////////////////

	getchar();
	return 0;
}
void form(Loc cities[])
{
    int i;
    printf("Start entering coordinates\n");
    for(i=0;i<NUMCITY;i++)
    {
        scanf("%d",&cities[i][0]);
        scanf("%d",&cities[i][1]);
        printf("(%d %d)\n",cities[i][0],cities[i][1]);
    }
}


void generate(Loc cities[])
{
    int i, j;
    total_no_of_input=NUMCITY;
    for (i = 0; i < NUMCITY; i++)
        for (j = 0; j < 2; j++)
            cities[i][j] = rand() % LANDSIZE;
}

float Route_length(Loc cities[])
{
	int i;
	float length = 0.0;
	for(i = 0; i < total_no_of_input - 1; i++)
		length += distance(cities[i], cities[i+1]);
	length += distance(cities[total_no_of_input - 1], cities[0]);
	return length;
}

void target_function(Loc cities[])
{
    float length;
    length = Route_length(cities);
    if (length < shortestRouteLength)
    {//Longest path
        shortestRouteLength = length;
        copy_Route(shortestRoute, cities);
    }
}

/*pivot is the base address in the cities[NUMCITY] array
 *for the recursive scrambling; the only reason we also
 *pass the unchanged cities address is because we need it
 *to call the target function (which does *something* to
 *the scrambled array) at each recursive call to scramble
 */
void scramble(Loc cities[], Loc *pivot, int numCities)
{
	int i;
	Loc *newPivot;
	if (numCities <= 1)
	{ //Scrambled! Call the target function
		target_function(cities);
		return;
	}
	for (i = 0; i < numCities; i++)
	{
		newPivot = &pivot[1];
		scramble(cities, newPivot, numCities - 1);
		display_cities(cities);
		permutations(pivot, numCities);
	}
}

void permutations(Loc cities[], int numCities)
{
	int i;
	Loc tmp;
	copy_City(tmp, cities[0]);
	for (i = 0; i < numCities - 1; i++)
		copy_City(cities[i], cities[i + 1]);
	copy_City(cities[numCities - 1], tmp);
}

void copy_Route(Loc citiesDest[], Loc citiesSource[])
{
    int i;
    for (i = 0; i < NUMCITY; i++)
        copy_City(citiesDest[i], citiesSource[i]);
  //  printf("Cities...");
  //  print_cities(citiesDest);
}

void copy_City(Loc dest, Loc source)
{
    dest[0] = source[0];
    dest[1] = source[1];
}

void swap_cities(Loc city1, Loc city2)
{
    Loc tmp;
    copy_City(tmp, city1);
    copy_City(city1, city2);
    copy_City(city2, tmp);
}

float distance(Loc city1, Loc city2)
{
    float result;
    result = sqrtf((float)square(city2[0] - city1[0]) +
                 (float)square(city2[1] - city1[1]));
               //  printf("Result= %f",result);
    return result;
}

void display_cities(Loc cities[])
{
    int i;
    for (i = 0; i < total_no_of_input; i++) {
        printf("%d [%d,%d]\n",i+1, cities[i][0], cities[i][1]);

    }
    printf("\n");
}
