import csv
import requests
import time

# 1. Target the submission endpoint (Change /prefill to /formResponse)
FORM_URL = "https://docs.google.com/forms/u/2/d/1wogPcTErtcV0HS19LNsUG2R8wMoVcB9dxNi1aUbMlNM/formResponse"

# 2. Map your exact CSV headers to the Google Form Entry IDs you provided
FORM_MAPPING = {
    # SECTION 1: Demographics
    'Full Name': 'entry.957502644', 
    'Nationality/Country of origin': 'entry.1369026413',
    'Gender': 'entry.1790955068',
    'Age': 'entry.1909187122',
    'Current Program at DU': 'entry.980905620',
    'Name of the College/department': 'entry.1237127457',
    'Year of Enrollment at DU': 'entry.1099337086',
    'Current Year of Study': 'entry.623285207',
    'Accomodation type': 'entry.1933116388',
    
    # SECTION 2: Choosing DU & Impressions 
    'Why did you specifically choose Delhi University for your studies?': 'entry.1779043042',
    'What factors most influenced your decision to study in India? (Select top 3)': 'entry.1327639304', 
    'Did you apply to universities outside India?': 'entry.684617857',
    'How is DU perceived in your home country?': 'entry.1354473',
    'Before arriving, your expectations of DU were:': 'entry.1340191401',
    'Did DU meet your expectations?': 'entry.242585041',
    'Your first impression of DU campus was:': 'entry.1020768229',
    'Your first impression of Delhi city was:': 'entry.2025555619',
    'How welcoming did you find students/faculty on your first day?': 'entry.1600110084',
    
    # SECTION 3: Cultural Experience & Satisfaction 
    'Which cultural shocks did you experience? (Select all that apply)': 'entry.922273542', 
    'How long did it take to adapt to Delhi\'s culture?': 'entry.389488824',
    'What aspect of Indian culture do you appreciate most?': 'entry.1089202853',
    'How does DU\'s academic culture compare to your home country?': 'entry.1981274924',
    'What does DU do BETTER than your home country\'s universities?': 'entry.1386460733',
    'What does your home country do BETTER than DU?': 'entry.2066168067',
    'How has DU contributed to your academic growth?': 'entry.133381568',
    'Rate your interaction with DU faculty': 'entry.2095250583', 
    'How inclusive is your classroom environment?': 'entry.1099504079',
    'Are you staying in DU hostel for foreign students?': 'entry.409110305',
    'If in hostel: Rate the facilities': 'entry.421685063',
    'Have you used FSR (Foreign Students Registry) Office services?': 'entry.1311140191',
    'Rate safety as a foreign student in Delhi': 'entry.356865288',
    'What do you LOVE MOST about DU?': 'entry.1806007194',
    'What is your biggest complaint about DU?': 'entry.1637493605',
    'Would you recommend DU to students from your country?': 'entry.53645292',
    'Rate your overall DU experience': 'entry.306388001', 
    'If you could start over, would you choose DU again?': 'entry.770797788',
    'I consent to my responses being used for research': 'entry.1129523573'
}

# 3. Define the Checkbox/Multi-select columns 
# Google Forms requires a list of items for multiple-choice checkboxes
CHECKBOX_COLUMNS = [
    'What factors most influenced your decision to study in India? (Select top 3)', 
    'Which cultural shocks did you experience? (Select all that apply)'
]

def submit_form(data_row):
    payload = {}
    
    for csv_header, entry_id in FORM_MAPPING.items():
        # Get the value from the CSV row, default to empty string if missing
        value = data_row.get(csv_header, '').strip()
        
        if not value:
            continue # Skip empty fields
            
        if csv_header in CHECKBOX_COLUMNS:
            # Split comma-separated string into a list for Google Forms
            options = [opt.strip() for opt in value.split(',')]
            payload[entry_id] = options
        else:
            payload[entry_id] = value

    # For multi-section forms, simulating page history is sometimes required.
    # "0,1,2" indicates navigating through all 3 sections.
    payload['pageHistory'] = "0,1,2"

    try:
        # POST the data
        response = requests.post(FORM_URL, data=payload)
        
        if response.status_code == 200:
            print(f"✅ Successfully submitted response for: {data_row.get('Full Name', 'Unknown')}")
        else:
            print(f"❌ Failed to submit for {data_row.get('Full Name', 'Unknown')}. Status: {response.status_code}")
    except Exception as e:
        print(f"⚠️ Error submitting row: {e}")

# 4. Read the CSV and execute
CSV_FILE_PATH = '/home/aepvoid/Desktop/#hansraj/Sem 4/VAC/project/du_survey_responses.csv' 

if __name__ == "__main__":
    print("Starting automated form submissions...")
    
    with open(CSV_FILE_PATH, mode='r', encoding='utf-8') as file:
        reader = csv.DictReader(file)
        
        # Verify CSV headers match our mapping
        csv_headers = reader.fieldnames
        missing_headers = [h for h in FORM_MAPPING.keys() if h not in csv_headers]
        if missing_headers:
            print(f"ERROR: Missing the following headers in your CSV file:\n{missing_headers}")
            exit()
            
        for row in reader:
            submit_form(row)
            # 1.5 second delay to ensure Google doesn't rate-limit or block the rapid submissions
            time.sleep(1.5) 
            
    print("All submissions complete!")