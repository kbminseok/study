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
    tutolling_value VARCHAR2(10) := '2�ð�'; -- ���ϴ� tutolling ������ ����
BEGIN
    GetStudentsByTutolling(tutolling_value);
END;
/

-- Ư�� ����ð��� �ش��ϴ� �л� ��� ���ν��� ȣ��
EXEC GetStudentsByTutolling('1�ð�');

-- DBMS_OUTPUT�� Ȱ��ȭ
SET SERVEROUTPUT ON;

-- ���ν��� ȣ��
EXEC GetStudentsByTutolling('2�ð�');
