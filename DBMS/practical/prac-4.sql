create database if not exists prac4;
use prac4;

drop table if exists employees;
create table employees(
	emp_id int,
    first_name varchar(30),
    department varchar(20),
    salary int
);

insert into employees values (101, "Rahul", "Sales", 45000);
insert into employees values (102, "Priya", "HR", 55000);
insert into employees values (103, "Amit", "IT", 60000);
insert into employees values (104, "Neha", "Sales", 48000);
insert into employees values (105, "Karan", "Finance", 52000);

-- Query: Average salary by department
SELECT department, AVG(salary) AS avg_salary
FROM employees
GROUP BY department;

-- You can group by multiple columns
SELECT department, hire_year, COUNT(*) AS emp_count
FROM employees
GROUP BY department, hire_year;

-- Can combine GROUP BY with HAVING to filter aggregated results
SELECT department, COUNT(*) AS emp_count
FROM employees
GROUP BY department
HAVING COUNT(*) > 1;

drop table if exists employees_1;
create table employee_1(
	emp_id int,
    first_name varchar(30),
    last_name varchar(30),
    department varchar(20),
    salary int,
    hire_date date
);
insert into employees_1 values (101, "Rahul", "Sharma", "Sales", 45000, '2020-01-15');
insert into employees_1 values (102, "Priya", "Mehta", "HR", 55000, '2019-03-12');
insert into employees_1 values (103, "Amit", "Verma", "IT", 60000, '2021-06-01');
insert into employees_1 values (104, "Neha", "Kapoor", "Sales", 48000, '2022-07-10');
insert into employees_1 values (105, "Karan", "Singh", "Finance", 52000, '2020-11-23');
insert into employees_1 values (106, "Anjali", "Rao", "IT", 62000, '2021-02-20');
insert into employees_1 values (107, "Rohan", "Das", "HR", 53000, '2018-08-25');

-- 1. Count employees in each department
SELECT department, COUNT(*) AS emp_count
FROM employees
GROUP BY department;

-- 2. Average salary by department
SELECT department, AVG(salary) AS avg_salary
FROM employees
GROUP BY department;

-- 3. Maximum salary in each department
SELECT department, MAX(salary) AS max_salary
FROM employees
GROUP BY department;

-- 4. Minimum salary in each department
SELECT department, MIN(salary) AS min_salary
FROM employees
GROUP BY department;

-- 5. Total salary by department
SELECT department, SUM(salary) AS total_salary
FROM employees
GROUP BY department;

-- 6. Departments with more than 1 employee
SELECT department, COUNT(*) AS emp_count
FROM employees
GROUP BY department
HAVING COUNT(*) > 1;

-- 7. Count employees by year of hire
SELECT YEAR(hire_date) AS hire_year, COUNT(*) AS emp_count
FROM employees
GROUP BY hire_year;

-- 8. Average salary by department for employees hired after 2020
SELECT department, AVG(salary) AS avg_salary
FROM employees
WHERE hire_date > '2020-12-31'
GROUP BY department;

-- 9. Departments and years having more than 1 employee
SELECT department, YEAR(hire_date) AS hire_year, COUNT(*) AS emp_count
FROM employees
GROUP BY department, YEAR(hire_date)
HAVING COUNT(*) > 1;

-- 10. Total salary and average salary by department
SELECT department, SUM(salary) AS total_salary, AVG(salary) AS avg_salary
FROM employees
GROUP BY department;