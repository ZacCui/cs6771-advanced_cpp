#!/bin/sh

for i in {1,2,3,4,5,6,7,8m,8c,9m,9c,10,11,12,13}
do
	wget -q "http://www.cse.unsw.edu.au/~abadim/CS6771_Ass3/test$i.cpp"
	wget -q "http://www.cse.unsw.edu.au/~abadim/CS6771_Ass3/result$i.txt"
done