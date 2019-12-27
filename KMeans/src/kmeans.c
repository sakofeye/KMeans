/*
 * kmeans.c
 *
 *  Created on: Sep 20, 2017
 *      Author: isak
 */
#include<stdio.h>
#include <stdlib.h>
#include<math.h>
int k;
double **centroids;
double **distanceMatrix;
int *label;
int *centDist;
int atoi(const char *str);
double **malloc_array(int m, int n);
void **fillCentroids(double **data, double **centroids, int k, int numAttr);
void **calculateTotalDistance(double **data, double **centroids, double **distanceMatrix, int numItems,
		int numAttr, int k);
void *assignLabel(int *label, double **distance, int numItems, int k);
void free_matrix(int n1, double **a);
void free(void *ptr);
void *centroidDistribution(int *centDist, int *label, int numItems, int k);
void *malloc(size_t size);
double calculateDistance(int numAttr, double *tempDist);
double pow(double x, double y);
void *memset(void *str, int c, size_t n);
double sqrt(double x);
void free(void *ptr);

/**
 * Helper that allocates memory for an mxn dimensional array
 */
double **malloc_array(int m, int n) {
	if (m == 0 || n == 0) {
		printf("Invalid Argument\n");
		exit(1);
	}
	double **mat = malloc(m * sizeof(double*));
	if (m > 0 && n > 0) {
		for (int i = 0; i < m; i++) {
			mat[i] = malloc(n * sizeof(double));
		}
	return mat;
	}else {
		return NULL;
	}
}

/**
 * Helper to fill centroids array with pseudorandom data points from the data matrix
 */
void **fillCentroids(double **data, double **centroids, int k, int numAttr) {
	if (k > 0 && numAttr > 0) {
		for (int i = 0; i < k; i++){
			for (int j = 0; j < numAttr; j++) {
				centroids[i][j] = (double)data[i+4][j];
			}
		}
	}
	else {
		printf("Invalid Parameters\n");
	}
}
/**
 * Calculates distance between the data point and centroid
 * and stores it in a matrix
 */
void **calculateTotalDistance(double **data, double **centroids, double **distanceMatrix, int numItems,
		int numAttr, int k) {
	if (data == NULL || centroids == NULL || distanceMatrix == NULL || numItems == 0 || numAttr == 0 || k == 0) {
		printf("Invalid argument\n");
		exit(1);
	}
	double *tempDist = malloc(numAttr * sizeof(double));
	for (int i = 0; i < numItems; i++) {
		for (int m = 0; m < k; m++) {
			for (int j = 0; j < numAttr; j++) {
				tempDist[j] = pow((data[i][j] - centroids[m][j]),2);
			}
			distanceMatrix[i][m] = (double)calculateDistance(numAttr, tempDist);
			for (int i = 0; i < numAttr; i++) {
				tempDist[i] = 0;
			}
		}
	}
free(tempDist);
}
/**
 * Calculates the distance between two points
 */
double calculateDistance (int numAttr, double *tempDist) {
	if (numAttr == 0 || tempDist == NULL) {
		printf("Invalid Arguments\n");
		exit(1);
	}
	double sumOfDist = 0;
	for (int i = 0; i < numAttr; i++) {
		sumOfDist +=  (double)tempDist[i];
	}
	return (double)sqrt(sumOfDist);
}
/**
 * Assigns the centroid closest to eah data point datapoint
 */
void *assignLabel(int *label, double **distance, int numItems, int k) {
	if (distance == NULL || label == NULL || numItems == 0 || k == 0) {
			printf("Invalid argument\n");
			exit(1);
		}
	double min;
	for (int i = 0; i < numItems; i++) {
		min = distance[i][0];
		for (int j = 0; j < k; j++) {
			if (distance[i][j] < min) {
				min = distance[i][j];
				label[i] = j;
			}
		}
	}
}
/**
 * Calculates the averages of the data points at each centroid and sets the centroid to the averaged
 * point.
 */
double **avgCentroids(int *label, double **data, double **centroids, int numItems, int numAttr, int k) {
	if (data == NULL || centroids == NULL || label == NULL || numItems == 0 || numAttr == 0 || k == 0) {
			printf("Invalid argument\n");
			exit(1);
		}
	int *count = malloc(k * sizeof(int));
	double *sum = malloc(numAttr * sizeof(double));
	for (int i = 0; i < numItems; i++) {
		for (int j = 0; j < k; j++) {
			if (label[i] == j) {
				count[j]++;
				for (int m = 0; m < numAttr; m++) {
					sum[m] += data[i][m];
				}
			}
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < numAttr; j++) {
			centroids[i][j] = sum[j] / count[i];
		}
	}
	free(count);
	free(sum);
	return centroids;
}
/**
 * Free's the matrix
 */
