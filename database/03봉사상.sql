SELECT
    s.hakbeon,
    s.name,
    SUM(v.vol_hour) AS total_volunteer_hours
FROM
    Student s
JOIN
    Volunteer v ON s.hakbeon = v.hakbeon
GROUP BY
    s.hakbeon, s.name
ORDER BY
    total_volunteer_hours DESC;
