-- Q1: CREATE TABLE WITH CONSTRAINTS

-- 1. Create the department table
CREATE TABLE department (
    dept_id INT PRIMARY KEY,
    dept_name VARCHAR(50) UNIQUE,
    location VARCHAR(50),
    phone VARCHAR(15)
);

-- 2. Create the doctor table
CREATE TABLE doctor (
    doctor_id INT PRIMARY KEY,
    name VARCHAR(60) NOT NULL,
    specialisation VARCHAR(50),
    salary DECIMAL(10,2),
    experience INT,
    dept_id INT,
    CHECK (salary > 0),
    FOREIGN KEY (dept_id) REFERENCES department(dept_id)
);

-- 3. Create the patient table
CREATE TABLE patient (
    patient_id INT PRIMARY KEY,
    name VARCHAR(60) NOT NULL,
    age INT,
    gender CHAR(1),
    city VARCHAR(40),
    admission_date DATE DEFAULT CURDATE(),
    CHECK (gender IN ('M', 'F'))
);

-- 4. Create the appointment table
CREATE TABLE appointment (
    appt_id INT PRIMARY KEY,
    doctor_id INT,
    patient_id INT,
    appt_date DATE,
    fees DECIMAL(8,2),
    status VARCHAR(20) DEFAULT 'Scheduled',
    CHECK (fees >= 0),
    FOREIGN KEY (doctor_id) REFERENCES doctor(doctor_id),
    FOREIGN KEY (patient_id) REFERENCES patient(patient_id)
);

-- 5. Insert records into department table
INSERT INTO department VALUES (1, 'Cardiology', 'Building A', '9876543210');
INSERT INTO department VALUES (2, 'Neurology', 'Building B', '9876543211');
INSERT INTO department VALUES (3, 'Orthopedics', 'Building C', '9876543212');
INSERT INTO department VALUES (4, 'Pediatrics', 'Building D', '9876543213');
INSERT INTO department VALUES (5, 'Dermatology', 'Building E', '9876543214');

-- Insert records into doctor table
INSERT INTO doctor VALUES (101, 'Amit Sharma', 'Cardiologist', 75000.00, 10, 1);
INSERT INTO doctor VALUES (102, 'Priya Patel', 'Neurologist', 82000.00, 12, 2);
INSERT INTO doctor VALUES (103, 'Rahul Verma', 'Orthopedic Surgeon', 68000.00, 8, 3);
INSERT INTO doctor VALUES (104, 'Ananya Gupta', 'Pediatrician', 55000.00, 6, 4);
INSERT INTO doctor VALUES (105, 'Arjun Reddy', 'Dermatologist', 62000.00, 7, 5);

-- Insert records into patient table
INSERT INTO patient (patient_id, name, age, gender, city, admission_date) VALUES (201, 'Ravi Kumar', 45, 'M', 'Mumbai', '2024-01-15');
INSERT INTO patient (patient_id, name, age, gender, city, admission_date) VALUES (202, 'Sneha Rao', 32, 'F', 'Delhi', '2024-02-20');
INSERT INTO patient (patient_id, name, age, gender, city, admission_date) VALUES (203, 'Vikram Singh', 55, 'M', 'Bangalore', '2024-03-10');
INSERT INTO patient (patient_id, name, age, gender, city, admission_date) VALUES (204, 'Pooja Mehta', 28, 'F', 'Mumbai', '2023-12-05');
INSERT INTO patient (patient_id, name, age, gender, city, admission_date) VALUES (205, 'Karan Shah', 40, 'M', 'Delhi', '2024-04-18');

-- Insert records into appointment table
INSERT INTO appointment VALUES (301, 101, 201, '2024-01-20', 800.00, 'Completed');
INSERT INTO appointment VALUES (302, 102, 202, '2024-02-25', 600.00, 'Completed');
INSERT INTO appointment VALUES (303, 103, 203, '2024-03-15', 450.00, 'Scheduled');
INSERT INTO appointment VALUES (304, 104, 204, '2024-01-10', 500.00, 'Completed');
INSERT INTO appointment VALUES (305, 105, 205, '2024-04-20', 700.00, 'Scheduled');


