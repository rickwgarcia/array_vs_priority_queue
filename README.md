# dijkstra_array_vs_queue

Comparison of array-based vs min-heap Dijkstra implementations.

## Directory structure

```
.
├── README.md
├── assignment/
│   └── CS_361-Project-2.pdf
└── src/
    ├── eval.cpp                       # correctness check on small graphs
    ├── graph_list.h                   # adjacency list + array Dijkstra
    ├── graph_matrix.h                 # adjacency matrix + array Dijkstra
    ├── graph_priority_queue.h         # adjacency list + min-heap Dijkstra
    ├── priority_queue.h               # min-heap implementation
    ├── measure.h                      # timing helper for eval
    ├── ablations/
    │   ├── size_ablations.cpp         # runtime + memory benchmarks
    │   ├── generate_graphs.h          # random graph generator
    │   ├── results.csv                # benchmark output
    │   └── graph_stats.csv            # generated graph stats
    └── figures/
        ├── generate_heatmaps.py       # plots from results.csv
        ├── runtime_heatmap.png
        ├── memory_heatmap.png
        ├── memory_heatmap_algorithm.png
        └── memory_heatmap_datastructure.png
```

## Run eval

```sh
cd src
g++ eval.cpp -o eval
./eval
```

## Run ablations and generate figures

```sh
cd src/ablations
g++ size_ablations.cpp -o size_ablations
./size_ablations
cd ../figures
python generate_heatmaps.py
```
