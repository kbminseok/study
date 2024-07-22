-- 己利 乞闭 轰 积己
CREATE VIEW AverageGrades AS
SELECT hakbeon, AVG(score) AS average_score
FROM SubjectGrade
GROUP BY hakbeon;

-- 己利 乞闭 炼雀
SELECT * FROM AverageGrades;
