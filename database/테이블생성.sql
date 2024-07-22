-- 학생 테이블 생성
CREATE TABLE Student (
    hakbeon CHAR(10) PRIMARY KEY,
    name VARCHAR2(60),
    adress VARCHAR2(60),
    phonnumber VARCHAR2(60) UNIQUE,
    callnumber VARCHAR2(60) UNIQUE
);

create table subject(
subject_code varchar2(60) primary key,
subject_name varchar2(60)
);

create table teacher( 
techernumber varchar2(60) primary key,
classteanumber varchar2(60) unique,
name varchar2(60),
subject_code varchar2(60),
foreign key(subject_code) references subject(subject_code)
);

-- 반 테이블 생성
CREATE TABLE class (
    classnumber varchar2(60) PRIMARY KEY,
    classteanumber varchar2(60),
    foreign key(classteanumber) references teacher(classteanumber),
    hakbeon char(10),
    foreign key(hakbeon) references student(hakbeon)
);

create table club(
club_number int primary key,
club_name varchar2(60),
club_budget int,
hakbeon char(10),
constraint fk_club_hack foreign key (hakbeon) references Student(hakbeon)
);

create table volunteer(
vol_number int primary key,
vol_name varchar2(60),
vol_hour int,
hakbeon char(10),
constraint fk_volunteer_hack foreign key (hakbeon) references Student(hakbeon)
);

-- 과목별 성적 테이블 생성
CREATE TABLE SubjectGrade (
    grade_number INT PRIMARY KEY,
    subject_code VARCHAR2(10),
    hakbeon CHAR(10),
    score INT,
    CONSTRAINT FK_SubjectGrade_SubjectCode FOREIGN KEY (subject_code) REFERENCES Subject(subject_code),
    CONSTRAINT FK_SubjectGrade_StudentID FOREIGN KEY (hakbeon) REFERENCES Student(hakbeon)
);



