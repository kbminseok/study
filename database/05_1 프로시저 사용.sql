CREATE OR REPLACE PROCEDURE GetStudentsByTutolling(
    tutolling_value VARCHAR2
) AS
BEGIN
    FOR student_rec IN (SELECT * FROM Student WHERE tutolling = tutolling_value) LOOP
        DBMS_OUTPUT.PUT_LINE('Hakbeon: ' || student_rec.hakbeon || ', Name: ' || student_rec.name || ', Tutolling: ' || student_rec.tutolling);
    END LOOP;
END GetStudentsByTutolling;
/

DECLARE
    tutolling_value VARCHAR2(10) := '2시간'; -- 원하는 tutolling 값으로 설정
BEGIN
    GetStudentsByTutolling(tutolling_value);
END;
/

-- 특정 보충시간에 해당하는 학생 출력 프로시저 호출
EXEC GetStudentsByTutolling('1시간');

-- DBMS_OUTPUT을 활성화
SET SERVEROUTPUT ON;

-- 프로시저 호출
EXEC GetStudentsByTutolling('2시간');
