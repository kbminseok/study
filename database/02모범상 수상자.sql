-- 矫啮胶 积己
CREATE SEQUENCE grade_number_seq
  START WITH 1
  INCREMENT BY 1
  NOMAXVALUE
  NOCYCLE;

-- TopVolunteers 轰 积己
CREATE VIEW TopVolunteers AS
SELECT hakbeon, vol_hour
FROM Volunteer
ORDER BY vol_hour DESC
FETCH FIRST 10 PERCENT ROWS ONLY;

-- TopGrades 轰 积己
CREATE VIEW TopGrades AS
SELECT hakbeon, score
FROM SubjectGrade
ORDER BY score DESC
FETCH FIRST 10 PERCENT ROWS ONLY;

-- TopStudents 轰 积己
CREATE VIEW TopStudents AS
SELECT s.hakbeon, s.name
FROM Student s
JOIN TopVolunteers v ON s.hakbeon = v.hakbeon
JOIN TopGrades g ON s.hakbeon = g.hakbeon;

-- TopStudents 轰 炼雀
SELECT * FROM TopStudents;