use GamesRental;

-- a. 2 queries with the union operation; use UNION [ALL] and OR;

-- show all prople involved in the rental process (be it managers or employees)
select e.name
from employees e
union
select m.name
from managers m;

-- get first 10 Simulation or Sports games in alphabetical order
select top 10 g.name, g.genre
from games g
where g.genre = 'Simulation' or g.genre = 'Sports'
order by g.name;

-- b. 2 queries with the intersection operation; use INTERSECT and IN;

-- get all client IDs who were served by both employee 3 and employee 37
select r.clientID
from rentals r
where employeeID = 3
intersect
select r2.clientID
from rentals r2
where employeeID = 37;

-- get all games IDs which are both on PS3 PAL and Xbox One PAL
select i.gameID
from isOnPlatform i
where i.platformID = 5 and i.gameID in (select i2.gameID from isOnPlatform i2 where i2.platformID = 17)

-- c. 2 queries with the difference operation; use EXCEPT and NOT IN;

-- get all game IDs which are composed by Gee Song but not by Michel Song
select i.gameID
from isComposed i
where i.composerID = 2
except
select i2.gameID
from isComposed i2
where i2.composerID = 17

-- get first 25% of all employees who have a contract for
-- more than 5 months
-- but less than 24 months
-- they passed the trial period but they are not considered veterans
select top 25 percent e.name, e.contractDuration
from employees e
where e.contractDuration > 3
	  and e.name not in (select e2.name from employees e2 where e2.contractDuration >= 24)
order by e.contractDuration;
	  
-- d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN; 
-- one query will join at least 3 tables, 
-- while another one will join at least two many-to-many relationships;
	  
-- select all the games rental information involving the employee who authorized the rental
-- and the office where the rental was authorized
-- including games which were not rented AT ALL
select g.name, t1.*
from games g left join (select r.gameID, r.clientID, r.rentalDate, r.dueDate, t.*
	                     from rentals r inner join
	                                    (select e.id as employeeID, e.name as employeeName, o.id as officeID, o.officeAddress 
	                                     from employees e inner join offices o on e.officeID = o.id) t 
										 on r.employeeID = t.employeeID) t1 on g.id = t1.gameID;

-- select all the games rented by the clients who have their phone number ending in "742" or "168"
-- along their programmers

select name as programmerName, t3.*
from programmers p inner join (select ip.programmerID, t2.*
							 from isProgrammed ip inner join (select g.name as gameName, t1.*
															 from games g inner join (select r.gameID, t.* from rentals r inner join (select c.id as clientID, c.name as clientName, c.phoneNumber
																						     										  from clients c
																																	  where c.phoneNumber like '%742' or c.phoneNumber like '%168') t
																														  on t.clientID = r.clientID) t1
																		  on t1.gameID = g.id) t2 on ip.gameID = t2.gameID) t3 on p.id = t3.programmerID;

-- select all the games rented by the clients on 'Socului' Street
-- along their composers

select name as composerName, composerSalary = rating * 2 + 33.1, t3.*
from composers c right join (select ic.composerID, t2.*
							 from isComposed ic inner join (select g.name as gameName, t1.*
															 from games g inner join (select r.gameID, t.* from rentals r inner join (select c.id as clientID, c.name as clientName, c.phoneNumber
																						     										  from clients c
																																	  where c.address like 'Socului%') t
																														  on t.clientID = r.clientID) t1
																		  on t1.gameID = g.id) t2 on ic.gameID = t2.gameID) t3 on c.id = t3.composerID;

-- select all the programmers and all the games, regardless they worked at a game or not
select *
from (games g full join isProgrammed ip on g.id = ip.gameID) full join programmers p on programmerID = p.id;

-- e. 2 queries using the IN operator to introduce a subquery in the WHERE clause; 
-- in at least one query, the subquery should include a subquery in its own WHERE clause;

-- get all rentals for the clients which live on Sperantei street
-- each rental has an importance based on the duration of the rental

select r.*, rentalImportance = datediff(day, r.rentalDate, r.dueDate) * 0.25 + 7.21
from rentals r
where r.clientID in (select id
					 from clients c
					 where c.address like 'Sperantei%');

-- select all the game names which are published on PSVita PAL(13) and PC x64(20)

