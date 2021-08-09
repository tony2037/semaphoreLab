# This lab demostrates how to use inotify + poll to implement a mechanism that makes a process to acquire the semaphore and monitor a cache file, then release the semaphore after the cache file being removed

# Usage
```
make
sh run.sh
```

after few seconds you should find that the proc1 is waiting for proc2 because proc2 is holding the semaphore.

To release the semaphore:
```
rm cache
```

you should see that the proc2 is releasing the semaphore and proc1 is then able to acquire it.
