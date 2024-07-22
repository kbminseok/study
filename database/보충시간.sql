-- ������� �ð� �Ҵ� ����
UPDATE Student s
SET tutoring_class = 
    CASE 
        WHEN score < (SELECT PERCENTILE_CONT(0.1) WITHIN GROUP (ORDER BY score) FROM SubjectGrade WHERE hakbeon = s.hakbeon) THEN '2�ð�'
        WHEN score >= (SELECT PERCENTILE_CONT(0.1) WITHIN GROUP (ORDER BY score) FROM SubjectGrade WHERE hakbeon = s.hakbeon) AND
             score < (SELECT PERCENTILE_CONT(0.2) WITHIN GROUP (ORDER BY score) FROM SubjectGrade WHERE hakbeon = s.hakbeon) THEN '1�ð�'
        ELSE NULL
    END;
