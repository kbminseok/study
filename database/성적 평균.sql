-- ���� ��� �� ����
CREATE VIEW AverageGrades AS
SELECT hakbeon, AVG(score) AS average_score
FROM SubjectGrade
GROUP BY hakbeon;

-- ���� ��� ��ȸ
SELECT * FROM AverageGrades;
