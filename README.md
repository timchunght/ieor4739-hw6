# IEOR 4739 HW#4 -- Explaining asset returns using assets

Due March 28, 2016

*(a) Extend the principal components code we developed in class so as to compute the top ten eigenvalues and corresponding eigenvectors. Run it on the Russell-1000 covariance matrix (computed using qas many days as you have). 

From the same directory as this README, run:
```
sh part-a/run.sh
```

Results:

```
ID 0 eigenvalue 0  0.0832175!
ID 0 eigenvalue 1  0.0217713!
ID 0 eigenvalue 2  0.018991!
ID 0 eigenvalue 3  0.0181188!
ID 0 eigenvalue 4  0.00789802!
ID 0 eigenvalue 5  0.00628969!
ID 0 eigenvalue 6  0.00431537!
ID 0 eigenvalue 7  0.00379329!
ID 0 eigenvalue 8  0.00371618!
ID 0 eigenvalue 9  0.00312891!

real	0m6.138s
user	0m5.923s
sys	  0m0.110s
```

*(b)Compare your code from (a) with the best numpy implementation you can find. Do they agree (i.e. are the eigenvalues and eigenvectors about the same)? Which one is faster? Note that numpy comes with several operators already. 

From the same directory as this README, run:
```
python part-b/pca.py
```

Results (There are 947 eigen values):

```
time taken: 7.82972502708s
```

*(c) Take a portfolio allocation (percentages) you computed for the Russell-1000 using the porfolio optimization algorithm you developed. Convert them into stock quantities as per the first day prices, using a total of one billion dollars for the initial portfolio value. This exercise asks you to run the P & L analysis for the resulting portfolio, without any rebalancing (so the quantities you have on day 1 are the quantities you will have at the end). You will run a number of simulations of this analysis, using random perturbations of the prices. On each run you will report the final portfolio value, and the average daily portfolio return. This program should be in C.

The random perturbations are constructed as follows. Consider an asset k. Suppose that over the entire history, the average change (up or down) for the price of asset k (day over day) is delta[k], and the standard deviation for the change of price of asset k (again day over day) is sigma[k]. Then, on each day t, you change the price of asset k by a normally distributed random variable of mean delta[k] and standard deviation sigma[k]. This is done independently for all assets, and for all days in the history. This ensemble of new prices constitutes one sample, on which you need to perform the P & L. 

Do this on at least one million samples. Feel free to use a multithreaded setup if you have a multicore machine. 
Note: you may use the "Box-Muller" transform to draw normally distributed values. 


