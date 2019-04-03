#!/bin/bash

if (( $# < 1 ))
then
	echo "./merge num_of_process";
	exit;
fi

touch res

sed '1,/comp time/d' mpi_record.0 | awk '{print $1}' > res;

for (( i=0; i<$1; i++))
do
  sed '1,/comp time/d' mpi_record.$i | awk '{print $2}' > shit;
  paste res shit > res.temp;
  mv res.temp res; 
done

mv res mpi_all

rm -f res.temp res shit


