#!/usr/bin/env python3
import csv
from pathlib import Path

import matplotlib
import matplotlib.pyplot as plt

matplotlib.use("Agg")

S_EXACT = 0.9445171859
DATA_DIR = Path("data")
PLOTS_DIR = Path("plots")


def read_csv(filename):
    """Load Monte Carlo results from CSV into simple lists."""
    n_values, s_est, abs_err, rel_err = [], [], [], []
    with open(filename, "r") as f:
        reader = csv.DictReader(f)
        for row in reader:
            n_values.append(int(row["N"]))
            s_est.append(float(row["S_est"]))
            abs_err.append(float(row["abs_err"]))
            rel_err.append(float(row["rel_err"]))
    return n_values, s_est, abs_err, rel_err


def setup_common_style(ax, title, y_label):
    ax.set_title(title)
    ax.set_xlabel("N (log scale)")
    ax.set_ylabel(y_label)
    ax.set_xscale("log")
    ax.grid(True, which="both", linestyle="--", linewidth=0.5, alpha=0.6)
    ax.legend()


def generate_area_plot(wide_data, tight_data, output_path: Path):
    fig, ax = plt.subplots(figsize=(12, 8))
    wide_n, wide_s = wide_data
    tight_n, tight_s = tight_data

    ax.plot(wide_n, wide_s, label="Wide", color="#3465a4", linewidth=2)
    ax.plot(tight_n, tight_s, label="Tight", color="#c83c3c", linewidth=2)
    ax.axhline(S_EXACT, color="#0a7c0a", linestyle=":", linewidth=2, label="Exact")

    setup_common_style(ax, "Area vs N", "Estimated area")
    fig.tight_layout()
    fig.savefig(output_path, dpi=200)
    plt.close(fig)


def generate_error_plot(wide_data, tight_data, output_path: Path):
    fig, ax = plt.subplots(figsize=(12, 8))
    wide_n, wide_rel = wide_data
    tight_n, tight_rel = tight_data

    ax.plot(wide_n, wide_rel, label="Wide", color="#3465a4", linewidth=2)
    ax.plot(tight_n, tight_rel, label="Tight", color="#c83c3c", linewidth=2)
    ax.set_yscale("log")

    setup_common_style(ax, "Relative error vs N", "Relative error")
    fig.tight_layout()
    fig.savefig(output_path, dpi=200)
    plt.close(fig)


def main():
    PLOTS_DIR.mkdir(exist_ok=True)
    wide_n, wide_s, _, wide_rel = read_csv(DATA_DIR / "results_wide.csv")
    tight_n, tight_s, _, tight_rel = read_csv(DATA_DIR / "results_tight.csv")

    generate_area_plot(
        (wide_n, wide_s),
        (tight_n, tight_s),
        PLOTS_DIR / "area_vs_n.png",
    )
    generate_error_plot(
        (wide_n, wide_rel),
        (tight_n, tight_rel),
        PLOTS_DIR / "error_vs_n.png",
    )
    print("Графики сохранены в каталоге plots/")


if __name__ == "__main__":
    main()
