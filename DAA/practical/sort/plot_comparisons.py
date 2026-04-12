import pandas as pd
import matplotlib.pyplot as plt
import os

def generate_charts():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    csv_file = os.path.join(script_dir, 'comparison.csv')
    
    print(f"Looking for file at: {csv_file}")

    try:
        df = pd.read_csv(csv_file)
    except FileNotFoundError:
        print(f"Error: The file '{csv_file}' was not found.")
        print("Please ensure 'comparison.csv' is in the same folder as this script.")
        return

    df.columns = df.columns.str.strip()
    
    algorithm_order = [
        'Insertion Sort', 
        'Merge Sort', 
        'Heap Sort', 
        'Quick Sort', 
        'Bubble Sort',
        'Selection Sort',
        'Radix Sort',
        'Count Sort'
    ]
    
    df['Algorithm'] = ''
    chunk_size = 100
    
    for i, algo_name in enumerate(algorithm_order):
        start_index = i * chunk_size
        end_index = (i + 1) * chunk_size
        
        if start_index < len(df):
            df.loc[start_index:end_index-1, 'Algorithm'] = algo_name

    charts_config = [
        ('avg_comp', 'Average Comparisons vs Array Size', 'No. of Comparisons (Average)', 'chart1_avg_comparisons.png'),
        ('min_comparisons', 'Best Case Comparisons vs Array Size', 'No. of Comparisons (Best Case)', 'chart2_best_case.png'),
        ('max_comparisons', 'Worst Case Comparisons vs Array Size', 'No. of Comparisons (Worst Case)', 'chart3_worst_case.png')
    ]

    # 6. Generate and Save Plots
    for y_col, title, y_label, filename in charts_config:
        plt.figure(figsize=(10, 6))
        
        for algo in algorithm_order:
            subset = df[df['Algorithm'] == algo]
            if not subset.empty:
                subset = subset.sort_values(by='current_arr_size')
                plt.plot(subset['current_arr_size'], subset[y_col], marker='.', label=algo)

        plt.title(title)
        plt.xlabel('Size of Array')
        plt.ylabel(y_label)
        plt.legend()
        plt.grid(True)
        
        save_path = os.path.join(script_dir, filename)
        plt.savefig(save_path)
        print(f"Generated {save_path}")
        plt.close()

if __name__ == "__main__":
    generate_charts()