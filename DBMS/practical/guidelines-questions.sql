-- Student-Society Database - SQL Practice Questions
-- Based on DBMS Guidelines Practical List

-- Create database
CREATE DATABASE IF NOT EXISTS student_society_db;
USE student_society_db;

-- Drop tables if exist
DROP TABLE IF EXISTS ENROLLMENT;
DROP TABLE IF EXISTS STUDENT;
DROP TABLE IF EXISTS SOCIETY;

-- Create STUDENT table
CREATE TABLE STUDENT (
    RollNo CHAR(6) PRIMARY KEY,
    StudentName VARCHAR(20),
    Course VARCHAR(10),
    DOB DATE
);

-- Create SOCIETY table
CREATE TABLE SOCIETY (
    SocID CHAR(6) PRIMARY KEY,
    SocName VARCHAR(20),
    MentorName VARCHAR(15),
    TotalSeats INT UNSIGNED
);

-- Create ENROLLMENT table (with foreign keys)
CREATE TABLE ENROLLMENT (
    RollNo CHAR(6),
    SID CHAR(6),
    DateOfEnrollment DATE,
    PRIMARY KEY (RollNo, SID),
    FOREIGN KEY (RollNo) REFERENCES STUDENT(RollNo),
    FOREIGN KEY (SID) REFERENCES SOCIETY(SocID)
);

-- Insert sample data into STUDENT
INSERT INTO STUDENT VALUES ('X001A1', 'Aarav Gupta', 'BSc CS', '2001-05-15');
INSERT INTO STUDENT VALUES ('Z002B2', 'Priya Sharma', 'BSc Chem', '2000-08-22');
INSERT INTO STUDENT VALUES ('X003C3', 'Ananya Verma', 'BSc CS', '2001-03-10');
INSERT INTO STUDENT VALUES ('Y004D4', 'Aditya Kumar', 'BA Eco', '1999-12-05');
INSERT INTO STUDENT VALUES ('Z005E9', 'Riya Patel', 'BSc Chem', '2002-01-18');
INSERT INTO STUDENT VALUES ('X006F6', 'Neha Singh', 'BSc CS', '2000-06-30');
INSERT INTO STUDENT VALUES ('Y007G7', 'Vikram Rao', 'BA Eng', '2001-11-25');
INSERT INTO STUDENT VALUES ('Z008H9', 'Divya Mehta', 'BSc Phy', '2001-09-14');
INSERT INTO STUDENT VALUES ('A009I9', 'Kabir Khan', 'BSc CS', '1998-04-08');
INSERT INTO STUDENT VALUES ('B010J0', 'Sneha Joshi', 'BA Hist', '2002-07-19');

-- Insert sample data into SOCIETY
INSERT INTO SOCIETY VALUES ('S1', 'NSS', 'Dr. R Gupta', 50);
INSERT INTO SOCIETY VALUES ('S2', 'Debating', 'Prof. A Sharma', 30);
INSERT INTO SOCIETY VALUES ('S3', 'Dancing', 'Mrs. P Gupta', 40);
INSERT INTO SOCIETY VALUES ('S4', 'Sashakt', 'Dr. K Gupta', 25);
INSERT INTO SOCIETY VALUES ('S5', 'Music', 'Prof. S Verma', 60);
INSERT INTO SOCIETY VALUES ('S6', 'Drama', 'Mr. N Kapoor', 20);

-- Insert sample data into ENROLLMENT
INSERT INTO ENROLLMENT VALUES ('X001A1', 'S1', '2018-01-10');
INSERT INTO ENROLLMENT VALUES ('X001A1', 'S2', '2018-01-12');
INSERT INTO ENROLLMENT VALUES ('Z002B2', 'S1', '2018-01-15');
INSERT INTO ENROLLMENT VALUES ('X003C3', 'S3', '2018-02-01');
INSERT INTO ENROLLMENT VALUES ('X003C3', 'S1', '2018-01-20');
INSERT INTO ENROLLMENT VALUES ('X003C3', 'S4', '2018-03-05');
INSERT INTO ENROLLMENT VALUES ('Z005E9', 'S2', '2018-01-18');
INSERT INTO ENROLLMENT VALUES ('Z005E9', 'S3', '2018-01-25');
INSERT INTO ENROLLMENT VALUES ('Z005E9', 'S4', '2018-02-10');
INSERT INTO ENROLLMENT VALUES ('X006F6', 'S1', '2017-12-20');
INSERT INTO ENROLLMENT VALUES ('Y007G7', 'S2', '2018-01-08');
INSERT INTO ENROLLMENT VALUES ('Z008H9', 'S3', '2018-01-22');
INSERT INTO ENROLLMENT VALUES ('A009I9', 'S5', '2018-01-05');
INSERT INTO ENROLLMENT VALUES ('B010J0', 'S6', '2018-02-15');

