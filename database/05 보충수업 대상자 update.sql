-- 보충 시간을 부여하기 위한 업데이트 쿼리
UPDATE Student s
SET s.tutolling = (
    SELECT 
        CASE 
            WHEN sg.score < 70 THEN '2시간'
            WHEN sg.score < 80 THEN '1시간'
            ELSE NULL
        END AS tutolling
    FROM SubjectGrade sg
    WHERE s.hakbeon = sg.hakbeon
    FETCH FIRST 1 ROWS ONLY
)
WHERE EXISTS (SELECT 1 FROM SubjectGrade sg WHERE s.hakbeon = sg.hakbeon);

-- 업데이트된 보충 시간 확인
SELECT * FROM Student;


-- tutolling을 초기화하는 업데이트 쿼리
UPDATE Student
SET tutolling = NULL;

-- 업데이트된 tutolling 확인
SELECT * FROM Student;
