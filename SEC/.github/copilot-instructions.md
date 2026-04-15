# SEC Frontend Development - Copilot Instructions

## Project Context
This is a **Delhi University B.Sc Computer Science** practical course:
- **Course**: Front End Web Design & Development (SEC)
- **Target Students**: 4th Semester Undergraduates
- **Scope**: HTML, CSS, JavaScript basics only
- **Reference**: Official Delhi University Syllabus + Kimi's Reference Notes

## Code Quality Standards

### Constraint 1: Complexity Level
- **DO USE**: Basic HTML semantic tags, simple CSS properties, vanilla JavaScript
- **DON'T USE**: Frameworks (React, Vue, Angular), advanced CSS (grid, complex animations), ES6+ features beyond basic arrow functions
- **Style**: Clean, readable, well-commented code suitable for beginners

### Constraint 2: Follow Syllabus Structure
Practicals map to official syllabus units:

| Practical | Syllabus Unit | Topics | Focus |
|-----------|---------------|--------|-------|
| **1** | Unit 2.1 | Text formatting, headings, colors, fonts | HTML semantic structure |
| **2** | Unit 2.2-2.3 | Lists (ul, ol), hyperlinks (internal/external) | Information organization |
| **3** | Unit 2.4 | Tables with rows, columns, headers | Data presentation |
| **4** | Unit 2.5-2.6 | Images, forms, form controls | Multimedia & user input |
| **5** | Unit 2.2 | Timetable creation using tables | Practical data display |
| **6** | Unit 3 | CSS selectors, box model, basic styling | CSS fundamentals |
| **7** | Unit 3 | CSS layout (simple flexbox or float) | Page structure |
| **8** | Unit 4 | Form validation, basic DOM manipulation | JavaScript interactivity |

