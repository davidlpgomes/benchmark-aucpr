#!/bin/bash

ws=(1000 2000 5000 10000 50000)
csv="results.csv"

echo 'W,TIME_BATCH,TIME_ROLLING,RATIO' > $csv

for w in ${ws[@]}
do
    echo $(date)
    echo "W: $w"

    echo -n "$w," >> $csv

    result="$(./bench -f scores.csv -w $w)"
    echo "$result"

    echo "$result" | grep "Batch" | cut -d' ' -f2 | xargs echo -n >> $csv
    echo -n "," >> $csv

    echo "$result" | grep "Rolling" | cut -d' ' -f2 | xargs echo -n >> $csv
    echo -n "," >> $csv

    echo "$result" | grep "Ratio" | cut -d' ' -f2 | xargs echo >> $csv

    echo ""
done
