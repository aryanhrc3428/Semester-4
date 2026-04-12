import requests
import csv
import time

POST_URL = ''

q6_map = {'1': 'It does not pose any real threat', '2': 'It poses a minor and manageable threat', '3': 'It poses a moderate but concerning threat', '4': 'It poses a serious and long-term threat', '5': 'It poses an extreme and urgent threat to humanity'}
q7_map = {'1': 'It will not affect me at all', '2': 'It may have a slight impact on my life', '3': 'It will moderately affect my lifestyle or opportunities', '4': 'It will significantly influence my future decisions', '5': 'It will critically shape my long-term future'}
q8_map = {'1': 'I have not experienced any noticeable event', '2': 'I may have experienced minor changes', '3': 'I have experienced at least one significant event', '4': 'I have experienced multiple noticeable events', '5': 'I frequently experience climate-related impacts'}
q9_map = {'1': 'I never feel concerned about it', '2': 'I rarely think about it', '3': 'I sometimes feel concerned', '4': 'I often feel worried about its consequences', '5': 'I feel frequent or persistent anxiety regarding climate change'}
q10_map = {'1': 'It has not influenced any decisions', '2': 'It has slightly influenced my thinking', '3': 'It has moderately shaped some decisions', '4': 'It has significantly influenced major life choices', '5': 'It has strongly determined important long-term decisions'}
q11_map = {'1': 'I do not actively seek information', '2': 'I occasionally come across information passively', '3': 'I sometimes search for information intentionally', '4': 'I regularly follow climate-related updates', '5': 'I actively and consistently track scientific developments'}
q12_map = {'1': 'I am not confident at all', '2': 'I have limited confidence', '3': 'I am moderately confident', '4': 'I am very confident', '5': 'I am highly confident in distinguishing facts from misinformation'}
q13_map = {'1': 'I have not taken any steps', '2': 'I have made very minor adjustments', '3': 'I have made moderate lifestyle changes', '4': 'I have adopted several sustainable practices', '5': 'I have significantly transformed my lifestyle to reduce impact'}
q14_map = {'1': 'No noticeable changes in my habits', '2': 'Slight adjustments in some areas', '3': 'Moderate changes in daily habits', '4': 'Significant changes in multiple areas', '5': 'A comprehensive shift toward sustainable consumption'}
q15_map = {'1': 'I have never participated', '2': 'I have participated once', '3': 'I occasionally participate', '4': 'I regularly participate', '5': 'I am actively involved in organized initiatives'}
q16_map = {'1': 'Strongly unwilling to incur additional costs', '2': 'Somewhat unwilling', '3': 'Neutral or uncertain', '4': 'Willing under proper accountability', '5': 'Strongly willing to financially contribute'}
q17_map = {'1': 'Not willing to compromise comfort', '2': 'Slightly willing in limited situations', '3': 'Moderately willing when feasible', '4': 'Very willing to make consistent compromises', '5': 'Fully committed to reducing comfort for sustainability'}
q18_map = {'1': 'I never consider environmental factors', '2': 'I rarely consider them', '3': 'I sometimes consider them', '4': 'I often prioritize environmentally responsible brands', '5': 'I consistently base decisions on environmental impact'}
q19_map = {'1': 'Individual citizens through lifestyle changes', '2': 'Corporations through sustainable business practices', '3': 'National governments through policy and regulation', '4': 'International organizations through global cooperation', '5': 'A shared responsibility among all stakeholders'}
q20_map = {'1': 'Very unlikely to change further', '2': 'Somewhat unlikely', '3': 'Undecided', '4': 'Likely to increase my efforts', '5': 'Highly likely to substantially increase my actions'}


print("Starting submissions...")

with open('survey_data.csv', 'r') as file:
    reader = csv.DictReader(file)
    submission_count = 0

    for row in reader:
        ans_q6 = q6_map.get(row['Q6'], '')
        ans_q7 = q7_map.get(row['Q7'], '')
        ans_q8 = q8_map.get(row['Q8'], '')
        ans_q9 = q9_map.get(row['Q9'], '')
        ans_q10 = q10_map.get(row['Q10'], '')
        ans_q11 = q11_map.get(row['Q11'], '')
        ans_q12 = q12_map.get(row['Q12'], '')
        ans_q13 = q13_map.get(row['Q13'], '')
        ans_q14 = q14_map.get(row['Q14'], '')
        ans_q15 = q15_map.get(row['Q15'], '')
        ans_q16 = q16_map.get(row['Q16'], '')
        ans_q17 = q17_map.get(row['Q17'], '')
        ans_q18 = q18_map.get(row['Q18'], '')
        ans_q19 = q19_map.get(row['Q19'], '')
        ans_q20 = q20_map.get(row['Q20'], '')

        form_data = {
            'entry.': row['age'],             # What is your age group?
            'entry.': row['qualification'],   # What is your highest educational qualification?
            'entry.': row['area'],            # Which area do you live in?
            'entry.': ans_q6,                 # To what extent do you believe...
            'entry.': ans_q7,                 # How strongly do you feel...
            'entry.': ans_q8,                 # Have you personally experienced events...
            'entry.': ans_q9,                 # How often do you feel worried...
            'entry.': ans_q10,                # Has climate change influenced...
            'entry.': ans_q11,                # How actively do you seek...
            'entry.': ans_q12,                # How confident are you in identifying...
            'entry.': ans_q13,                # Have you intentionally taken steps...
            'entry.': ans_q14,                # Has climate awareness altered...
            'entry.': ans_q15,                # Have you participated in...
            'entry.': ans_q16,                # Are you willing to pay higher taxes...
            'entry.': ans_q17,                # Are you willing to reduce personal comfort...
            'entry.': ans_q18,                # Do you consider environmental responsibility...
            'entry.': ans_q19,                # Who should bear the primary responsibility...
            'entry.': ans_q20                 # How likely are you to increase...
        }

        try:
            response = requests.post(POST_URL, data=form_data)
            
            if response.status_code == 200:
                submission_count += 1
                print(f"Success! Submitted row {submission_count} (Age: {row['age']}, Area: {row['area']})")
            else:
                print(f"Failed to submit row. Status code: {response.status_code}")
                
        except Exception as e:
            print(f"An error occurred: {e}")

        time.sleep(0.5)

print("\nAll rows processed! Check your Google Forms analytics.")