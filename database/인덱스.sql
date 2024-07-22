-- SubjectGrade ���̺��� FK_SubjectGrade_SubjectCode �ܷ� Ű�� ���� �ε����� ������
CREATE INDEX idx_subject_code ON SubjectGrade(subject_code);

-- SubjectGrade ���̺��� FK_SubjectGrade_StudentID �ܷ� Ű�� ���� �ε����� ������
CREATE INDEX idx_hakbeon ON SubjectGrade(hakbeon);


create index idx_score on SubjectGrade(score DESC);

select hakbeon, score
from subjectgrade
where score >=0;

select hakbeon, score
from subjectgrade;

select /*+ INDEX(student SYS_C008536) */
         a.hakbeon as �й�,
       a.name as �̸�
        ,a.adress as �ּ�
       ,a.phonnumber as ��ȭ��ȣ,
        a.tutolling as �������
    from student a
    where a.tutolling IN ('1�ð�','2�ð�');

SELECT /*+ INDEX(sg idx_score) */
       sg.hakbeon, s.name, sg.score
FROM SubjectGrade sg
JOIN Student s ON sg.hakbeon = s.hakbeon;
