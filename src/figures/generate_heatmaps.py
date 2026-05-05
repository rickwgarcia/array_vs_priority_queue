"""
Heatmap figures for the array vs min-heap Dijkstra implementations.

Reads ../ablations/results.csv and writes:
  - runtime_heatmap.png                 (avg_us)
  - memory_heatmap.png                  (total_kb: algorithm + graph storage)
  - memory_heatmap_algorithm.png        (algo_kb: working set during shortest_path)
  - memory_heatmap_datastructure.png    (graph_kb: persistent graph storage)

Each figure has two side-by-side panels: array on the left, heap on the right,
sharing a common color scale so the two implementations can be compared directly.

The "Array" panel pairs each density with the conventional array-Dijkstra storage:
GraphList (adjacency list) for sparse, GraphMatrix (adjacency matrix) for dense.
The "Min-Heap" panel uses GraphPriorityQueue (adjacency list) for both densities.
"""

from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

HERE = Path(__file__).resolve().parent
CSV_PATH = HERE.parent / "ablations" / "results.csv"

DENSITY_ORDER = ["sparse", "dense"]
V_ORDER = [100, 500, 1000, 2000, 5000]

# Per-panel mapping: which implementation row to read for each density column.
ARRAY_IMPL_BY_DENSITY = {"sparse": "GraphList", "dense": "GraphMatrix"}
HEAP_IMPL_BY_DENSITY = {"sparse": "GraphPriorityQueue", "dense": "GraphPriorityQueue"}

ARRAY_XTICK_LABELS = ["sparse\n(adj list)", "dense\n(adj matrix)"]
HEAP_XTICK_LABELS = ["sparse\n(adj list)", "dense\n(adj list)"]


def pivot_mixed(df: pd.DataFrame, impl_by_density: dict, value_col: str) -> pd.DataFrame:
    columns = {}
    for density, impl in impl_by_density.items():
        sub = df[(df["implementation"] == impl) & (df["density_label"] == density)]
        columns[density] = sub.set_index("V")[value_col]
    table = pd.DataFrame(columns)
    return table.reindex(index=V_ORDER, columns=DENSITY_ORDER)


def draw_heatmap(ax, data: pd.DataFrame, title: str, vmin: float, vmax: float,
                 fmt: str, cmap: str, xtick_labels: list, hide_y: bool = False):
    im = ax.imshow(
        data.values,
        aspect="auto",
        cmap=cmap,
        vmin=vmin,
        vmax=vmax,
        origin="upper",
    )
    ax.set_xticks(range(len(DENSITY_ORDER)))
    ax.set_xticklabels(xtick_labels)
    if hide_y:
        ax.set_yticks([])
    else:
        ax.set_yticks(range(len(V_ORDER)))
        ax.set_yticklabels(V_ORDER)
        ax.set_ylabel("Vertices (V)")
    ax.set_xlabel("Density")
    ax.set_title(title)

    # Sequential cmaps (Blues, Reds): high values = dark cells → white text reads better.
    midpoint = (vmin + vmax) / 2
    for i in range(data.shape[0]):
        for j in range(data.shape[1]):
            val = data.values[i, j]
            ax.text(
                j, i,
                format(val, fmt),
                ha="center", va="center",
                color="white" if val > midpoint else "black",
                fontsize=9,
            )
    return im


def make_figure(df, value_col, fmt, suptitle, out_path, cmap):
    array_table = pivot_mixed(df, ARRAY_IMPL_BY_DENSITY, value_col)
    heap_table = pivot_mixed(df, HEAP_IMPL_BY_DENSITY, value_col)

    vmin = float(min(array_table.values.min(), heap_table.values.min()))
    vmax = float(max(array_table.values.max(), heap_table.values.max()))
    if vmin == vmax:  # avoid degenerate color scale when all values are equal
        vmax = vmin + 1.0

    fig, axes = plt.subplots(1, 2, figsize=(11, 7), gridspec_kw={"wspace": 0.15})
    draw_heatmap(axes[0], array_table, "Array",
                 vmin, vmax, fmt, cmap, xtick_labels=ARRAY_XTICK_LABELS)
    draw_heatmap(axes[1], heap_table, "Min-Heap",
                 vmin, vmax, fmt, cmap, xtick_labels=HEAP_XTICK_LABELS, hide_y=True)

    fig.suptitle(suptitle, fontsize=13)
    fig.savefig(out_path, dpi=150, bbox_inches="tight")
    plt.close(fig)
    print(f"wrote {out_path}")


def main():
    df = pd.read_csv(CSV_PATH)

    make_figure(
        df,
        value_col="avg_us",
        fmt=".0f",
        suptitle="Dijkstra average runtime over 5 trials",
        out_path=HERE / "runtime_heatmap.png",
        cmap="Blues",
    )

    make_figure(
        df,
        value_col="total_kb",
        fmt="d",
        suptitle="Dijkstra total memory (algorithm + graph storage)",
        out_path=HERE / "memory_heatmap.png",
        cmap="Reds",
    )

    make_figure(
        df,
        value_col="algo_kb",
        fmt="d",
        suptitle="Dijkstra algorithm working set",
        out_path=HERE / "memory_heatmap_algorithm.png",
        cmap="Reds",
    )

    make_figure(
        df,
        value_col="graph_kb",
        fmt="d",
        suptitle="Dijkstra graph storage",
        out_path=HERE / "memory_heatmap_datastructure.png",
        cmap="Reds",
    )


if __name__ == "__main__":
    main()
