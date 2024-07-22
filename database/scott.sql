-- �� ���̺� ����
CREATE TABLE Class (
    class_number INT PRIMARY KEY,
    teacher_id INT,
    teacher_name VARCHAR2(50),
    FOREIGN KEY (teacher_id) REFERENCES Teacher(teacher_id)
);

-- �л� ���̺� ����
CREATE TABLE Student (
    student_id INT PRIMARY KEY,
    student_name VARCHAR2(50),
    address VARCHAR2(100),
    phone_number VARCHAR2(20) UNIQUE,
    home_phone VARCHAR2(20) UNIQUE,
    grade INT,
    tutoring_class VARCHAR2(50),
    class_number INT,
    FOREIGN KEY (class_number) REFERENCES Class(class_number)
);

-- ���� ���̺� ����
CREATE TABLE Teacher (
    teacher_id INT PRIMARY KEY,
    certification_number INT,
    teacher_name VARCHAR2(50),
    subject_code VARCHAR2(10),
    FOREIGN KEY (subject_code) REFERENCES Subject(subject_code)
);

-- ���� ���̺� ����
CREATE TABLE Subject (
    subject_code VARCHAR2(10) PRIMARY KEY,
    subject_name VARCHAR2(50)
);

-- ���Ƹ� ���̺� ����
CREATE TABLE Club (
    club_number INT PRIMARY KEY,
    club_name VARCHAR2(50),
    club_budget int
);

-- ����Ȱ�� ���̺� ����
CREATE TABLE Volunteer(
    activity_number INT PRIMARY KEY,
    activity_name VARCHAR2(50),
    activity_hours INT
);

-- �л� ���̺� ����

-- Ŭ�� ���̺� ����
ALTER TABLE Club
ADD CONSTRAINT FK_StudentClub FOREIGN KEY (student_id) REFERENCES Student(student_id);

-- ����Ȱ�� ���̺� ����
ALTER TABLE Volunteer
ADD CONSTRAINT FK_StudentVolunteer FOREIGN KEY (student_id) REFERENCES Student(student_id);

