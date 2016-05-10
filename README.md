IEOR 4739 -- HW6: Trading Impact Model (tim)
UNI: tec2123

In this homework set you will extend the P& L computation in HW4 as follows:

(a) Compute a portfolio using robust portfolio optimization (you can use my code -- but you need to choose gamma and Gamma). Alternatively, use the chance-constrained version. In either case, make sure to choose a large enough lambda, through trial and error, so that your portfolio has many names.

### Goal

Create new input for pnl using rob

Inside ``part-a/src``, run

```
make rob
../bin/rob input.txt 10.0 0.2 0.5
```

This will generate a ``positions.txt`` file in your local directory compatible with ``part-b``'s pnl simulation

(b) Compute a portfolio using robust portfolio optimization (you can use Now run the P&L simulation using rebalancing every three months -- any gains or costs are reinvested into the portfolio so as to keep the same "x" positions, as explained in class. You need to output the average (over the simulations) of the mean daily portfolio return and daily variance of return. 

### Changelog
Added rebalancing every 90 days
Added code to update the weight by modifying the default rebalancing code

In side ``part-b/src``, run

```
make
./pnl
```
or if you want to output the stdout to a file, run:

```
./pnl >> outputs.txt
```
An ``outputs.txt`` is committed with this repo as well.

* Notice: I should have made the ``runs_count``, ``filename`` and ``input file paths`` dynamically set by command line args


```
<!-- lines omitted -->
Solved with dual simplex
Solved in 693 iterations and 2.23 seconds
Infeasible model
run 9: portfolio value: 1.06606e+10
run 9: portfolio return: 0.000723253
Average value: 7.50714e+09
Average return: -0.00219775
```
