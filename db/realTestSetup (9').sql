use GamesRental;

go
create view view_getAllGames
as
	select *
	from games;
go

create view view_getAllGamesWithProgrammers
as
	select t.name as GameName, t.yearOfRelease as GameYOR, t.genre as GameGenre, p.name
	from (select * from games g inner join isProgrammed ip on g.id = ip.gameID) t inner join programmers p on t.programmerID = p.id
go

create view view_getAllActivePublishers
as
	select p.name
	from games g inner join publishers p on g.publisherID = p.id
	group by p.name
go

go
alter proc usp_deleteAll @tableName nvarchar(50)
as
	declare @query varchar(500)
	set @query = 'delete from ' + @tableName
	exec(@query)
go

go
alter function uf_mySplitString (@stringToSplit nvarchar(MAX), @delim nvarchar(10))
returns
	@returnList TABLE ([Name] [nvarchar] (500))
as
begin

	declare @name nvarchar(255)
	declare @pos int

	while CHARINDEX(@delim, @stringToSplit) > 0
	begin
		select @pos  = CHARINDEX(@delim, @stringToSplit)  
		select @name = SUBSTRING(@stringToSplit, 1, @pos-1)

		insert into @returnList 
		select @name

		select @stringToSplit = SUBSTRING(@stringToSplit, @pos + 1, LEN(@stringToSplit) - @pos)
	end

	if @stringToSplit = ''
	begin
		return
	end
	insert into @returnList
	select @stringToSplit

	return
end
go

---------------------------- CREATE TEST PHASE ----------------------------

go
alter proc usp_checkTables @tablesString nvarchar(500)
as
	-- get all table names into a table --
	declare @userTables table(Name nvarchar(500))
	insert into @userTables
	select * from uf_mySplitString(@tablesString, ',')
	-- get all table names into a table --

	declare @tableName nvarchar(100)
	declare @counter int
	declare @validTest bit
	set @validTest = 0

	-- check the existence of the provided tables in the database --
	declare TablesCursor cursor for
		select Name
		from @userTables
	open TablesCursor
	fetch next from TablesCursor into @tableName
	while @@FETCH_STATUS = 0
	begin
		set @counter = (select count(*) from sys.tables where name = @tableName)
		if @counter <> 0
			set @validTest = 1
		fetch next from TablesCursor into @tableName
	end
	close TablesCursor
	deallocate TablesCursor
	-- check the existence of the provided tables in the database --

	if @validTest = 0
	begin
		raiserror('One or more provided tables do not exist in the database', 16, 1)
		return
	end

	-- add all tables to Tables --
	insert into Tables
	select distinct ut.Name from @userTables ut
	where ((select count(*)
	       from Tables t
		   where t.Name = ut.Name) = 0)
	-- add all tables to Tables --
go

go
alter proc usp_checkViews @viewsString nvarchar(500)
as
	-- get all views names into a table --
	declare @userViews table(Name nvarchar(500))
	insert into @userViews
	select * from uf_mySplitString(@viewsString, ',')
	-- get all views names into a table --

	declare @viewName nvarchar(100)
	declare @counter int

	-- check the existence of the provided views in the database --
	declare ViewsCursor cursor for
		select Name
		from @userViews
	open ViewsCursor
	fetch next from ViewsCursor into @viewName
	while @@FETCH_STATUS = 0
	begin
		set @counter = (select count(*) from sys.views where name = @viewName)
		if @counter = 0
		begin
			raiserror('One or more provided views do not exist in the database', 16, 1)
			return
		end
		fetch next from ViewsCursor into @viewName
	end
	close ViewsCursor
	deallocate ViewsCursor
	-- check the existence of the provided views in the database --

	-- add all views to Views --
	insert into Views
	select distinct uv.Name from @userViews uv
	where ((select count(*)
	       from Views v
		   where v.Name = uv.Name) = 0)
	-- add all views to Tables --
go

go
alter proc usp_registerTest @testName nvarchar(100), @id int output
as
	declare @cnt int
	select @cnt = count(*)
	from Tests t
	where t.Name = @testName

	-- check if the test isn't already registered
	if @cnt <> 0
	begin
		raiserror('Test already set', 16, 1)
		return
	end

	insert into Tests values (@testName)
	select @id = t.TestID
	from Tests t
	where t.Name = @testName
go

go
alter proc usp_registerTables @testID int, @tables nvarchar(500), @numberOfRows int
as
	declare @userTables table(Name nvarchar(500))
	insert into @userTables
	select * from uf_mySplitString(@tables, ',')
	-- get all table names into a table --

	declare @tableName nvarchar(100)
	declare @counter int
	declare @tableID int
	declare @position int
	declare @duplicatesCounter int
	set @position = 1

	declare TablesCursor cursor for
		select Name
		from @userTables
	open TablesCursor
	fetch next from TablesCursor into @tableName
	while @@FETCH_STATUS = 0
	begin
		-- get the table ID
		select @tableID = t.TableID
		from Tables t
		where t.Name = @tableName

		select @duplicatesCounter = count(*)
		from TestTables tt
		where tt.TestID = @testID and tt.TableID = @tableID and tt.NoOfRows = @numberOfRows

		if @duplicatesCounter = 0
		begin
			insert into TestTables
			values (@testID, @tableID, @numberOfRows, @position)
		end

		set @position = @position + 1
		fetch next from TablesCursor into @tableName
	end
	close TablesCursor
	deallocate TablesCursor
go

go
alter proc usp_registerViews @testID int, @views nvarchar(500)
as
	-- get all views names into a table --
	declare @userViews table(Name nvarchar(500))
	insert into @userViews
	select * from uf_mySplitString(@views, ',')
	-- get all views names into a table --

	declare @viewName nvarchar(100)
	declare @viewID int
	declare @duplicatesCounter int

	-- check the existence of the provided views in the database --
	declare ViewsCursor cursor for
		select Name
		from @userViews
	open ViewsCursor
	fetch next from ViewsCursor into @viewName
	while @@FETCH_STATUS = 0
	begin
		select @viewID = v.ViewID
		from Views v
		where v.Name = @viewName

		select @duplicatesCounter = count(*)
		from TestViews tv
		where tv.TestID = @testID and tv.ViewID = @viewID

		if @duplicatesCounter = 0
		begin
			insert into TestViews
			values (@testID, @viewID)
		end
		fetch next from ViewsCursor into @viewName
	end
	close ViewsCursor
	deallocate ViewsCursor
go

go
alter proc usp_createTest @testName nvarchar(100), @tables nvarchar(500), @views nvarchar(500), @numberOfRows int
as
	if (LEN(@tables) = 0 and LEN(@views) = 0)
	begin
		raiserror('Neither tables or views provided', 16, 1)
		return
	end

	-- check if the tables are valid tables in the database and insert them in Tables --
	exec usp_checkTables @tables 
	-- check if the tables are valid tables in the database and insert them in Tables --
	if @@error <> 0
	begin
		return
	end
	-- check if the views are valid views in the database and insert them in Views --
	exec usp_checkViews @views
	-- check if the views are valid views in the database and insert them in Views --
	if @@error <> 0
	begin
		return
	end

	-- from now on, the test is valid and it can be registered
	declare @testID int = 0
	exec usp_registerTest @testName = @testName, @id = @testID output
	if @@error <> 0
	begin
		return
	end

	-- insert tables in TestTables (now we have the testID)
	exec usp_registerTables @testID, @tables, @numberOfRows
	if @@error <> 0
	begin
		return
	end
	-- insert views in TestViews (now we have the testID)
	exec usp_registerViews @testID, @views
	if @@error <> 0
	begin
		return
	end
go

---------------------------- CREATE TEST PHASE ----------------------------

----------------------------- RUN TEST PHASE -----------------------------
go
create proc usp_runDeleteTablesTest @testID int, @testRunID int
as
	declare @tableName nvarchar(200)
	declare @tableID int
	declare @start datetime
	declare @stop datetime
	declare @query nvarchar(500)
	declare @counter int
	declare @numberOfRows int

	select @numberOfRows = tt.NoOfRows
	from TestTables tt
	where tt.TestID = @testID
	group by tt.NoOfRows

	declare TablesCursor cursor for
		select t.Name
		from Tables t inner join TestTables tt on tt.TestID = @testID
		order by tt.Position desc
	open TablesCursor
	fetch next from TablesCursor into @tableName
	while @@FETCH_STATUS = 0
	begin
		exec usp_deleteAll @tableName
		fetch next from TablesCursor into @tableName
	end
	close TablesCursor
	deallocate TablesCursor
go

go
alter proc usp_insertRow @tableName nvarchar(100)
as
	declare @columnName nvarchar(50)
	declare @tableObjectID int
	declare @tableFKID int
	declare @isIdentity bit
	declare @columnType nvarchar(50)
	declare @query nvarchar(500)
	declare @skippedFirst bit
	declare @refObjectID int
	declare @refColumnID int
	declare @refTableName nvarchar(50)
	declare @refColumnName nvarchar(50)
	declare @randomNumber float
	declare @randomIntNumber int
	declare @randomFKID int
	declare @randomFKQuery nvarchar(100)

	select @tableObjectID = st.object_id
	from sys.tables st
	where st.name = @tableName

	set @query = 'insert into ' + @tableName + ' values('
	set @skippedFirst = 0
	declare ColumnsCursor cursor for
		select sc.name, sc.is_identity, st.name, sfk.referenced_object_id, sfk.referenced_column_id
		from (sys.columns sc inner join sys.types st on sc.system_type_id = st.system_type_id)
			 left join sys.foreign_key_columns sfk on (sfk.parent_object_id = @tableObjectID and sc.column_id = sfk.parent_column_id)
		where sc.object_id = @tableObjectID and st.name <> 'sysname'
		order by sc.column_id
	open ColumnsCursor
	fetch next from ColumnsCursor into @columnName, @isIdentity, @columnType, @refObjectID, @refColumnID
	while @@FETCH_STATUS = 0
	begin
		if @isIdentity = 0
		begin
			if @skippedFirst = 0
				set @skippedFirst = 1
			else
				set @query = @query + ','

			if @refObjectID is NULL
			begin
				if @columnType = 'int'
				begin
					set @randomNumber = rand() * 5000
					select @randomIntNumber = round(@randomNumber, 0)
					set @query = @query + cast(@randomIntNumber as nvarchar)
				end
				else if @columnType = 'nvarchar'
				begin
					set @randomNumber = rand() * 5000
					select @randomIntNumber = round(@randomNumber, 0)
					set @query = @query + '''random' + cast(@randomIntNumber as nvarchar) + ''''
				end
				else if @columnType = 'float'
				begin
					set @randomNumber = rand() * 5000
					set @query = @query + cast(@randomNumber as nvarchar)
				end
			end
			else
			begin
				select @refTableName = st.name, @refColumnName = sc.name
				from sys.tables st inner join sys.columns sc on st.object_id = sc.object_id
				where st.object_id = @refObjectID and sc.column_id = @refColumnID

				create table #number (id int)
				set @randomFKQuery = 'insert into #number select top 1 ' + @refColumnName + ' from ' + @refTableName + ' order by newid()'
				exec(@randomFKQuery)
				set @randomFKID = (select top 1 id from #number)
				drop table #number
				set @query = @query + cast(@randomFKID as nvarchar)
			end
		end
		fetch next from ColumnsCursor into @columnName, @isIdentity, @columnType, @refObjectID, @refColumnID
	end
	close ColumnsCursor
	deallocate ColumnsCursor
	set @query = @query + ')'
	exec (@query)
go

select st.object_id, st.name, sc.*, sty.name from (sys.tables st inner join sys.columns sc on st.object_id = sc.object_id) inner join sys.types sty on sc.system_type_id = sty.system_type_id
select * from sys.types
select * from sys.tables where object_id = 1325247776
select * from sys.columns where object_id = 1725249201
select * from sys.foreign_key_columns
select st.name, sc.name
from sys.tables st inner join sys.columns sc on st.object_id = sc.object_id
where st.object_id = 1725249201 and sc.column_id = 1

declare @x int
set @x = 
(select top 1 sfk.referenced_object_id
from (sys.columns sc inner join sys.types st on sc.system_type_id = st.system_type_id)
     left join sys.foreign_key_columns sfk on (sfk.parent_object_id = 1357247890 and sc.column_id = sfk.parent_column_id)
where sc.object_id = 1357247890 and st.name <> 'sysname'
order by sc.column_id)

go
alter proc usp_runInsertTablesTest @testID int, @testRunID int
as
	declare @tableName nvarchar(200)
	declare @tableID int
	declare @start datetime
	declare @stop datetime
	declare @query nvarchar(500)
	declare @counter int
	declare @numberOfRows int

	select @numberOfRows = tt.NoOfRows
	from TestTables tt
	where tt.TestID = @testID
	group by tt.NoOfRows

	print('iterez prin tabele')
	declare TablesCursor cursor for
		select t.Name
		from Tables t inner join TestTables tt on tt.TableID = t.TableID
		where tt.TestID = @testID
		order by tt.Position
	open TablesCursor
	fetch next from TablesCursor into @tableName
	while @@FETCH_STATUS = 0
	begin
		print ('am preluat ' + @tableName)
		set @counter = 1
		set @start = SYSDATETIME()
		while @counter <= @numberOfRows
		begin
			exec usp_insertRow @tableName
			set @counter = @counter + 1
			print(@tableName + ' ' + cast(@counter as nvarchar))
		end
		set @stop = SYSDATETIME()

		select @tableID = t.TableID
		from Tables t
		where t.name = @tableName

		print('trying to insert ' + cast(@testRunID as nvarchar) + ' '
		                          + cast(@tableID as nvarchar) + ' '
								  + cast(@start as nvarchar) + ' '
								  + cast(@stop as nvarchar) + ' ')
		insert into TestRunTables values (@testRunID, @tableID, @start, @stop)
		fetch next from TablesCursor into @tableName
	end
	close TablesCursor
	deallocate TablesCursor
go

go
alter proc usp_runTablesTest @testID int, @testRunID int
as
	print('testrun id ' + cast(@testRunID as nvarchar) + ' test id ' + cast(@testID as nvarchar))
	exec usp_runDeleteTablesTest @testID, @testRunID
	exec usp_runInsertTablesTest @testID, @testRunID
go

go
alter proc usp_runViewsTest @testID int, @testRunID int
as
	declare @viewName nvarchar(200)
	declare @viewID int
	declare @start datetime
	declare @stop datetime
	declare @query nvarchar(500)

	declare ViewsCursor cursor for
		select v.Name
		from Views v inner join TestViews tv on v.ViewID = tv.ViewID
		where tv.TestID = @testID
	open ViewsCursor
	fetch next from ViewsCursor into @viewName
	while @@FETCH_STATUS = 0
	begin
		set @start = SYSDATETIME()
		set @query = 'select * from ' + @viewName
		exec(@query)
		set @stop = SYSDATETIME()

		select @viewID = v.ViewID
		from Views v
		where v.Name = @viewName

		insert into TestRunViews
		values (@testRunID, @viewID, @start, @stop)
		fetch next from ViewsCursor into @viewName
	end
	close ViewsCursor
	deallocate ViewsCursor
go

go
alter proc usp_runTest @testName nvarchar(100)
as
	if (select count(*) from Tests t where t.Name = @testName) = 0
	begin
		raiserror('The test does not exist', 16, 1)
		return
	end

	declare @testID int
	declare @testRunID int
	declare @startBigTest datetime
	declare @stopBigTest datetime

	select @testID = t.TestID
	from Tests t
	where t.Name = @testName

	insert into TestRuns(Description) values('Test run of ' + @testName)
	set @testRunID = @@IDENTITY

	set @startBigTest = SYSDATETIME()
	exec usp_runTablesTest @testID, @testRunID
	exec usp_runViewsTest @testID, @testRunID
	set @stopBigTest = SYSDATETIME()

	update TestRuns
	set StartAt = @startBigTest, EndAt = @stopBigTest
	where TestRunID = @testRunID
go

----------------------------- RUN TEST PHASE -----------------------------

exec usp_createTest 'test_1000', 'publishers,games,programmers,isProgrammed',
								'view_getAllActivePublishers,view_getAllGames,view_getAllGamesWithProgrammers',
								1000

exec usp_createTest 'test_50_2', 'publishers,publishers,programmers,isProgrammed',
								'view_getAllGames,view_getAllGames,view_getAllGamesWithProgrammers',
								50

exec usp_runTest 'test_50'

select * from Tests
select * from Tables
select * from TestTables
select * from Views
select * from TestViews
select * from TestRuns
select * from TestRunTables
select * from TestRunViews
select * from publishers
select * from games
select * from programmers
select * from isProgrammed