-- Q2: ALTER TABLE OPERATIONS

-- 1. Add email column to doctor table
ALTER TABLE doctor ADD COLUMN email VARCHAR(80);

-- 2. Add blood_group column to patient table
ALTER TABLE patient ADD COLUMN blood_group VARCHAR(5);

-- 3. Change phone column data type in department table
ALTER TABLE department MODIFY COLUMN phone VARCHAR(20);

-- 4. Rename status column to appt_status in appointment table
ALTER TABLE appointment CHANGE COLUMN status appt_status VARCHAR(20);

-- 5. Add NOT NULL constraint to specialisation column in doctor table
ALTER TABLE doctor MODIFY COLUMN specialisation VARCHAR(50) NOT NULL;

-- 6. Drop location column from department table
ALTER TABLE department DROP COLUMN location;


-- Q3: SELECT QUERIES

-- 1. Names and salaries of doctors with salary > 60000, ordered by salary DESC
SELECT name, salary FROM doctor WHERE salary > 60000 ORDER BY salary DESC;

-- 2. Patients aged 30-60 from Mumbai or Delhi
SELECT * FROM patient WHERE age BETWEEN 30 AND 60 AND city IN ('Mumbai', 'Delhi');

-- 3. Doctors whose name starts with 'A'
SELECT * FROM doctor WHERE name LIKE 'A%';

-- 4. Appointments with status 'Completed' and fees > 500
SELECT * FROM appointment WHERE appt_status = 'Completed' AND fees > 500;

-- 5. Patients with NULL blood_group
SELECT * FROM patient WHERE blood_group IS NULL;

-- 6. Count patients admitted in year 2024
SELECT COUNT(*) AS total_patients_2024 FROM patient WHERE YEAR(admission_date) = 2024;

-- 7. Maximum, minimum, and average fees from appointment table
SELECT MAX(fees) AS max_fees, MIN(fees) AS min_fees, AVG(fees) AS avg_fees FROM appointment;

-- 8. Specialisation with count of doctors, showing only those with more than 1 doctor
SELECT specialisation, COUNT(*) AS doctor_count FROM doctor GROUP BY specialisation HAVING COUNT(*) > 1;


-- Q4: JOIN OPERATIONS

-- 1. INNER JOIN: Doctor name with department name
SELECT d.name AS doctor_name, dept.dept_name AS department_name 
FROM doctor d 
INNER JOIN department dept ON d.dept_id = dept.dept_id;

-- 2. LEFT JOIN: All departments and doctors, including departments with no doctors
SELECT dept.dept_name, d.name AS doctor_name 
FROM department dept 
LEFT JOIN doctor d ON dept.dept_id = d.dept_id;

-- 3. Patient name, doctor name, appointment date, and fees for completed appointments
SELECT p.name AS patient_name, d.name AS doctor_name, a.appt_date, a.fees 
FROM appointment a 
INNER JOIN patient p ON a.patient_id = p.patient_id 
INNER JOIN doctor d ON a.doctor_id = d.doctor_id 
WHERE a.appt_status = 'Completed';

-- 4. Patients who have never had an appointment
SELECT p.name FROM patient p 
LEFT JOIN appointment a ON p.patient_id = a.patient_id 
WHERE a.appt_id IS NULL;

-- 5. Department name and total fees collected from appointments in that department
SELECT dept.dept_name, SUM(a.fees) AS total_fees 
FROM department dept 
INNER JOIN doctor d ON dept.dept_id = d.dept_id 
INNER JOIN appointment a ON d.doctor_id = a.doctor_id 
GROUP BY dept.dept_name;
