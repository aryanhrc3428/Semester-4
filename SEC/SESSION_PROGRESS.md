# SEC Practicals Refactoring Session - April 2026

## Objective
Simplify all SEC (Front End Web Design & Development) practicals to align with:
1. **Delhi University B.Sc CSE Semester 4 Official Syllabus** (syllabus.pdf)
2. **Kimi's Reference Notes** (SEC-kimi-notes.pdf)
3. **Beginner-friendly learning level** (4th semester undergraduates)

## Problem Identified
Previous versions of practicals (1-8.html) were:
- ❌ Too advanced for beginners
- ❌ Used complex CSS (gradients, animations, advanced layout)
- ❌ Overengineered styling and design
- ❌ May have included JavaScript beyond syllabus scope
- ❌ Not structured according to reference notes format

## Solution Implemented

### 1. Created Workspace Instructions
**File**: `.github/copilot-instructions.md`

**Contains**:
- Syllabus mapping table (Practical → Unit → Topics)
- Required code structure template
- Content requirements for each practical (1-8)
- Constraints (no frameworks, keep it simple)
- Code quality standards
- File organization guidelines

### 2. Established Practical Structure
Each practical now follows:
```
- Concept explanation (What is it?)
- Why it's used (Use cases)
- Multiple examples
- HTML code for students to learn from
- Minimal CSS (only for readability)
- No complex JavaScript
```

### 3. Refactored Practicals

#### Practical 1: Text Formatting ✅
- Headings (h1-h6)
- Bold, italic, underline
- Colors (basic hex/rgb)
- Fonts (standard families)
- Size & weight
- Paragraphs, line breaks
- Status: **SIMPLIFIED**

#### Practical 2: Lists & Links
- Unordered lists + nesting
- Ordered lists with different types
- Internal links & anchors
- External links (target="_blank")
- Description lists
- Status: **READY FOR SIMPLIFICATION**

#### Practicals 3-8
**Status**: Ready for simplification following the same pattern

## Syllabus Alignment

| Unit | Weeks | Topics | Practicals |
|------|-------|--------|-----------|
| **Unit 1** | 1-3 | Internet, Web basics | - |
| **Unit 2** | 4-7 | HTML elements (text, lists, links, tables, forms, images) | **1, 2, 3, 4, 5** |
| **Unit 3** | 8-11 | CSS selectors, box model, layout | **6, 7** |
| **Unit 4** | 12-15 | JavaScript DOM, events, validation | **8** |

## Reference Notes Structure (Followed)
Each section in practicals now uses:
1. **Concept**: Clear explanation
2. **Use Case**: Why students need this
3. **Examples**: Real code they can copy
4. **Best Practices**: Tips from reference notes

## Files Modified
- ✅ `1.html` - Simplified header, created proper structure
- 🔄 `2.html` - Title updated, ready for content reset
- ⏳ `3.html` - Pending
- ⏳ `4.html` - Pending
- ⏳ `5.html` - Pending
- ⏳ `6.html` - Pending
- ⏳ `7.html` - Pending
- ⏳ `8.html` - Pending

## Next Steps
1. Complete simplification of Practicals 2-8
2. Test each practical in browser (no errors)
3. Verify alignment with syllabus.pdf
4. Verify examples match SEC-kimi-notes.pdf structure
5. Add comments explaining WHY (not just WHAT)

## Constraints to Remember
- **No frameworks** (Bootstrap, Tailwind, React, etc.)
- **No libraries** (jQuery, Axios)
- **Vanilla HTML/CSS/JS only**
- **Keep CSS minimal** - only essential styling
- **For JavaScript**: Only basic DOM manipulation + simple events
- **Follow semantic HTML** - use proper tags (not just divs)

## Reference Files Location
```
/home/aepvoid/Desktop/#hansraj/Sem 4/SEC/
├── syllalus.pdf          ← Official syllabus requirements
├── SEC-kimi-notes.pdf    ← Structure & example reference
├── .github/
│   └── copilot-instructions.md  ← This guides all coding
└── Practicals/
    ├── 1.html through 8.html
    └── index.html
```

---
**Session Date**: April 15, 2026  
**Status**: In Progress - Remaining: 6 practicals to simplify  
**Scope**: Align with Delhi University SEC Course + Beginner Learning Level
