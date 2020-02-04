use GamesRental;

create table version(version int);
insert into version values (0);
create table versionLog(id int primary key identity(1, 1), oldVersion int, newVersion int, changeTime datetime);