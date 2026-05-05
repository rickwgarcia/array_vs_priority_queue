"""
Two heatmap figures for the array (GraphList) vs min-heap (GraphPriorityQueue)
Dijkstra implementations.

Reads ../ablations/results.csv and writes:
  - runtime_heatmap.png  (avg_us)
  - memory_heatmap.png   (peak_kb from getrusage's ru_maxrss delta)

Each figure has two side-by-side panels: array on the left, heap on the right,
sharing a common color scale so the two implementations can be compared directly.

NOTE: "Array implementation" is rendered using GraphList (adjacency-list + linear
min-scan). The matrix variant is excluded because the project uses GraphList
across all densities for the single-array comparison.
"""

from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

HERE = Path(__file__).resolve().parent
CSV_PATH = HERE.parent / "ablations" / "results.csv"

DENSITY_ORDER = ["sparse", "dense"]
V_ORDER = [100, 500, 1000, 2000, 5000]


def pivot_for(df: pd.DataFrame, impl: str, value_col: str) -> pd.DataFrame:
    sub = df[df["implementation"] == impl]
    table = sub.pivot(index="V", columns="density_label", values=value_col)
    return table.reindex(index=V_ORDER, columns=DENSITY_ORDER)


def draw_heatmap(ax, data: pd.DataFrame, title: str, vmin: float, vmax: float, fmt: str):
    im = ax.imshow(
        data.values,
        aspect="auto",
        cmap="viridis",
        vmin=vmin,
        vmax=vmax,
        origin="upper",
    )
    ax.set_xticks(range(len(DENSITY_ORDER)))
    ax.set_xticklabels(DENSITY_ORDER)
    ax.set_yticks(range(len(V_ORDER)))
    ax.set_yticklabels(V_ORDER)
    ax.set_xlabel("Density")
    ax.set_ylabel("Vertices (V)")
    ax.set_title(title)

    midpoint = (vmin + vmax) / 2
    for i in range(data.shape[0]):
        for j in range(data.shape[1]):
            val = data.values[i, j]
            ax.text(
                j, i,
                format(val, fmt),
                ha="center", va="center",
                color="white" if val < midpoint else "black",
                fontsize=9,
            )
    return im


def make_figure(df, value_col, fmt, suptitle, cbar_label, out_path):
    array_table = pivot_for(df, "GraphList", value_col)
    heap_table = pivot_for(df, "GraphPriorityQueue", value_col)

    vmin = float(min(array_table.values.min(), heap_table.values.min()))
    vmax = float(max(array_table.values.max(), heap_table.values.max()))
    if vmin == vmax:  # avoid degenerate color scale when all values are equal
        vmax = vmin + 1.0

    fig, axes = plt.subplots(1, 2, figsize=(8, 7))
    im_a = draw_heatmap(axes[0], array_table, "Array (GraphList)", vmin, vmax, fmt)
    draw_heatmap(axes[1], heap_table, "Min-Heap (GraphPriorityQueue)", vmin, vmax, fmt)

    cbar = fig.colorbar(im_a, ax=axes, fraction=0.04, pad=0.04)
    cbar.set_label(cbar_label)

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
        cbar_label="Avg runtime (μs)",
        out_path=HERE / "runtime_heatmap.png",
    )

    make_figure(
        df,
        value_col="peak_kb",
        fmt="d",
        suptitle="Dijkstra peak RSS delta (max over 5 trials, getrusage ru_maxrss)",
        cbar_label="Peak RSS delta (KB)",
        out_path=HERE / "memory_heatmap.png",
    )


if __name__ == "__main__":
    main()
