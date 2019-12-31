# KMeans
This project was something I built as an assignment in my junior year of my undergrad degree. It performs a Naive Kmeans clustering operation by reading in a dataset as a csv and assigns each data point to a centroid. After following the iterative assignment steps, the number of points assigned to the centroid and the coordinates are printed to the console and an output csv file is generated that prints the data points attributes along with the centroid that it is assigned to. The output file was used by another team member to perform a K-Nearest Neighbor clustering.

# Data
The data can have however many attributes as desired, as the algorythm allocates memory for an mxn matrix, but the first row must essentially be simple metadata. The first column of the first row is the amount of datapoints and the second column is how many attributes. A [sample dataset](https://github.com/sakofeye/KMeans/blob/master/KMeans/data/faithful-Kmeans.txt) that describes Old Faithful's "eruptions." The first attribute in the sample dataset is the length of the eruption and the second attribute is the temperature in celsius. This can be used to test the code.

# Arguments and Libraries
There are three command line arguments. The first is the file that is going to be read, the second is the number of centroids to be used and lastly the name of the output file. The only library that needs to be linked is the math.h library. 
