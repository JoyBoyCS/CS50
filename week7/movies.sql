--1
SELECT title FROM movies WHERE year = '2008';

--2
SELECT birth FROM people WHERE name = 'Emma Stone';

--3
SELECT title FROM movies WHERE year >= 2018 ORDER BY title;

--4
SELECT COUNT(movie_id) FROM ratings WHERE rating = 10.0;

--5
SELECT title, year FROM movies WHERE title LIKE 'Harry Potter%' ORDER BY year;

--6
SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);

--7
SELECT rating, title FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE year = 2010 ORDER BY rating DESC, title;

--8
SELECT name FROM movies, stars, people WHERE title = 'Toy Story' AND movies.id = stars.movie_id AND people.id = stars.person_id;

--9
SELECT name FROM movies, stars, people WHERE year = 2004 AND movies.id = stars.movie_id AND people.id = stars.person_id ORDER BY birth;

--10
SELECT distinct(name) FROM ratings, directors, people WHERE directors.movie_id = ratings.movie_id AND people.id = directors.person_id AND rating >= 9.0;

--11
SELECT title FROM movies, stars, ratings, people WHERE name = 'Chadwick Boseman' AND people.id = stars.person_id AND stars.movie_id = movies.id AND movies.id = ratings.movie_id ORDER BY rating DESC LIMIT 5;

--12
SELECT title FROM people, stars, movies WHERE name = 'Jennifer Lawrence' AND people.id = stars.person_id AND stars.movie_id = movies.id AND title IN (SELECT title FROM people, stars, movies WHERE name = 'Bradley Cooper' AND people.id = stars.person_id AND stars.movie_id = movies.id);

--13
SELECT name FROM people, stars WHERE people.id = stars.person_id AND name != 'Kevin Bacon' AND movie_id IN (SELECT movie_id FROM people, stars WHERE name = 'Kevin Bacon' AND birth = 1958 AND stars.person_id = people.id);