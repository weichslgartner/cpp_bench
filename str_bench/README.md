# strcat bench

benchmarking different possibilities to concat strings

Install folly: https://github.com/facebook/folly
To turn of CPU frequency scaling I used:  
```
sudo cpupower frequency-set --governor performance  
```

```
pip install conan  
mkdir build && cd build  
conan install .. --build=missing  
cmake ..  
./bin/strtest
```
![Benchmarkresults of  concatenating 3 strings with size 28 each.](img/strcat.png)

