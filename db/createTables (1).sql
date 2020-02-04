use GamesRental;

create table publishers
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	revenue float
);

create table games
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	yearOfRelease int,
	genre nvarchar(20),
	publisherID int foreign key references publishers(id) on delete cascade on update cascade
);

create table managers
(
	id int identity (1, 1),
	name nvarchar(50),
	phoneNumber nvarchar(10) not null,
	constraint PK_Managers primary key (id)
);

create table offices
(
	id int primary key identity (1, 1),
	officeAddress nvarchar(75),
	managerID int foreign key references managers(id) on delete cascade on update cascade
);

create table employees
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	contractDuration int,
	officeID int foreign key references offices(id) on delete cascade on update cascade
);

create table platforms
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	architecture nvarchar(20)
);

create table programmers
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	programmingLanguage nvarchar(20)
);

create table clients
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	phoneNumber nvarchar(10),
	address nvarchar(100)
);

create table composers
(
	id int primary key identity (1, 1),
	name nvarchar(50),
	rating int
);

create table isOnPlatform
(
	gameID int,
	platformID int,
	primary key (gameID, platformID),
	foreign key (gameID) references games(id) on delete cascade on update cascade,
	foreign key (platformID) references platforms(id) on delete cascade on update cascade
);

create table isProgrammed
(
	gameID int,
	programmerID int,
	primary key (gameID, programmerID),
	foreign key (gameID) references games(id) on delete cascade on update cascade,
	foreign key (programmerID) references programmers(id) on delete cascade on update cascade
);

create table isComposed
(
	gameID int,
	composerID int,
	primary key (gameID, composerID),
	foreign key (gameID) references games(id) on delete cascade on update cascade,
	foreign key (composerID) references composers(id) on delete cascade on update cascade
);

create table rentals
(
	gameID int,
	clientID int,
	rentalDate date,
	dueDate date,
	employeeID int,
	foreign key (gameID) references games(id) on delete cascade on update cascade,
	foreign key (clientID) references clients(id) on delete cascade on update cascade,
	foreign key (employeeID) references employees(id) on delete cascade on update cascade,
	constraint PK_Rentals primary key (gameID, clientID, rentalDate, dueDate, employeeID)
);