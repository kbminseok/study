CREATE OR REPLACE FUNCTION AddStudent(
  hakbeon_in IN VARCHAR2,
  name_in IN VARCHAR2,
  address_in IN VARCHAR2,
  phone_number_in IN VARCHAR2
)
RETURN VARCHAR2
AS
BEGIN
  -- ��ȭ��ȣ ���� üũ
  IF NOT REGEXP_LIKE(phone_number_in, '^\d{3}-\d{4}-\d{4}$') THEN
    RAISE_APPLICATION_ERROR(-20001, '��ȭ��ȣ ������ �ùٸ��� �ʽ��ϴ�. (��: 010-1234-5678)');
    RETURN NULL;
  END IF;

  -- �й��� �ԷµǾ����� üũ
  IF hakbeon_in IS NULL OR hakbeon_in = '' THEN
    RAISE_APPLICATION_ERROR(-20002, '�й��� �ʼ� �Է� �����Դϴ�.');
    RETURN NULL;
  END IF;

  -- �й��� ����ũ���� üũ
  DECLARE
    hakbeon_count INT;
  BEGIN
    SELECT COUNT(1) INTO hakbeon_count
    FROM Student
    WHERE hakbeon = hakbeon_in;

    IF hakbeon_count > 0 THEN
      RAISE_APPLICATION_ERROR(-20003, '�̹� �����ϴ� �й��Դϴ�. �ٸ� �й��� �Է��ϼ���.');
      RETURN NULL;
    END IF;
  END;

  -- ���ο� �л��� �߰�
  INSERT INTO Student (hakbeon, name, adress, phonnumber)
  VALUES (hakbeon_in, name_in, address_in, phone_number_in);

  RETURN hakbeon_in;
END;
/

-- �й��� �Էµ� ���
DECLARE
  student_name VARCHAR2(60) := '���л��̸�';
  student_address VARCHAR2(60) := '�ּ�';
  student_phone_number VARCHAR2(60) := '010-1234-5678';
  student_hakbeon VARCHAR2(50) := '3012';  -- ����� �Է� �Ǵ� �ڵ� ����

  result_hakbeon VARCHAR2(50);
BEGIN
  result_hakbeon := AddStudent(student_hakbeon,student_name, student_address, student_phone_number);
  IF result_hakbeon IS NOT NULL THEN
    DBMS_OUTPUT.PUT_LINE('���ο� �л��� �߰��Ǿ����ϴ�. �й�: ' || result_hakbeon);
  END IF;
END;
/

select * from student;
