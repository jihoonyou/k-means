#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define BUFFER_SIZE 1000

struct Coord {
    float x;
    float y;
};


float e_dist(float centr_x, float centr_y, float data_x, float data_y) {
    float diff_x = centr_x - data_x;
    float diff_y = centr_y - data_y;
    float dist = sqrt(diff_x*diff_x + diff_y*diff_y);
    return dist;
}

int find_closest(struct Coord *centeroids, struct Coord *data,int data_loc, int cluster) {
    
    int belonged = 0;
    float min = e_dist(centeroids[belonged].x, centeroids[belonged].y, data[data_loc].x, data[data_loc].y);
    float dist;
    for(int i = 1; i < cluster; i++){
        dist = e_dist(centeroids[i].x, centeroids[i].y, data[data_loc].x, data[data_loc].y);
        if(dist < min){
            min = dist;
            belonged = i;
        }
    }
    return belonged; 

}


void kmeans(int iter, int cluster, struct Coord *dataPointer, int numberOfData) {


    //set centeroid according to number of cluster
    struct Coord centeroids[cluster];
    //belonged clusters
    int clusters[numberOfData];
    //number counter for cluster
    int num[cluster];
    float mean_x[cluster];
    float mean_y[cluster];
    struct timeval s_time, e_time, time;
    

    gettimeofday(&s_time, NULL);

    //set initial centeroids
    for(int i = 0; i < cluster; i++) {
        centeroids[i] = dataPointer[i];
    }


    for(int y = 0; y < iter; y++)
    {
        //reset arrays
        for(int k = 0; k < cluster; k++) {
            num[k] = 0;
            mean_x[k] = 0.0;
            mean_y[k] = 0.0;
        }    
       
        //find closest cluster on each point
        for(int j = 0; j < numberOfData; j++){
            clusters[j] = find_closest(centeroids, dataPointer, j, cluster);
            mean_x[clusters[j]] += dataPointer[j].x;
            mean_y[clusters[j]] += dataPointer[j].y;
            num[clusters[j]]++;
        }

        for(int h = 0; h < cluster; h++) {
            centeroids[h].x = mean_x[h]/num[h];        
            centeroids[h].y = mean_y[h]/num[h];
        }
    }

    gettimeofday(&e_time, NULL);

    time.tv_usec = e_time.tv_usec - s_time.tv_usec;
    
    if(time.tv_usec < 0) {
        time.tv_usec = time.tv_usec + 1000000;
    }
    
    printf("%ld microseconds\n", time.tv_usec);

    for(int z = 0; z < numberOfData; z++) {
        printf("%i\n", clusters[z]);
    }

}


int main() {
    char str[BUFFER_SIZE];
    int numberOfTest;
    int numberOfIteration;
    int numberOfCluster;
    int numberOfData;
    struct Coord *coordArr;
    //number of test case T
    numberOfTest = atoi(fgets(str, sizeof str, stdin));

    for(int i = 0; i < numberOfTest; i++) {
        //number of iterations
        numberOfIteration = atoi(fgets(str, sizeof str, stdin));
        //number of Klusters
        numberOfCluster = atoi(fgets(str, sizeof str, stdin));
        //number of data objects
        numberOfData = atoi(fgets(str, sizeof str, stdin));
        //array of struct coord x and y
        coordArr = malloc(numberOfData * sizeof(struct Coord)); 
        
        //loop through data object and assign to coord struct 
        for(int j = 0; j < numberOfData; j++) {
            char *dataXY = fgets(str, sizeof str, stdin);
            char *pch;
            
            pch = strtok(dataXY, " ");
            coordArr[j].x = atof(pch);
            
            pch = strtok(NULL, " ");
            coordArr[j].y = atof(pch);
        }
        printf("Test Case #%i\n", i);

        kmeans(numberOfIteration, numberOfCluster, coordArr, numberOfData);
        free(coordArr);
    }
    return 0;
}