void free_matrix(int n1, double **a) {
	if (n1 == 0 || a == NULL) {
			printf("Invalid argument\n");
			exit(1);
		}
	if (n1 > 0) {
		for (int i = 0; i < n1; i++) {
			free(a[i]);
		}
		free(a);
	}
	else {
		printf("Invalid Input!\n");
	}
}
/**
 * Determines the distribution of the centroids among the data points
 */
void *centroidDistribution(int *centDist, int *label, int numItems, int k) {
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < numItems; j++) {
			if (label[j] == i) {
				centDist[i]++;
			}
		}
	}
}
int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("Error in program\n");
	}
	//Pass in the second argument which is the number of centroids
	k = atoi(argv[2]);
	if (k == 0) {
		printf("Invalid Input\n");
		exit(1);
	}
	//Open and read the file that is passed as the first argument
	FILE *dataFile = fopen(argv[1], "r");
	if (dataFile == NULL) {
		printf("Error reading file\n");
		exit(1);
	}
	//Scans the file and initializes the variables of numItems and numAttr
	int numItems, numAttr;
	fscanf(dataFile, "%d", &numItems);
	fscanf(dataFile, "%d", &numAttr);
	printf("numItems: %d numAttr: %d\n", numItems, numAttr);
	//Allocates memory for a matrix for the data that is passed from dataFile
	//Then passes in the data from the file to the matrix
	double **data = malloc_array(numItems, numAttr);
	for (int i = 0; i < numItems; i++) {
		for (int j = 0; j < numAttr; j++) {
			double currData;
			fscanf(dataFile, "%lf", &currData);
			data[i][j] = currData;
		}
	}
	centroids = malloc_array(k, numAttr);
	distanceMatrix = malloc_array(numItems, k);
	label = malloc(numItems * sizeof(int));
	fillCentroids(data, centroids, k, numAttr);
	double **newCentroids = malloc_array(k, numAttr);
	int count = 0;
	while (count < k) {
		calculateTotalDistance(data, centroids, distanceMatrix, numItems, numAttr, k);

		assignLabel(label, distanceMatrix, numItems, k);
		newCentroids = avgCentroids(label, data, centroids, numItems, numAttr, k);
		//checks the new and initial centroid matrices to determine if the centroids were relocated
		for (int i = 0; i < k; i++) {
			int sim = 0;
			for (int j = 0; j < numAttr; j++) {
				if (newCentroids[i][j] == centroids[i][j]) {
					sim++;
				}
				if (sim == numAttr) {
					count++;
				}
			}
		}
		//if the centroids have moved, sets the old centroid matrix to the new matrix
		centroids = newCentroids;
	}
	centDist = malloc(k * sizeof(int));
	for (int i = 0; i < k; i++) {
		centDist[i] = 0;
	}
	centroidDistribution(centDist, label, numItems, k);
	//prints the distribution of the centroids nd the centroids coordinates
	for (int i = 0; i < k; i++) {
		printf("Number of points assigned to centroid %d = %d\n", i, centDist[i]);
		printf("The coordinates of centroid %d = ", i);
		for(int j = 0; j < numAttr; j++) {
			printf("%lf ", centroids[i][j]);
		}
		printf("\n");
	}
	//Prints the root mean squared of the data points and the centroid assigned to it
	double min;
	for (int i = 0; i < numItems; i++) {
		if (i < 11) {
			printf("The distance from datapoint %d to assigned centroid is ", i);
			for (int j = 0; j < k; j++) {
				if (distanceMatrix[i][j] < distanceMatrix[i][0]) {
					min = distanceMatrix[i][j];
				}
			}
			printf("%lf\n", min);
		}

		}
	printf("etc...\n");
	//Opens to write to the file passed in as the third command line argument
	FILE *output = fopen(argv[3], "w");
	if (output == NULL) {
		printf("Error writing to file.");
		exit(1);
	}
	fprintf(output, "%d %d %d\n", numItems, numAttr + 1, k);
	for (int i = 0; i < numItems; i++) {
		for(int j = 0; j < numAttr; j++) {
			fprintf(output, "%lf ", data[i][j]);
		}
		fprintf(output, "%d\n", label[i]);
	}
	fclose(output);
	free(label);
	free_matrix(numItems, data);
	free_matrix(k, centroids);
	free_matrix(numItems, distanceMatrix);
	free(centDist);
}





