set -e
for TEST in $*
do echo ./$TEST; ./$TEST
done
