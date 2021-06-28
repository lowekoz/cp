for((i = 1; i <= 10000; ++i)); do
    echo $i
    ./gen $i > inp
    ./a < inp > out1
    ./brute < inp > out2
    diff -w out1 out2 || break
done