### Constraint 3: Code Structure for Each Practical

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <title>Practical [N] - [Topic]</title>
    <meta charset="UTF-8">
    <style>
        /* MINIMAL CSS - only essential styling */
        body { font-family: Arial, sans-serif; margin: 20px; }
        .section { background: white; padding: 15px; margin: 20px 0; border-left: 5px solid #007bff; }
        .section h2 { color: #007bff; }
    </style>
</head>
<body>
    <h1>Practical [N]: [Topic Description]</h1>
    <p style="text-align: center; color: #666;">Delhi University Syllabus</p>
    <hr>
    
    <!-- SECTION 1 -->
    <div class="section">
        <h2>1. [Concept Name]</h2>
        <p>[EXPLAIN what it is and why it's used]</p>
        
        <div class="example">
            <h3>Example:</h3>
            <!-- ACTUAL CODE EXAMPLE HERE -->
        </div>
        
        <p><strong>Use case:</strong> [When/why students would use this]</p>
    </div>
    
    <!-- Additional sections follow same pattern -->
</body>
</html>
```

### Constraint 4: Practical Content Requirements

#### Practical 1: Text Formatting
- Headings (h1-h6 hierarchy)
- Text formatting (<strong>, <em>, <u>)
- Colors (inline style only)
- Fonts (Arial, Georgia, Times New Roman, Courier)
- Font size & weight
- Paragraphs & line breaks (<p>, <br>)
- Horizontal lines (<hr>)
- **JavaScript**: NONE
- **CSS**: Minimal (colors, fonts, basic spacing)

#### Practical 2: Lists &Lists
- Unordered lists (<ul>, <li>)
- Ordered lists (<ol>, <li> with different types: i, I, a, A)
- Nested lists (one level only)
- Internal links (href to other .html files, anchor tags)
- External links (target="_blank")
- Description lists (<dl>, <dt>, <dd>)
- **JavaScript**: NONE
- **CSS**: Link colors, hover effects only

#### Practical 3: Tables & Timetables
- Table structure (<table>, <tr>, <td>, <th>)
- Table headers (<thead>, <tbody>)
- Colspan/rowspan attributes
- Timetable as practical example (class schedule)
- Bordered tables with basic formatting
- **JavaScript**: NONE
- **CSS**: Borders, padding, background colors for headers

#### Practical 4: Images & Forms
- Image tags (<img> with src, alt, width, height)
- Responsive images (max-width)
- Form elements (<form>, <input>, <select>, <textarea>, <button>)
- Input types: text, email, date, password, radio, checkbox
- Form labels (<label>) with for attribute
- **JavaScript**: Basic onclick for button (if any)
- **CSS**: Form styling (borders, padding, basic layout)

#### Practical 5: Timetable (Complete)")
- Create college timetable using <table>
- Multiple subjects, time slots
- Color-coded classes or sections
- Use colspan for merged cells if needed
- CSS styling for readability
- **No JavaScript**

#### Practical 6: CSS Selectors & Box Model
- CSS selectors: element, class, ID
- Descendant selectors
- Pseudo-classes (:hover, :visited, :active)
- Box model: margin, border, padding
- Display: block vs inline
- Simple layout containers
- **No JavaScript**

#### Practical 7: CSS Layout
- Float-based or Flexbox layout (simple)
- Header, sidebar, main content, footer layout
- Responsive design basics (media queries)
- CSS Grid (optional, if covered)
- Navigation menu styling
- **No JavaScript**

#### Practical 8: Form Validation
- HTML5 validation attributes (required, pattern, type)
- JavaScript validation functions (basic)
- Regular expressions for email/phone
- Show/hide error messages
- Change input border color on error/success
- DOM manipulation (getElementById, textContent, classList)
- Event handlers (onblur, onsubmit)

### Constraint 5: Code Comments
```javascript
// GOOD: Clear, explains WHY
function validateEmail(email) {
    // Check if email matches basic pattern: something@something.something
    const emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailPattern.test(email);
}

// BAD: Unnecessary or vague
function validateEmail(email) {
    // validate
    const pat = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return pat.test(email);
}
```

### Constraint 6: File Organization
```
SEC/Practicals/
├── 1.html          # Text formatting
├── 2.html          # Lists & Links
├── 3.html          # Tables
├── 4.html          # Images & Forms
├── 5.html          # Timetable
├── 6.html          # CSS Selectors & Box Model
├── 7.html          # CSS Layout
├── 8.html          # Form Validation
├── index.html      # Index page
└── images/         # For images (if any)
```

## What NOT to Do

❌ Use Bootstrap, Tailwind, or any CSS framework
❌ Use JavaScript libraries (jQuery, Axios, etc.)
❌ Use ES6+ features like async/await, destructuring, arrow functions in complex ways
❌ Create complex animations or effects
❌ Use external dependencies or package managers
❌ Overcomplicate with advanced CSS (pseudo-elements, complex selectors)
❌ Skip semantic HTML in favor of divs everywhere
❌ Use inline JavaScript in onclick attributes (except for very simple cases)

## When Creating/Editing Practicals

1. **Check syllabus mapping** - Ensure the practical aligns with the unit topics
2. **Keep it beginner-friendly** - Comments should explain the "why"
3. **Use reference notes structure** - Follow Kimi's organization (concept explanation → example → use case)
4. **Test in browser** - Ensure all code runs without errors
5. **Validate HTML** - Use semantic tags appropriately
6. **Keep CSS minimal** - Only style what's needed for clarity

## Reference Materials
- **Syllabus**: See syllabus.pdf (Delhi University official)
- **Notes**: See SEC-kimi-notes.pdf (structure and examples)
- **Scope**: Only materials covered in these two documents

## Example: Good vs Bad Practice

### Good (Simple, Educational)
```html
<h2>What is a list?</h2>
<p>Lists organize information in a clear, scannable format.</p>
<ul>
    <li>Bullets show no particular order</li>
    <li>Perfect for features or ingredients</li>
</ul>
```

### Bad (Overly Complex)
```html
<div className="grid grid-cols-1 md:grid-cols-2 gap-4">
    <Card>
        <h2 className="text-2xl font-bold">What is a list?</h2>
        <List items={['Bullets', 'Perfect for features']} />
    </Card>
</div>
```

---

**Last Updated**: April 2026  
**Scope**: Delhi University B.Sc CSE Semester 4 - Front End Web Design & Development
