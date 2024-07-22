SELECT s.name as 학생_이름, c.classname as 반_이름, SUM(v.vol_hour) as 총_봉사_시간
FROM Student s
JOIN class c ON s.hakbeon = c.hakbeon
JOIN volunteer v ON s.hakbeon = v.hakbeon
GROUP BY s.name, c.classname
HAVING SUM(v.vol_hour) >= 30;
