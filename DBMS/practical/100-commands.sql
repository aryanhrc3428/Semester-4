-- 1. CREATE DATABASE
CREATE DATABASE IF NOT EXISTS company_db;

-- 2. USE
USE company_db;

-- 3. DROP DATABASE
-- DROP DATABASE IF EXISTS company_db;

-- 4. SHOW DATABASES
SHOW DATABASES;

-- 5. SHOW CREATE DATABASE
SHOW CREATE DATABASE company_db;

-- ============================================
-- TABLE CREATION & MODIFICATION
-- ============================================

-- 6-10. CREATE TABLE
CREATE TABLE IF NOT EXISTS departments (
    dept_id INT PRIMARY KEY AUTO_INCREMENT,
    dept_name VARCHAR(50) NOT NULL,
    location VARCHAR(50),
    budget DECIMAL(12,2) DEFAULT 0.00,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS employees (
    emp_id INT PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE,
    phone VARCHAR(20),
    hire_date DATE NOT NULL,
    salary DECIMAL(10,2),
    dept_id INT,
    manager_id INT,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (dept_id) REFERENCES departments(dept_id) ON DELETE SET NULL,
    FOREIGN KEY (manager_id) REFERENCES employees(emp_id) ON DELETE SET NULL
);

CREATE TABLE IF NOT EXISTS projects (
    project_id INT PRIMARY KEY AUTO_INCREMENT,
    project_name VARCHAR(100) NOT NULL,
    start_date DATE,
    end_date DATE,
    status ENUM('Planning', 'Active', 'Completed', 'Cancelled') DEFAULT 'Planning',
    budget DECIMAL(12,2),
    CONSTRAINT chk_dates CHECK (end_date IS NULL OR end_date >= start_date)
);

CREATE TABLE IF NOT EXISTS employee_projects (
    emp_id INT,
    project_id INT,
    role VARCHAR(50),
    hours_allocated INT DEFAULT 0,
    assigned_date DATE DEFAULT (CURDATE()),
    PRIMARY KEY (emp_id, project_id),
    FOREIGN KEY (emp_id) REFERENCES employees(emp_id) ON DELETE CASCADE,
    FOREIGN KEY (project_id) REFERENCES projects(project_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS salary_history (
    history_id INT PRIMARY KEY AUTO_INCREMENT,
    emp_id INT,
    old_salary DECIMAL(10,2),
    new_salary DECIMAL(10,2),
    change_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    changed_by VARCHAR(50),
    FOREIGN KEY (emp_id) REFERENCES employees(emp_id) ON DELETE CASCADE
);

-- 11. ALTER TABLE ADD COLUMN
ALTER TABLE employees ADD COLUMN middle_name VARCHAR(50) AFTER last_name;

-- 12. ALTER TABLE DROP COLUMN
ALTER TABLE employees DROP COLUMN middle_name;

-- 13. ALTER TABLE MODIFY COLUMN
ALTER TABLE employees MODIFY COLUMN phone VARCHAR(25);

-- 14. ALTER TABLE RENAME COLUMN
ALTER TABLE employees CHANGE COLUMN phone phone_number VARCHAR(25);

-- 15. ALTER TABLE RENAME
ALTER TABLE employees RENAME TO staff;
ALTER TABLE staff RENAME TO employees;

-- 16. DROP TABLE
CREATE TABLE IF NOT EXISTS temp_table (id INT);
DROP TABLE IF EXISTS temp_table;

-- 17. TRUNCATE TABLE
-- TRUNCATE TABLE salary_history;

-- 18. CREATE INDEX
CREATE INDEX idx_employee_name ON employees(last_name, first_name);
CREATE INDEX idx_employee_email ON employees(email);

-- 19. DROP INDEX
DROP INDEX idx_employee_email ON employees;

-- ============================================
-- DATA MANIPULATION - INSERT
-- ============================================

-- 20. INSERT
INSERT INTO departments (dept_name, location, budget) VALUES
('Engineering', 'Building A', 500000.00),
('Sales', 'Building B', 300000.00),
('Marketing', 'Building B', 250000.00),
('HR', 'Building C', 150000.00),
('Finance', 'Building C', 200000.00);

-- Insert employees
INSERT INTO employees (first_name, last_name, email, phone_number, hire_date, salary, dept_id) VALUES
('John', 'Smith', 'john.smith@company.com', '555-0101', '2020-01-15', 85000.00, 1),
('Jane', 'Doe', 'jane.doe@company.com', '555-0102', '2020-03-20', 75000.00, 1),
('Bob', 'Johnson', 'bob.johnson@company.com', '555-0103', '2019-06-10', 90000.00, 2),
('Alice', 'Williams', 'alice.williams@company.com', '555-0104', '2021-01-05', 65000.00, 3),
('Charlie', 'Brown', 'charlie.brown@company.com', '555-0105', '2018-11-20', 95000.00, 4),
('Diana', 'Prince', 'diana.prince@company.com', '555-0106', '2022-02-14', 60000.00, 1),
('Eve', 'Davis', 'eve.davis@company.com', '555-0107', '2021-08-30', 70000.00, 2),
('Frank', 'Miller', 'frank.miller@company.com', '555-0108', '2020-05-15', 80000.00, 5),
('Grace', 'Wilson', 'grace.wilson@company.com', '555-0109', '2023-01-10', 55000.00, 3),
('Henry', 'Taylor', 'henry.taylor@company.com', NULL, '2022-07-22', 72000.00, 1);

-- Update manager relationships
UPDATE employees SET manager_id = 1 WHERE emp_id IN (2, 6, 10);
UPDATE employees SET manager_id = 3 WHERE emp_id = 7;
UPDATE employees SET manager_id = 5 WHERE emp_id = 8;

-- Insert projects
INSERT INTO projects (project_name, start_date, end_date, status, budget) VALUES
('Website Redesign', '2023-01-01', '2023-06-30', 'Completed', 50000.00),
('Mobile App', '2023-03-01', '2023-12-31', 'Active', 120000.00),
('Database Migration', '2023-06-01', NULL, 'Active', 80000.00),
('AI Integration', '2024-01-01', NULL, 'Planning', 200000.00),
('Legacy System Update', '2022-01-01', '2022-12-31', 'Completed', 75000.00);

-- Insert employee-project assignments
INSERT INTO employee_projects (emp_id, project_id, role, hours_allocated) VALUES
(1, 1, 'Lead Developer', 500),
(2, 1, 'Developer', 400),
(1, 2, 'Project Manager', 300),
(6, 2, 'Developer', 600),
(3, 3, 'Consultant', 200),
(4, 4, 'Marketing Lead', 100),
(5, 5, 'Coordinator', 150);

-- ============================================
-- SELECT & BASIC QUERIES
-- ============================================

-- 21. SELECT
SELECT first_name, last_name, email FROM employees;

-- 22. SELECT *
SELECT * FROM departments;

-- 23. WHERE
SELECT * FROM employees WHERE dept_id = 1;
SELECT * FROM employees WHERE salary > 70000;

-- 24. AND / OR
SELECT * FROM employees WHERE dept_id = 1 AND salary > 70000;
SELECT * FROM employees WHERE dept_id = 1 OR dept_id = 2;

-- 25. ORDER BY
SELECT first_name, last_name, salary FROM employees ORDER BY salary DESC;
SELECT * FROM employees ORDER BY dept_id ASC, salary DESC;

-- 26. DISTINCT
SELECT DISTINCT dept_id FROM employees;
SELECT DISTINCT location FROM departments;

-- 27. LIMIT / OFFSET
SELECT * FROM employees LIMIT 5;
SELECT * FROM employees LIMIT 5 OFFSET 5;
SELECT * FROM employees LIMIT 5, 5;

-- 28. BETWEEN
SELECT * FROM employees WHERE salary BETWEEN 60000 AND 80000;
SELECT * FROM employees WHERE hire_date BETWEEN '2020-01-01' AND '2021-12-31';

-- 29. IN / NOT IN
SELECT * FROM employees WHERE dept_id IN (1, 2, 3);
SELECT * FROM employees WHERE dept_id NOT IN (4, 5);

-- 30. LIKE
SELECT * FROM employees WHERE first_name LIKE 'J%';
SELECT * FROM employees WHERE email LIKE '%@company.com';
SELECT * FROM employees WHERE last_name LIKE '_o%';

-- 31. IS NULL / IS NOT NULL
SELECT * FROM employees WHERE phone_number IS NULL;
SELECT * FROM employees WHERE phone_number IS NOT NULL;

-- 32. AS (Aliases)
SELECT first_name AS 'First Name', last_name AS 'Last Name', salary AS 'Annual Salary' FROM employees;

-- 33. CONCAT
SELECT CONCAT(first_name, ' ', last_name) AS full_name FROM employees;

-- 34. Aggregate Functions
SELECT COUNT(*) AS total_employees FROM employees;
SELECT COUNT(phone_number) AS employees_with_phone FROM employees;
SELECT SUM(salary) AS total_salary FROM employees;
SELECT SUM(budget) AS total_budget FROM departments;
SELECT AVG(salary) AS average_salary FROM employees;
SELECT AVG(salary) AS avg_eng_salary FROM employees WHERE dept_id = 1;
SELECT MIN(salary) AS minimum_salary FROM employees;
SELECT MIN(hire_date) AS earliest_hire FROM employees;
SELECT MAX(salary) AS maximum_salary FROM employees;
SELECT MAX(hire_date) AS latest_hire FROM employees;

-- 35. GROUP BY
SELECT dept_id, COUNT(*) AS employee_count FROM employees GROUP BY dept_id;
SELECT dept_id, YEAR(hire_date) AS hire_year, COUNT(*) AS count FROM employees GROUP BY dept_id, YEAR(hire_date);

-- 36. HAVING
SELECT dept_id, AVG(salary) AS avg_salary FROM employees GROUP BY dept_id HAVING AVG(salary) > 70000;
SELECT dept_id, COUNT(*) AS emp_count FROM employees GROUP BY dept_id HAVING COUNT(*) >= 2;

-- 37. COALESCE
SELECT first_name, last_name, COALESCE(phone_number, 'No Phone') AS contact FROM employees;

-- 38. NULLIF
SELECT first_name, NULLIF(salary, 75000) AS salary_if_not_75k FROM employees;

-- 39. CASE
SELECT first_name, last_name, salary,
    CASE WHEN salary >= 90000 THEN 'High' WHEN salary >= 70000 THEN 'Medium' ELSE 'Low' END AS salary_grade
FROM employees;

-- ============================================
-- JOINS
-- ============================================

-- 40. INNER JOIN
SELECT e.first_name, e.last_name, d.dept_name FROM employees e
INNER JOIN departments d ON e.dept_id = d.dept_id;

-- 52. LEFT JOIN / LEFT OUTER JOIN - All from left, matching from right
SELECT 
    e.first_name,
    e.last_name,
    d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.dept_id;

-- 53. RIGHT JOIN / RIGHT OUTER JOIN - All from right, matching from left
SELECT 
    e.first_name,
    e.last_name,
    d.dept_name
FROM employees e
RIGHT JOIN departments d ON e.dept_id = d.dept_id;

-- 54. FULL JOIN / FULL OUTER JOIN - All records from both (MySQL workaround)
-- MySQL doesn't support FULL JOIN directly, use UNION
SELECT 
    e.first_name,
    e.last_name,
    d.dept_name
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.dept_id
UNION
SELECT 
    e.first_name,
    e.last_name,
    d.dept_name
FROM employees e
RIGHT JOIN departments d ON e.dept_id = d.dept_id;

-- 55. CROSS JOIN - Cartesian product
SELECT 
    e.first_name,
    d.dept_name
FROM employees e
CROSS JOIN departments d;

-- 56. SELF JOIN - Join table to itself
SELECT 
    e.first_name AS employee,
    m.first_name AS manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.emp_id;

-- 57. Multiple JOINs
SELECT 
    e.first_name,
    e.last_name,
    d.dept_name,
    p.project_name,
    ep.role
FROM employees e
INNER JOIN departments d ON e.dept_id = d.dept_id
LEFT JOIN employee_projects ep ON e.emp_id = ep.emp_id
LEFT JOIN projects p ON ep.project_id = p.project_id;

-- 58. JOIN with WHERE
SELECT 
    e.first_name,
    e.last_name,
    d.dept_name
FROM employees e
INNER JOIN departments d ON e.dept_id = d.dept_id
WHERE d.location = 'Building A';

-- 59. JOIN with GROUP BY
SELECT 
    d.dept_name,
    COUNT(e.emp_id) AS emp_count,
    AVG(e.salary) AS avg_salary
FROM departments d
LEFT JOIN employees e ON d.dept_id = e.dept_id
GROUP BY d.dept_id, d.dept_name;

-- 60. JOIN with HAVING
SELECT 
    d.dept_name,
    COUNT(e.emp_id) AS emp_count
FROM departments d
LEFT JOIN employees e ON d.dept_id = e.dept_id
GROUP BY d.dept_id, d.dept_name
HAVING COUNT(e.emp_id) > 2;

-- ============================================================================
-- SECTION 6: SET OPERATIONS (Commands 61-65)
-- ============================================================================

-- Create temporary tables for set operations demonstration
CREATE TABLE IF NOT EXISTS high_earners (
    emp_id INT,
    full_name VARCHAR(100),
    salary DECIMAL(10,2)
);

CREATE TABLE IF NOT EXISTS engineers (
    emp_id INT,
    full_name VARCHAR(100),
    specialty VARCHAR(50)
);

INSERT INTO high_earners VALUES
(1, 'John Smith', 85000.00),
(3, 'Bob Johnson', 90000.00),
(5, 'Charlie Brown', 95000.00),
(8, 'Frank Miller', 80000.00);

INSERT INTO engineers VALUES
(1, 'John Smith', 'Backend'),
(2, 'Jane Doe', 'Frontend'),
(6, 'Diana Prince', 'DevOps'),
(10, 'Henry Taylor', 'Database');

-- 61. UNION - Combine distinct results
SELECT full_name FROM high_earners
UNION
SELECT full_name FROM engineers;

-- 62. UNION ALL - Combine all results (including duplicates)
SELECT full_name FROM high_earners
UNION ALL
SELECT full_name FROM engineers;

-- 63. INTERSECT - Common records (MySQL workaround using JOIN)
SELECT h.full_name 
FROM high_earners h
INNER JOIN engineers e ON h.full_name = e.full_name;

-- 64. EXCEPT / MINUS - Records in first but not second (MySQL workaround)
SELECT full_name FROM high_earners
WHERE full_name NOT IN (SELECT full_name FROM engineers);

-- Clean up temporary tables
DROP TABLE IF EXISTS high_earners;
DROP TABLE IF EXISTS engineers;

-- 65. Subqueries - Query within query
SELECT * FROM employees 
WHERE dept_id IN (SELECT dept_id FROM departments WHERE location = 'Building A');

-- ============================================================================
-- SECTION 7: DATA MODIFICATION - UPDATE & DELETE (Commands 66-68)
-- ============================================================================

-- 66. UPDATE - Modify existing data
UPDATE employees SET salary = salary * 1.05 WHERE dept_id = 1;

-- UPDATE with JOIN (MySQL syntax)
UPDATE employees e
JOIN departments d ON e.dept_id = d.dept_id
SET e.salary = e.salary * 1.03
WHERE d.location = 'Building B';

-- UPDATE multiple columns
UPDATE employees 
SET 
    phone_number = '555-0200',
    updated_at = NOW()
WHERE emp_id = 10;

-- 67. DELETE - Remove specific records
-- First, create a test record
INSERT INTO employees (first_name, last_name, email, hire_date, salary, dept_id) 
VALUES ('Temp', 'User', 'temp@company.com', '2024-01-01', 50000.00, 1);

-- Delete the test record
DELETE FROM employees WHERE email = 'temp@company.com';

-- DELETE with JOIN (MySQL syntax)
-- DELETE e FROM employees e
-- JOIN departments d ON e.dept_id = d.dept_id
-- WHERE d.dept_name = 'Sales';

-- 68. DELETE with subquery
DELETE FROM salary_history 
WHERE emp_id IN (SELECT emp_id FROM employees WHERE is_active = FALSE);

-- ============================================================================
-- SECTION 8: TRANSACTION CONTROL (Commands 69-74)
-- ============================================================================

-- 69. BEGIN TRANSACTION / START TRANSACTION
START TRANSACTION;

-- 70. COMMIT - Save changes
-- (Demonstrated below with SAVEPOINT)

-- 71. ROLLBACK - Undo changes
-- (Demonstrated below with SAVEPOINT)

-- 72. SAVEPOINT - Mark a point in transaction
SAVEPOINT before_salary_update;

-- Make some changes
UPDATE employees SET salary = salary + 1000 WHERE emp_id = 1;
UPDATE employees SET salary = salary + 1000 WHERE emp_id = 2;

-- 73. ROLLBACK TO SAVEPOINT - Undo to specific point
ROLLBACK TO SAVEPOINT before_salary_update;

-- 74. COMMIT - Finalize transaction
COMMIT;

-- Alternative: SET TRANSACTION (MySQL specific)
SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- 75. CREATE VIEW - Virtual table
CREATE VIEW IF NOT EXISTS employee_details AS
SELECT 
    e.emp_id,
    CONCAT(e.first_name, ' ', e.last_name) AS full_name,
    e.email,
    d.dept_name,
    d.location,
    e.salary
FROM employees e
LEFT JOIN departments d ON e.dept_id = d.dept_id;

-- Query the view
SELECT * FROM employee_details WHERE salary > 70000;

-- 76. CREATE VIEW with CHECK OPTION
CREATE VIEW IF NOT EXISTS active_employees AS
SELECT * FROM employees WHERE is_active = TRUE
WITH CHECK OPTION;

-- ============================================================================
-- SECTION 11: ADDITIONAL MYSQL FEATURES (Commands 86-90)
-- ============================================================================

-- 86. SHOW COMMANDS - Database metadata
SHOW DATABASES;
SHOW TABLES;
SHOW TABLES LIKE '%employee%';
DESCRIBE employees;
SHOW COLUMNS FROM employees;
SHOW CREATE TABLE employees;
SHOW INDEX FROM employees;

-- 87. Comments in SQL
-- Single line comment
/* Multi-line
   comment block */

-- 88. Constraints information
-- Show all constraints on a table
SELECT 
    CONSTRAINT_NAME,
    CONSTRAINT_TYPE
FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE TABLE_NAME = 'employees' AND TABLE_SCHEMA = 'company_db';

-- 89. CAST and CONVERT - Data type conversion
SELECT 
    emp_id,
    CAST(salary AS CHAR) AS salary_string,
    CAST(hire_date AS DATETIME) AS hire_datetime
FROM employees;

-- 90. CONVERT - Alternative conversion syntax
SELECT CONVERT('2024-01-01', DATE);

-- ============================================================================
-- SECTION 12: DATE AND STRING FUNCTIONS (Commands 91-95)
-- ============================================================================

-- 91. DATE functions
SELECT 
    first_name,
    hire_date,
    YEAR(hire_date) AS hire_year,
    MONTH(hire_date) AS hire_month,
    DAY(hire_date) AS hire_day,
    DATEDIFF(CURDATE(), hire_date) AS days_employed
FROM employees;

-- 92. String concatenation with GROUP_CONCAT
SELECT 
    d.dept_name,
    GROUP_CONCAT(e.first_name ORDER BY e.last_name SEPARATOR ', ') AS employees
FROM departments d
LEFT JOIN employees e ON d.dept_id = e.dept_id
GROUP BY d.dept_id, d.dept_name;

-- 93. User-defined variables
SET @min_salary = 70000;
SELECT * FROM employees WHERE salary > @min_salary;

-- 94. Prepared Statements
SET @sql = 'SELECT * FROM employees WHERE dept_id = ?';
PREPARE stmt FROM @sql;
SET @dept = 1;
EXECUTE stmt USING @dept;
DEALLOCATE PREPARE stmt;

-- ============================================================================
-- SECTION 13: ADDITIONAL MYSQL-SPECIFIC FEATURES
-- ============================================================================

-- CAST - Data type conversion
SELECT 
    emp_id,
    CAST(salary AS CHAR) AS salary_string,
    CAST(hire_date AS DATETIME) AS hire_datetime
FROM employees;

-- CONVERT - Alternative conversion
SELECT CONVERT('2024-01-01', DATE);

-- DATE functions
SELECT 
    first_name,
    hire_date,
    YEAR(hire_date) AS hire_year,
    MONTH(hire_date) AS hire_month,
    DAY(hire_date) AS hire_day,
    DATEDIFF(CURDATE(), hire_date) AS days_employed
FROM employees;

-- String aggregation (MySQL 8.0+)
SELECT 
    d.dept_name,
    GROUP_CONCAT(e.first_name ORDER BY e.last_name SEPARATOR ', ') AS employees
FROM departments d
LEFT JOIN employees e ON d.dept_id = e.dept_id
GROUP BY d.dept_id, d.dept_name;

-- Variables
SET @min_salary = 70000;
SELECT * FROM employees WHERE salary > @min_salary;

-- Prepared Statements
SET @sql = 'SELECT * FROM employees WHERE dept_id = ?';
PREPARE stmt FROM @sql;
SET @dept = 1;
EXECUTE stmt USING @dept;
DEALLOCATE PREPARE stmt;

-- ============================================================================
-- CLEANUP SECTION (Uncomment to remove all created objects)
-- ============================================================================

DROP VIEW IF EXISTS employee_details;
DROP VIEW IF EXISTS active_employees;
DROP TABLE IF EXISTS salary_history;
DROP TABLE IF EXISTS employee_projects;
DROP TABLE IF EXISTS projects;
DROP TABLE IF EXISTS employees;
DROP TABLE IF EXISTS departments;
DROP DATABASE IF EXISTS company_db;