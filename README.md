# Page-Replacement-Algo-Visualizer

## Features
- FIFO (First-In-First-Out)

  - Maintains the order of insertion
  - Removes the oldest element when cache is full
  - Simple to implement but doesn't consider usage frequency

- LRU (Least Recently Used)

  - Tracks the usage of each element
  - Removes the least recently used element when cache is full
  - More efficient for real-world usage patterns
  - Slightly more complex implementation

- Statistics Tracked

  - Cache Hits
  - Cache Misses
  - Hit Rate (%)
  - Miss Rate (%)

## Customization
- Web Version  <br/>
You can modify the following parameters in script.js:
  - Default cache size (currently set to 3)
  - Default algorithm (currently set to 'FIFO')

- C++ Version <br/>
You can modify these parameters in cache.cpp:
  - Cache size (modify cacheSize variable)
  - Test sequence (modify sequence vector)

## Acknowledgments

Inspired by various Paging replacement algorithm visualizations<br/>
Built for educational purposes to help understand paging concepts<br/>
Designed to be extensible for adding more replacement algorithms<br/>

## Support
If you found this helpful, please star the repository and feel free to contribute or report issues.

## For C++ visualization:
    g++ cache.cpp -o cache
    ./cache 

# Author
Nishtha Doshi
