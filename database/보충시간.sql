-- 보충수업 시간 할당 쿼리
UPDATE Student s
SET tutoring_class = 
    CASE 
        WHEN score < (SELECT PERCENTILE_CONT(0.1) WITHIN GROUP (ORDER BY score) FROM SubjectGrade WHERE hakbeon = s.hakbeon) THEN '2시간'
        WHEN score >= (SELECT PERCENTILE_CONT(0.1) WITHIN GROUP (ORDER BY score) FROM SubjectGrade WHERE hakbeon = s.hakbeon) AND
             score < (SELECT PERCENTILE_CONT(0.2) WITHIN GROUP (ORDER BY score) FROM SubjectGrade WHERE hakbeon = s.hakbeon) THEN '1시간'
        ELSE NULL
    END;
