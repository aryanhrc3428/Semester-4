import random
import os

def generate_datasets():
    # --- 1. Get the directory where this script lives ---
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    # --- 2. Create full paths for the output files ---
    lin_file = os.path.join(script_dir, 'lin_dataset.txt')
    bin_file = os.path.join(script_dir, 'bin_dataset.txt')
    
    print(f"Generating files in: {script_dir}")
    
    with open(lin_file, 'w') as f_lin, open(bin_file, 'w') as f_bin:
        
        # Generate 100 arrays, size 100 to 10,000
        for i in range(1, 101):
            size = i * 100
            
            # Generate random integers
            # We use a wider range (0 to 100,000) to reduce duplicates
            raw_data = [random.randint(0, 100000) for _ in range(size)]
            
            # --- FILE 1: Linear Search (Unsorted) ---
            # Linear search works on unsorted data, so we leave it random
            lin_line = ",".join(map(str, raw_data))
            f_lin.write(lin_line + "\n")
            
            # --- FILE 2: Binary Search (Sorted) ---
            # BINARY SEARCH REQUIRES SORTED DATA
            # We sort the data before writing it to the file
            raw_data.sort()
            bin_line = ",".join(map(str, raw_data))
            f_bin.write(bin_line + "\n")

    print("Success! Generated:")
    print(f"1. {lin_file} (Unsorted arrays)")
    print(f"2. {bin_file} (Sorted arrays)")

if __name__ == "__main__":
    generate_datasets()