# IEOR 4739 -- HW6: Trading Impact Model (tim)

UNI: tec2123

### Setup (You need Go, Redis(TCP and Queue), and gcc)
```
go get "github.com/jrallison/go-workers"
make #this will create client and worker binary in the root directory of folder
```
### Run worker
```
redis-server # start queueing server
export LD_LIBRARY_PATH=. 
./worker # start worker

```
### Client Usage
```
./client -model=deterministic -alpha=0.001 -shares=1000 -periods=10
```