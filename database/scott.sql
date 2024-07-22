-- 반 테이블 생성
CREATE TABLE Class (
    class_number INT PRIMARY KEY,
    teacher_id INT,
    teacher_name VARCHAR2(50),
    FOREIGN KEY (teacher_id) REFERENCES Teacher(teacher_id)
);

-- 학생 테이블 생성
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

-- 선생 테이블 생성
CREATE TABLE Teacher (
    teacher_id INT PRIMARY KEY,
    certification_number INT,
    teacher_name VARCHAR2(50),
    subject_code VARCHAR2(10),
    FOREIGN KEY (subject_code) REFERENCES Subject(subject_code)
);

-- 과목 테이블 생성
CREATE TABLE Subject (
    subject_code VARCHAR2(10) PRIMARY KEY,
    subject_name VARCHAR2(50)
);

-- 동아리 테이블 생성
CREATE TABLE Club (
    club_number INT PRIMARY KEY,
    club_name VARCHAR2(50),
    club_budget int
);

-- 봉사활동 테이블 생성
CREATE TABLE Volunteer(
    activity_number INT PRIMARY KEY,
    activity_name VARCHAR2(50),
    activity_hours INT
);

-- 학생 테이블 수정

-- 클럽 테이블 수정
ALTER TABLE Club
ADD CONSTRAINT FK_StudentClub FOREIGN KEY (student_id) REFERENCES Student(student_id);

-- 봉사활동 테이블 수정
ALTER TABLE Volunteer
ADD CONSTRAINT FK_StudentVolunteer FOREIGN KEY (student_id) REFERENCES Student(student_id);

