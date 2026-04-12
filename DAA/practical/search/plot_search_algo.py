import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_search_stats():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    csv_file = os.path.join(script_dir, 'search_comparisons.csv')

    print(f"Reading data from: {csv_file}")

    try:
        df = pd.read_csv(csv_file)
    except FileNotFoundError:
        print(f"Error: '{csv_file}' not found.")
        print("Run 1_binary.cpp and 2_linear.cpp first.")
        return

    df.columns = df.columns.str.strip()
    df_clean = df.groupby(['search algo', 'array_size'], as_index=False)['no._of_comparisons'].mean()

    algos = df_clean['search algo'].unique()
    plt.figure(figsize=(10, 6))

    for algo in algos:
        subset = df_clean[df_clean['search algo'] == algo]
        subset = subset.sort_values(by='array_size')
        
        plt.plot(subset['array_size'], subset['no._of_comparisons'], 
                 marker='o', label=algo, linewidth=2)

    plt.title('Search Algorithms: Comparisons vs Array Size (Worst Case)', fontsize=14)
    plt.xlabel('Array Size (N)', fontsize=12)
    plt.ylabel('Number of Comparisons', fontsize=12)
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.6)

    output_img = os.path.join(script_dir, 'search_comparison_chart.png')
    plt.tight_layout()
    plt.savefig(output_img)
    print(f"Chart saved to: {output_img}")
    plt.show()

if __name__ == "__main__":
    plot_search_stats()