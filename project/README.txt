CREATE TABLE student FROM student.txt
CREATE TABLE lecture FROM lecture.txt
CREATE TABLE xuanke (StudentID,StudentName,CourseID,CourseName) TO xuanke.txt
TABLE LIST
SELECT studentID,Names FROM student
SELECT CourseID,CourseName FROM lecture
INSERT INTO xuanke VALUES (1733098,ha,00360070,Classic_literature_of_Russia)
INSERT INTO xuanke VALUES (1733099,en,00201010,More_beautiful_life)
UPDATE xuanke SET CourseName = Calculus WHERE StudentName = en
SELECT * FROM xuanke 
SELECT DISTINCT StudentName FROM xuanke
SELECT studentID,Names FROM student ORDER BY studentID DESC
SELECT * FROM xuanke WHERE StudentName = en
SELECT CourseID,CourseName FROM lecture TO coursename.txt
DELETE FROM xuanke WHERE CourseName = Calculus
DROP TABLE student
DROP TABLE lecture
TABLE LIST
