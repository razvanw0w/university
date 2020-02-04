use GamesRental;

if OBJECT_ID('TC', 'U') is not null
	drop table TC
if OBJECT_ID('TA', 'U') is not null
	drop table TA
if OBJECT_ID('TB', 'U') is not null
	drop table TB

create table TA (
	aid int primary key identity(1, 1),
	a2 int unique,
	a3 int
)

create table TB (
	bid int primary key identity(1, 1),
	b2 int,
	b3 int
)

create table TC (
	cid int primary key identity(1, 1),
	aid int references TA(aid),
	bid int references TB(bid)
)

exec sp_helpindex TA
exec sp_helpindex TB
exec sp_helpindex TC

-- a)
select aid from TA where TA.a3 = 1 -- clustered index scan
select aid from TA where TA.aid between 1 and 3 -- clustered index seek
select a2 from TA -- nonclustered index scan
select aid from TA where Ta.a2 > 1 -- nonclustered index seek
select * from TA where TA.a2 = 3 -- nonclustered index seek (on a2) + key lookup (for the rest of the columns)

-- b)
if exists(select * from sys.indexes where name = 'idx_nc_b2')
	drop index idx_nc_b2 on TB
select b2 from TB where b2 between 1 and 10 -- cl. index scan (PK TB) - 0.033238
create nonclustered index idx_nc_b2 on TB(b2)
select b2 from TB where b2 between 1 and 10 -- ncl index seek (idx_nc_b2) - 0.0032831

-- c)
go
alter view view_tatbtc
as
	select TC.cid, TC.aid
	from TC inner join TA on TC.aid = TA.aid
	where TC.aid between 2 and 10
go

-- c)
select * from view_tatbtc -- before indexing
                          -- cl. index scan TC (PK TC) - 0.003326
						  -- cl. index seek TA (PK TA) - 0.0042317

if exists(select * from sys.indexes i inner join sys.objects o on i.object_id = o.object_id where i.name = 'idx_nc_aid' and o.name = 'TC')
	drop index idx_nc_aid on TC
create nonclustered index idx_nc_aid on TC(aid)

select * from view_tatbtc -- after indexing
						  -- cl. index seek TA (PK TA) - 0.0042317
						  -- ncl. index seek TC (idx_nc_aid) - 0.0032897

exec sp_helpindex TA
exec sp_helpindex TB
exec sp_helpindex TC