create database if not exists prac0;
use prac0;

drop table if exists SOCIETY;
drop table if exists TEACHES;
drop table if exists PROFESSOR;
drop table if exists ENROLLMENT;
drop table if exists COURSE;
drop table if exists STUDENT;

create table STUDENT(
    StudentID int primary key,
    Name varchar(50),
    Email varchar(50),
    Department varchar(30),
    Year int,
    DOB date
);
insert into STUDENT values (10001, 'Aryan', 'aryan@gmail.com', 'CS', 2, '2006-11-05');
insert into STUDENT values (10002, 'Shefali', 'shefali@gmail.com', 'BCOM', 2, '2006-08-15');
insert into STUDENT values (10003, 'Roy', 'roy@gmail.com', 'PS', 2, '2006-02-14');
insert into STUDENT values (10004, 'Bansal', 'bansal@gmail.com', 'BA', 2, '2006-11-22');

create table COURSE(
    CourseID int primary key,
    Title varchar(100),
    Credits int,
    CourseType varchar(20) check (CourseType in ('Fulltime', 'Parttime')),
    TotalSeats int
);
insert into COURSE values (101, 'CS', 24, 'Fulltime', 25);
insert into COURSE values (102, 'BCOM', 24, 'Fulltime', 22);
insert into COURSE values (103, 'PS', 24, 'Parttime', 45);
insert into COURSE values (104, 'BA', 24, 'Parttime', 567);

create table ENROLLMENT(
    EnrollID int primary key,
    StudentID int,
    CourseID int,
    DateOfAdmission date,
    Grade char(2),
    foreign key(StudentID) references STUDENT(StudentID),
    foreign key(CourseID) references COURSE(CourseID)
);
insert into ENROLLMENT values (20001, 10001, 101, '2024-08-01', 'O');
insert into ENROLLMENT values (20002, 10002, 102, '2024-08-01', 'A+');
insert into ENROLLMENT values (20003, 10003, 103, '2024-08-01', 'A');
insert into ENROLLMENT values (20004, 10004, 104, '2024-08-01', 'A-');

create table PROFESSOR(
    ProfID int primary key,
    Name varchar(50),
    Department varchar(30),
    Email varchar(50)
);
insert into PROFESSOR values (301, 'Dr. Sharma', 'CS', 'sharma@example.com');
insert into PROFESSOR values (302, 'Dr. Verma', 'BCOM', 'verma@example.com');
insert into PROFESSOR values (303, 'Dr. Gupta', 'PS', 'gupta@example.com');
insert into PROFESSOR values (304, 'Dr. Singh', 'BA', 'singh@example.com');

create table TEACHES(
    ProfID int,
    CourseID int,
    Semester varchar(10),
    Year int,
    primary key(ProfID, CourseID, Semester, Year),
    foreign key(ProfID) references PROFESSOR(ProfID),
    foreign key(CourseID) references COURSE(CourseID)
);
insert into TEACHES values (301, 101, 'Fall', 2024);
insert into TEACHES values (302, 102, 'Fall', 2024);
insert into TEACHES values (303, 103, 'Spring', 2024);
insert into TEACHES values (304, 104, 'Spring', 2024);

create table SOCIETY(
    SocID int primary key,
    SocName varchar(50),
    FacultyInCharge varchar(50)
);
insert into SOCIETY values (401, 'Coding Club', 'Dr. Sharma');
insert into SOCIETY values (402, 'Commerce Society', 'Dr. Verma');
insert into SOCIETY values (403, 'Debate Society', 'Dr. Gupta');
insert into SOCIETY values (404, 'Cultural Society', 'Dr. Singh');
