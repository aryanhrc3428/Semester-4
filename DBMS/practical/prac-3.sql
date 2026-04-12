use prac2;

-- 1. Convert names to uppercase
SELECT UPPER(`first_name`) AS `FirstName_Upper`
FROM `employees`;

-- 2. Convert names to lowercase
SELECT LOWER(`last_name`) AS `LastName_Lower`
FROM `employees`;

-- 3. Find length of first names
SELECT `first_name`, LENGTH(`first_name`) AS `Name_Length`
FROM `employees`;

-- 4. Concatenate first and last names
SELECT CONCAT(`first_name`, ' ', `last_name`) AS `Full_Name`
FROM `employees`;

-- 5. Extract first 3 letters of first name
SELECT LEFT(`first_name`, 3) AS `ShortName`
FROM `employees`;

-- 6. Replace department name
SELECT REPLACE(`department`, 'Sales', 'Marketing') AS `Updated_Department`
FROM `employees`;

-- 7. Extract year from hire date
SELECT `first_name`, YEAR(`hire_date`) AS `Hire_Year`
FROM `employees`;

-- 8. Extract month from hire date
SELECT `first_name`, MONTH(`hire_date`) AS `Hire_Month`
FROM `employees`;

-- 9. Current date
SELECT CURDATE() AS `Today`;

-- 10. Calculate years of service
SELECT `first_name`, TIMESTAMPDIFF(YEAR, `hire_date`, CURDATE()) AS `Years_of_Service`
FROM `employees`;

-- 11. Add 6 months to hire date
SELECT `first_name`, DATE_ADD(`hire_date`, INTERVAL 6 MONTH) AS `Probation_End`
FROM `employees`;

-- 12. Difference in days since hire date
SELECT `first_name`, DATEDIFF(CURDATE(), `hire_date`) AS `Days_Since_Hire`
FROM `employees`;