use GamesRental;

go
alter proc usp_version1
as
	alter table games
	alter column yearOfRelease float
go

alter proc usp_version1undo
as
	alter table games
	alter column yearOfRelease int
go

alter proc usp_version2
as
	alter table publishers
	add ceo nvarchar(40);
go

alter proc usp_version2undo
as
	alter table publishers
	drop column ceo;
go

alter proc usp_version3
as
	alter table clients
	add constraint DEF_ClientAddress default 'Not located' for address;
go

alter proc usp_version3undo
as
	alter table clients
	drop constraint DEF_ClientAddress
go

alter proc usp_version4
as
	alter table rentals
	drop constraint PK_Rentals;
go

alter proc usp_version4undo
as
	alter table rentals
	add constraint PK_Rentals primary key (gameID, clientID, rentalDate, dueDate, employeeID);
go

alter proc usp_version5
as
	alter table composers
	add constraint CK_Composers unique (name);
go

alter proc usp_version5undo
as
	alter table composers
	drop constraint CK_Composers;
go

alter proc usp_version6
as
	alter table rentals
	add managerID int;
	alter table rentals
	add constraint FK_RentalsManager foreign key (managerID) references managers(id);
go

alter proc usp_version6undo
as
	alter table rentals
	drop constraint FK_RentalsManager;
	alter table rentals
	drop column managerID;
go

alter proc usp_version7
as
	create table markets (id int primary key identity(1, 1),
						  continent nvarchar(15),
						  size int);
go

alter proc usp_version7undo
as
	drop table markets;
go

alter proc usp_getCurrentVersion @vr smallint output
as
	select @vr = ver.version
	from version ver;
go

alter proc usp_goToNextVersion @v smallint
as
	if @v = 0
		exec usp_version1;
	else if @v = 1
		exec usp_version2;
	else if @v = 2
		exec usp_version3;
	else if @v = 3
		exec usp_version4;
	else if @v = 4
		exec usp_version5;
	else if @v = 5
		exec usp_version6;
	else if @v = 6
		exec usp_version7;
go

alter proc usp_goToPrevVersion @v smallint
as
	if @v = 1
		exec usp_version1undo;
	else if @v = 2
		exec usp_version2undo;
	else if @v = 3
		exec usp_version3undo;
	else if @v = 4
		exec usp_version4undo;
	else if @v = 5
		exec usp_version5undo;
	else if @v = 6
		exec usp_version6undo;
	else if @v = 7
		exec usp_version7undo;
go

alter proc usp_updateCurrentVersion @v int
as
	update version
	set version = @v;
go

alter proc usp_updateLog @old smallint, @new smallint
as
	insert into versionLog
	values (@old, @new, SYSDATETIME());
go
	
alter proc usp_changeVersion @targetVersion smallint
as
	declare @currentVersion smallint = 1;
	exec usp_getCurrentVersion @vr = @currentVersion output
	declare @source smallint = @currentVersion;
	if @source < @targetVersion
		while @source < @targetVersion
		begin
			exec usp_goToNextVersion @v = @source;
			set @source = @source + 1
		end
	else if @source > @targetVersion
		while @source > @targetVersion
		begin
			exec usp_goToPrevVersion @v = @source;
			set @source = @source - 1
		end
	exec usp_updateCurrentVersion @v = @targetVersion
	exec usp_updateLog @old = @currentVersion, @new = @targetVersion
go

exec usp_changeVersion @targetVersion = 0;
select * from version;
select * from versionLog;
--delete from versionLog;
--update version set version = 4;