-- ============================================
-- SECTION I: Sample Queries (Q1-Q30)
-- ============================================

-- Q1. Retrieve names of students enrolled in any society.
SELECT DISTINCT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo;

-- Q2. Retrieve all society names.
SELECT SocName FROM SOCIETY;

-- Q3. Retrieve students' names starting with the letter 'A'.
SELECT StudentName FROM STUDENT WHERE StudentName LIKE 'A%';

-- Q4. Retrieve students' details studying in courses 'computer science' or 'chemistry'.
SELECT * FROM STUDENT WHERE Course = 'BSc CS' OR Course = 'BSc Chem';
-- Alternative using IN
SELECT * FROM STUDENT WHERE Course IN ('BSc CS', 'BSc Chem');

-- Q5. Retrieve students' names whose roll no either starts with 'X' or 'Z' and ends with '9'.
SELECT StudentName FROM STUDENT 
WHERE (RollNo LIKE 'X%' OR RollNo LIKE 'Z%') AND RollNo LIKE '%9';

-- Q6. Find society details with more than N TotalSeats where N is to be input by the user.
-- Using variable (for MySQL: SET @N = 30;)
SET @N = 30;
SELECT * FROM SOCIETY WHERE TotalSeats > @N;

-- Q7. Update society table for the mentor name of a specific society.
UPDATE SOCIETY SET MentorName = 'Prof. R Sharma' WHERE SocID = 'S1';

-- Q8. Find society names in which more than five students have enrolled.
SELECT s.SocName 
FROM SOCIETY s 
JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName 
HAVING COUNT(e.RollNo) > 5;

-- Q9. Find the name of the youngest student enrolled in society 'NSS'.
SELECT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
JOIN SOCIETY so ON e.SID = so.SocID 
WHERE so.SocName = 'NSS' 
ORDER BY s.DOB DESC 
LIMIT 1;

-- Q10. Find the name of the most popular society (on the basis of enrolled students).
SELECT s.SocName, COUNT(e.RollNo) AS StudentCount
FROM SOCIETY s 
LEFT JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName 
ORDER BY StudentCount DESC 
LIMIT 1;

-- Q11. Find the name of two least popular societies (on the basis of enrolled students).
SELECT s.SocName, COUNT(e.RollNo) AS StudentCount
FROM SOCIETY s 
LEFT JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName 
ORDER BY StudentCount ASC 
LIMIT 2;

-- Q12. Find the students names who are not enrolled in any society.
SELECT s.StudentName 
FROM STUDENT s 
LEFT JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
WHERE e.RollNo IS NULL;
-- Alternative using NOT EXISTS
SELECT StudentName FROM STUDENT s 
WHERE NOT EXISTS (SELECT 1 FROM ENROLLMENT e WHERE e.RollNo = s.RollNo);

-- Q13. Find the students names enrolled in at least two societies.
SELECT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
GROUP BY s.RollNo, s.StudentName 
HAVING COUNT(DISTINCT e.SID) >= 2;

-- Q14. Find society names in which maximum students are enrolled.
SELECT s.SocName, COUNT(e.RollNo) AS EnrolledCount
FROM SOCIETY s 
JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName 
HAVING EnrolledCount = (
    SELECT MAX(StudentCount) 
    FROM (SELECT COUNT(RollNo) AS StudentCount FROM ENROLLMENT GROUP BY SID) AS counts
);

-- Q15. Find names of all students who have enrolled in any society and society names in which at least one student has enrolled.
SELECT DISTINCT s.StudentName, so.SocName
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
JOIN SOCIETY so ON e.SID = so.SocID;

