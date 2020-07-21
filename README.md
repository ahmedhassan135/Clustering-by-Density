# Clustering-by-Density

The goal of this program is to cluster or extract information by grouping items into cohesive groups.
this program uses undirected graphs to represent the problem as a network. The main objective is to 
find such sub-graphs (group of nodes) whose density is more or equal to the given threshold value. 
Basically a node that is part of a cluster should be connected to reasonable number of edges within cluster
have many common neighbors. 

Density is measured by the formula D = (no. of edges in cluster/total no. of edges)

The program starts from a random single node as a cluster. The cluster grows by adding nodes from neighbors one by one.
as long as the density of the cluster doesn't fall below a certain threshold value, and the newly added node is connected to
a reasonble number of nodes within the cluster.


Note that the dataset is extremely large and potentially takes hours to complete, so we were instructed to truncate it to make a smaller dataset.
The dataset "PPI-I Dataset.txt" contains a Protein-Protein interaction network, to make it easier to process the program Numbering Nodes takes that list as input
and generates numbers/id for each name of the protein "Numbered PPI-I Dataset.txt". 

The smaller dataset are "Reduced PPI Dataset.txt" and their generated "Reduced Numbered PPI-I Dataset.txt", and "Temp.txt" being a very small dataset for diagnosing purposes.
