#!/usr/bin/env python3
import csv
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import sys
import os

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

S_EXACT = 0.9445171859

def read_csv(filename):
    n_values = []
    s_est = []
    abs_err = []
    rel_err = []
    
    with open(filename, 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            n_values.append(int(row['N']))
            s_est.append(float(row['S_est']))
            abs_err.append(float(row['abs_err']))
            rel_err.append(float(row['rel_err']))
    
    return n_values, s_est, abs_err, rel_err

wide_n, wide_s, wide_abs, wide_rel = read_csv('../data/results_wide.csv')
tight_n, tight_s, tight_abs, tight_rel = read_csv('../data/results_tight.csv')

plt.figure(figsize=(10, 6))
plt.plot(wide_n, wide_s, 'b-', label='Wide', linewidth=2)
plt.plot(tight_n, tight_s, 'r-', label='Tight', linewidth=2)
plt.axhline(y=S_EXACT, color='g', linestyle='--', label=f'Exact ({S_EXACT:.10f})', linewidth=2)
plt.xlabel('N (количество точек)', fontsize=12)
plt.ylabel('Площадь', fontsize=12)
plt.title('Зависимость площади от N', fontsize=14, fontweight='bold')
plt.legend(fontsize=12)
plt.grid(True, alpha=0.3)
plt.xscale('log')
plt.tight_layout()
plt.savefig('../plots/area_vs_n.png', dpi=300, bbox_inches='tight')
plt.close()
print("Сохранён график: plots/area_vs_n.png")

plt.figure(figsize=(10, 6))
plt.plot(wide_n, wide_rel, 'b-o', label='Wide', markersize=4, linewidth=2)
plt.plot(tight_n, tight_rel, 'r-s', label='Tight', markersize=4, linewidth=2)
plt.xlabel('N (количество точек)', fontsize=12)
plt.ylabel('Относительная ошибка', fontsize=12)
plt.title('Зависимость относительной ошибки от N', fontsize=14, fontweight='bold')
plt.legend(fontsize=12)
plt.grid(True, alpha=0.3)
plt.xscale('log')
plt.yscale('log')
plt.tight_layout()
plt.savefig('../plots/error_vs_n.png', dpi=300, bbox_inches='tight')
plt.close()
print("Сохранён график: plots/error_vs_n.png")

print("\nГрафики успешно построены!")