-- Q16. Find names of students who are enrolled in any of the three societies 'Debating', 'Dancing' and 'Sashakt'.
SELECT DISTINCT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
JOIN SOCIETY so ON e.SID = so.SocID 
WHERE so.SocName IN ('Debating', 'Dancing', 'Sashakt');

-- Q17. Find society names such that its mentor has a name with 'Gupta' in it.
SELECT SocName FROM SOCIETY WHERE MentorName LIKE '%Gupta%';

-- Q18. Find the society names in which the number of enrolled students is only 10% of its capacity.
SELECT s.SocName 
FROM SOCIETY s 
JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName, s.TotalSeats 
HAVING COUNT(e.RollNo) = s.TotalSeats * 0.1;

-- Q19. Display the vacant seats for each society.
SELECT SocName, TotalSeats - IFNULL(EnrolledCount, 0) AS VacantSeats
FROM SOCIETY s 
LEFT JOIN (SELECT SID, COUNT(RollNo) AS EnrolledCount FROM ENROLLMENT GROUP BY SID) e 
ON s.SocID = e.SID;

-- Q20. Increment Total Seats of each society by 10%.
UPDATE SOCIETY SET TotalSeats = TotalSeats * 1.1;
-- Reset back for testing: UPDATE SOCIETY SET TotalSeats = FLOOR(TotalSeats / 1.1);

-- Q21. Add the enrollment fees paid ('yes'/'No') field in the enrollment table.
ALTER TABLE ENROLLMENT ADD COLUMN FeesPaid VARCHAR(3) DEFAULT 'No';

-- Q22. Update date of enrollment of society id 's1' to '2018-01-15', 's2' to the current date and 's3' to '2018-01-02'.
UPDATE ENROLLMENT SET DateOfEnrollment = '2018-01-15' WHERE SID = 'S1';
UPDATE ENROLLMENT SET DateOfEnrollment = CURDATE() WHERE SID = 'S2';
UPDATE ENROLLMENT SET DateOfEnrollment = '2018-01-02' WHERE SID = 'S3';

-- Q23. Create a view to keep track of society names with the total number of students enrolled in it.
CREATE VIEW Society_Enrollment_Count AS
SELECT s.SocName, COUNT(e.RollNo) AS TotalEnrolled
FROM SOCIETY s 
LEFT JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName;
-- Query the view
SELECT * FROM Society_Enrollment_Count;

-- Q24. Find student names enrolled in all the societies.
SELECT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
GROUP BY s.RollNo, s.StudentName 
HAVING COUNT(DISTINCT e.SID) = (SELECT COUNT(*) FROM SOCIETY);

-- Q25. Count the number of societies with more than 5 students enrolled in it.
SELECT COUNT(*) AS SocietyCount
FROM (SELECT SID FROM ENROLLMENT GROUP BY SID HAVING COUNT(RollNo) > 5) AS PopularSocieties;

-- Q26. Add column Mobile number in student table with default value '9999999999'.
ALTER TABLE STUDENT ADD COLUMN MobileNumber VARCHAR(10) DEFAULT '9999999999';

-- Q27. Find the total number of students whose age is > 20 years.
SELECT COUNT(*) AS StudentsAbove20 
FROM STUDENT 
WHERE TIMESTAMPDIFF(YEAR, DOB, CURDATE()) > 20;

-- Q28. Find names of students who were born in 2001 and are enrolled in at least one society.
SELECT DISTINCT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
WHERE YEAR(s.DOB) = 2001;

-- Q29. Count all societies whose name starts with 'S' and ends with 't' and at least 5 students are enrolled in the society.
SELECT COUNT(*) AS SocietyCount
FROM SOCIETY s 
JOIN ENROLLMENT e ON s.SocID = e.SID 
WHERE s.SocName LIKE 'S%t'
GROUP BY s.SocID 
HAVING COUNT(e.RollNo) >= 5;

-- Q30. Display the following information: Society name, Mentor name, Total Capacity, Total Enrolled, Unfilled Seats.
SELECT 
    s.SocName,
    s.MentorName,
    s.TotalSeats AS TotalCapacity,
    COUNT(e.RollNo) AS TotalEnrolled,
    s.TotalSeats - COUNT(e.RollNo) AS UnfilledSeats
FROM SOCIETY s 
LEFT JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName, s.MentorName, s.TotalSeats;

