-- SubjectGrade 테이블의 FK_SubjectGrade_SubjectCode 외래 키에 대한 인덱스를 재정의
CREATE INDEX idx_subject_code ON SubjectGrade(subject_code);

-- SubjectGrade 테이블의 FK_SubjectGrade_StudentID 외래 키에 대한 인덱스를 재정의
CREATE INDEX idx_hakbeon ON SubjectGrade(hakbeon);


create index idx_score on SubjectGrade(score DESC);

select hakbeon, score
from subjectgrade
where score >=0;

select hakbeon, score
from subjectgrade;

select /*+ INDEX(student SYS_C008536) */
         a.hakbeon as 학번,
       a.name as 이름
        ,a.adress as 주소
       ,a.phonnumber as 전화번호,
        a.tutolling as 보충수업
    from student a
    where a.tutolling IN ('1시간','2시간');

SELECT /*+ INDEX(sg idx_score) */
       sg.hakbeon, s.name, sg.score
FROM SubjectGrade sg
JOIN Student s ON sg.hakbeon = s.hakbeon;
