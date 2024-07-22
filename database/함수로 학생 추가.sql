CREATE OR REPLACE FUNCTION AddStudent(
  hakbeon_in IN VARCHAR2,
  name_in IN VARCHAR2,
  address_in IN VARCHAR2,
  phone_number_in IN VARCHAR2
)
RETURN VARCHAR2
AS
BEGIN
  -- 전화번호 형식 체크
  IF NOT REGEXP_LIKE(phone_number_in, '^\d{3}-\d{4}-\d{4}$') THEN
    RAISE_APPLICATION_ERROR(-20001, '전화번호 형식이 올바르지 않습니다. (예: 010-1234-5678)');
    RETURN NULL;
  END IF;

  -- 학번이 입력되었는지 체크
  IF hakbeon_in IS NULL OR hakbeon_in = '' THEN
    RAISE_APPLICATION_ERROR(-20002, '학번은 필수 입력 사항입니다.');
    RETURN NULL;
  END IF;

  -- 학번이 유니크한지 체크
  DECLARE
    hakbeon_count INT;
  BEGIN
    SELECT COUNT(1) INTO hakbeon_count
    FROM Student
    WHERE hakbeon = hakbeon_in;

    IF hakbeon_count > 0 THEN
      RAISE_APPLICATION_ERROR(-20003, '이미 존재하는 학번입니다. 다른 학번을 입력하세요.');
      RETURN NULL;
    END IF;
  END;

  -- 새로운 학생을 추가
  INSERT INTO Student (hakbeon, name, adress, phonnumber)
  VALUES (hakbeon_in, name_in, address_in, phone_number_in);

  RETURN hakbeon_in;
END;
/

-- 학번이 입력된 경우
DECLARE
  student_name VARCHAR2(60) := '새학생이름';
  student_address VARCHAR2(60) := '주소';
  student_phone_number VARCHAR2(60) := '010-1234-5678';
  student_hakbeon VARCHAR2(50) := '3012';  -- 사용자 입력 또는 자동 생성

  result_hakbeon VARCHAR2(50);
BEGIN
  result_hakbeon := AddStudent(student_hakbeon,student_name, student_address, student_phone_number);
  IF result_hakbeon IS NOT NULL THEN
    DBMS_OUTPUT.PUT_LINE('새로운 학생이 추가되었습니다. 학번: ' || result_hakbeon);
  END IF;
END;
/

select * from student;
