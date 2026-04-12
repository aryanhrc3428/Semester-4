create database if not exists prac6;
use prac6;

drop table if exists Employees;
create table Employees(
    EmpID int,
    EmpName varchar(50),
    DeptID varchar(10)
);

drop table if exists Departments;
create table Departments(
    DeptID varchar(10),
    DeptName varchar(30),
    Location varchar(30)
);

insert into Departments values('D001', 'IT', 'Delhi');
insert into Departments values('D002', 'HR', 'Mumbai');
insert into Departments values('D003', 'Finance', 'Delhi');
insert into Departments values('D004', 'Admin', 'Bangalore');

insert into Employees values(1, 'Amit Sharma', 'D001');
insert into Employees values(2, 'Ravi Kumar', 'D002');
insert into Employees values(3, 'Anita Verma', 'D001');
insert into Employees values(4, 'Reena Kapoor', 'D003');
insert into Employees values(5, 'Aman Gupta', 'D001');
insert into Employees values(6, 'Rohit Singh', 'D004');

-- Q1. Display employee names along with their department names. 
SELECT Employees.EmpName, Departments.DeptName 
FROM Employees 
INNER JOIN Departments 
ON Employees.DeptID = Departments.DeptID;

-- Q2. Display employee names, department names, and locations. 
SELECT EmpName, DeptName, Location 
FROM Employees INNER JOIN Departments 
ON Employees.DeptID = Departments.DeptID;

-- Q3. Display names of employees working in the 'IT' department. 
SELECT EmpName 
FROM Employees INNER JOIN Departments 
ON Employees.DeptID = Departments.DeptID 
WHERE Departments.DeptName = 'IT';

-- Q4. Display names of employees and their department locations in 'Delhi'. 
SELECT EmpName, Location 
FROM Employees INNER JOIN Departments 
ON Employees.DeptID = Departments.DeptID 
WHERE Departments.Location = 'Delhi';

-- Q5. List employees and their department details for only matching DeptIDs. 
SELECT * 
FROM Employees INNER JOIN Departments 
ON Employees.DeptID = Departments.DeptID;

-- Q6. Display employee ID, employee name, department name, and location ordered by department.
SELECT Employees.EmpID, Employees.EmpName, Departments.DeptName, Departments.Location
FROM Employees INNER JOIN Departments
ON Employees.DeptID = Departments.DeptID
ORDER BY Departments.DeptName;

-- Q7. Display employees from Delhi with their employee ID, name, and department.
SELECT Employees.EmpID, Employees.EmpName, Departments.DeptName, Departments.Location
FROM Employees INNER JOIN Departments
ON Employees.DeptID = Departments.DeptID
WHERE Departments.Location = 'Delhi';

-- Q8. Display count of employees per department with department name and location.
SELECT Departments.DeptName, Departments.Location, COUNT(Employees.EmpID) as EmployeeCount
FROM Employees INNER JOIN Departments
ON Employees.DeptID = Departments.DeptID
GROUP BY Departments.DeptID, Departments.DeptName, Departments.Location;
