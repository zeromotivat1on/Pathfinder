# Pathfinder
A program that finds all the shortest paths between all the islands, using information about the bridges that connect them. The program:

1. Reads data from a file. Its name is specified as a command-line argument
2. Finds all the shortest paths between each combination of two islands
3. Prints the paths using the FIFO (first) rule for the islands to the standard output.

Input file description:

1. The first line in the file is the number of islands
2. The remaining lines describe the distance between the two islands, one per line. Eachline consists of two islands, the length of the bridge between them and a newline in a format: "island1-island2,length_of_bridge":

–the names of the islands contain only alphabetic characters and cannot be emptyor identical\
–the length of the bridge contains only numbers, cannot be empty and has a positivevalue\
–the sum of the lengths of all bridges in the file does not exceed INT_MAX
