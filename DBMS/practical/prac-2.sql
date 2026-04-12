use prac2;

-- Count employees
SELECT COUNT(*) AS total_employees
FROM employees;

-- Average salary
SELECT AVG(salary) AS avg_salary
FROM employees;

-- Maximum salary
SELECT MAX(salary) AS highest_salary
FROM employees;

-- Minimum salary
SELECT MIN(salary) AS lowest_salary
FROM employees;
-- Sum of salaries

SELECT SUM(salary) AS total_salary
FROM employees;

-- Count employees in Sales
SELECT COUNT(*) AS sales_count
FROM employees
WHERE department = 'Sales';

-- Average salary by department
SELECT department, AVG(salary) AS avg_salary
FROM employees
GROUP BY department;

-- Maximum salary by department
SELECT department, MAX(salary) AS max_salary
FROM employees
GROUP BY department;

-- Departments having more than 1 employee
SELECT department, COUNT(*) AS emp_count
FROM employees
GROUP BY department
HAVING COUNT(*) > 1;

-- Total salary of employees hired after 2020
SELECT SUM(salary) AS total_salary
FROM employees
WHERE hire_date > '2020-12-31';