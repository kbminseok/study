CREATE TABLE GradeHistory (
    grade_number INT,
    subject_code VARCHAR2(10),
    hakbeon CHAR(10),
    old_score INT,
    new_score INT,
    update_time TIMESTAMP,
    PRIMARY KEY (grade_number)
);
CREATE OR REPLACE TRIGGER UpdateGradeTrigger
BEFORE UPDATE ON SubjectGrade
FOR EACH ROW
BEGIN
    IF :OLD.score IS NOT NULL THEN
        INSERT INTO GradeHistory (grade_number, subject_code, hakbeon, old_score, new_score, update_time)
        VALUES (:OLD.grade_number, :OLD.subject_code, :OLD.hakbeon, :OLD.score, :NEW.score, SYSTIMESTAMP);
    END IF;
END;
/

