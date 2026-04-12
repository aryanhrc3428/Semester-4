import pandas as pd
import matplotlib.pyplot as plt
import os

def plot_minmax_stats():
    # --- 1. Fix File Path ---
    # Gets the directory where THIS script is currently saved
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Joins it with the filename so it works from ANY terminal location
    csv_file = os.path.join(script_dir, 'min_max_stats.csv')

    print(f"Reading data from: {csv_file}")

    try:
        df = pd.read_csv(csv_file)
    except FileNotFoundError:
        print(f"Error: The file '{csv_file}' was not found.")
        print("Please check if the C++ program ran successfully.")
        return

    # Clean column names just in case
    df.columns = df.columns.str.strip()

    # --- 2. Process Data for Clean Plotting ---
    # We group by Function and Array_Size to handle duplicate sizes.
    # If you have multiple arrays of size 100, this takes the average comparisons for them.
    # This prevents the "vertical line" noise seen in your screenshot.
    df_clean = df.groupby(['Function', 'Array_Size'], as_index=False)['Comparisons'].mean()

    # Get unique algorithms to loop through
    algorithms = df_clean['Function'].unique()
    
    plt.figure(figsize=(10, 6))

    for algo in algorithms:
        # Filter data for this algorithm
        subset = df_clean[df_clean['Function'] == algo]
        
        # --- 3. CRITICAL FIX: Sort by Size ---
        # We must sort by Array_Size so the line connects left-to-right
        subset = subset.sort_values(by='Array_Size')
        
        # Plot
        plt.plot(subset['Array_Size'], subset['Comparisons'], 
                 marker='o', markersize=4, label=algo, linewidth=1.5)

    # --- 4. Chart Styling ---
    plt.title('Min-Max Algorithms: Comparisons vs Array Size', fontsize=14)
    plt.xlabel('Array Size (N)', fontsize=12)
    plt.ylabel('Number of Comparisons', fontsize=12)
    
    # Using specific markers for clarity
    plt.legend()
    plt.grid(True, which="both", linestyle='--', alpha=0.6)

    # Save and Show
    output_img = os.path.join(script_dir, 'min_max_comparison_chart.png')
    plt.tight_layout()
    plt.savefig(output_img)
    print(f"Chart saved successfully to: {output_img}")
    plt.show()

if __name__ == "__main__":
    plot_minmax_stats()