-- ============================================
-- TASK: Additional Practice Queries
-- ============================================

-- Display students enrolled in exactly 3 societies.
SELECT s.StudentName, COUNT(e.SID) AS SocietyCount
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
GROUP BY s.RollNo, s.StudentName 
HAVING SocietyCount = 3;

-- Display societies with no students enrolled.
SELECT s.SocName 
FROM SOCIETY s 
LEFT JOIN ENROLLMENT e ON s.SocID = e.SID 
WHERE e.RollNo IS NULL;

-- Find the average age of students in each course.
SELECT Course, AVG(TIMESTAMPDIFF(YEAR, DOB, CURDATE())) AS AverageAge
FROM STUDENT 
GROUP BY Course;

-- List students in descending order of their age (oldest first).
SELECT StudentName, DOB, TIMESTAMPDIFF(YEAR, DOB, CURDATE()) AS Age
FROM STUDENT 
ORDER BY DOB ASC;

-- Find societies where enrollment is at 50% or more of capacity.
SELECT s.SocName, s.TotalSeats, COUNT(e.RollNo) AS Enrolled,
    (COUNT(e.RollNo) / s.TotalSeats * 100) AS EnrollmentPercentage
FROM SOCIETY s 
JOIN ENROLLMENT e ON s.SocID = e.SID 
GROUP BY s.SocID, s.SocName, s.TotalSeats 
HAVING EnrollmentPercentage >= 50;

-- Display student names with their enrolled society names (comma-separated simulation with GROUP_CONCAT).
SELECT s.StudentName, GROUP_CONCAT(so.SocName ORDER BY so.SocName) AS EnrolledSocieties
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
JOIN SOCIETY so ON e.SID = so.SocID 
GROUP BY s.RollNo, s.StudentName;

-- Find mentors who guide more than one society.
SELECT MentorName, COUNT(*) AS SocietyCount
FROM SOCIETY 
GROUP BY MentorName 
HAVING SocietyCount > 1;

-- Display students enrolled in 'NSS' but not in 'Dancing'.
SELECT s.StudentName 
FROM STUDENT s 
JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
JOIN SOCIETY so ON e.SID = so.SocID 
WHERE so.SocName = 'NSS'
AND s.RollNo NOT IN (
    SELECT e2.RollNo FROM ENROLLMENT e2 
    JOIN SOCIETY so2 ON e2.SID = so2.SocID 
    WHERE so2.SocName = 'Dancing'
);

-- Find the month with highest number of enrollments.
SELECT MONTH(DateOfEnrollment) AS EnrollmentMonth, COUNT(*) AS EnrollmentCount
FROM ENROLLMENT 
GROUP BY MONTH(DateOfEnrollment) 
ORDER BY EnrollmentCount DESC 
LIMIT 1;

-- Display course-wise student count and how many are enrolled in societies.
SELECT 
    s.Course,
    COUNT(DISTINCT s.RollNo) AS TotalStudents,
    COUNT(DISTINCT e.RollNo) AS EnrolledStudents
FROM STUDENT s 
LEFT JOIN ENROLLMENT e ON s.RollNo = e.RollNo 
GROUP BY s.Course;

-- ============================================
-- SECTION II: Database Administration Commands
-- ============================================

-- Create user
CREATE USER 'student_user'@'localhost' IDENTIFIED BY 'password123';

-- Create role
CREATE ROLE 'society_manager';

-- Grant privileges to a role
GRANT SELECT, INSERT, UPDATE ON student_society_db.ENROLLMENT TO 'society_manager';
GRANT SELECT ON student_society_db.STUDENT TO 'society_manager';
GRANT SELECT ON student_society_db.SOCIETY TO 'society_manager';

-- Assign role to user
GRANT 'society_manager' TO 'student_user'@'localhost';

-- Revoke privileges from a role
REVOKE INSERT ON student_society_db.ENROLLMENT FROM 'society_manager';

-- Create index
CREATE INDEX idx_student_name ON STUDENT(StudentName);
CREATE INDEX idx_enrollment_date ON ENROLLMENT(DateOfEnrollment);

-- Show all indexes
SHOW INDEX FROM STUDENT;
SHOW INDEX FROM ENROLLMENT;
