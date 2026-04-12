create database if not exists prac1;
use prac1;

drop table if exists employees;
create table employees(
	emp_id int,
    first_name varchar(30),
    last_name varchar(30),
    department varchar(20),
    salary int,
    hire_date date
);
insert into employees values (101, "Rahul", "Sharma", "Sales", 45000, '2020-01-15');
insert into employees values (102, "Priya", "Mehta", "HR", 55000, '2019-03-12');
insert into employees values (103, "Amit", "Verma", "IT", 60000, '2021-06-01');
insert into employees values (104, "Neha", "Kapoor", "Sales", 48000, '2022-07-10');
insert into employees values (105, "Karan", "Singh", "Finance", 52000, '2020-11-23');


-- Equality condition (=)
SELECT *
FROM employees
WHERE department = 'Sales';

-- Greater than (>)
SELECT first_name, salary
FROM employees
WHERE salary > 50000;

-- Less than or equal to (<=)
SELECT first_name, department, salary
FROM employees
WHERE salary <= 48000;

-- Range with BETWEEN
SELECT first_name, salary
FROM employees
WHERE salary BETWEEN 45000 AND 55000;

-- Pattern matching with LIKE
SELECT first_name, last_name
FROM employees
WHERE first_name LIKE 'P%';

-- Logical AND
SELECT *
FROM employees
WHERE department = 'Sales' AND salary > 46000;

-- Logical OR
SELECT *
FROM employees
WHERE department = 'IT' OR department = 'Finance';

-- NOT operator
SELECT first_name, department
FROM employees
WHERE NOT department = 'HR';

-- Date condition
SELECT first_name, hire_date
FROM employees
WHERE hire_date > '2020-12-31';

-- IN operator
SELECT first_name, department
FROM employees
WHERE department IN ('Sales', 'Finance');