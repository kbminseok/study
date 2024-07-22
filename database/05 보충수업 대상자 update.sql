-- ���� �ð��� �ο��ϱ� ���� ������Ʈ ����
UPDATE Student s
SET s.tutolling = (
    SELECT 
        CASE 
            WHEN sg.score < 70 THEN '2�ð�'
            WHEN sg.score < 80 THEN '1�ð�'
            ELSE NULL
        END AS tutolling
    FROM SubjectGrade sg
    WHERE s.hakbeon = sg.hakbeon
    FETCH FIRST 1 ROWS ONLY
)
WHERE EXISTS (SELECT 1 FROM SubjectGrade sg WHERE s.hakbeon = sg.hakbeon);

-- ������Ʈ�� ���� �ð� Ȯ��
SELECT * FROM Student;


-- tutolling�� �ʱ�ȭ�ϴ� ������Ʈ ����
UPDATE Student
SET tutolling = NULL;

-- ������Ʈ�� tutolling Ȯ��
SELECT * FROM Student;
