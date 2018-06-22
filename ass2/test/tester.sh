for i in $(seq 0 19);
do
  cat makefile_1  | sed "s/test_lol/test$i/" > Makefile
  make clean > /dev/null
  make > /dev/null
  echo "TEST #$i"
  ./EuclideanVectorTester

done
