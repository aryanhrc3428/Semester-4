create database if not exists prac5;
use prac5;

drop table if exists Employees;
create table Employees(
	EmpID int,
    EmpName varchar(50),
    Department varchar(20),
    City varchar(30)
);
insert into Employees values(1, "Amit Sharma", "HR", "Delhi");
insert into Employees values(2, "Ravi Kumar", "IT", "Mumbai");
insert into Employees values(3, "Anita Verma", "Finance", "Pune");
insert into Employees values(4, "Reena Kapoor", "IT", "Delhi");
insert into Employees values(5, "Aman Gupta", "Admin", "Chennai");
insert into Employees values(6, "Rohit Singh", "Finance", "Kolkata");

-- Q1. Display employees whose name starts with 'A'.
SELECT * FROM Employees WHERE EmpName LIKE 'A%';

-- Q2. Display employees whose city ends with 'i'.
SELECT * FROM Employees WHERE City LIKE '%i';

-- Q3. Display employees whose department contains the letter 'i'.
SELECT * FROM Employees WHERE Department LIKE '%i%';

-- Q4. Display employees whose name has 'a' as the second character.
SELECT * FROM Employees WHERE EmpName LIKE '_a%';

-- Q5. Display employees whose city starts with any character and then 'e'.
SELECT * FROM Employees WHERE City LIKE '_e%';

-- Q6. Display employees whose name does not contain the letter 'a'.
SELECT * FROM Employees WHERE EmpName NOT LIKE '%a%';

-- -- -- -- -- Task
-- -- Write 5 additional queries using LIKE and wildcards on the Employees table.
-- Display employees whose name ends with the letter 'a'.
SELECT * FROM Employees WHERE EmpName LIKE '%a';
-- Display employees whose last name starts with 'K'.
SELECT * FROM Employees WHERE EmpName LIKE '% K%';
-- Display employees whose City contains the letter 'n'.
SELECT * FROM Employees WHERE City LIKE '%n%';
-- Display employees whose department does NOT start with 'F'.
SELECT * FROM Employees WHERE Department NOT LIKE 'F%';
-- Display employees whose name has exactly 'e' as the second and third characters.
SELECT * FROM Employees WHERE EmpName LIKE '_ee%';

-- -- Try patterns like names ending with a specific letter, starting with a letter, or containing certain letters.
-- Names ending with a specific letter ('i' in this case).
SELECT * FROM Employees WHERE EmpName LIKE '%i %'; 
-- Names starting with a specific letter ('R').
SELECT * FROM Employees WHERE EmpName LIKE 'R%';
-- Names containing certain letters ('m' anywhere in the name).
SELECT * FROM Employees WHERE EmpName LIKE '%m%';
-- Names where the first name ends with 'a'.
SELECT * FROM Employees WHERE EmpName LIKE '%a %';
-- Names starting with 'A' and ending with 'a'.
SELECT * FROM Employees WHERE EmpName LIKE 'A%a';

-- -- Use NOT LIKE to filter out specific patterns.
-- Exclude employees whose name starts with the letter 'A'.
SELECT * FROM Employees WHERE EmpName NOT LIKE 'A%';
-- Exclude employees whose city ends with 'i'.
SELECT * FROM Employees WHERE City NOT LIKE '%i';
-- Exclude employees whose department contains the letters 'in'.
SELECT * FROM Employees WHERE Department NOT LIKE '%in%';
-- Exclude employees whose name has 'm' as the second character.
SELECT * FROM Employees WHERE EmpName NOT LIKE '_m%';
-- Exclude employees whose city contains the letter 'e'.
SELECT * FROM Employees WHERE City NOT LIKE '%e%';