select g.name
from games g
where g.id in (select iop.gameID from isOnPlatform iop where iop.platformID = 13 and iop.gameID in (select gameID
																									from isOnPlatform
				
																					where platformID = 20));
																					
-- f. 2 queries using the EXISTS operator to introduce a subquery in the WHERE clause;

-- select all rentals which involve a game whose publisher made a profit of <= $100 mil.

select t.*
from (select r.*, g.publisherID from rentals r inner join games g on r.gameID = g.id) t
where exists (select *
			  from publishers p
			  where t.publisherID = p.id and p.revenue > 100);
			  
-- select all rentals which involve employees which have a contract duration of more than 3 years
-- they will be selected for a special bonus

select r.*, contractDuration * 150 + (contractDuration / 10) as 'specialBonus (in RON)'
from (rentals r inner join employees e2 on r.employeeID = e2.id)
where exists (select *
			  from employees e
			  where r.employeeID = e.id and e.contractDuration > 36);
			  
-- g. 2 queries with a subquery in the FROM clause;

-- get all programming languages known by the programmers

select distinct t.* 
from (select programmingLanguage from programmers) t;

-- get all offices whose managers' name are 'Scott'

select *
from offices o inner join (select m.* from managers m where m.name like '%Master%') t on o.managerID = t.id;

-- h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause;
-- 2 of the latter will also have a subquery in the HAVING clause;
-- use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

-- get all architecture of the available games

select architecture
from (select iop.platformID from games g inner join isOnPlatform iop on g.id = iop.gameID) t inner join platforms p on p.id = t.platformID
group by architecture;

-- find the year (after 2000) when the latest game was published for each genre with at least two such games
select g.genre as gameGenre, max(g.yearOfRelease) as maxYear 
from games g
where g.yearOfRelease >= 2000
group by g.genre
having count(*) > 1;

-- for each genre of a rented game, find the average revenue of the publishers which published at least 13 games of that genre

select t1.genre, avg(t1.revenue) as averageRevenue
from (select t.*, p.revenue
	  from (select r.gameID, g.genre, g.publisherID from rentals r inner join games g on r.gameID = g.id) t inner join publishers p on t.publisherID = p.id) t1
group by t1.genre
having 12 < (select count(*) from (publishers p1 inner join games g1 on p1.id = g1.publisherID) where genre = t1.genre);

-- find all the games which have the largest number of programmers

select g.*, t1.maxNumberOfProgrammers
from games g inner join (select ip.gameID, count(*) maxNumberOfProgrammers
						 from isProgrammed ip
						 group by ip.gameID
						 having count(*) = (select max(numberOfProgrammers)
											from (select count(*) numberOfProgrammers
												  from isProgrammed ip2
												  group by ip2.gameID) t) ) t1 on g.id = t1.gameID;

-- i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause;
-- 2 of them should be rewritten with aggregation operators
-- while the other 2 should also be expressed with [NOT] IN.

-- Find the games which due date is after some Horror game

select distinct r.gameID
from rentals r
where r.dueDate > any (select dueDate from (rentals r2 inner join games g on r2.gameID = g.id) where genre = 'Horror');

select distinct r.gameID
from rentals r
where r.dueDate > (select min(dueDate) from (rentals r2 inner join games g on r2.gameID = g.id) where genre = 'Horror');

-- Find all composers who composed for Magical games

select c.name
from composers c
where c.id = any (select composerID
				  from (isComposed ic inner join games g on ic.gameID = g.id)
				  where genre = 'Magical');

select c.name
from composers c
where c.id in (select composerID
			   from (isComposed ic inner join games g on ic.gameID = g.id)
			   where genre = 'Magical');

-- Find all the Mystery games which were published later than all Magical games

select g.name, g.genre, g.yearOfRelease
from games g
where g.genre = 'Mystery' and g.yearOfRelease > all (select g2.yearOfRelease from games g2 where g2.genre = 'Magical');

select g.name, g.genre, g.yearOfRelease
from games g
where g.genre = 'Mystery' and g.yearOfRelease > (select max(g2.yearOfRelease) from games g2 where g2.genre = 'Magical');

-- Find all the games which weren't rented (at all)
-- so they can be more popularized

select g.*
from games g
where g.id <> all (select r.gameID from rentals r);

select g.*
from games g
where g.id not in (select r.gameID from rentals r);