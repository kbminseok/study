SELECT
    c.classnumber,
    t.subject_code,
    s.hakbeon,
    s.name,
    sg.score
FROM
    Class c
JOIN
    Teacher t ON c.classteanumber = t.classteanumber
JOIN
    SubjectGrade sg ON c.hakbeon = sg.hakbeon
JOIN
    Student s ON sg.hakbeon = s.hakbeon
WHERE
    sg.score = (SELECT MAX(score) FROM SubjectGrade WHERE subject_code = t.subject_code);
