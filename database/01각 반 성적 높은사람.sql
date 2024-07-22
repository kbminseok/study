CREATE VIEW TopScorerPerClassView AS
SELECT
    className,
    studentName,
    hakbeon,
    score
FROM (
    SELECT
        c.className,
        s.name AS studentName,
        sg.hakbeon,
        sg.score,
        RANK() OVER (PARTITION BY c.className ORDER BY sg.score DESC) AS ranking
    FROM
        Class c
    JOIN
        Student s ON c.hakbeon = s.hakbeon
    JOIN
        SubjectGrade sg ON s.hakbeon = sg.hakbeon
) ranked
WHERE
    ranking = 1;

SELECT * FROM TopScorerPerClassView;
