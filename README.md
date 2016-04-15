IEOR 4739 -- HW5: better rebalancing

In this homework set you will extend the P& L computation in HW4 as follows:

(a) Compute a portfolio using robust portfolio optimization (you can use my code -- but you need to choose gamma and Gamma). Alternatively, use the chance-constrained version. In either case, make sure to choose a large enough lambda, through trial and error, so that your portfolio has many names.

(b) Compute a portfolio using robust portfolio optimization (you can use Now run the P&L simulation using rebalancing every three months -- any gains or costs are reinvested into the portfolio so as to keep the same "x" positions, as explained in class. You need to output the average (over the simulations) of the mean daily portfolio return and daily variance of return. 


#### Instructions:

```
cd part-a/pnl
make
./pnl
```

It will run 1 million simulations and print out each of the run id, portfolio value, and porfolio return. Lastly, it will calculate the avg_value and avg_return.

#### Output:

```
<!-- lines omitted -->
run 999998: portfolio return: 0.000457346
run 999999: portfolio value: 1.24834e+10
run 999999: portfolio return: 0.000449826
Average value: 1.25358e+10
Average return: 0.000465522
```
