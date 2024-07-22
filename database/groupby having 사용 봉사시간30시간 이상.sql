SELECT s.name as �л�_�̸�, c.classname as ��_�̸�, SUM(v.vol_hour) as ��_����_�ð�
FROM Student s
JOIN class c ON s.hakbeon = c.hakbeon
JOIN volunteer v ON s.hakbeon = v.hakbeon
GROUP BY s.name, c.classname
HAVING SUM(v.vol_hour) >= 30;
